#include "LuaState.hpp"
namespace APGE
{
  namespace Script
  {
    LuaState::LuaState()
      : mLuaState_(luaL_newstate())
      , owner_(true)
    {
      LOGD("+LuaState Created Lua State");
    }

    LuaState::LuaState(lua_State *ptrLuaState, bool owner)
      : mLuaState_(ptrLuaState)
      , owner_(owner)
    {
      LOGD("+LuaState from pointer, owner="<<owner);
    }

    LuaState::~LuaState()
    {
      if(owner_)
        {
          lua_close(mLuaState_);
          LOGI("-LuaState: Closing LUA State");
        }
      else
        {
          LOGD("LuaState::Dtor() called but not owner.");
        }
    }

    bool LuaState::loadFile(const std::string fileName)
    {
      int status = luaL_loadfile(mLuaState_,fileName.c_str());
      if(status == 0)
        {
          return true;
        }
      else
        {
          errors_.append("Could not load file: ")
                 .append(fileName).append("\r\n");
          postErrors();
          return false;
        }
    }

    void LuaState::registerFunction(const std::string name, lua_CFunction func)
    {
      lua_register(mLuaState_,name.c_str(),func);
    }

    bool LuaState::run()
    {
      int state = lua_pcall(mLuaState_,0,0,0);
      if(state==0)
        {
          return true;
        }
      else
        {
          postErrors();
          return false;
        }

    }

    bool LuaState::callFunction(const std::string name, int nArgs, int nResults)
    {
      lua_getglobal(mLuaState_,name.c_str());
      int state = lua_pcall(mLuaState_,nArgs,nResults,0);
      if(state == 0)
        {
          return true;
        }
      else
        {
          postErrors();
          return false;
        }
    }
  }
}
