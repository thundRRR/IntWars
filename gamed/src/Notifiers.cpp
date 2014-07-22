#include "stdafx.h"
#include "Game.h"
#include "Packets.h"

#include <iostream>

using namespace std;

void Game::notifyMinionSpawned(Minion* m) {
   MinionSpawn ms(m);
   sendPacket(currentPeer, reinterpret_cast<uint8*>(&ms),sizeof(ms), CHL_S2C);
   notifySetHealth(m);
}

void Game::notifySetHealth(Unit* u) {
   SetHealth sh(u);
   sendPacket(currentPeer, sh, CHL_S2C);
}

void Game::notifyUpdatedStats(Unit* u) {
   cout << "Updating Stats" << endl;
   UpdateStats us(u);
   printPacket(&us.getBuffer().getBytes()[0], us.getBuffer().getBytes().size());
   sendPacket(currentPeer, us, CHL_LOW_PRIORITY, 2);
}