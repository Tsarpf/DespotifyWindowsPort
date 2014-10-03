/*
 * $Id: network.c 399 2009-07-29 11:50:46Z noah-w $
 *
 * Cross platform networking for despotify
 *
 */
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdlib.h>
//#include <unistd.h>
#include <io.h>

#include "network.h"
 
int network_init (void)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1,1), &wsaData) != 0) {
		fprintf (stderr, "Winsock failed. \n");
		return -1;
	}
	return 0;
}
int network_cleanup (void)
{
	#ifdef __use_winsock__
	return WSACleanup();
	#endif
	return 0;
}
