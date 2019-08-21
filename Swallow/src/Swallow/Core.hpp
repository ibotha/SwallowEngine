#pragma once

#include <memory>
#include <sstream>
#include <string>

#ifdef SW_DEBUG
	#define SW_ENABLE_ASSERTS
#endif

#ifdef SW_PLATFORM_WINDOWS
#else
	#ifdef SW_PLATFORM_MACOSX
	#else
		#error Swallow Only Supports Windows and Mac!
	#endif // SW_PLATFORM_MACOSX
#endif // SW_PLATFORM_WINDOWS

#ifdef SW_ENABLE_ASSERTS
	#ifdef SW_PLATFORM_WINDOWS
		#define SW_ASSERT(x, ...) {if (!(x)) {SW_ERROR(__VA_ARGS__); __debugbreak(); } }
		#define SW_CORE_ASSERT(x, ...) {if (!(x)) {SW_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }
	#else
		#ifdef SW_PLATFORM_MACOSX
			#define SW_ASSERT(x, ...) {if (!(x)) {SW_ERROR(__VA_ARGS__); exit(0); } }
			#define SW_CORE_ASSERT(x, ...) {if (!(x)) {SW_CORE_ERROR(__VA_ARGS__); exit(0); } }
		#else
			#error Swallow Only Supports Windows and Mac!
		#endif // SW_PLATFORM_MACOSX
	#endif // SW_PLATFORM_WINDOWS
#else
	#define SW_ASSERT(x, ...)
	#define SW_CORE_ASSERT(x, ...)
#endif // SW_ENABLE_ASSERTS


#define BIT(x) (1 << x)

namespace Swallow {

	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T>
	using Ref = std::shared_ptr<T>;

}

