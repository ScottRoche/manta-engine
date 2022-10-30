#include "window.h"

#include "log.h"

#if defined(__linux__)
#include "linux/x11-window.h"
#endif

namespace Manta
{
	std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{
#if defined(__linux__)
		return std::make_unique<X11Window>(props);
#endif
		LOG_FATAL("No window class for current platform!");
		return nullptr;
	}
}