@echo off

IF EXIST "C:\Program Files\Wireshark\Lua52.dll" (
	SET DLL="C:\Program Files\Wireshark\Lua52.dll"
) ELSE (
	IF EXIST "C:\Program Files (x86)\Wireshark\Lua52.dll" (
		SET DLL="C:\Program Files (x86)\Wireshark\Lua52.dll"
	) ELSE (
		ECHO "Wireshark\Lua52.dll not found."
		GOTO end
	)
)

@echo on

IF NOT EXIST enet MKDIR enet

IF NOT EXIST lolkeys MKDIR lolkeys

g++ -shared -static-libgcc -static-libstdc++ -static -I../../dep/include/lua -I../pcapDecrypt blowfish.c ../pcapDecrypt/base64.cpp ../pcapDecrypt/blowfish.cpp %DLL% -o enet/blowfish.dll

:end