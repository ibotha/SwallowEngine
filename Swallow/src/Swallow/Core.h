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

