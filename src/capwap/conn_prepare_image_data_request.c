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

#include "capwap.h"
#include "lwapp.h"

//#include "string.h"		//tube


int conn_prepare_image_data_request(struct conn *conn, struct image_data *data,
				    struct image_identifier *id)
{
	struct cwmsg *cwmsg = &conn->req_msg;
	cwmsg_init(cwmsg, conn->req_buffer, CWMSG_IMAGE_DATA_REQUEST, conn_get_next_seqnum(conn),
		   0);

	if (!data) 
		return 0;



	/* for Cisco APs send image data in "LWAPP format" */
	if (conn->capwap_mode == CWMODE_CISCO) {
		uint8_t type = 3;
		uint16_t checksum = htons(lw_checksum(data->data, data->len));
		cwmsg_vaddelem(cwmsg, CWMSGELEM_IMAGE_DATA, 3,
			       &type, 1, &checksum, 2, data->data, data->len);
		return 0;
	}


	/* standard capwap operation */

	cwmsg_vaddelem(cwmsg,CWMSGELEM_IMAGE_DATA, 2,
		&data->type, sizeof(data->type),
		data->data, data->len
	);


	return 0;
}
