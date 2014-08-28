#include <cstdlib>

#include "lua.hpp"

#include "base64.h"
#include "blowfish.h"

BlowFish *_blowfish = NULL;

int lua_Init(lua_State* L)
{
	const char* message = luaL_checkstring(L, 1);

	std::string key = base64_decode(message);
	if(_blowfish) {
		delete _blowfish;
	}
	_blowfish = new BlowFish((unsigned char*)key.c_str(), 16);
	
	return 0;
}

int lua_Decrypt(lua_State* L)
{
	int commandLength = luaL_checknumber(L, 2);
	
	unsigned char* pkt_ptr = (unsigned char*)malloc(commandLength);
	
	for(int i = 0; i < commandLength; i++) {
		lua_rawgeti (L, 1, i);
		int n = (int)lua_tonumber( L, -1 );
		lua_pop(L, 1);
		pkt_ptr[i] = (unsigned char)n;
	}

	if(_blowfish) {
		_blowfish->Decrypt(pkt_ptr, commandLength);
	}
		
	for(int i = 0; i < commandLength; i++) {
		lua_pushnumber (L, pkt_ptr[i]);
		lua_rawseti (L, 1, i);
	}
	
	free(pkt_ptr);

	lua_pop(L, 1);
	
	return 1;
}

#ifdef __cplusplus
extern "C" {
#endif
int __declspec(dllexport) luaopen_blowfish (lua_State* L)
{
	lua_register(L, "bf_Init",  lua_Init);
	lua_register(L, "bf_Decrypt",  lua_Decrypt);
	
	return 0;
}
#ifdef __cplusplus
}
#endif
