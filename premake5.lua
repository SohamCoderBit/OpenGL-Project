workspace "Renderer" -- Name of sln file
    configurations { "Debug", "Release" }

project "OpenGLRenderer" -- Name of project

    kind "ConsoleApp" -- Uses the console
    language "C++"
    location "Renderer" -- location of vcxproj file
    targetdir "RendererBuild" -- .exe files is in bin/(debug or release)/(x86 or x64)/
    --location of source files to include. Here we include All files ending with .h and .cpp
    --in the folder Minimal Example even files in subfolders.

    	files
	{
		"Renderer/src/**.h",
		"Renderer/src/**.cpp"	
    }

    --Include directories
    includedirs {
        "Dependencies/GLFW/include",
        "Dependencies/GLEW/include",
        "Dependencies/glm",
        "Dependencies/stb"
    }

    --libraries and links
        --links (the library files)
        links {
            "glew32s",
            "opengl32",
            "glfw3"
        }

        defines
        {
            "GLEW_STATIC"
        }

            libdirs { 
                "Dependencies/GLFW/lib",
                "Dependencies/GLEW/lib/Release/x64"
            }
    
    --Debug and Release configurations
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    -- filter "configurations:Release"
    --     defines { "NDEBUG" }
    --     optimize "On"