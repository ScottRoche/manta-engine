// Copyright 2022 Scott Roche
#include "x11-window.h"

#include "../log.h"

#include "GL/gl.h"

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, bool, const int*);

namespace Manta
{
	X11Window::X11Window(const WindowProps& props)
	{
		Init(props);
		CreateContext();

		int glMajor, glMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &glMajor);
		glGetIntegerv(GL_MINOR_VERSION, &glMinor);

		LOG_DEBUG("OpenGL context version: %d.%d", glMajor, glMinor);
		LOG_DEBUG("Vendor: %s", glGetString(GL_VENDOR));
		LOG_DEBUG("Renderer: %s", glGetString(GL_RENDERER));
	}

	void X11Window::Update()
	{
		PollEvents();
	}

	void X11Window::Init(const WindowProps& props)
	{
		unsigned long black, white;

		m_Display = XOpenDisplay(nullptr);
		m_Screen = DefaultScreen(m_Display);
		black = BlackPixel(m_Display, m_Screen);
		white = WhitePixel(m_Display, m_Screen);

		m_Window = XCreateSimpleWindow(m_Display,
		                               DefaultRootWindow(m_Display),
		                               0, 0,
		                               props.Width, props.Height,
		                               5,
		                               white,
		                               black);

		XSetStandardProperties(m_Display,
		                       m_Window,
		                       props.Title,
		                       props.Title,
		                       None,
		                       nullptr,
		                       0,
		                       nullptr);
		
		XSelectInput(m_Display,
		             m_Window,
		             ExposureMask | ButtonPressMask | KeyPressMask);

		XClearWindow(m_Display, m_Window);
		XMapRaised(m_Display, m_Window);

		m_WMDeleteWindow = XInternAtom(m_Display, "WM_DELETE_WINDOW", False);
		XSetWMProtocols(m_Display, m_Window, &m_WMDeleteWindow, 1);

		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;
	}

	void X11Window::DeInit()
	{
		XDestroyWindow(m_Display, m_Window);
		XCloseDisplay(m_Display);
	}

	void X11Window::PollEvents()
	{
		XEvent event;
	
		XNextEvent(m_Display, &event);

		switch(event.type)
		{
			case ClientMessage:
				if (event.xclient.data.l[0] == m_WMDeleteWindow)
				{
					LOG_DEBUG("Closing window");
					if (m_Data.EventCallback)
					{
						m_Data.EventCallback();
					}
					DeInit();
				}
				break;
		}
	}

	void X11Window::CreateContext()
	{
		static int visualAttribs[] = {
			GLX_RENDER_TYPE, GLX_RGBA_BIT,
			GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_DOUBLEBUFFER, true,
			GLX_RED_SIZE, 1,
			GLX_GREEN_SIZE, 1,
			GLX_BLUE_SIZE, 1,
			None
		};

		int framebufferConfigCount = 0;
		GLXFBConfig* framebufferConfigs = nullptr;

		framebufferConfigs = glXChooseFBConfig(m_Display,
		                                       m_Screen,
		                                       visualAttribs,
		                                       &framebufferConfigCount);
		if (framebufferConfigs == nullptr)
		{
			LOG_ERROR("glXChooseFBConfig() failed");
			return;
		}

		glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
		glXCreateContextAttribsARB =
			(glXCreateContextAttribsARBProc)glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");

		static int contextAttribs[] = {
			GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
			GLX_CONTEXT_MINOR_VERSION_ARB, 6
		};

		m_GLContext = glXCreateContextAttribsARB(m_Display,
		                                         framebufferConfigs[0],
		                                         nullptr,
		                                         true,
		                                         contextAttribs);

		glXMakeCurrent(m_Display, m_Window, m_GLContext);
	}
}