// Copyright 2022 Scott Roche
#pragma once

#include "window.h"

namespace Manta
{
	class Application
	{
	public:
		Application();
		~Application() = default;

		/**
		 * @name Run
		 * @brief Main update loop of the application
		 */
		void Run();

	private:
		std::unique_ptr<Window> window;
	};
}