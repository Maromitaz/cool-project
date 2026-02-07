workspace "frontend"
    configurations { "Debug", "Release" }
    platforms { "Win64" }

    targetdir "%{wks.location}/bin/out/%{cfg.buildcfg}/"
    objdir"%{wks.location}/bin/obj/%{cfg.buildcfg}/"

    startproject "frontend"

    architecture "amd64"

project "frontend"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    staticruntime "On"
    
    kind "WindowedApp"
    postbuildcommands { 
        "{COPYDIR} \"%{wks.location}/thirdparty/CEF/copy/*\" \"%{wks.location}/bin/out/%{cfg.buildcfg}/\""
    }
    -- links "stdc++exp"
    links {
        "%{wks.location}/thirdparty/CEF/libs/libcef.lib"
    }

    includedirs {
        "%{wks.location}/thirdparty/CEF"
    }

    files {
        "%{wks.location}/frontend/**.cpp",
        "%{wks.location}/frontend/**.h",
        "%{wks.location}/frontend/**.hpp"
    }

    defines {
        "DEBUG_ASSETS_FOLDER=\"%{wks.location}/frontend/assets\"",

        "RELEASE_ASSETS_FOLDER=\"%{wks.location}/assets\""
    }

    filter "configurations:Debug"
        links {
            "%{wks.location}/thirdparty/CEF/libs/libcef_dll_wrapper_debug.lib"
        }
        runtime "Debug"
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        links {
            "%{wks.location}/thirdparty/CEF/libs/libcef_dll_wrapper_release.lib"
        }
        runtime "Release"
        defines { "NDEBUG" }
        optimize "On"