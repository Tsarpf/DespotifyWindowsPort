#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "../dirent/dirent.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "util.h"
#include "cache.h"
#include "../../DespotifyLib/DespotifyLib/deslib/despotify.h"
#include "../../DespotifyLib/DespotifyLib/deslib/despotify-simple.h"
#include "../../DespotifyLib/DespotifyLib/deslib/session.h"

//#include <stdio.h>
//#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
int main()
{
	SESSION* ses = session_init_client();
	return 0;
}