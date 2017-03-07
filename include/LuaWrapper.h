#ifndef _LuaWrapper_h
#define _LuaWrapper_h

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

//#include "luabind/luabind.hpp"

namespace lua {

typedef lua_State* State;

enum
{
    TNIL           = LUA_TNIL,
    TBOOLEAN       = LUA_TBOOLEAN,
    TLIGHTUSERDATE = LUA_TLIGHTUSERDATA,
    TNUMBER        = LUA_TNUMBER,
    TSTRING        = LUA_TSTRING,
    TTABLE         = LUA_TTABLE,
    TFUNCTION      = LUA_TFUNCTION,
    TUSERDATA      = LUA_TUSERDATA,
    TTHREAD        = LUA_TTHREAD,
};

inline State open()
{
    return luaL_newstate();
}

inline void close(State state)
{
    lua_close(state);
}

inline void open_base(State state)
{
    luaopen_base(state);
}

inline void open_table(State state)
{
    luaopen_table(state);
}

inline void open_io(State state)
{
    luaopen_io(state);
}

inline void open_string(State state)
{
    luaopen_string(state);
}

inline void open_math(State state)
{
    luaopen_math(state);
}

inline void dostring(State state, const char* str)
{
    luaL_dostring(state, str);
}

inline void dofile(State state, const char* file)
{
    luaL_dofile(state, file);
}

} // namespace lua

#endif // _LuaWrapper_h
