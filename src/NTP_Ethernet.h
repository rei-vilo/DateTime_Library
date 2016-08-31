///
/// @file		NTP_Ethernet.h
/// @brief		Library header
/// @details	Get date and time from NTP server through Ethernet
/// @n
/// @n @b		Project DateTimeLibrary_v2
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
///
/// @date		Dec 22, 2015
/// @version	301
///
/// @copyright	(c) Rei Vilo, 2015-2016
/// @copyright	CC = BY NC SA
///
/// @see		ReadMe.txt for references
///


// Core library for code-sense - IDE-based
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(ROBOTIS) // Robotis specific
#include "libpandora_types.h"
#include "pandora.h"
#elif defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(LITTLEROBOTFRIENDS) // LittleRobotFriends specific
#include "LRF.h"
#elif defined(MICRODUINO) // Microduino specific
#include "Arduino.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(REDBEARLAB) // RedBearLab specific
#include "Arduino.h"
#elif defined(RFDUINO) // RFduino specific
#include "Arduino.h"
#elif defined(SPARK) // Spark specific
#include "application.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

#ifndef ETHERNET_NTP_RELEASE
///
/// @brief	Release
///
#define ETHERNET_NTP_RELEASE 301

#include <Ethernet.h>
#include <EthernetUdp.h>

///
/// @brief	NTP error codes
///
/// @{
#define GET_NTP_SUCCESS 0           ///< success
#define GET_NTP_NO_CONNECTION 1     ///< no connection
#define GET_NTP_DATA_ERROR 2        ///< wrong data received
#define GET_NTP_OTHER_ERROR 9       ///< other error
/// @}

///
/// @brief      Get date and time from NTP server
/// @param      epochNTP time in epoch format
/// @param      serverNTP IP address of the NTP server, default =
/// @return     0 is successful, error code otherwise
/// @note       epochNTP is updated only if successful.
/// @warning    A valid connection to Internet is required.
/// @note       Examples of NTP servers
/// * time.nist.gov   IPAddress(206,246,122,250)
/// * wwv.nist.gov    IPAddress(24,56,178,140)
/// * ntp-p1.obspm.fr IPAddress(145,238,203,14)
///
/// @code
///     time_t myEpoch;
///     result = getTimeNTP(myEpoch);
///     if (result == GET_NTP_SUCCESS) myDateTime.setTime(myEpoch);
/// @endcode
///
/// @n      Based on UDP NTP Client, provided with Energia 16
/// * Created 4 Sep 2010 by Michael Margolis
/// * Modified 9 Apr 2012 by Tom Igoe
/// * Modified 1 July 2014 by Noah Luskey
/// * Updated July 19, 2015 by Rei Vilo with RTC for CC3200, MSP432, TM4C123 and TM4C129
/// * Updated Dec 22, 2015 by Rei Vilo as separate libraries for WiFi and Ethernet
///
/// @see 	NTP time servers and messages
/// @n		http://en.wikipedia.org/wiki/Network_Time_Protocol
///
uint8_t getTimeNTP(time_t &epochNTP, IPAddress serverNTP = IPAddress(145, 238, 203, 14));

#endif
