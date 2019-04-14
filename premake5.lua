workspace "Swallow"

	startproject "Sandbox"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directoies relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Swallow/vendor/GLFW/include"
IncludeDir["Glad"] = "Swallow/vendor/Glad/include"
IncludeDir["ImGui"] = "Swallow/vendor/imgui"
IncludeDir["glm"] = "Swallow/vendor/glm/glm"

group "Dependencies"
	include "Swallow/vendor/GLFW"
	include "Swallow/vendor/Glad"
	include "Swallow/vendor/imgui"
group ""

project "Swallow"
	staticruntime "Off"
	location "Swallow"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "swpch.h"
	pchsource "Swallow/src/swpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"SW_PLATFORM_WINDOWS",
			"SW_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "SW_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SW_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SW_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	staticruntime "Off"
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
		"Swallow/src",
		"%{IncludeDir.glm}",
	}

	links
	{
		"Swallow"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"SW_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SW_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SW_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SW_DIST"
		runtime "Release"
		optimize "On"