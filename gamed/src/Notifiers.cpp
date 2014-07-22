#include "stdafx.h"
#include "Game.h"
#include "Packets.h"

void Game::notifyMinionSpawned(Minion* m) {
   MinionSpawn ms(m);
   sendPacket(currentPeer, reinterpret_cast<uint8*>(&ms),sizeof(ms), CHL_S2C);
   notifySetHealth(m);
}

void Game::notifySetHealth(Unit* u) {
   SetHealth sh(u);
   sendPacket(currentPeer, sh, CHL_S2C);
}