
OUTPUT = ..\..\UG_content\UG.exe

#COMPILER = "C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe"
COMPILER = "C:\Program Files (x86)\CodeBlocks\MinGW\bin\mingw32-g++.exe"

CSWITCHES = \
	-fexceptions \
	-O3 \
	-std=c++11

LSWITCHES = \

INCLUDES = \
	-I..\..\UG_lua\include \
	-I..\..\UG_sfml\include \
	-I..\..\UG_libavc\include \
	-I..\include

LIBPATH = \
	-L..\..\UG_lua\src\Lua5.2.3\bin\Release \
	-L..\..\UG_sfml\lib \
	-L..\..\UG_libavc\lib

LIBRARIES = \
	-lsfml-audio \
	-lsfml-network \
	-lsfml-graphics \
	-lsfml-window \
	-lsfml-system \
	..\..\UG_lua\src\Lua5.2.3\bin\Release\libLua5.2.3.a \
	-lavcodec \
	-lavformat \
	-lavutil \
	-lswscale

OBJECTS = \
	..\src\Core\main.o \
	..\src\Utilities\Logger.o \
	..\src\Assets\Texture.o \
	..\src\Assets\TextureManager.o \
	..\src\Input\EventManager.o \
	..\src\Data\Vector.o

rebuild: clean build
	echo DONE!

build: $(OBJECTS)
	chdir
	$(COMPILER) $(LSWITCHES) $(LIBPATH) -o $(OUTPUT) $(OBJECTS)   $(LIBRARIES)

clean:
	chdir
	echo "Cleaning up"
	del /S ..\src\*.o
	echo "Clean complete"

$(OBJECTS): $(SOURCEDIR)$(@R).cpp
	$(COMPILER) $(CSWITCHES) $(INCLUDES) -c $(@R).cpp -o $(@R).o
	