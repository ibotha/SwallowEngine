workspace "Swallow"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Swallow"
	location "Swallow"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SW_PLATFORM_WINDOWS",
			"SW_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "SW_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SW_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SW_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Swallow/vendor/spdlog/include",
		"Swallow/src"
	}

	links
	{
		"Swallow"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SW_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SW_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SW_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SW_DIST"
		optimize "On"