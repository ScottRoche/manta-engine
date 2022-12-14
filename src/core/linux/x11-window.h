// Copyright 2022 Scott Roche
#pragma once

#include "../window.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <GL/glx.h>

typedef Window XWindow;

namespace Manta
{
	class X11Window : public Window
	{
	public:
		X11Window(const WindowProps& props);
		virtual ~X11Window() = default;

		void Update() override;

		inline void SetEventCallback(const EventCallbackFn& callback) override
		{
			m_Data.EventCallback = callback;
		}

	private:
		void Init(const WindowProps& props);
		void DeInit();
		void PollEvents();

		void CreateContext();

	private:
		struct WindowData
		{
			uint32_t Width;
			uint32_t Height;

			const char* Title;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

		Display* m_Display;
		int m_Screen;
		XWindow m_Window;
		GLXContext m_GLContext;

		Atom m_WMDeleteWindow;
	};
}