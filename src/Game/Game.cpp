#include "Game/Game.h"
#include "Engine/Font/FontTrueType.h"
#include "Engine/Event/SystemEventSource.h"
#include "Engine/Graphics/Surface.h"
#include "Engine/Graphics/Color.h"
#include "Engine/Exception.h"
#include "Engine/Util/Logger.h"
#include "Engine/GUI/Widget.h"
#include "Engine/GUI/Frame.h"
#include "Engine/Font/FontImage.h"
#include "Engine/Graphics/Painter.h"
#include "Engine/SmartPtr.h"
#include "SDLWrapper.h"
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <iostream>

namespace Game {

using Engine::SmartPtr;
using Engine::Util::Logger;
using Engine::Font::FontTrueType;
using Engine::Font::FontImage;

Game::Game(int argc, char* argv[])
{
    SystemEventSource::getInstance()->addWindowListener(this);
    SystemEventSource::getInstance()->addKeyListener(this);
    SystemEventSource::getInstance()->addMouseListener(this);
    SystemEventSource::getInstance()->addMouseMotionListener(this);
  
    display = Display::getInstance();
    
    display->setWindowTitle("Isometrie");
    display->setMode(800, 600);

    map    = new Map("test.map");
    font   = new FontImage("font.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.'!()?", 10); //TrueType("/usr/X11R6/lib/X11/fonts/truetype/verdana.ttf", 14);
    cursor = new Surface("img/cursor.png");

    mixer = Mixer::getInstance();
    cannon = new Sound("cannon.wav");
    explosion = new Sound("explosion.wav");
    music = new Sound("music.wav");
    
    SDL::showCursor(false);

    tree = new Surface("img/tree2.png");

    moving = false;
/*
    widget = new GUI::Widget(Rect(100, 100, 300, 200));
    widget->setBgColor(Color(255, 255, 255));
    widget->setBorderColor(Color(255, 0, 0));
    widget->setBorder(true);
    widget->setAlpha(160);

    GUI::Widget* childWidget = new GUI::Widget(Rect(10, 10, 100, 100));
    childWidget->setBgColor(Color(0, 0, 255));
    childWidget->setBorderColor(Color(0, 0, 128));
    childWidget->setBorder(true);
    childWidget->setAlpha(160);

    widget->addChild(childWidget);
*/
    widget = new Frame(Rect(100, 100, 300, 200));
    widget->setBgColor(Color(255, 255, 255));
    widget->setBorderColor(Color(65, 65, 65));
    widget->setBorder(true);
    widget->setCaption("Hallo");
    widget->setFont(font);
    widget->setAlpha(230);

/*
    GUI::Widget* childWidget = new GUI::Widget(Rect(-100, -100, 300, 300));
    childWidget->setBgColor(Color(0, 0, 255));
    childWidget->setBorderColor(Color(0, 0, 128));
    childWidget->setBorder(true);
    childWidget->setAlpha(160);

    widget->addChild(childWidget);
*/
}

Game::~Game()
{
    SystemEventSource::getInstance()->removeWindowListener(this);
    SystemEventSource::getInstance()->removeKeyListener(this);
}

void Game::updateCamera()
{
    Vector2 oldPos = cameraPos;

    // FIXME: Input
    int mouseX, mouseY;
    SDL::getMouseState(&mouseX, &mouseY);

    if ((mouseX < 30 || mouseX > display->getWidth() - 30) &&
        (mouseY < 30 || mouseY > display->getHeight() - 30))
    {
        if (mouseX < 30)
            cameraPos.x -= 2 * timer.getFrameTime();
        else
            cameraPos.x += 2 * timer.getFrameTime();

        if (mouseY < 30)
            cameraPos.y -= 2 * timer.getFrameTime();
        else
            cameraPos.y += 2 * timer.getFrameTime();
    }
    else
    {
        if (mouseX < 30)
            cameraPos.x -= 2 * timer.getFrameTime();
        else if (mouseX > display->getWidth() - 30)
            cameraPos.x += timer.getFrameTime();

        if (mouseY < 30)
            cameraPos.y -= 2 * timer.getFrameTime() / 3;
        else if (mouseY > display->getHeight() - 30)
            cameraPos.y += 2 * timer.getFrameTime() / 3;
    }
}

int Game::run()
{
    /*
    Channel* channel = mixer->getFreeChannel();
    channel->setRepeating(true);
    channel->play(music);
    //channel->fadeOut(1000);
    */
 
    Rect cursorRect;
    Uint8 cursorBackup[8000];
 
    int frames = 30;
    while (true)
    {
        SystemEventSource::getInstance()->processEvents();	
	
	if (frames >= 10)
	{
	    timer.nextFrame();
	    
	    updateCamera();

            display->clear();
	
            map->draw(display, cameraPos);
	
	    //widget->draw();
/*
            Painter p(display);
            p.setColor(Color::RED);
	    for (int y = -cameraPos.y % 32; y < display->getHeight(); y += 32)
	        p.drawHLine(y, 0, display->getWidth());
            for (int x = -cameraPos.x % 64; x < display->getWidth(); x += 64)
                p.drawVLine(x, 0, display->getHeight()); 
	    p.end();
	
  	    Painter p(display);	
	    //p.setBlending(true);
	    p.setColor(Color(0, 255, 0, 127));
	    p.fillRect(Rect(100, 100, 100, 100));
	    p.setColor(Color(255, 0, 0, 127));
	    p.fillRounded(Rect(100, 100, 100, 100), 10);
	    //p.fillCircle(200, 200, 200);
	    //p.fillRounded(Rect(100, 100, 100, 30), 10);
	    //p.setColor(Color(100, 100, 100));
	    //p.drawRounded(Rect(100, 100, 100, 30), 10);
	    //p.setColor(Color::RED);
	    //p.floodFill(0, 0);
	    p.end();
*/

	    std::ostringstream fpsText;
	    fpsText << "FPS: " << std::setprecision(3) << timer.getFrameRate() << std::flush;

	    font->drawText(display, fpsText.str(), Color::WHITE, 10, 10);

            int mouseX, mouseY;
	    SDL::getMouseState(&mouseX, &mouseY);
	    
	    cursorRect = Rect(mouseX, mouseY, cursor->getWidth(), cursor->getHeight());
	    display->readPixelBlock(cursorBackup, cursorRect);
	   
	    display->blit(cursor, cursor->getRect(), cursorRect);
	
	    display->addDirtyRect(display->getRect());
	    display->update();
            
            frames = 0;
        }
	else
	{
	    display->writePixelBlock(cursorBackup, cursorRect);
	    display->addDirtyRect(cursorRect);
	  
            int mouseX, mouseY;
	    SDL::getMouseState(&mouseX, &mouseY);		
	    
	    cursorRect = Rect(mouseX, mouseY, cursor->getWidth(), cursor->getHeight());
	    display->readPixelBlock(cursorBackup, cursorRect);
	    
	    display->blit(cursor, cursor->getRect(), cursorRect);
            
	    display->addDirtyRect(cursorRect);
            display->update();

            ++frames;
        }
    }
    
    return 0;
}

void Game::windowCloseEvent(const WindowEvent& event)
{
    display->close();
    exit(0);
}

void Game::windowActiveEvent(const WindowEvent& event)
{
    timer.reset();
}

void Game::keyDownEvent(const KeyEvent& event)
{
    switch (event.key)
    {
    case SDLK_ESCAPE:
        display->close();
	exit(0);
	break;
	
    case SDLK_f:
        if (event.mod & KMOD_LCTRL)
	    display->setFullscreen(!display->isFullscreen());
        break;

    case SDLK_c:
        mixer->getFreeChannel()->play(cannon);
	break;

    case SDLK_e:
        mixer->getFreeChannel()->play(explosion);
    }
}

void Game::mouseDownEvent(const MouseEvent& event)
{
    if (event.x > widget->getX() && event.x < widget->getX() + widget->getWidth() &&
        event.y > widget->getY() && event.y < widget->getY() + 20)
    {
        if (event.x < widget->getX() + 17)
	    widget->setVisible(false);
	moving = true;
    }

    int x, y;
    map->screenToTile(event.x, event.y, x, y, cameraPos);
    //LOG_INFO(Logger::mainLogger, x << '/' << y);
    std::cout << x << '/' << y << std::endl;
}

void Game::mouseUpEvent(const MouseEvent& event)
{
    moving = false;
}

void Game::mouseMotionEvent(const MouseMotionEvent& event)
{
    if (moving)
        widget->setPos(widget->getX() + event.xrel, widget->getY() + event.yrel);
}

} // namespace Game

int main(int argc, char* argv[])
{
    try
    {
        Game::Game game(argc, argv);
        std::exit(game.run());
    }
    catch (const Engine::Exception& ex)
    {
        LOG_ERROR(Engine::Util::Logger::mainLogger, "Exception caught: " << ex.what());
    }
    catch (...)
    {
        LOG_ERROR(Engine::Util::Logger::mainLogger, "Unknown exception caught");
    }
    
    std::exit(1);
}
