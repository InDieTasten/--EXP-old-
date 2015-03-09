
OUTPUT = ..\..\UG_content\UG.exe

COMPILER = "C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe"
#COMPILER = "C:\Program Files\CodeBlocks\MinGW\bin\mingw32-g++.exe"

SWITCHES = \
	-fexceptions \
	-O3 \
	-std=c++11 \
	-m32

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
	..\src\Core\GUIManager.o \
	..\src\Core\ThreadManager.o \
	..\src\Core\EventThread.o \
	..\src\Core\GravityThread.o \
	..\src\Core\MovementThread.o \
	..\src\Core\GraphicsThread.o \
	..\src\Assets\Asset.o \
	..\src\Assets\Texture.o \
	..\src\Assets\Font.o \
	..\src\Assets\Sound.o \
	..\src\Assets\Music.o \
	..\src\Assets\Video.o \
	..\src\Level\Level.o \
	..\src\Level\SolarSystem.o \
	..\src\Level\Planet.o \
	..\src\Level\Bullet.o \
	..\src\Level\Construction.o \
	..\src\Level\Ship.o \
	..\src\Level\Asteroid.o \
	..\src\Level\Debris.o \
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
	$(COMPILER) -m32 $(LIBRARIES) -o $(OUTPUT) $(OBJECTS)   $(MORESWITCHES)

clean:
	chdir
	echo "Cleaning up"
	del /S ..\src\*.o
	echo "Clean complete"

$(OBJECTS): $(SOURCEDIR)$(@R).cpp
	$(COMPILER) $(SWITCHES) $(INCLUDES) -c $(@R).cpp -o $(@R).o
	