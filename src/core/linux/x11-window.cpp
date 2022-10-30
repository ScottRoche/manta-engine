// Copyright 2022 Scott Roche
#include "x11-window.h"

#include "../log.h"

namespace Manta
{
	X11Window::X11Window(const WindowProps& props)
	{
		Init(props);
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

		m_GraphicsContext = XCreateGC(m_Display, m_Window, 0, 0);
		XSetBackground(m_Display, m_GraphicsContext, black);
		XSetForeground(m_Display, m_GraphicsContext, white);

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
		XFreeGC(m_Display, m_GraphicsContext);
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
}