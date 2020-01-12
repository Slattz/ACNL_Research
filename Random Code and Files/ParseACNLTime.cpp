#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
	
typedef enum : s8
{
    WEEK_SUNDAY = 0,   ///< Sunday.
    WEEK_MONDAY,       ///< Monday.
    WEEK_TUESDAY,      ///< Tuesday.
    WEEK_WEDNESDAY,    ///< Wednesday.
    WEEK_THURSDAY,     ///< Thursday.
    WEEK_FRIDAY,       ///< Friday.
    WEEK_SATURDAY,     ///< Saturday.
    WEEK_MAX
} Week;

/*!
@brief Structure representing the date and time.
*/
typedef struct
{
    s32     year;         ///< Year.
    s8      month;        ///< Month.
    s8      day;          ///< Day.
    Week    week;         ///< Day of the week.
    s8      hour;         ///< Hour.
    s8      minute;       ///< Minute.
    s8      second;       ///< Seconds.
    s16     milliSecond;  ///< Milliseconds.
} DateTimeParameters;

int main()
{
    u8 bytes[] = {
        0xE3, 0x07, 0x00, 0x00, 0x03, 0x0D, 0x03, 0x12, 0x09, 0x17,
        0x24, 0x01
    };

    DateTimeParameters* DT = reinterpret_cast<DateTimeParameters*>(malloc(sizeof(DateTimeParameters)));
    memcpy(DT, bytes, sizeof(DateTimeParameters));

    printf("Year: %d\n", DT->year);
    printf("Month: %d\n", DT->month);
    printf("Day: %d\n", DT->day);
    printf("Week Day: %d\n", DT->week);
    printf("Hour: %d\n", DT->hour);
    printf("Minute: %d\n", DT->minute);
    printf("Second: %d\n", DT->second);
    printf("MilliSecond: %d\n", DT->milliSecond);
    printf("sizeof DateTimeParameters: %X\n", sizeof(DateTimeParameters));

    return 0;
}