CXX=g++
#CFLAGS=-O3 -fexceptions -funroll-loops -Wall -Wno-switch
CFLAGS=-g -Wall -fexceptions -Wall -Wno-switch
LIBS=-lSDL -lSDL_image -lSDL_ttf -llua -llualib
INCLUDES=-I/usr/include/SDL -Iinclude

SOURCES=\
src/Engine/Audio/Mixer.cpp\
src/Engine/Audio/Channel.cpp\
src/Engine/Audio/Sound.cpp\
src/Engine/Font/FontImage.cpp\
src/Engine/Font/FontTrueType.cpp\
src/Engine/Graphics/Rect.cpp\
src/Engine/Graphics/Surface.cpp\
src/Engine/Graphics/Painter.cpp\
src/Engine/Graphics/Color.cpp\
src/Engine/Graphics/Display.cpp\
src/Engine/Script/LuaScript.cpp\
src/Engine/Util/Logger.cpp\
src/Engine/Util/ActionTrigger.cpp\
src/Engine/Util/FrameTimer.cpp\
src/Engine/Util/Thread.cpp\
src/Engine/Util/LogAppender.cpp\
src/Engine/Map/Map.cpp\
src/Engine/Event/SystemEventSource.cpp\
src/Engine/GUI/Theme.cpp\
src/Engine/GUI/Frame.cpp\
src/Engine/GUI/Widget.cpp\
src/Engine/Graphics/TileSet.cpp\
src/Game/Game.cpp

OBJECTS=$(SOURCES:.cpp=.o)

isometric: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LIBS)

.cpp.o:
	$(CXX) -c $(CFLAGS) $(INCLUDES) -o $@ $<

clean:
	rm -f $(OBJECTS)	
