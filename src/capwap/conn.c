/*
    This file is part of libcapwap.

    libcapwap is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libcapwap is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "cw_log.h"
#include "conn.h"
#include "sock.h"
#include "capwap.h"


void conn_init(struct conn * conn)
{
	memset(conn,0,sizeof(struct conn));
	conn->retransmit_interval=CAPWAP_RETRANSMIT_INTERVAL;
	conn->max_retransmit=CAPWAP_MAX_RETRANSMIT;
	conn->wait_dtls=CAPWAP_WAIT_DTLS;
	conn->wait_join=CAPWAP_WAIT_JOIN;
}



/**
 * function
 * @retval 1 Success
 * @retval 0 failure, conslt errno for more details
 */
struct conn * conn_create(int sock, struct sockaddr * addr, int qsize)
{
	struct conn * conn; 
	conn = malloc(sizeof (struct conn));
	if (!conn)
		return NULL;

	conn_init(conn);

	conn->sock=sock;

	if (addr)
		sock_copyaddr(&conn->addr,addr);

//	printf("AF IN: %i\n",addr->sa_family);
//	char str[200] ;
//	sock_addrtostr((struct sockaddr*)&conn->addr,str,200);
//	printf("CONN CREATOR: %s\n",str);

	conn->fragman = fragman_create();
	if (conn->fragman==NULL){
		conn_destroy(conn);
		return NULL;
	}

	conn->qsize=qsize;
	if (qsize != 0){
		if (!(conn->q=malloc( sizeof(uint8_t *) * qsize))){
			conn_destroy(conn);
			return NULL;
		}
		conn->qrpos=-1;
		if (sem_init(&conn->q_sem,0,0)!=0){
			cw_log(LOG_ERR,"sem_init %s",strerror(errno));
			conn_destroy(conn);
			return NULL;
		};
		conn->recv_packet=conn_q_recv_packet;
	}
	else
		conn->recv_packet = conn_recv_packet;


	conn->last_seqnum_received=-1;
	conn->mtu=1500;

	conn->send_packet = conn_send_packet;

	conn->cur_packet=0;
	conn->recv_timeout=1;

	conn->seqnum=-1;
	conn->write = conn->send_packet;
	conn->read = conn->recv_packet;


	return conn;
}


