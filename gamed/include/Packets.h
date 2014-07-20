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
#ifndef _PACKETS_H
#define _PACKETS_H

#include <enet/enet.h>
#include "common.h"
#include <time.h>
#include <intlib/general.h>
#include <cmath>

#if defined( __GNUC__ )
#pragma pack(1)
#else
#pragma pack(push,1)
#endif

struct PacketHeader {
    PacketHeader() {
        netId = 0;
    }

    PacketCmd cmd;
    uint32 netId;
};

struct GameHeader {
    GameHeader() {
        netId = ticks = 0;
    }

    GameCmd cmd;
    uint32 netId;
    uint32 ticks;
};
typedef struct _SynchBlock {
    _SynchBlock() {
        userId = 0xFFFFFFFFFFFFFFFF;
        netId = 0x1E;
        teamId = 0x64;
        unk2 = 0;
        flag = 0; //1 for bot?
        memset(data1, 0, 64);
        memset(data2, 0, 64);
        unk3 = 0x19;
    }

    uint64 userId;
    uint16 netId;
    uint32 skill1;
    uint32 skill2;
    uint8 flag;
    uint32 teamId;
    uint8 data1[64];
    uint8 data2[64];
    uint32 unk2;
    uint32 unk3;
} SynchBlock;

struct ClientReady {
    uint32 cmd;
    uint32 playerId;
    uint32 teamId;
};

typedef struct _SynchVersionAns {
    _SynchVersionAns() {
        header.cmd = PKT_S2C_SynchVersion;
        ok = ok2 = 1;
        memcpy(version, "Version 4.12.0.356 [PUBLIC]", 27);
        memcpy(gameMode, "CLASSIC", 8);
        memset(zero, 0, 2232);
        end1 = 0xE2E0;
        end2 = 0xA0;
    }

    PacketHeader header;
    uint8 ok;
    uint32 mapId;
    SynchBlock players[12];
    uint8 version[27];      //Ending zero so size 26+0x00
    uint8 ok2;              //1
    uint8 unknown[228];     //Really strange shit
    uint8 gameMode[8];
    uint8 zero[2232];
    uint16 end1;            //0xE2E0
    uint8 end2;             //0xA0 || 0x08
} SynchVersionAns;

typedef struct _PingLoadInfo {
    PacketHeader header;
    uint32 unk1;
    uint64 userId;
    float loaded;
    float ping;
    float f3;
} PingLoadInfo;

uint8 *createDynamicPacket(uint8 *str, uint32 size);

typedef struct _LoadScreenInfo {
    _LoadScreenInfo() {
        //Zero this complete buffer
        memset(this, 0, sizeof(_LoadScreenInfo));
        cmd = PKT_S2C_LoadScreenInfo;
        blueMax = redMax = 6;
    }

    uint8 cmd;
    uint32 blueMax;
    uint32 redMax;
    uint64 bluePlayerIds[6]; //Team 1, 6 players max
    uint8 blueData[144];
    uint64 redPlayersIds[6]; //Team 2, 6 players max
    uint8 redData[144];
    uint32 bluePlayerNo;
    uint32 redPlayerNo;
} LoadScreenInfo;

typedef struct _LoadScreenPlayer {
    static _LoadScreenPlayer *create(PacketCmd cmd, int8 *str, uint32 size) {
        //Builds packet buffer
        uint32 totalSize = sizeof(_LoadScreenPlayer) + size + 1;
        uint8 *buf = new uint8[totalSize];
        memset(buf, 0, totalSize);
        //Set defaults
        _LoadScreenPlayer *packet = (_LoadScreenPlayer *)buf;
        packet->cmd = cmd;
        packet->length = size;
        packet->userId = 0;
        packet->skinId = 0;
        memcpy(packet->getDescription(), str, packet->length);
        return packet;
    }

    static void destroy(_LoadScreenPlayer *packet) {
        delete [](uint8 *)packet;
    }

    uint8 cmd;
    uint64 userId;
    uint32 skinId;
    uint32 length;
    uint8 description;
    uint8 *getDescription() {
        return &description;
    }

    uint32 getPacketLength() {
        return sizeof(_LoadScreenPlayer) + length;
    }
} LoadScreenPlayer;


typedef struct _KeyCheck {
    _KeyCheck() {
        cmd = PKT_KeyCheck;
        playerNo = 0;
        checkId = 0;
        trash = trash2 = 0;
    }

    uint8 cmd;
    uint8 partialKey[3];   //Bytes 1 to 3 from the blowfish key for that client
    uint32 playerNo;
    uint64 userId;         //uint8 testVar[8];   //User id
    uint32 trash;
    uint64 checkId;        //uint8 checkVar[8];  //Encrypted testVar
    uint32 trash2;
} KeyCheck;

typedef struct _AttentionPing {
    _AttentionPing() {
    }
    _AttentionPing(_AttentionPing *ping) {
        cmd = ping->cmd;
        unk1 = ping->unk1;
        x = ping->x;
        y = ping->y;
        z = ping->z;
        unk2 = ping->unk2;
        type = ping->type;
    }

    uint8 cmd;
    uint32 unk1;
    float x;
    float y;
    float z;
    uint32 unk2;
    uint8 type;
} AttentionPing;

typedef struct _AttentionPingAns {
    _AttentionPingAns(AttentionPing *ping) {
        attentionPing = AttentionPing(ping);
        attentionPing.cmd = PKT_S2C_AttentionPing;
    }

    AttentionPing attentionPing;
    uint32 response;
} AttentionPingAns;

struct CameraLock {
    PacketHeader header;
    uint8 isLock;
    uint32 padding;
};

typedef struct _ViewReq {
    uint8 cmd;
    uint32 unk1;
    float x;
    float zoom;
    float y;
    float y2;		//Unk
    uint32 width;	//Unk
    uint32 height;	//Unk
    uint32 unk2;	//Unk
    uint8 requestNo;
} ViewReq;

struct CastSpell {
    PacketHeader header;
    uint8 spellSlot;
    float x, y;
    float x2, y2;
    uint32 targetNetId; // If 0, use coordinates, else use target net id
};

/**
 * Change Target ??
 */
struct Unk {
   Unk(uint32 netId, float x, float y) : unk1(0x0F), unk2(1), unk3(1), x(x), unk4(0), y(y), targetNetId(0) {
      header.cmd = PKT_S2C_UNK;
      header.netId = netId;
   }

   PacketHeader header;
   uint8 unk1, unk2, unk3;

   float x, unk4, y;
   uint32 targetNetId;
};

struct MinionSpawn {
   
   MinionSpawn(uint32 netId) : netId(netId), netId2(netId), netId3(netId), unk(0x00150017), unk2(0x03), unk3(0x53b83640), unk4(0xff), unk5_1(1), type(2), unk5_3(0), unk5_4(0), unk7(5), unk8(0x0ff84540f546f424) {
      header.cmd = PKT_S2C_MinionSpawn;
      header.netId = netId;
      memcpy(unk6, "\x0a\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x3f\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x2c\x27\x00\x00\x06", 36);
   }

   PacketHeader header;
   
   uint32 unk;
   uint8 unk2;
   uint32 netId, netId2;
   uint32 unk3;
   uint8 unk4;
   uint8 unk5_1;
   uint8 type; // 0 - Melee minion, 1 - Caster minion, 2 - Cannon minion
   uint8 unk5_3;
   uint8 unk5_4;
   uint8 unk6[36];
   uint32 netId3;
   uint8 unk7;
   uint64 unk8;
};

struct MovementVector {
    short x;
    short y;
    MovementVector() {
        x = 0;
        y = 0;
    }
    MovementVector(uint16 x, uint16 y) {
        this->x = x;
        this->y = y;
    }
};

struct MovementReq {
    PacketHeader header;
    MoveType type;
    float x;
    float y;
    uint32 zero;
    uint8 vectorNo;
    uint32 netId;
    uint8 moveData;
};

struct MovementAns {
    MovementAns() {
        header.cmd = PKT_S2C_MoveAns;
    }

    GameHeader header;
    uint16 ok;
    uint8 vectorNo;
    uint32 netId;
    uint8 moveData; //bitMasks + Move Vectors

    MovementVector *getVector(uint32 index) {
        if(index >= vectorNo / 2)
        { return NULL; }
        MovementVector *vPoints = (MovementVector *)(&moveData + maskCount());
        return &vPoints[index];
    }

    int maskCount() {
        float fVal = vectorNo / 2;
        return std::ceil((fVal - 1) / 4);
    }

    static uint32 size(uint8 vectorNo) {
        float fVectors = vectorNo;
        int maskCount = std::ceil((fVectors - 1) / 4);
        return sizeof(MovementAns) + (vectorNo * sizeof(MovementVector)) + maskCount; //-1 since struct already has first moveData byte
    }

    uint32 size() {
        return size(vectorNo / 2);
    }

    static MovementAns *create(uint32 vectorNo) {
        int nSize = size(vectorNo / 2);
        MovementAns *packet = (MovementAns *)new uint8[nSize];
        memset(packet, 0, nSize);
        packet->header.cmd = PKT_S2C_MoveAns;
        packet->header.ticks = clock();
        packet->vectorNo = vectorNo;
        return packet;
    }

    static void destroy(MovementAns *packet) {
        delete [](uint8 *)packet;
    }

};

typedef struct _ViewAns {
    _ViewAns() {
        cmd = PKT_S2C_ViewAns;
        unk1 = 0;
    }

    uint8 cmd;
    uint32 unk1;
    uint8 requestNo;
} ViewAns;


typedef struct _QueryStatus {
    _QueryStatus() {
        header.cmd = PKT_S2C_QueryStatusAns;
        ok = 1;
    }
    PacketHeader header;
    uint8 ok;
} QueryStatus;

typedef struct _SynchVersion {
    PacketHeader header;
    uint32 unk1;
    uint32 unk2;
    uint8 version[50]; //Dunno how big and when usefull data begins
} SynchVersion;

typedef struct _WorldSendGameNumber {
    _WorldSendGameNumber() {
        header.cmd = PKT_World_SendGameNumber;
        memset(data, 0, sizeof(data1));
        memset(data, 0, sizeof(data));
        gameId = 0;
    }

    PacketHeader header;
    uint64 gameId; //_0x0000
    uint8 server[5]; //0x0008
    uint8 data1[27]; //0x000D
    uint8 data[0x80];//0x0028
} WorldSendGameNumber;


struct CharacterStats {

   CharacterStats(uint8 masterMask, uint32 netId, uint32 mask, float value) : updateNo(1), masterMask(masterMask), netId(netId), mask(mask), size(4) {
      header.cmd = (GameCmd)PKT_S2C_CharStats;
      header.ticks = clock();
      this->value.fValue = value;
   }
   
   CharacterStats(uint8 masterMask, uint32 netId, uint32 mask, unsigned short value) : updateNo(1), masterMask(masterMask), netId(netId), mask(mask), size(2) {
      header.cmd = (GameCmd)PKT_S2C_CharStats;
      header.ticks = clock();
      this->value.sValue = value;
   }

   GameHeader header;
   uint8 updateNo;
   uint8 masterMask;
   uint32 netId;
   uint32 mask;
   uint8 size;
   union {
      unsigned short sValue;
      float fValue;
   } value;
};

struct ChatMessage {
    uint8 cmd;
    uint32 netId;
    uint32 unk1;
    uint8 unk2;

    uint32 playerNo;
    ChatType type;
    uint32 lenght;
    uint8 unk3[32];
    int8 msg;

    int8 *getMessage() {
        return &msg;
    }
};

typedef struct _UpdateModel {
    _UpdateModel(uint32 netID, const char *szModel) {
        memset(this, 0, sizeof(_UpdateModel));
        header.cmd = (PacketCmd)0x97;
        header.netId = netID;
        id = netID & ~0x40000000;
        bOk = 1;
        unk1 = -1;
        strncpy((char *)szName, szModel, 32);
    }
    PacketHeader header;
    uint32 id;
    uint8 bOk;
    uint32 unk1;
    uint8 szName[32];
} UpdateModel;
typedef struct _StatePacket {
    _StatePacket(PacketCmd state) {
        header.cmd = state;
    }
    PacketHeader header;
} StatePacket;
typedef struct _StatePacket2 {
    _StatePacket2(PacketCmd state) {
        header.cmd = state;
        nUnk = 0;
    }
    PacketHeader header;
    int16 nUnk;
} StatePacket2;

struct FogUpdate2 {
    FogUpdate2() {
        header.cmd = PKT_S2C_FogUpdate2;
        header.netId = 0x40000019;
    }
    PacketHeader header;
    float x;
    float y;
    uint32 radius;
    uint8 unk1;
};

struct HeroSpawn {
    HeroSpawn() {
        header.cmd = PKT_S2C_HeroSpawn;
        unk1 = 0;
        memset(&name, 0, 128 + 64); //Set name + type to zero
        x = 130880;
        y = 502;
    }

    PacketHeader header;
    uint32 netId; //Also found something about locking flag//Perhaps first 4 bits is type and rest is netId?? or something?? //Linked for mastery's (first uitn32, and also animation (looks like it) and possible more) often looks like XX 00 00 40 where XX is around 10-30
    uint32 gameId; //1-number of players
    uint32 x;       //Some coordinates, no idea how they work yet
    uint32 y;
    uint16 unk1;
    uint8 name[128];
    uint8 type[64];
} ;
struct HeroSpawn2 {
    HeroSpawn2() {
        header.cmd = (PacketCmd)0xBA;
        memset(unk, 0, 30);
        unk[15] = 0x80;
        unk[16] = 0x3F;
        unk1 = 3;
        unk2 = 1;
        f1 = 0x420F9C78;
        f2 = 0x4388C6A5;
        f3 = 0x3F441B7D;
        f4 = 0x3F248DBB;
    }

    PacketHeader header;
    uint8 unk[30];
    uint8 unk1;
    uint32 unk2;
    uint32 f1;
    uint32 f2;
    uint32 f3;
    uint32 f4;
};
struct HeroSpawn3 {
    HeroSpawn3() {
        header.cmd = (PacketCmd)0xAE;
        unk = 0;
        health = 1337;
        maxHealth = 666;
    }

    PacketHeader header;
    uint16 unk;
    float health;
    float maxHealth;
};

struct TurretSpawn {
    TurretSpawn() {
        header.cmd = PKT_S2C_TurretSpawn;
        tID = 0;
        memset(&name, 0, 29 + 42); //Set name + type to zero
    }

    PacketHeader header;
    uint32 tID;
    uint8 name[28];
    uint8 type[42];
};
struct GameTimer {
    GameTimer(float fTime) {
        header.cmd = PKT_S2C_GameTimer;
        header.netId = 0;
        this->fTime = fTime;
    }
    PacketHeader header;
    float fTime;
};
struct GameTimerUpdate {
    GameTimerUpdate(float fTime) {
        header.cmd = PKT_S2C_GameTimerUpdate;
        header.netId = 0;
        this->fTime = fTime;
    }
    PacketHeader header;
    float fTime;
};
struct SpellSet {
    SpellSet(uint32 netID, uint32 _spellID, uint32 _level) {
        memset(this, 0, sizeof(SpellSet));
        header.cmd = PacketCmd(0x5A);
        header.netId = netID;
        spellID = _spellID;
        level = _level;
    }
    PacketHeader header;
    uint32 spellID;
    uint32 level;
};
class LevelPropSpawn {
    public:
        LevelPropSpawn() {
            header.cmd = PKT_S2C_LevelPropSpawn;
            netId = 0;
            memset(&unk, 0, 50 + 64 + 64); //Set name + type to zero
        }
        void SetProp(char *szName, char *szType) {
            header.cmd = PKT_S2C_LevelPropSpawn;
            netId = 0;
            x = 0;
            y = 0;
            memset(&unk, 0, 50);
            memset(&name, 0, 64);
            memset(&type, 0, 64);
            if(szName)
            { strcpy((char *)name, szName); }
            if(szType)
            { strcpy((char *)type, szType); }
        }
        PacketHeader header;
        uint32 netId;
        float x;
        float y;
        uint8 unk[50];
        uint8 name[64];
        uint8 type[64];
};

struct Announce {
    PacketHeader header;
    uint8 msg;
    uint64 unknown;
    uint32 mapNo;
};

typedef struct _SkillUpPacket {
    PacketHeader header;
    uint8 skill;
} SkillUpPacket;

typedef struct _SkillUpResponse {
    _SkillUpResponse() {
        header.cmd = PKT_S2C_SkillUp;
        skill = 0;
        level = 0;
        pointsLeft = 0;
    }
    PacketHeader header;
    uint8 skill;
    uint8 level; //?
    uint8 pointsLeft;

} SkillUpResponse;

typedef struct _BuyItemReq {
    PacketHeader header;
    uint32 id;
} BuyItemReq;

typedef struct _BuyItemAns {
    _BuyItemAns() {
        header.cmd = (PacketCmd)PKT_S2C_BuyItemAns;
        unk1 = 0;
        unk2 = 0;
        unk3 = 0;
    }
    PacketHeader header;
    uint16 itemId;
    uint16 unk1;
    uint8 slotId;
    uint8 stack;
    uint16 unk2;
    uint8 unk3;
} BuyItemAns;

typedef struct _EmotionPacket {
    PacketHeader header;
    uint8 id;
} EmotionPacket;

typedef struct _EmotionResponse {
    _EmotionResponse() {
        header.cmd = PKT_S2C_Emotion;
    }
    PacketHeader header;
    uint8 id;
} EmotionResponse;
#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif

#endif