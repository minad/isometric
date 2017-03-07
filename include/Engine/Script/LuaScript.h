#ifndef _Engine_Script_LuaScript_h
#define _Engine_Script_LuaScript_h

#include "LuaWrapper.h"
#include <string>

namespace Engine {
namespace Script {

class LuaScript
{
public:

    LuaScript();
    ~LuaScript();
   
    void doFile(const std::string& file)
    {
        lua::dofile(state, file.c_str());
    }

    void doString(const std::string& code)
    {
        lua::dostring(state, code.c_str());
    }
   
    operator lua::State() const
    {
        return state;
    }

private:

    lua::State state;
};

} // namespace Script
} // namespace Engine

#endif // _Engine_Script_LuaScript_h
