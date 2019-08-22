

configurations
{
	"Debug",
	"Release",
	"Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directoies relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["Glad"] = "vendor/Glad/include"
IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm/glm"
IncludeDir["stb_image"] = "vendor/stb_image"

group "Dependencies"
	include "Swallow/vendor/GLFW"
	include "Swallow/vendor/Glad"
	include "Swallow/vendor/imgui"
group ""

project "Swallow"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "swpch.hpp"
	pchsource "Swallow/src/swpch.cpp"

	files
	{
		"src/**.hpp",
		"src/**.hpp",
		"src/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/stb_image/**",
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:macosx"
		systemversion "latest"

		defines
		{
			"SW_PLATFORM_MACOSX",
			"GLFW_INCLUDE_NONE"
		}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SW_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "SW_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SW_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SW_DIST"
		runtime "Release"
		optimize "on"