# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Uni\GraficaAvanzada\ProyectoFinal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Uni\GraficaAvanzada\ProyectoFinal\build

# Include any dependencies generated for this target.
include Proyecto/CMakeFiles/Proyecto.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Proyecto/CMakeFiles/Proyecto.dir/compiler_depend.make

# Include the progress variables for this target.
include Proyecto/CMakeFiles/Proyecto.dir/progress.make

# Include the compile flags for this target's objects.
include Proyecto/CMakeFiles/Proyecto.dir/flags.make

Proyecto/CMakeFiles/Proyecto.dir/src/main.cpp.obj: Proyecto/CMakeFiles/Proyecto.dir/flags.make
Proyecto/CMakeFiles/Proyecto.dir/src/main.cpp.obj: Proyecto/CMakeFiles/Proyecto.dir/includes_CXX.rsp
Proyecto/CMakeFiles/Proyecto.dir/src/main.cpp.obj: D:/Uni/GraficaAvanzada/ProyectoFinal/Proyecto/src/main.cpp
Proyecto/CMakeFiles/Proyecto.dir/src/main.cpp.obj: Proyecto/CMakeFiles/Proyecto.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Uni\GraficaAvanzada\ProyectoFinal\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Proyecto/CMakeFiles/Proyecto.dir/src/main.cpp.obj"
	cd /d D:\Uni\GraficaAvanzada\ProyectoFinal\build\Proyecto && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Proyecto/CMakeFiles/Proyecto.dir/src/main.cpp.obj -MF CMakeFiles\Proyecto.dir\src\main.cpp.obj.d -o CMakeFiles\Proyecto.dir\src\main.cpp.obj -c D:\Uni\GraficaAvanzada\ProyectoFinal\Proyecto\src\main.cpp

Proyecto/CMakeFiles/Proyecto.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Proyecto.dir/src/main.cpp.i"
	cd /d D:\Uni\GraficaAvanzada\ProyectoFinal\build\Proyecto && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Uni\GraficaAvanzada\ProyectoFinal\Proyecto\src\main.cpp > CMakeFiles\Proyecto.dir\src\main.cpp.i

Proyecto/CMakeFiles/Proyecto.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Proyecto.dir/src/main.cpp.s"
	cd /d D:\Uni\GraficaAvanzada\ProyectoFinal\build\Proyecto && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Uni\GraficaAvanzada\ProyectoFinal\Proyecto\src\main.cpp -o CMakeFiles\Proyecto.dir\src\main.cpp.s

# Object files for target Proyecto
Proyecto_OBJECTS = \
"CMakeFiles/Proyecto.dir/src/main.cpp.obj"

# External object files for target Proyecto
Proyecto_EXTERNAL_OBJECTS =

D:/Uni/GraficaAvanzada/ProyectoFinal/bin/Proyecto.exe: Proyecto/CMakeFiles/Proyecto.dir/src/main.cpp.obj
D:/Uni/GraficaAvanzada/ProyectoFinal/bin/Proyecto.exe: Proyecto/CMakeFiles/Proyecto.dir/build.make
D:/Uni/GraficaAvanzada/ProyectoFinal/bin/Proyecto.exe: CGALib/libCGALib.dll.a
D:/Uni/GraficaAvanzada/ProyectoFinal/bin/Proyecto.exe: Proyecto/CMakeFiles/Proyecto.dir/linkLibs.rsp
D:/Uni/GraficaAvanzada/ProyectoFinal/bin/Proyecto.exe: Proyecto/CMakeFiles/Proyecto.dir/objects1.rsp
D:/Uni/GraficaAvanzada/ProyectoFinal/bin/Proyecto.exe: Proyecto/CMakeFiles/Proyecto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Uni\GraficaAvanzada\ProyectoFinal\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable D:\Uni\GraficaAvanzada\ProyectoFinal\bin\Proyecto.exe"
	cd /d D:\Uni\GraficaAvanzada\ProyectoFinal\build\Proyecto && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Proyecto.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Proyecto/CMakeFiles/Proyecto.dir/build: D:/Uni/GraficaAvanzada/ProyectoFinal/bin/Proyecto.exe
.PHONY : Proyecto/CMakeFiles/Proyecto.dir/build

Proyecto/CMakeFiles/Proyecto.dir/clean:
	cd /d D:\Uni\GraficaAvanzada\ProyectoFinal\build\Proyecto && $(CMAKE_COMMAND) -P CMakeFiles\Proyecto.dir\cmake_clean.cmake
.PHONY : Proyecto/CMakeFiles/Proyecto.dir/clean

Proyecto/CMakeFiles/Proyecto.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Uni\GraficaAvanzada\ProyectoFinal D:\Uni\GraficaAvanzada\ProyectoFinal\Proyecto D:\Uni\GraficaAvanzada\ProyectoFinal\build D:\Uni\GraficaAvanzada\ProyectoFinal\build\Proyecto D:\Uni\GraficaAvanzada\ProyectoFinal\build\Proyecto\CMakeFiles\Proyecto.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : Proyecto/CMakeFiles/Proyecto.dir/depend

