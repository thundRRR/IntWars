/*
IntWars playground server for League of Legends protocol testing
Copyright (C) 2012  Intline9 <Intline9@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stdafx.h"
#include "Game.h"
#include "RAFFile.h"
#include "Inibin.h"

#define SERVER_HOST ENET_HOST_ANY 
#define SERVER_PORT 5119
#define SERVER_KEY "17BLOhi6KZsTtldTsizvHg=="

#define SERVER_VERSION "0.0.2"

int main(int argc, char ** argv) 
{
   /*RAFFile raf("Archive_2.raf");
   std::vector<unsigned char> testFile;
   
   raf.readFile("DATA/Characters/Yasuo/Yasuo.inibin", testFile);
   
   printf("size : %d\n", testFile.size());
   printf("%s\n", &testFile[0]);
   
   Inibin yasuo(testFile);*/

	Game g;
	ENetAddress address;
	address.host = SERVER_HOST;
	address.port = SERVER_PORT;

	g.initialize(&address, SERVER_KEY);
	g.netLoop();
	
}