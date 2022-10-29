// Copyright 2022 Scott Roche

#include "../window.h"
#include "../log.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

/**
 * Dealing with X structs having the same name as classes and variables 
 * was getting annoying.
 */

typedef Display XDisplay;
typedef Window XWindow;

namespace Manta
{
	struct WindowData
	{
		XDisplay* Display;
		int Screen;
		XWindow Window;
		GC GraphicsContext;
	};

	Window::Window()
	{
		unsigned long black, white;
		WindowData data;

		data.Display = XOpenDisplay((char*)0);
		data.Screen = DefaultScreen(data.Display);
		black = BlackPixel(data.Display, data.Screen);
		white = WhitePixel(data.Display, data.Screen);

		data.Window = XCreateSimpleWindow(data.Display,
		                               DefaultRootWindow(data.Display),
		                               0, 0,
		                               800, 600,
		                               5,
		                               white,
		                               black);

		XSetStandardProperties(data.Display,
		                       data.Window,
		                       "Manta Window",
		                       "Manta",
		                       None,
		                       nullptr,
		                       0,
		                       nullptr);
		
		XSelectInput(data.Display,
			data.Window,
			ExposureMask | ButtonPressMask | KeyPressMask);

		data.GraphicsContext = XCreateGC(data.Display, data.Window, 0, 0);
		XSetBackground(data.Display, data.GraphicsContext, black);
		XSetForeground(data.Display, data.GraphicsContext, white);

		XClearWindow(data.Display, data.Window);
		XMapRaised(data.Display, data.Window);

		m_Data = new WindowData(data);
	}

	Window::~Window()
	{
		XFreeGC(((WindowData*)m_Data)->Display, ((WindowData*)m_Data)->GraphicsContext);
		XDestroyWindow(((WindowData*)m_Data)->Display, ((WindowData*)m_Data)->Window);
		XCloseDisplay(((WindowData*)m_Data)->Display);
	}

	void Window::Update()
	{
		XEvent event;
		KeySym key;
		char text[255];
	
		XNextEvent(((WindowData*)m_Data)->Display, &event);
	}
}