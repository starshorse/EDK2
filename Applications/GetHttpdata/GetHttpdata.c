/** @file
  GetHttpdata

  Copyright (c) 2011-2012, Intel Corporation
  All rights reserved. This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

// #include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Uefi.h>
#include <unistd.h>

#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include  <Library/UefiRuntimeServicesTableLib.h>
#include  <Library/UefiBootServicesTableLib.h>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024
int i, year, month, day, hour, minute, second;
int parse_string(char* timedata);
/**
  Receive a datagram

  @param [in] Argc  The number of arguments
  @param [in] Argv  The argument value array

  @retval  0        The application exited normally.
  @retval  Other    An error occurred.
**/
int
main (
  IN int Argc,
  IN char **Argv
  )
{
    EFI_TIME cur_time;
	char buffer[BUFFER_SIZE];
	int on = 1, sock;
	struct sockaddr_in addr;

    addr.sin_addr.s_addr = inet_addr("14.35.235.162") ;
	addr.sin_port = htons(80);
	addr.sin_family = AF_INET;
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));

	if(sock == -1){
		perror("setsockopt");
		exit(1);
	}
	if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
		perror("connect");
		exit(1);
	}
	write(sock, "GET / HTTP/1.0\r\nHost: 14.35.235.162\r\n\r\n\r\n", strlen("GET / HTTP/1.0\r\nHost: 14.35.235.162\r\n\r\n\r\n"));
//	bzero(buffer, BUFFER_SIZE);
    memset(buffer, 0,BUFFER_SIZE );

	while(read(sock, buffer, BUFFER_SIZE - 1) != 0){
		fprintf(stderr, "%s", buffer);
		parse_string(buffer);
//		bzero(buffer, BUFFER_SIZE);
         memset(buffer, 0,BUFFER_SIZE );
	}
	gRT->GetTime(&cur_time, NULL);
	printf("cur_time.Year: %d\n", cur_time.Year);       // 1998 – 20XX
    printf("cur_time.Month: %d\n", cur_time.Month);      // 1 – 12
    printf("cur_time.Day: %d\n", cur_time.Day);        // 1 – 31
    printf("cur_time.Hour: %d\n", cur_time.Hour);       // 0 – 23
    printf("cur_time.Minute: %d\n", cur_time.Minute);     // 0 – 59
    printf("cur_time.Second: %d\n", cur_time.Second);     // 0 – 59
/* Change to Current Date & Time  */
    cur_time.Year =(UINT16)year;
    cur_time.Month =(UINT8)month;
    cur_time.Day = (UINT8)day;
    cur_time.Hour = (UINT8)hour;
    cur_time.Minute = (UINT8)minute;
    cur_time.Second = (UINT8)second;
    printf("\n*** Now Set as Web Checked time \n");
    gRT->SetTime(&cur_time);

	shutdown(sock, SHUT_RDWR);
	close(sock);
	return 0;

}
int parse_string(char* timedata)
{
    char *cur_p = NULL;
    char Tmp[5] ;

/*
    Retrive  Date Information
*/
    printf("\n*======================================*\n");
    printf("\n*========Today Date & Time=============*\n");
    printf("\n*======================================*\n");
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
    return 0;
}
