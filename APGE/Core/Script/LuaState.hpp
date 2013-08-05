#ifndef LUASTATE_HPP
#define LUASTATE_HPP
#include "APGE/Core/CoreTypes.hpp"
#include "LuaNil.hpp"
#include "lua.hpp"

namespace APGE
{
  namespace Script
  {
    class LuaState : boost::noncopyable
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
      bool loadFile(const std::string& fileName);

      /**
       * @brief registerFunction
       * @param name
       * @param func
       */
      inline void registerFunction(const std::string& name, lua_CFunction func)
      {
        lua_register(mLuaState_,name.c_str(),func);
      }

      /**
       * @brief run - Call this before calling callFunction
       * @return
       */
      bool run();

      bool callFunction(const std::string& name, int nResults)
      {
        lua_getglobal(mLuaState_, name.c_str());
        if(lua_pcall(mLuaState_,0,nResults,0))
          {
            postErrors();
            return false;
          }
        else
          {
            return true;
          }
      }

      template<typename T>
      bool callFunction(const std::string& name, int nResults, const T& head)
      {
        lua_getglobal(mLuaState_, name.c_str());
        push(head);
        if(lua_pcall(mLuaState_,1,nResults,0))
          {
            postErrors();
            return false;
          }
        else
          {
            return true;
          }
      }

      template<typename T, typename... U>
      bool callFunction(const std::string& name, int nResults, const T& head, const U&... tail)
      {
        lua_getglobal(mLuaState_, name.c_str());
        push(head);
        return callFunctionRecurse(nResults,1,tail...);
      }

      inline void pop(const int amt)
      {
        lua_pop(mLuaState_,amt);
      }

      inline void push(const int arg)
      {
        lua_pushinteger(mLuaState_,arg);
      }

      inline void push(const std::string arg)
      {
        lua_pushstring(mLuaState_,arg.c_str());
      }

      inline void push(const char* arg)
      {
        lua_pushstring(mLuaState_,arg);
      }

      inline void push(const float arg)
      {
        lua_pushnumber(mLuaState_,arg);
      }

      inline void push(const double arg)
      {
        lua_pushnumber(mLuaState_,arg);
      }

      inline void push(const LuaNil /*unused*/)
      {
        lua_pushnil(mLuaState_);
      }

      inline void push(const bool arg)
      {
        lua_pushboolean(mLuaState_,arg);
      }

      inline void push(const unsigned int arg)
      {
        lua_pushunsigned(mLuaState_,arg);
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
        const char* errstring = lua_tostring(mLuaState_,-1);
        if(errstring)
          {
            errors_.append(errstring).append("\r\n");
          }
      }

      template<typename T>
      __alwaysinline bool callFunctionRecurse(int nResults, int nArgs, const T& head)
      {
        push(head);
        if(lua_pcall(mLuaState_,nArgs+1,nResults,0))
          {
            postErrors();
            return false;
          }
        else
          {
            return true;
          }
      }

      template<typename T, typename... U>
      __alwaysinline bool callFunctionRecurse(int nResults, int nArgs, const T& head, const U&... tail)
      {
        push(head);
        return callFunctionRecurse(nResults,nArgs+1, tail...);
      }

      lua_State *mLuaState_;
      std::string errors_;
      bool owner_;

    };
  }
}
#endif // LUASTATE_HPP
