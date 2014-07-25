/**
 * Parse a pcap(ng) file containing a raw dump of a LoL game
 * Decrypt and dump the packets in plaintext
 * Support enet overhead and fragments
 * Usage : pcapDecrypt <pcapFile> [b64key]
 * @author Elyotna
 * @date 18/07/2014
 */

#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#if defined(WIN32) || defined(_WIN32)
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include "win/platforms-time.h"
	#include "win/ip.h"
#else
	#include <netinet/ip.h>
	#include <arpa/inet.h>
#endif
#include <string.h>

#include "blowfish.h"
#include "base64.h"

#define B64_KEY "Z6zrBNmC42AhIC6UQR6KDg=="
//#define B64_KEY "3FAYg4Md9Qzl0O4qC7NZbQ=="
//#define B64_KEY "17BLOhi6KZsTtldTsizvHg=="
#define PACKET_FILE "packets.txt"

#define min(a, b)       ((a) < (b) ? (a) : (b))
#define FLAG_SAME_COMMAND 0x01 // If this is set, then there's another flag byte before the command, and the opCode is skipped
#define FLAG_UNK 0x02 // Seems related to netId

using namespace std;

void printPacket(unsigned char* buffer, unsigned int size) {

   unsigned int i;
   
   for(i = 0; i < size; ++i) {
      if(i != 0&& i%16 == 0) {
         for(unsigned int j = i-16; j < i; ++j) {
         
            if(buffer[j] >= 32 && buffer[j] <= 126)
               printf("%c", buffer[j]);
            else
               printf(".");
         }
         
         puts("");
      
      }
      
      if(i%16 == 0) {
         printf("%04d-%04d ", i, min(i+15, size-1));
      }

      printf("%02x ", buffer[i]);
   }
   
   for(i = ((16-i%16)%16); i > 0; --i)
      printf("   ");
   
   for(i = size- (size%16 == 0 ? 16 : size%16); i < size; ++i) {
      if(buffer[i] >= 32 && buffer[i] <= 126)
         printf("%c", buffer[i]);
      else
         printf(".");
   }
   
   puts("\n");
   for(i = 0; i < size; ++i) {
      printf("\\x%02x", buffer[i]);
   }
   puts("\n");
}

void dumpBatch(u_char* pkt_ptr) {

   int nbPackets = pkt_ptr[1];
   int firstPacketSize = pkt_ptr[2];
   pkt_ptr += 3;
   
   unsigned char previousCommand = pkt_ptr[0];
   
   printf("Packet 1 (100%% accurate)\n");
   printf("Length : %d\n", firstPacketSize);
   
   printPacket(pkt_ptr, firstPacketSize);
   pkt_ptr += firstPacketSize;
   

   for(int i = 2; i < nbPackets+1; ++i) {
      unsigned char flagsAndLength = pkt_ptr[0]; // 6 first bits = size (if not 0xFC), 2 last bits = flags
      unsigned char size = flagsAndLength >> 2;
      unsigned char additionalByte = pkt_ptr[1]; // Only preset if flagsAndLength & FLAG_UNK
      unsigned char command;
      unsigned char buffer[8192];
      
      ++pkt_ptr;
      
      if(flagsAndLength & FLAG_SAME_COMMAND) { // additionnal byte, skip command
         ++pkt_ptr;
         command = previousCommand;
      } else {
         command = pkt_ptr[0];
         ++pkt_ptr;
         if(flagsAndLength & FLAG_UNK) { // looks like when this is set, we keep the same netId, else we use a new one
            pkt_ptr += 1;
         } else {
            pkt_ptr += 4;
         }
      }
      
      if(size == 0x3F) { // size is too big to be on 6 bits, so instead it's stored later
         size = pkt_ptr[0];
         ++pkt_ptr;
      }
      
      printf("Packet %d (The start might be wrong, especially the netId (missing))\n", i);
      printf("Length : %d\n", size+1);
      
      buffer[0] = command;
      memcpy(buffer+1, pkt_ptr, size);
      
      printPacket(buffer, size+1);
      pkt_ptr += size;
      
      previousCommand = command;
   } 
}

//------------------------------------------------------------------- 
int main(int argc, char **argv) 
{
  struct pcap_pkthdr header; // The header that pcap gives us 
  const u_char *packet; // The actual packet 
  struct timeval startTime = {0, 0};
  
  //check command line arguments 
  if (argc < 2) { 
    fprintf(stderr, "Usage: %s <input pcap> [b64key]\n", argv[0]); 
    exit(1); 
  }
  
   string decryptedKey = base64_decode(argc == 3 ? argv[2] : B64_KEY);
   BlowFish b((unsigned char*)decryptedKey.c_str(), (size_t)decryptedKey.length());
 
    //----------------- 
    //open the pcap file 
    pcap_t *handle; 
    char errbuf[PCAP_ERRBUF_SIZE]; //not sure what to do with this, oh well 
    handle = pcap_open_offline(argv[1], errbuf);   //call pcap library function 

    if (handle == NULL) { 
      fprintf(stderr,"Couldn't open pcap file %s: %s\n", argv[1], errbuf); 
      return(2); 
    } 
 
    //----------------- 
    //begin processing the packets in this particular file, one at a time 
    u_char *pkt_ptr;
    int packet_length;
    
    u_char finalPacket[65536];
    int finalLength = 0;
 
    while (packet = pcap_next(handle,&header)) { 
      // header contains information about the packet (e.g. timestamp) 
      pkt_ptr = (u_char *)(packet+14); //cast a pointer to the packet data 
      
      if(startTime.tv_sec == 0 && startTime.tv_usec == 0) {
         startTime = header.ts;
      }
      
      //parse the IP header 
      struct ip *ip_hdr = (struct ip *)pkt_ptr; //point to an IP header structure 
      bool isFragment = false;
      
      unsigned char* ipSrc = &pkt_ptr[12];
      unsigned char* ipDst = &pkt_ptr[16];
 
      packet_length = ntohs(ip_hdr->ip_len)-20-8; 
      pkt_ptr += 20+8;
      
      char channel = pkt_ptr[5];
      
      // Right now pkt_ptr points to enet header start.
      
      if(pkt_ptr[1] < 0x80 && pkt_ptr[2] == 0x01) // this is an ACK. Don't care.
         continue;
      else if(pkt_ptr[1] >= 0x80 && pkt_ptr[4] == 0x85 || pkt_ptr[4] == 0x84 || pkt_ptr[4] == 0x83 || pkt_ptr[4] == 0x82 ) // Connect/disconnect/Ping. Don't care
         continue;
      else if(pkt_ptr[1] >= 0x80 && pkt_ptr[4] == 0x88) { // Fragment
         memcpy(finalPacket+finalLength, pkt_ptr+28, packet_length-28);
         finalLength += packet_length-28;
         unsigned int packetCount = ntohl(*((unsigned int*)&pkt_ptr[12]));
         unsigned int packetNumber = ntohl(*((unsigned int*)&pkt_ptr[16]));
         if(packetNumber != packetCount-1) {
            continue;
         }
         pkt_ptr = &finalPacket[0];
         isFragment = true;
      }
      else {
         finalLength = packet_length;
      }
      
      //printf("== New Packet ; Total Size = %d ==\n", packet_length);
      
      if(!isFragment) {
         if(pkt_ptr[1] >= 0x80) {
            pkt_ptr += 4;
            finalLength -= 4;
         } else  {
            pkt_ptr += 2;
            finalLength -= 2;
         }
      }
      
      while(finalLength > 0) {
         int commandLength;
         if(!isFragment) {
            int headerLength = 6;
      
            if(pkt_ptr[0] == 0x07 || pkt_ptr[0] == 0x49)
               headerLength = 8;
               
            channel = pkt_ptr[1];
      
            commandLength = ntohs(*((unsigned short*)(pkt_ptr+headerLength-2)));
            pkt_ptr += headerLength;
            finalLength -= headerLength;
         } else {
            commandLength = finalLength;
         }
         
         struct timeval result;
         timersub(&header.ts, &startTime, &result);
         
         printf("%ld.%06ld\n", result.tv_sec, result.tv_usec);
         printf("%d.%d.%d.%d -> %d.%d.%d.%d\n", ipSrc[0], ipSrc[1], ipSrc[2], ipSrc[3], ipDst[0], ipDst[1], ipDst[2], ipDst[3]);
         printf("Size : %d ; Channel : %d\n", commandLength, channel);
      
         b.Decrypt(pkt_ptr, commandLength);
         printPacket(pkt_ptr, commandLength);
         
         if(pkt_ptr[0] == 0xFF) { // Batch Packet
            puts("=== Attempting to parse batch packet ===");
            dumpBatch(pkt_ptr);
            puts("=== End of batch packet ===");
         }
         
         pkt_ptr += commandLength;
         finalLength -= commandLength;
         
      }
      
      finalLength = 0;
 
    }
 
    pcap_close(handle);

  return 0; 
}
