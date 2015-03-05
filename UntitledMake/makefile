
OUTPUT = ..\..\UG_content\UG.exe

COMPILER = "C:\Program Files (x86)\CodeBlocks\MinGW\bin\mingw32-g++.exe"
#COMPILER = "C:\Program Files\CodeBlocks\MinGW\bin\mingw32-g++.exe"

SWITCHES = \
	-fexceptions \
	-O3 \
	-std=c++11

INCLUDES = \
	-I..\..\UG_lua\include \
	-I..\..\UG_sfml\include \
	-I..\..\UG_libavc\include \
	-I..\include

LIBRARIES = \
	-L..\..\UG_lua\src\Lua5.2.3\bin\Release \
	-L..\..\UG_sfml\lib \
	-L..\..\UG_libavc\lib

MORESWITCHES = \
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
	..\src\Core\Databank.o \
	..\src\Assets\Asset.o \
	..\src\Assets\Texture.o \
	..\src\Assets\Font.o \
	..\src\Assets\Sound.o \
	..\src\Assets\Music.o \
	..\src\Assets\Video.o \
	..\src\Level\Level.o \
	..\src\Level\SolarSystem.o \
	..\src\Level\Planet.o \
	..\src\Level\PhysicalInstance.o \
	..\src\Level\Vector.o \
	..\src\Level\CollisionMesh.o \
	..\src\Level\Line.o \
	..\src\Level\Poly.o \
	..\src\Utilities\Logger.o

rebuild: clean build
	echo DONE!

build: $(OBJECTS)
	chdir
	$(COMPILER) $(LIBRARIES) -o $(OUTPUT) $(OBJECTS)   $(MORESWITCHES)

clean:
	chdir
	echo "Cleaning up"
	del /S ..\src\*.o
	echo "Clean complete"

$(OBJECTS): $(SOURCEDIR)$(@R).cpp
	$(COMPILER) $(SWITCHES) $(INCLUDES) -c $(@R).cpp -o $(@R).o
	