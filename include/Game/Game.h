#ifndef _Game_Game_h
#define _Game_Game_h

#include "Engine/SmartPtr.h"
#include "Engine/Font/Font.h"
#include "Engine/Graphics/Display.h"
#include "Engine/Graphics/Rect.h"
#include "Engine/Event/WindowEvent.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseMotionEvent.h"
#include "Engine/Event/MouseEvent.h"
#include "Engine/Event/WindowListener.h"
#include "Engine/Event/KeyListener.h"
#include "Engine/Event/MouseMotionListener.h"
#include "Engine/Event/MouseListener.h"
#include "Engine/Audio/Mixer.h"
#include "Engine/Audio/Sound.h"
#include "Engine/Util/FrameTimer.h"
#include "Engine/Map/Map.h"
#include "Engine/GUI/Widget.h"

namespace Game {

using namespace Engine;
using Engine::Font::Font;
using namespace Engine::Event;
using namespace Engine::Audio;
using Engine::Map::Map;
using namespace Engine::Util;
using namespace Engine::GUI;
using namespace Engine::Graphics;

class Game : public WindowListener, KeyListener, MouseMotionListener, MouseListener
{
public:

    Game(int argc, char* argv[]);
    virtual ~Game();
    
    int run();
    void updateCamera();

    void windowCloseEvent(const WindowEvent& event);
    void windowActiveEvent(const WindowEvent& event);
    void keyDownEvent(const KeyEvent& event);
    void mouseMotionEvent(const MouseMotionEvent& event);
    void mouseDownEvent(const MouseEvent& event);
    void mouseUpEvent(const MouseEvent& event);
    
private:

    bool moving;

    Surface* tree;
    
    GUI::Widget* widget;

    SmartPtr<Mixer>   mixer;
    SmartPtr<Sound>   cannon, explosion, music;
    FrameTimer        timer;
    SmartPtr<Display> display;
    SmartPtr<Map>     map;
    SmartPtr<Font>    font;
    SmartPtr<Surface> cursor;
    Vector2           cameraPos;
};

} // namespace Game

#endif // _Game_Game_h

