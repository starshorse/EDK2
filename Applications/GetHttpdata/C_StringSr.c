#include <stdio.h>
#include <string.h>

char *timedata = "Today is 2018-02-01<br>The time is 01:34:50pm";
char Tmp[5] ;

int main( int argc , char *argv[]){
    char *cur_p = NULL;
    int i, year, month, day, hour, minute, second;
/*
    Retrive  Date Information
*/
    memset( Tmp , 0, 5 );
    cur_p = strstr( timedata, "Today is ");
    cur_p += 9;
    for(i=0;i<4;i++){
        Tmp[i] = *cur_p++;
    }
    year = atoi(Tmp);
    printf("Year: %d\n", year);
    memset( Tmp , 0, 5 );
    cur_p++;      /*  Skip "-"  */
    for(i=0;i<2;i++){
        Tmp[i] = *cur_p++;
    }
    month = atoi(Tmp);
    printf("Month: %d\n", month);
    memset( Tmp , 0, 5 );
    cur_p++;      /*  Skip "-"  */
    for(i=0;i<2;i++){
        Tmp[i] = *cur_p++;
    }
    day = atoi(Tmp);
    printf("Day: %d\n", day);
/*
    Retrive  Time Information
*/
    memset( Tmp , 0, 5 );
    cur_p = strstr( timedata, "time is ");
    cur_p += 8;
    for(i=0;i<2;i++){
        Tmp[i] = *cur_p++;
    }
    hour = atoi(Tmp);
    printf("Hour: %d\n", hour);
    memset( Tmp , 0, 5 );
    cur_p++;      /*  Skip ":"  */
    for(i=0;i<2;i++){
        Tmp[i] = *cur_p++;
    }
    minute = atoi(Tmp);
    printf("Minute: %d\n", minute);
    memset( Tmp , 0, 5 );
    cur_p++;      /*  Skip ":"  */
    for(i=0;i<2;i++){
        Tmp[i] = *cur_p++;
    }
    second = atoi(Tmp);
    printf("Second: %d", second);

}
