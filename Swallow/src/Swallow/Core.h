#pragma once

#ifdef SW_PLATFORM_WINDOWS
	#ifdef SW_BUILD_DLL
		#define SWALLOW_API __declspec(dllexport)
	#else	
		#define SWALLOW_API __declspec(dllimport)
	#endif // SW_BUILD_DLL
#else
	#error Swallow Only Supports Windows!
#endif // SW_PLATFORM_WINDOWS

#ifdef SW_ENABLE_ASSERTS
	#define SW_ASSERT(x, ...) {if (!(x)) {SW_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak(); } }
	#define SW_CORE_ASSERT(x, ...) {if (!(x)) {SW_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SW_ASSERT(x, ...)
	#define SW_CORE_ASSERT(x, ...)
#endif // SW_ENABLE_ASSERTS


#define BIT(x) (1 << x)

