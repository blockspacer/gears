#!lua

-- A solution contains projects, and defines the available configurations
solution "gears"
    configurations { "Debug", "Release" }

    buildoptions { "-std=c++17" }

    -- A project defines one build target
    project "gears"

        kind "ConsoleApp"

        language "C++"

        files { "**.hpp", "**.cpp" }

        pchheader "src/stdafx.hpp"
        pchsource "src/stdafx.cpp"

        includedirs
        {
            "src/",
            "include/",
            "/usr/include/lua5.3"
        }

        links
        {
            --sfml
            "sfml-system",
            "sfml-window",
            "sfml-graphics",
            "sfml-audio",
            "sfml-network",

            --thor
            "thor",

            --tgui
            "tgui",

            --anax
            "anax",

            --lua
            "lua5.3"
        }

        configuration "Debug"
            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            defines { "NDEBUG" }
            flags { "Optimize" }
