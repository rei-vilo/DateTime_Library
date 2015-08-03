///
/// @file		DateTimeLibrary.h
/// @brief		Library header
/// @details	RTC Date and Time Library for MSP432 and CC3200
/// @n	
/// @n @b		Project MSP432_RTC
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
/// 
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
///
/// @date		Jul 31, 2015
/// @version	103
/// 
/// @copyright	(c) Rei Vilo, 2015
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
/// @n          http://www.epochconverter.com
///


// Core library for code-sense - IDE-based
#include "Energia.h"

#ifndef DateTimeLibrary_h
#define DateTimeLibrary_h

#include "time.h"

#if defined(__MSP432P401R__)
#	include "rtc_c.h"
#elif defined(__CC3200R1M1RGC__)
#   include <driverlib/prcm.h>
#elif defined(__LM4F120H5QR__) || defined(__TM4C123GH6PM__) || defined(__TM4C129XNCZAD__)
// nothing, as TivaWare is already in ROM!
#else
#	error Platform not supported.
#endif


///
/// @brief      Scope for NTP
/// @details    1 to include NTP utility, 0 otherwise
///
#define INCLUDE_NTP 1

///
/// @brief      Predefined time zones
/// @details    Difference in seconds to GMT/CUT
/// @n          CET = 3600 = GMT + 1 hour
/// @{
///
#define tz_GMT  0          ///< Greenwich Mean Time
#define tz_CUT  0          ///< Coordinated Universal Time
#define tz_BST  1*60*60    ///< British Summer Time

#define tz_CET  1*60*60    ///< Central Europe Time
#define tz_CEST 2*60*60    ///< Central Europe Summer Time

#define tz_PST -8*60*60    ///< Pacific Standard Time
#define tz_PDT -7*60*60    ///< Pacific Daylight Time

#define tz_CST -6*60*60    ///< Central Standard Time
#define tz_PDT -5*60*60    ///< Central Daylight Time
/// @}

///
/// @brief      Class for RTC
/// @note       Tested on MSP432-EMT, CC3200, LM4F120, TM4C123, TM4C129
/// @bug        Compilation fails on CC3200-EMT
///
class DateTime
{
public:
    ///
    /// @brief	Constructor
    ///
    DateTime();

    ///
    /// @brief	Initialisation
    ///
    void begin();
    
    ///
    /// @brief	Get GMT date and time
    /// @return	epoch = number of seconds since Jan 1st, 1970, uint32_t or time_t
    ///
    uint32_t getTime();

    ///
    /// @brief	Get local date and time
    /// @return	epoch = number of seconds since Jan 1st, 1970, uint32_t or time_t
    /// @note   Set the time zone with setTimeZone()
    ///
    uint32_t getLocalTime();

    ///
    /// @brief	Set GMT date and time
    /// @param	timeEpoch time as epoch, number of seconds since Jan 1st, 1970
    ///
    void setTime(uint32_t timeEpoch);

    ///
    /// @brief	Set GMT date and time
    /// @param	timeStructure time as structure
    ///
    void setTime(tm timeStructure);
    
    ///
    /// @brief	Set time zone
    /// @param	timeZone difference in seconds between local time zone and GMT
    /// @note   Use pre-defined tz_CET, tz_CEST, tz_PST, tz_PDT, ...
    ///
    void setTimeZone(int32_t timeZone = tz_GMT);
    
    ///
    /// @brief	Set local date and time
    /// @param	timeEpoch time as epoch, number of seconds since Jan 1st, 1970
    /// @note   Set the time zone with setTimeZone()
    ///
    void setLocalTime(uint32_t timeEpoch);

    ///
    /// @brief	Set local date and time
    /// @param	timeStructure time as structure
    /// @note   Set the time zone with setTimeZone()
    ///
    void setLocalTime(tm timeStructure);

private:
    time_t  _epochRTC;
    tm      _structureRTC;
    int32_t _timeZoneDifference;
    
#if defined(__MSP432P401R__)
    RTC_C_Calendar _calendarMSP432;
#endif
};

///
/// @brief  Utilities
/// @{

/// @n  There are 2 representation for data and time.
/// * @b Epoch
/// @n POSIX time = number of seconds since 00:00 Jan 1st, 1979
/// * @b Structure
/// @n The MSP432 has its own not compatible structure!
/// MSP432 specific structure | Standard C structure
/// ---------------- | ----------------
/// struct _RTC_C_Calendar | struct tm
/// { | {
///   uint_fast8_t seconds; | int tm_sec;  // seconds after the minute [0-60]
///   uint_fast8_t minutes; | int tm_min;  // minutes after the hour [0-59]
///   uint_fast8_t hours; | int tm_hour;  // hours since midnight [0-23]
///   uint_fast8_t dayOfWeek; | (*)
///   uint_fast8_t dayOfmonth; | int tm_mday;  // day of the month [1-31]
///   uint_fast8_t month; | int tm_mon;  // months since January [0-11]
///   uint_fast16_t year; | int tm_year;  // years since 1900
///   (*) | int tm_wday;  // days since Sunday [0-6]
///   . | int tm_yday;  // days since January 1 [0-365]
///   . | int tm_isdst;  // Daylight Savings Time flag
///   . | long tm_gmtoff;  // offset from CUT in seconds
///   . | char *tm_zone;  // timezone abbreviation
/// }; | };
///

///
/// @brief	Convert epoch into structure
/// @param	timeEpoch time as epoch, input
/// @param	timeStructure time as structure, output
///
void convertEpoch2Structure(time_t timeEpoch, tm &timeStructure);

///
/// @brief	Convert structure into epoch
/// @param	timeStructure time as time structure, input
/// @param	timeEpoch time as epoch, output
///
void convertStructure2Epoch(tm timeStructure, time_t &timeEpoch);

///
/// @brief	Convert a string into date and time, epoch format
/// @param	stringDateTime date and time as string, input
/// @param	stringFormat string format, input, see below
/// @param	timeEpoch time as epoch, output
/// @return	true if success, false if error
///
bool convertString2DateTime(String stringDateTime, String stringFormat, time_t &timeEpoch);

///
/// @brief	Convert a string into date and time, strcuture format
/// @param	stringDateTime date and time as string, input
/// @param	stringFormat string format, input, see below
/// @param	timeStructure time as strcuture, output
/// @return	true if success, false if error
///
bool convertString2DateTime(String stringDateTime, String stringFormat, tm &timeStructure);


///
/// @brief	Standard format for date and time string
/// @param	timeStructure time as structure
/// @return	String
/// @note   Sun Jul 19 18:55:13 2015
///
String stringDateTime(tm timeStructure);

///
/// @brief	Standard format for date and time string
/// @param	timeEpoch time as epoch
/// @return	String
/// @note   Sun Jul 19 18:55:13 2015
///
String stringDateTime(time_t timeEpoch);

///
/// @brief	Custom format for date and time
/// @param	format see below
/// @param	timeStructure time as structure
/// @return	String
///
String stringFormatDateTime(const char * format, tm timeStructure);

///
/// @brief	Custom format for time
/// @param	format see below
/// @param	timeEpoch time as epoch
/// @return	String
///
String stringFormatDateTime(const char * format, time_t timeEpoch);

///
/// @brief	Format for date and time string
/// @note   Valid for stringFormatDateTime() and convertString2DateTime()
///
/// Specifier | Replaced by | Example
/// ---- | ---------------- | ----------------
/// %a | Abbreviated weekday name * | Thu
/// %A | Full weekday name * | Thursday
/// %b | Abbreviated month name * | Aug
/// %B | Full month name * | August
/// %c | Date and time representation * | Thu Aug 23 14:55:02 2001
/// %C | Year divided by 100 and truncated to integer (00-99) | 20
/// %d | Day of the month, zero-padded (01-31) | 23
/// %D | Short MM/DD/YY date, equivalent to %m/%d/%y | 08/23/01
/// %e | Day of the month, space-padded ( 1-31) | 23
/// %F | Short YYYY-MM-DD date, equivalent to %Y-%m-%d | 2001-08-23
/// %g | Week-based year, last two digits (00-99) | 01
/// %G | Week-based year | 2001
/// %h | Abbreviated month name * (same as %b) | Aug
/// %H | Hour in 24h format (00-23) | 14
/// %I | Hour in 12h format (01-12) | 02
/// %j | Day of the year (001-366) | 235
/// %m | Month as a decimal number (01-12) | 08
/// %M | Minute (00-59) | 55
/// %n | New-line character ('\n')
/// %p | AM or PM designation | PM
/// %r | 12-hour clock time * | 02:55:02 pm
/// %R | 24-hour HH:MM time, equivalent to %H:%M | 14:55
/// %S | Second (00-61) | 02
/// %t | Horizontal-tab character ('\t')
/// %T | ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S | 14:55:02
/// %u | ISO 8601 weekday as number with Monday as 1 (1-7) | 4
/// %U | Week number with the first Sunday as the first day of week one  (00-53) | 33
/// %V | ISO 8601 week number (00-53) | 34
/// %w | Weekday as a decimal number with Sunday as 0 (0-6) | 4
/// %W | Week number with the first Monday as the first day of week one (00-53) | 34
/// %x | Date representation * | 08/23/01
/// %X | Time representation * | 14:55:02
/// %y | Year, last two digits (00-99) | 01
/// %Y | Year | 2001
/// %z | ISO 8601 offset from UTC in timezone (1 minute=1, 1 hour=100)
/// | If timezone cannot be determined, no characters | +100
/// %Z | Timezone name or abbreviation *
/// | If timezone cannot be determined, no characters | CDT
/// %% | A % sign | %
/// @see    http://www.cplusplus.com/reference/ctime/strftime/
/// @}


#if (INCLUDE_NTP == 1)
#include "WiFi.h"

///
/// @brief      Get date and time from NTP server
/// @param      epochNTP time in epoch format
/// @param      serverNTP IP address of the NTP server, default =
/// @return     true is successful, false otherwise
/// @note       epochNTP is updated only if successful.
/// @warning    A valid connection to Internet is required.
/// @note       Examples of NTP servers
/// * time.nist.gov   IPAddress(206,246,122,250)
/// * wwv.nist.gov    IPAddress(24,56,178,140)
/// * ntp-p1.obspm.fr IPAddress(145,238,203,14)
///
/// @n      Based on UDP NTP Client, provided with Energia 16
/// * Created 4 Sep 2010 by Michael Margolis
/// * Modified 9 Apr 2012 by Tom Igoe
/// * Modified 1 July 2014 by Noah Luskey
/// * Updated July 19, 2015 by Rei Vilo with RTC for CC3200, MSP432, TM4C123 and TM4C129
///
/// @see 	NTP time servers and messages
/// @n		http://en.wikipedia.org/wiki/Network_Time_Protocol
///
bool getTimeNTP(time_t &epochNTP, IPAddress serverNTP = IPAddress(145,238,203,14));

#endif // NTP
#endif // header
