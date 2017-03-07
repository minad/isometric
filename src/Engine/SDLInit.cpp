#include "Engine/Exception.h"
#include "SDLWrapper.h"

namespace {

struct SDLInit
{    
    SDLInit()
    {
        if (SDL::init(SDL::INIT_NOPARACHUTE) < 0)
            throw Exception("Couldn't initialize SDL", SDL::getError());
    }
        
    ~SDLInit()
    {
         SDL::quit();
    }
} sdlInit;

} // anonymous namespace