# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\builds\dynamic

# Include any dependencies generated for this target.
include examples/ftp/CMakeFiles/ftp.dir/depend.make

# Include the progress variables for this target.
include examples/ftp/CMakeFiles/ftp.dir/progress.make

# Include the compile flags for this target's objects.
include examples/ftp/CMakeFiles/ftp.dir/flags.make

examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj: examples/ftp/CMakeFiles/ftp.dir/flags.make
examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj: examples/ftp/CMakeFiles/ftp.dir/includes_CXX.rsp
examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj: ../../examples/ftp/Ftp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\builds\dynamic\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj"
	cd /d C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\builds\dynamic\examples\ftp && C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\ftp.dir\Ftp.cpp.obj -c C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\examples\ftp\Ftp.cpp

examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ftp.dir/Ftp.cpp.i"
	cd /d C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\builds\dynamic\examples\ftp && C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\examples\ftp\Ftp.cpp > CMakeFiles\ftp.dir\Ftp.cpp.i

examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ftp.dir/Ftp.cpp.s"
	cd /d C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\builds\dynamic\examples\ftp && C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\examples\ftp\Ftp.cpp -o CMakeFiles\ftp.dir\Ftp.cpp.s

examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj.requires:
.PHONY : examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj.requires

examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj.provides: examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj.requires
	$(MAKE) -f examples\ftp\CMakeFiles\ftp.dir\build.make examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj.provides.build
.PHONY : examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj.provides

examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj.provides.build: examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj

# Object files for target ftp
ftp_OBJECTS = \
"CMakeFiles/ftp.dir/Ftp.cpp.obj"

# External object files for target ftp
ftp_EXTERNAL_OBJECTS =

examples/ftp/ftp.exe: examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj
examples/ftp/ftp.exe: examples/ftp/CMakeFiles/ftp.dir/build.make
examples/ftp/ftp.exe: lib/libsfml-network.a
examples/ftp/ftp.exe: lib/libsfml-system.a
examples/ftp/ftp.exe: examples/ftp/CMakeFiles/ftp.dir/objects1.rsp
examples/ftp/ftp.exe: examples/ftp/CMakeFiles/ftp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ftp.exe"
	cd /d C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\builds\dynamic\examples\ftp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ftp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/ftp/CMakeFiles/ftp.dir/build: examples/ftp/ftp.exe
.PHONY : examples/ftp/CMakeFiles/ftp.dir/build

examples/ftp/CMakeFiles/ftp.dir/requires: examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.obj.requires
.PHONY : examples/ftp/CMakeFiles/ftp.dir/requires

examples/ftp/CMakeFiles/ftp.dir/clean:
	cd /d C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\builds\dynamic\examples\ftp && $(CMAKE_COMMAND) -P CMakeFiles\ftp.dir\cmake_clean.cmake
.PHONY : examples/ftp/CMakeFiles/ftp.dir/clean

examples/ftp/CMakeFiles/ftp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\examples\ftp C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\builds\dynamic C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\builds\dynamic\examples\ftp C:\Users\InDie\Bibliotheken\Documents\GitHub\--UntitledGame--\libraries\SFML-Framework\builds\dynamic\examples\ftp\CMakeFiles\ftp.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/ftp/CMakeFiles/ftp.dir/depend

