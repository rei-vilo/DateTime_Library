///
/// @mainpage	MSP432_RTC
///
/// @details	RePaper test with MSP432
/// @n
/// @n
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
/// @date		19/07/2015 15:12
/// @version	403
///
/// @copyright	(c) Rei Vilo, 2015
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
///


///
/// @file		MSP432_RTC.ino
/// @brief		Main sketch
///
/// @details	RTC example
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
/// @date		19/07/2015 15:12
/// @version	403
///
/// @copyright	(c) Rei Vilo, 2015
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
/// @n
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
#elif defined(SPARK) || defined(PARTICLE) // Particle / Spark specific
#include "application.h"
#elif defined(ESP8266) // ESP8266 specific
#include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#   error Platform not defined
#endif // end IDE

// Include application, user and local libraries
// The time library provides all the tools.
// No need for reinventing them!
#include "time.h"
#define CEST 2*60*60

#include "RTC_Library.h"

// Prototypes

// Define variables and constants
time_t myEpochRTC;
tm myStructureRTC;

DateTime myRTC;


// Add setup code
void setup()
{
    Serial.begin(9600);
    delay(300);
    
    myRTC.begin();
    myRTC.setTimeZone(tz_CEST);
    
    // Date and time are local
    //
    // __DATE__ and __TIME__ are populated by Xcode during compilation
    String stampDateTime = String(__DATE__ " " __TIME__);
    
    // otherwise set
    // String stampDateTime = "Aug  3 2015 15:34:16";
    
    Serial.print("*** Date and time stamp = ");
    Serial.println(stampDateTime);
    
    
    if (convertString2DateTime(stampDateTime, "%b %d %Y %H:%M:%S", myEpochRTC))
    {
        myRTC.setLocalTime(myEpochRTC);
    }
    else
    {
        Serial.println("Error: wrong format.");
        
        // Fri, 31 Jul 2015 20:41:48 GMT
        myEpochRTC = 1438375308;
        Serial.print("Using default local time = ");
        Serial.println(convertDateTime2String(myEpochRTC));
        
        // Set time to RTC, only once
        myRTC.setLocalTime(myEpochRTC);
    }
    
    Serial.print("Set RTC = ");
    Serial.println(myEpochRTC, DEC);
    
    myEpochRTC = 0;
}

// Add loop code
void loop()
{
    myEpochRTC = myRTC.getTime();
    Serial.print("Get RTC  = ");
    Serial.println(myEpochRTC);
    
    convertEpoch2Structure(myEpochRTC, myStructureRTC);
    
    Serial.print("RTC = \t");
    Serial.print(convertDateTime2String(myEpochRTC));
    Serial.print("\r");
    
    
    // Local time zone
    myEpochRTC = myRTC.getLocalTime();
    Serial.print("Get CEST = ");
    Serial.println(myEpochRTC);
    
    convertEpoch2Structure(myEpochRTC, myStructureRTC);
    
    Serial.print("CEST = \t");
    Serial.print(convertDateTime2String(myEpochRTC));
    Serial.print("\r");
    
    
    // PDT time zone
    myEpochRTC = myRTC.getTime();
    Serial.print("Get GMT = ");
    Serial.println(myEpochRTC);
    myEpochRTC  += tz_PDT;
    Serial.println(tz_PDT);
    Serial.print("Get PDT = ");
    Serial.println(myEpochRTC);
    
    convertEpoch2Structure(myEpochRTC, myStructureRTC);
    
    Serial.print("PDT = \t");
    Serial.print(convertDateTime2String(myEpochRTC));
    Serial.print("\r");
    
    // Even more flexible output!
    // see http://www.cplusplus.com/reference/ctime/strftime/
    Serial.println(formatDateTime2String("Now it's %I:%M %p.", myStructureRTC));
    
    Serial.println();
    
    delay(5000);
}