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

/** 
 * @file 
 * @brief  Defines cwread_change_state_even_request function. 
 * 
 * Full text
 */

#include <stdio.h>

#include "capwap.h"
#include "cw_log.h"
#include "cw_util.h"

struct eparm {
	int * mand;
	uint32_t result_code;
	struct wtpinfo * wtpinfo;
};


static int readelem(void * eparm,int type,uint8_t* msgelem,int len)
{
	struct eparm * e = (struct eparm*)eparm;
	cw_dbg_msgelem(CWMSG_CHANGE_STATE_EVENT_REQUEST,type,msgelem,len);

	/* mandatory elements */
	if (cw_readelem_result_code(&e->result_code,type,msgelem,len))
		goto foundX;

	if (cw_readelem_radio_operational_state(e->wtpinfo->radioinfo,type,msgelem,len))
		goto foundX;

	return 0;

foundX:
	cw_mand_elem_found(e->mand,type);
	return 1;
}

/**
 * @brief Read elements of a Change State Event Request message.
 */
int cwread_change_state_event_request(struct wtpinfo * wtpinfo, uint8_t * msg, int len)
{
	int mand[] = {
		CWMSGELEM_RADIO_OPERATIONAL_STATE,
		CWMSGELEM_RESULT_CODE,
		-1};

	struct eparm eparm;
	eparm.wtpinfo = wtpinfo;
	eparm.mand=mand;

	cw_dbg(DBG_CW_MSGELEM,"Reading change state event request, len=%d",len);
	cw_foreach_msgelem(msg,len,readelem,&eparm);


	if (cw_is_missing_mand_elems(mand)){
		char str[512];
		cw_get_missing_mand_elems(str,mand);
		cw_dbg(DBG_CW_RFC, "Missing msgelems in change state event request: %s",str);
	}
	return eparm.result_code;
}

