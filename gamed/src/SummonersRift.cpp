#include "SummonersRift.h"
#include "Turret.h"
#include "Game.h"
#include "LevelProp.h"

using namespace std;

const static vector<vector<MovementVector> > ConstWaypoints = 
{
   { // blue top
      MovementVector(917.f, 1725.f),
      MovementVector(1170.f, 4041.f),
      MovementVector(861.f, 6459.f),
      MovementVector(880.f, 10180.f),
      MovementVector(1268.f, 11675.f),
      MovementVector(2806.f, 13075.f),
      MovementVector(3907.f, 13243.f),
      MovementVector(7550.f, 13407.f),
      MovementVector(10244.f, 13238.f),
      MovementVector(10947.f, 13135.f),
      MovementVector(12511.f, 12776.f)
   },
   { // blue bot
      MovementVector(1487.f, 1302.f),
      MovementVector(3789.f, 1346.f),
      MovementVector(6430.f, 1005.f),
      MovementVector(10995.f, 1234.f),
      MovementVector(12841.f, 3051.f),
      MovementVector(13148.f, 4202.f),
      MovementVector(13249.f, 7884.f),
      MovementVector(12886.f, 10356.f),
      MovementVector(12511.f, 12776.f)
   },
   { // blue mid
      MovementVector(1418.f, 1686.f),
      MovementVector(2997.f, 2781.f),
      MovementVector(4472.f, 4727.f),
      MovementVector(8375.f, 8366.f),
      MovementVector(10948.f, 10821.f),
      MovementVector(12511.f, 12776.f)
   },
   { // red top
      MovementVector(12451.f, 13217.f),
      MovementVector(10947.f, 13135.f),
      MovementVector(10244.f, 13238.f),
      MovementVector(7550.f, 13407.f),
      MovementVector(3907.f, 13243.f),
      MovementVector(2806.f, 13075.f),
      MovementVector(1268.f, 11675.f),
      MovementVector(880.f, 10180.f),
      MovementVector(861.f, 6459.f),
      MovementVector(1170.f, 4041.f),
      MovementVector(1418.f, 1686.f)
   },
   { // red bot
      MovementVector(13062.f, 12760.f),
      MovementVector(12886.f, 10356.f),
      MovementVector(13249.f, 7884.f),
      MovementVector(13148.f, 4202.f),
      MovementVector(12841.f, 3051.f),
      MovementVector(10995.f, 1234.f),
      MovementVector(6430.f, 1005.f),
      MovementVector(3789.f, 1346.f),
      MovementVector(1418.f, 1686.f)
   },
   { // red mid
      MovementVector(12511.f, 12776.f),
      MovementVector(10948.f, 10821.f),
      MovementVector(8375.f, 8366.f),
      MovementVector(4472.f, 4727.f),
      MovementVector(2997.f, 2781.f),
      MovementVector(1418.f, 1686.f)
   },
};

SummonersRift::SummonersRift(Game* game) : Map(game, 5*1000000, 30*1000000) {
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_R_03_A", 10097.62, 808.73, 2550, 156, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_R_02_A", 6512.53, 1262.62, 2550, 170, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_07_A", 3747.26, 1041.04, 2550, 190, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_R_03_A", 13459.f, 4284.f, 2550, 156, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_R_02_A", 12920.f, 8005.f, 2550, 170, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_R_01_A", 13205.f, 10474.f, 2550, 190, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_05_A", 5435.02, 6179.10, 2550, 156, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_04_A", 4633.66, 4591.91, 2550, 170, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_03_A", 3233.99, 3447.24, 2550, 190, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_01_A", 1341.63, 2029.98, 2425, 180, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_02_A", 1768.19, 1589.47, 2425, 180, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_C_05_A", 8548.f, 8289.f, 2550, 156, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_C_04_A", 9361.f, 9892.f, 2550, 170, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_C_03_A", 10743.f, 11010.f, 2550, 190, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_C_01_A", 12662.f, 12442.f, 2425, 180, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_C_02_A", 12118.f, 12876.f, 2425, 180, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_OrderTurretShrine_A", -236.05, -53.32, 9999, 999, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_ChaosTurretShrine_A", 14157.f, 14456.f, 9999, 999, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_L_03_A", 574.66, 10220.47, 2550, 156, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_L_02_A", 1106.26, 6485.25, 2550, 170, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_06_A", 802.81, 4052.36, 2550, 190, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_L_03_A", 3911.f, 13654.f, 2550, 156, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_L_02_A", 7536.f, 13190.f, 2550, 170, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_L_01_A", 10261.f, 13465.f, 2550, 190, 1));
   
   addObject(new LevelProp(this, GetNewNetID(), 12465, 14422.257f, 101, "LevelProp_Yonkey", "Yonkey"));
   addObject(new LevelProp(this, GetNewNetID(), -76, 1769.1589f, 94, "LevelProp_Yonkey1", "Yonkey"));
   addObject(new LevelProp(this, GetNewNetID(), 13374, 14245.673f, 194, "LevelProp_ShopMale", "ShopMale"));
   addObject(new LevelProp(this, GetNewNetID(), -99, 855.6632f, 191, "LevelProp_ShopMale1", "ShopMale"));
   
   // Start at xp to reach level 1
   expToLevelUp = { 0, 280, 660, 1140, 1720, 2400, 3180, 4060, 5040, 6120, 7300, 8580, 9960, 11440, 13020, 14700, 16480, 18360 };
}

void SummonersRift::update(long long diff) {
   Map::update(diff);
}

bool SummonersRift::spawn() {

   static const vector<MinionSpawnPosition> positions = {   
                                                      SPAWN_BLUE_TOP,
                                                      SPAWN_BLUE_BOT,
                                                      SPAWN_BLUE_MID,
                                                      SPAWN_RED_TOP,
                                                      SPAWN_RED_BOT,
                                                      SPAWN_RED_MID, 
                                                   };

   if(waveNumber < 3) {
      for(int i = 0; i < positions.size(); ++i) {
         Minion* m = new Minion(this, GetNewNetID(), MINION_TYPE_MELEE, positions[i], ConstWaypoints[i]);
         addObject(m);
         game->notifyMinionSpawned(m);
      }
      return false;
   }
   
   /*if(waveNumber < 6) {
      for(int i = 0; i < positions.size(); ++i) {
         Minion* m = new Minion(this, GetNewNetID(), MINION_TYPE_CASTER, positions[i], ConstWaypoints[i]);
         addObject(m);
         game->notifyMinionSpawned(m);
      }
      return false;
   }
   
   if(waveNumber == 6) {
      for(int i = 0; i < positions.size(); ++i) {
         Minion* m = new Minion(this, GetNewNetID(), MINION_TYPE_CANNON, positions[i], ConstWaypoints[i]);
         addObject(m);
         game->notifyMinionSpawned(m);
      }
      return true;
   }*/
}

const Target SummonersRift::getRespawnLoc(int side) const {
   switch(side) {
   case 0:
      return Target(25.90f, 280);
   case 1:
      return Target(14119, 14063);
   }
   
   return Target(25.90f, 280);
}