#ifndef __H_INIBIN
#define __H_INIBIN

#include <map>
#include <string>
#include <stdio.h>

#include "MemoryReader.h"

union Value {
   uint8 charV;
   uint16 shortV;
   uint32 longV;
   float floatV;
   char stringV[128];
};

class Inibin {
public:
   Inibin(const std::vector<unsigned char>& file) : buffer(file) {
      uint8 version;
      uint16 oldLength;
      uint16 bitmask;
      
      buffer >> version >> oldLength >> bitmask;
      
      uint16 nbKeys;
      
      if(bitmask & 0x0001) {
         buffer >> nbKeys;
         readUint32Values(readKeys(nbKeys));
      }
      
      if(bitmask & 0x0002) {
         buffer >> nbKeys;
         readFloatValues(readKeys(nbKeys));
      }
      
      if(bitmask & 0x0004) {
         buffer >> nbKeys;
         readUint10Values(readKeys(nbKeys));
      }
      
      if(bitmask & 0x0008) {
         buffer >> nbKeys;
         readUint16Values(readKeys(nbKeys));
      }
      
      if(bitmask & 0x0010) {
         buffer >> nbKeys;
         readUint8Values(readKeys(nbKeys));
      }
   }
   
   std::vector<uint32> readKeys(uint8 nbKeys) {
      std::vector<uint32> toReturn;
      
      for(uint8 i = 0; i < nbKeys; ++i) {
         uint32 key;
         buffer >> key;
         toReturn.push_back(key);
      }
      
      return toReturn;
   }
   
   static uint32 getKeyHash(const std::string& sectionName, const std::string& varName) {
      uint32 hash = 0;
      
      for(char c : sectionName) {
         hash = tolower(c) + 65599 * hash;
      }

      hash = (65599 * hash + 42);
      for(char c : varName) {
         hash = tolower(c) + 65599 * hash;
      }

      return hash;
   }
   
   void readUint32Values(const std::vector<uint32>& keys) {
      for(uint32 key : keys) {
         Value value;
         buffer >> value.longV;
         printf("%08x : %u\n", key, value.longV);
         values[key] = value;
      }
   }
   
   void readUint16Values(const std::vector<uint32>& keys) {
      for(uint32 key : keys) {
         Value value;
         buffer >> value.shortV;
         printf("%08x : %u\n", key, value.shortV);
         values[key] = value;
      }
   }
   
   void readUint8Values(const std::vector<uint32>& keys) {
      for(uint32 key : keys) {
         Value value;
         buffer >> value.charV;
         printf("%08x : %u\n", key, value.charV);
         values[key] = value;
      }
   }
   
   void readUint10Values(const std::vector<uint32>& keys) {
      for(uint32 key : keys) {
         uint8 v;
         buffer >> v;
         Value value;
         value.floatV = v*0.1f;
         printf("%08x : %f\n", key, value.floatV);
         values[key] = value;
      }
   }
   
   void readFloatValues(const std::vector<uint32>& keys) {
      for(uint32 key : keys) {
         Value value;
         buffer >> value.floatV;
         printf("%08x : %f\n", key, value.floatV);
         values[key] = value;
      }
   }
   
   uint32 getUint32Value(const std::string& sectionName, const std::string& varName) {
      return values[getKeyHash(sectionName, varName)].longV;
   }
   
   uint16 getUint16Value(const std::string& sectionName, const std::string& varName) {
      return values[getKeyHash(sectionName, varName)].shortV;
   }
   
   uint8 getUint8Value(const std::string& sectionName, const std::string& varName) {
      return values[getKeyHash(sectionName, varName)].charV;
   }
   
   float getFloatValue(const std::string& sectionName, const std::string& varName) {
      return values[getKeyHash(sectionName, varName)].floatV;
   }

private:
   
   std::map<uint32, Value> values;
   MemoryReader buffer;


};




#endif