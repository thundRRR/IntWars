#include <sol.hpp>
#include <stdafx.h>

#ifndef LUASCRIPT_H
#define	LUASCRIPT_H

class LuaScript{
private:

public:
    LuaScript(bool defineClasses);
    
    void loadScript(std::string location);
    sol::table getTable(std::string name);
    void setFunction();
    sol::state lua;
    
    void addChampion();
    void addUnit ();
    void addItem ();
    void addGame ();
};


#endif	/* LUASCRIPT_H */

