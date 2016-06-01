//
// EthernetNTP.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode+
// http://embedXcode.weebly.com
//
// Project 		DateTimeLibrary_v2
//
// Created by 	ReiVilo, 25/09/2015 20:49
// 				ReiVilo
//
// Copyright 	(c) ReiVilo, 2015
// Licence		<#license#>
//
// See 			EthernetNTP.h and ReadMe.txt for references
//

#if defined(__TM4C129XNCZAD__)

// Library header
#include "NTP_Ethernet.h"

// Code
uint8_t getTimeNTP(time_t &epochNTP, IPAddress serverNTP)
{
    uint8_t result = GET_NTP_OTHER_ERROR;

    //    // Check WiFi connection
    //    if (WiFi.localIP() == INADDR_NONE)
    //    {
    //        //        if (Serial)
    //        //            Serial.println("ERROR No WiFi");
    //        return GET_NTP_NO_CONNECTION;
    //    }

    const uint16_t localPort = 2390;      // local port to listen for UDP packets
    const uint8_t NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
    uint8_t bufferNTP[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

    // A UDP instance to let us send and receive packets over UDP
    EthernetUDP myUDPforNTP;

    if (myUDPforNTP.begin(2390) == 0)
    {
        return GET_NTP_NO_CONNECTION;
    }

    // Send NTP packet to a time server
    memset(bufferNTP, 0, NTP_PACKET_SIZE);
    // Initialize values needed to form NTP request
    // see https://www.meinbergglobal.com/english/info/ntp-packet.htm
    bufferNTP[0] = 0b11100011;   // LI, Version, Mode
    bufferNTP[1] = 0;     // Stratum, or type of clock
    bufferNTP[2] = 6;     // Polling Interval
    bufferNTP[3] = 0xEC;  // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    bufferNTP[12]  = 49;
    bufferNTP[13]  = 0x4e;
    bufferNTP[14]  = 49;
    bufferNTP[15]  = 52;

    // all NTP fields have been given values, now
    // you can send a packet requesting a timestamp:
    myUDPforNTP.beginPacket(serverNTP, 123); // NTP requests are to port 123
    myUDPforNTP.write(bufferNTP, NTP_PACKET_SIZE);
    myUDPforNTP.endPacket();

    delay(1000);

    if (myUDPforNTP.parsePacket())
    {
        // Packet received, to be read
        myUDPforNTP.read(bufferNTP, NTP_PACKET_SIZE);

        // Timestamp starts at byte 40 of the received packet and is 4 bytes long.
        epochNTP   = bufferNTP[40];
        epochNTP <<= 8;
        epochNTP  |= bufferNTP[41];
        epochNTP <<= 8;
        epochNTP  |= bufferNTP[42];
        epochNTP <<= 8;
        epochNTP  |= bufferNTP[43];

        // Rebase to 00:00 Jan 1, 1970
        // epoch = number of seconds since 00:00, Jan 1st, 1970 UTC = POSIX time.
        // see http://www.epochconverter.com
        epochNTP -= (uint32_t)2208988800;
        result = GET_NTP_SUCCESS;
    }
    else
    {
        result = GET_NTP_DATA_ERROR;
    }

    myUDPforNTP.stop();

    // Failure
    return result;
}

