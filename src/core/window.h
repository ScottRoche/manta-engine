#pragma once
// Copyright 2022 Scott Roche

#include <stdint.h>
#include <memory>
#include <functional>

namespace Manta
{
	using EventCallbackFn = std::function<void()>;

	struct WindowProps
	{
		uint32_t Width;
		uint32_t Height;

		const char* Title;
	};

	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void Update() = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		static std::unique_ptr<Window> Create(const WindowProps& props);
	};
}