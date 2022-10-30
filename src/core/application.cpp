// Copyright 2022 Scott Roche
#include "application.h"

#include "log.h"

namespace Manta
{
	static bool g_IsRunning = true;

	static void OnWindowClose()
	{
		g_IsRunning = false;
	}

	Application::Application()
	{
		LOG_INFO("---[ Manta Engine ]---");
		window = Window::Create({800, 600, "Manta Engine"});
		window->SetEventCallback(OnWindowClose);
	}

	void Application::Run()
	{
		/** To be filled with the main loop. */
		while(g_IsRunning)
		{
			window->Update();
		}
	}
}