#include  <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include  <Library/UefiRuntimeServicesTableLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <stdio.h>
//
int
main (
  IN int Argc,
  IN char **Argv
  )
{
    EFI_TIME cur_time;
    gRT->GetTime(&cur_time, NULL);
    printf("cur_time.Year: %d\n", cur_time.Year);       // 1998 – 20XX
    printf("cur_time.Month: %d\n", cur_time.Month);      // 1 – 12
    printf("cur_time.Day: %d\n", cur_time.Day);        // 1 – 31
    printf("cur_time.Hour: %d\n", cur_time.Hour);       // 0 – 23
    printf("cur_time.Minute: %d\n", cur_time.Minute);     // 0 – 59
    printf("cur_time.Second: %d\n", cur_time.Second);     // 0 – 59
    printf("cur_time.Pad1: %d\n", cur_time.Pad1);
    printf("cur_time.Nanosecond: %d\n", cur_time.Nanosecond); // 0 – 999,999,999
    printf("cur_time.TimeZone: %d\n", cur_time.TimeZone);   // -1440 to 1440 or 2047
    printf("cur_time.Daylight: %d\n", cur_time.Daylight);
    printf("cur_time.Pad2: %d\n", cur_time.Pad2);
    return 0;
}
