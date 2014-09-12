Wireshark Dissector for "LoL ENET"
==================
 
Tested with
-------
Wireshark Version 1.12.0 (v1.12.0-0-g4fab41a from master-1.12)
Compiled (64-bit) with ... Lua 5.2 ...
Running on 64-bit Windows 7 Service Pack 1 ...
 
Blowfish DLL build with
-------
MinGW x64-4.8.1-release-posix-sjlj-rev5
 
Installation
-------
1. build the dll -> Compile.bat
2. 
  1. use Install.bat
  2. or copy the files & folders:
	 * enet.lua
	 * GetLoLGameHash.vbs
	 * lolkeys/
	 * enet/
	 * enet/blowfish.dll

  into your "Wireshark personal plugin folder".
  See "Wireshark -> Help -> About Wireshark -> Folders -> Personal Plugins" for the exact path.
  If this folder doesnt exists, create it.
3. restart wireshark and check if the plugin is loaded:
  Check if "Wireshark -> Help -> About Wireshark -> Plugins" contains "enet.lua"
  
Usage
-------
Start a capture (Filter: "UDP"). As soon as a packet is captured and detected as "ENET" by the heuristic,
the lua script executes a VBScript to get the game key.
This key is then saved in a file in "your personal plugin folder"/lolkeys.
The filename contains the date&time of the first ENET packet and the server port.
If you open an already created .pcap file, the dissector will look for a matching key file.
If none is found, an empty file is created (you should have the corresponding game base64 key somewhere, 
else the capture is useless), so you can fill it with the correct key.
 
Best case scenario: It captures the packets, marks the ones from LoL as "ENET", 
saves they key in the corresponding key file, and shows the decrypted content in Wireshark.