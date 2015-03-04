
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
	..\src\Processing\ModModule.o \
	..\src\Processing\main.o \
	..\src\Processing\EventManager.o \
	..\src\Processing\GraphicsEngine.o \
	..\src\MemoryBank\DataBank.o \
	..\src\MemoryBank\Level\Level.o \
	..\src\MemoryBank\Level\SpaceObject.o \
	..\src\MemoryBank\Level\SolarSystem.o \
	..\src\MemoryBank\Level\Vector.o \
	..\src\MemoryBank\Level\LocalControl.o \
	..\src\MemoryBank\Entities\Texture.o \
	..\src\MemoryBank\Entities\Video.o \
	..\src\MemoryBank\Entities\Track.o \
	..\src\MemoryBank\Entities\Sound.o \
	..\src\MemoryBank\Entities\Script.o \
	..\src\MemoryBank\Entities\Font.o \
	..\src\GUI\GUIManager.o \
	..\src\GUI\GUIElement.o \
	..\src\GUI\GUIMenu.o \
	..\src\GUI\GUIDockItem.o \
	..\src\GUI\Elements\TextBox.o \
	..\src\GUI\Elements\CheckBox.o \
	..\src\GUI\Elements\HorSlider.o \
	..\src\GUI\Elements\Button.o \
	..\src\GUI\Elements\VertSlider.o \
	..\src\GUI\Elements\Label.o \
	..\src\GUI\Elements\CodeBox.o \
	..\src\GUI\Elements\Canvas.o \
	..\src\Utilities\util.o \
	..\src\Utilities\Logger.o \
	..\src\Utilities\FileLogger.o

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
	