// Copyright 2022 Scott Roche
#pragma once

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
	};
}