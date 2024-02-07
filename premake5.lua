workspace "Sorting Visualizer"
    configurations { "Debug", "Release" }

project "Sorting Visualizer"
  kind "ConsoleApp"

  language "c++"
  cppdialect "c++17"
  
  files {
    "src/**.cpp",
    "src/**.c",
    "include/**.h"
  }

  includedirs {
    "include/",
    "dependencies/include/",
  }

  libdirs {
    "dependencies/lib/",
  }

  links {
    "SDL2.lib",
    "SDL2main.lib"
  }

  postbuildcommands {
    '{COPY} %{wks.location}/dependencies/lib/**.dll %{cfg.buildtarget.directory}',
  }
