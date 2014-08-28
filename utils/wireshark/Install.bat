@echo off

SET COMPILECHECK="enet\blowfish.dll"

SET WSPERSONALDIR="%APPDATA%\Wireshark"

SET WSPLUGINDIR="%APPDATA%\Wireshark\plugins"

SET WSPLUGINDLLDIR="%APPDATA%\Wireshark\plugins\enet"

SET WSPLUGINKEYDIR="%APPDATA%\Wireshark\plugins\lolkeys"


IF NOT EXIST %COMPILECHECK% (
	echo "Missing file '%COMPILECHECK%', please run 'Compile.bat' first."
	goto end
)

IF NOT EXIST %WSPERSONALDIR% (
	echo "Missing folder '%WSPERSONALDIR%', please check the README for manual installation."
	goto end
)

IF NOT EXIST %WSPLUGINDIR% (
	MKDIR %WSPLUGINDIR%
	echo "Created the folder: %WSPLUGINDIR%."
)

@echo on


IF NOT EXIST %WSPLUGINDLLDIR% MKDIR %WSPLUGINDLLDIR%

xcopy /Y enet\blowfish.dll %WSPLUGINDLLDIR%

IF NOT EXIST %WSPLUGINKEYDIR% MKDIR %WSPLUGINKEYDIR%


xcopy enet.lua %WSPLUGINDIR%

xcopy GetLoLGameHash.vbs %WSPLUGINDIR%


:end
