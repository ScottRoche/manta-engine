// Copyright 2022 Scott Roche
#include "application.h"

#include "log.h"

namespace Manta
{
	Application::Application()
	{
		LOG_INFO("---[ Manta Engine ]---");
		window = new Window();
	}

	void Application::Run()
	{
		/** To be filled with the main loop. */
		while(window != nullptr)
		{
			window->Update();
		}
	}
}