/*
 * $Id: dns.c 425 2009-08-04 21:35:54Z noah-w $
 *
 */
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "network.h"
//#ifdef __use_winsock__
#include <windns.h>
//#elif defined __use_posix__
//#include <arpa/nameser.h>
//#include <arpa/nameser_compat.h>
//#include <resolv.h>
//#endif

#include "dns.h"

static int initialized;

/*
 * Return a string with all SRV records for a given hostname
 * Example: foo.example.net:42\nrazor.example.net:1911\n
 *
 */
char *dns_srv_list (char *hostname)
{
	char *svr_list = NULL;
    int i,j;
	char *svr[10];
	unsigned short svr_prio[10];
	unsigned short svr_port[10];
	int n_srv, lowest_prio;


	PDNS_RECORD pRoot = NULL, p;

	if (DnsQuery_A(hostname, DNS_TYPE_SRV, DNS_QUERY_STANDARD, NULL, &pRoot, NULL) != 0)
		return NULL;

	i = 0;
	for (p = pRoot; p != NULL && i < 10; p = p->pNext) {
		if(p->wType != DNS_TYPE_SRV)
			continue;

		svr[i] = _strdup (p->Data.SRV.pNameTarget);
		svr_prio[i] = p->Data.SRV.wPriority;
		svr_port[i++] = p->Data.SRV.wPort;
	}

	n_srv = i;
	DnsRecordListFree(pRoot, DnsFreeRecordListDeep);

    //#endif

	lowest_prio = 0;
	for (i = 0; i < n_srv; i++) {
		for (j = 0; j < n_srv; j++)
			if (svr_prio[lowest_prio] > svr_prio[j])
				lowest_prio = j;
		svr_list =
			realloc (svr_list, (svr_list ? strlen (svr_list) : 0)
				 + strlen (svr[lowest_prio]) + 6 + 2);
		if (!i)
			sprintf (svr_list, "%s:%05d\n", svr[lowest_prio],
				 svr_port[lowest_prio]);
		else
			sprintf (svr_list + strlen (svr_list), "%s:%d\n",
				 svr[lowest_prio], svr_port[lowest_prio]);

		svr_prio[lowest_prio] = (unsigned short) ~0;
		free (svr[lowest_prio]);
	}

	return svr_list;
}

/*
 * Return the IP adress of a hostname, in network byte order
 *
 */
in_addr_t dns_resolve_name (char *hostname)
{
	struct hostent *he;
	in_addr_t ip;
	

	if ((ip = inet_addr (hostname)) == INADDR_NONE) {
		if ((he = gethostbyname (hostname)) != NULL)
			memcpy (&ip, he->h_addr_list[0], 4);
	}

	return ip;
}
