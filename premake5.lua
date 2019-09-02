workspace "Sandbox"

startproject "Sandbox"

enginedir = "Swallow/"

include "Swallow"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		enginedir .. "vendor/spdlog/include",
		enginedir .. "src",
		enginedir .. "%{IncludeDir.GLFW}",
		enginedir .. "%{IncludeDir.Glad}",
		enginedir .. "%{IncludeDir.glm}",
		enginedir .. "%{IncludeDir.ImGui}",
		enginedir .. "%{IncludeDir.AssImp}",
		enginedir .. "%{IncludeDir.AssImpBuild}"
	}

	libdirs
	{
		enginedir .. "vendor/AssImp/build/code"
	}

	links
	{
		"Swallow",
		"assimp"
	}

	filter "system:macosx"
        systemversion "latest"
		buildoptions { "-Wall", "-Werror", "-Wextra"}
        defines
        {
            "SW_PLATFORM_MACOSX"
		}
		
		links
		{
			"Cocoa.framework",
			"IOKit.framework",
			"OpenGL.framework",
			"GLUT.framework",
			"CoreVideo.framework",
			"GLFW",
			"Glad",
			"ImGui"
		}

		postbuildcommands { "echo \"cd %{prj.name} && ../bin/" .. outputdir .. "/%{prj.name}/%{prj.name}\" > ../Run.sh" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SW_PLATFORM_WINDOWS"
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
