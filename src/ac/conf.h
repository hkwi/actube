/*
    This file is part of AC-Tube.

    AC-Tube is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AC-Tube is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __CONF_H
#define __CONF_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <confuse.h>
#include <sys/ioctl.h>
#include <net/if.h>


#include "capwap.h"
#include "lwapp.h"

#ifndef CONF_DEFAULT_ACNAME
	#define CONF_DEFAULT_ACNAME "AC"
#endif

#ifndef CONF_DEFAULT_MAXWTPS 
	#define CONF_DEFAULT_MAXWTPS 200
#endif

#ifndef CONF_DEFAULT_LOGFILENAME
	#define CONF_DEFAULT_LOGFILENAME NULL
#endif

#ifndef CONF_DEFAULT_CONFIGFILENAME
	#define CONF_DEFAULT_CONFIGFILENAME "ac.conf"
#endif

#ifndef CONF_DEFAULT_VENDOR_ID
	#define CONF_DEFAULT_VENDOR_ID CW_VENDOR_ID_FSF
#endif

#ifndef CONF_DEFAULT_SOFTWARE_VERSION
	#define CONF_DEFAULT_SOFTWARE_VERSION "AC-Tube 0.01"
#endif

#ifndef CONF_DEFAULT_HARDWARE_VERSION
	#define CONF_DEFAULT_HARDWARE_VERSION "Unknown"
#endif

#ifndef CONF_DEFAULT_CONTROL_PORT
	#define	CONF_DEFAULT_CONTROL_PORT CAPWAP_CONTROL_PORT
#endif

#ifndef CONF_DEFAULT_LW_CONTROL_PORT
	#define	CONF_DEFAULT_LW_CONTROL_PORT LWAPP_CONTROL_PORT
#endif


extern const char * conf_acname;
extern char * conf_acid;
extern int conf_acname_len;
extern long conf_max_wtps;
extern char * conf_logfilename;
extern struct sockaddr_storage * conf_salist;
extern int conf_salist_len;

extern long conf_vendor_id;
extern char * conf_hardware_version;
extern int conf_hardware_version_len;
extern char * conf_software_version;
extern int conf_software_version_len;



extern char ** conf_listen_addrs;
extern int conf_listen_addrs_len;

extern struct sockaddr * conf_ac_ips;
extern int conf_ac_ips_len;


extern int read_config(const char * filename);

extern char * conf_control_port;
#ifdef WITH_LWAPP
extern char * conf_lw_control_port;
extern int conf_lwapp;
#endif

extern char * conf_dtls_psk;
extern char * conf_sslcertfilename;
extern char * conf_sslkeyfilename;
extern char * conf_sslkeypass;
extern char * conf_dtls_psk;




extern char ** conf_mcast_groups;
extern int conf_mcast_groups_len;

extern char ** conf_bcast_addrs;
extern int conf_bcast_addrs_len;

extern long conf_debug_level;
extern uint8_t conf_macaddress[12];
extern uint8_t conf_macaddress_len;
extern int conf_dtls_verify_peer;

#endif
