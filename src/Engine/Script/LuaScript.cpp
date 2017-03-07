#include "Engine/Script/LuaScript.h"

namespace Engine {
namespace Script {

LuaScript::LuaScript()
{
    state = lua::open();
    lua::open_base(state);
    lua::open_table(state);
    lua::open_string(state);
    lua::open_math(state);
    lua::open_io(state);
    
    //luabind::open(state);
}

LuaScript::~LuaScript()
{
    lua::close(state);
}

} // namespace Script
} // namespace Engine
