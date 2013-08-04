#ifndef LUASTATE_HPP
#define LUASTATE_HPP
#include "APGE/Core/CoreTypes.hpp"
#include "lua.hpp"

namespace APGE
{
  namespace Script
  {
    class LuaState : sf::NonCopyable
    {
    public:
      LuaState();
      LuaState(lua_State *ptrLuaState, bool owner=false);
      ~LuaState();

      /**
       * @brief loadFile
       * @param fileName
       * @return
       */
      bool loadFile(const std::string fileName);

      /**
       * @brief registerFunction
       * @param name
       * @param func
       */
      void registerFunction(const std::string name, lua_CFunction func);

      /**
       * @brief run - Call this before calling callFunction
       * @return
       */
      bool run();

      /**
       * @brief callFunction call run() First!!
       * @param name
       * @param nArgs
       * @param nResults
       * @return
       */
      bool callFunction(std::string name, int nArgs=0, int nResults=0);

      inline void pop(const int amt)
      {
        lua_pop(mLuaState_,amt);
      }

      inline void pushInt(const int arg)
      {
        lua_pushinteger(mLuaState_,arg);
      }

      inline void pushString(const std::string arg)
      {
        lua_pushstring(mLuaState_,arg.c_str());
      }

      inline void pushString(const char* arg)
      {
        lua_pushstring(mLuaState_,arg);
      }

      inline void pushNumber(const float arg)
      {
        lua_pushnumber(mLuaState_,arg);
      }

      inline void pushNumber(const double arg)
      {
        lua_pushnumber(mLuaState_,arg);
      }

      inline void pushNil()
      {
        lua_pushnil(mLuaState_);
      }

      inline void pushBool(const bool arg)
      {
        lua_pushboolean(mLuaState_,arg);
      }

      inline void pushUInt(const unsigned int arg)
      {
        lua_pushunsigned(mLuaState_,arg);
      }

      inline void pushFunction(const lua_CFunction arg)
      {
        lua_pushcfunction(mLuaState_,arg);
      }

      inline bool isNumber(const int index) const
      {
        return lua_isnumber(mLuaState_,index);
      }

      inline lua_Number getNumber(const int index) const
      {
        return lua_tonumber(mLuaState_,index);
      }

      inline int getInt(const int index) const
      {
        return lua_tointeger(mLuaState_,index);
      }

      inline unsigned int getUInt(const int index) const
      {
        return lua_tounsigned(mLuaState_,index);
      }

      inline bool isNil(const int index) const
      {
        return lua_isnil(mLuaState_,index);
      }

      inline bool isNone(const int index) const
      {
        return lua_isnone(mLuaState_,index);
      }

      inline bool isNoneOrNil(const int index) const
      {
        return lua_isnoneornil(mLuaState_,index);
      }

      inline bool isString(const int index) const
      {
        return lua_isstring(mLuaState_,index);
      }

      inline std::string getString(const int index) const
      {
        return std::string(lua_tostring(mLuaState_,index));
      }

      inline const char* getCString(const int index) const
      {
        return lua_tostring(mLuaState_,index);
      }

      inline bool isFunction(const int index) const
      {
        return lua_isfunction(mLuaState_,index);
      }

      inline bool isBool(const int index) const
      {
        return lua_isboolean(mLuaState_,index);
      }

      inline bool getBool(const int index) const
      {
        return lua_toboolean(mLuaState_,index);
      }

      inline void openLibs()
      {
        luaL_openlibs(mLuaState_);
      }

      inline void openLib(const luaL_Reg& lib)
      {
        lua_pushcfunction(mLuaState_, lib.func);
        lua_pushstring(mLuaState_, lib.name);
        lua_call(mLuaState_, 1, 0);
      }

      inline void openLibBase()
      {
        openLib({"",luaopen_base});
      }

      inline void openLibPackage()
      {
        openLib({LUA_LOADLIBNAME,luaopen_package});
      }

      inline void openLibTable()
      {
         openLib({LUA_TABLIBNAME,luaopen_table});
      }

      inline void openLibString()
      {
        openLib({LUA_STRLIBNAME,luaopen_string});
      }

      inline void openLibMath()
      {
         openLib({LUA_MATHLIBNAME,luaopen_math});
      }

      inline void openLibDebug()
      {
         openLib({LUA_DBLIBNAME,luaopen_debug});
      }

      inline void openLibOS()
      {
        openLib({LUA_OSLIBNAME,luaopen_os});
      }

      inline void openLibIO()
      {
        openLib({LUA_IOLIBNAME,luaopen_io});
      }

      inline void openLibCoroutine()
      {
        openLib({LUA_COLIBNAME,luaopen_coroutine});
      }

      inline int error()
      {
        return lua_error(mLuaState_);
      }

      inline std::string getErrors() const
      {
        return errors_;
      }

      inline void clearErrors() {
        errors_.clear();
      }

      inline operator lua_State *() {
        return mLuaState_;
      }

    private:

      inline void postErrors()
      {
        std::string errs = lua_tostring(mLuaState_,-1);
        errors_.append(errs).append("\r\n");
      }

      lua_State *mLuaState_;
      std::string errors_;
      bool owner_;

    };
  }
}
#endif // LUASTATE_HPP
