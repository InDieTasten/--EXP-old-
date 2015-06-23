
OUTPUT = ..\..\UG_content\EXP.exe

#COMPILER = "C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe"
COMPILER = "C:\Program Files (x86)\CodeBlocks\MinGW\bin\mingw32-g++.exe"

CSWITCHES = \
	-fexceptions \
	-std=c++11 \
	-D SFML_STATIC

LSWITCHES = -D SFML_STATIC \

INCLUDES = \
	-I..\..\UG_lua\include \
	-I..\..\UG_sfml\include \
	-I..\..\UG_libavc\include \
	-I..\include \
	-I..\..\UG_boost \
	-I..\..\UG_luabind

LIBPATH = \
	-L..\..\UG_lua\src\Lua5.2.3\bin\Release \
	-L..\..\UG_sfml\lib \
	-L..\..\UG_libavc\lib \
	-L..\..\UG_luabind\lib \

LIBRARIES = \
	-lsfml-audio-s \
	-lsfml-network-s \
	-lsfml-graphics-s \
	-lsfml-window-s \
	-lsfml-system-s \
	..\..\UG_lua\src\Lua5.2.3\bin\Release\libLua5.2.3.a
#
#	-lavcodec \
#	-lavformat \
#	-lavutil \
#	-lswscale

OBJECTS = \
	..\src\Utilities\Logger.o \
	..\src\Utilities\UI.o \
	..\src\Assets\Texture.o \
	..\src\Assets\TextureManager.o \
	..\src\Assets\Font.o \
	..\src\Assets\FontManager.o \
	..\src\Assets\AssetManager.o \
	..\src\Input\EventManager.o \
	..\src\Input\Actuator.o \
	..\src\Data\Vector.o \
	..\src\Data\Mesh.o \
	..\src\Data\PhysicalInfo.o \
	..\src\Data\GraphicalInfo.o \
	..\src\Data\Ship.o \
	..\src\Data\Attachable.o \
	..\src\Data\PilotSeat.o \
	..\src\Data\Thruster.o \
	..\src\Data\ResourceType.o \
	..\src\Data\Container.o \
	..\src\Data\Taggable.o \
	..\src\Data\System.o \
	..\src\Processing\GameEngine.o \
	..\src\Processing\Renderer.o \
	..\src\Processing\Simulator.o \
	..\src\GUI\Button.o \
	..\src\GUI\GUIElement.o \
	..\src\GUI\GUIManager.o \
	..\src\GUI\GUIMenu.o \
	..\src\GUI\InputField.o \
	..\src\GUI\Label.o \
	..\src\GUI\Responsive.o \
	..\src\SFML\Text.o \

rebuild: clean build
	echo DONE!

build: ..\src\Core\main.o $(OBJECTS)
	chdir
	$(COMPILER) $(LSWITCHES) $(LIBPATH) -o $(OUTPUT) ..\src\Core\main.o $(OBJECTS)   $(LIBRARIES)

clean:
	chdir
	echo "Cleaning up"
	del /S ..\src\*.o
	echo "Clean complete"

..\src\Core\main.o: ..\src\Core\main.cpp ..\EXP-ExpandedExploration\TestCode.hpp
	$(COMPILER) $(CSWITCHES) $(INCLUDES) -c ..\src\Core\main.cpp -o ..\src\Core\main.o

$(OBJECTS): $(SOURCEDIR)$(@R).cpp
	$(COMPILER) $(CSWITCHES) $(INCLUDES) -c $(@R).cpp -o $(@R).o
