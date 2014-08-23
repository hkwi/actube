
#include "capwap.h"
#include "cwmsg.h"

void cwmsg_addelem_image_identifier(struct cwmsg *cwmsg,uint32_t vendor_id,uint8_t *img, int len)
{
	uint32_t net_vendor_id = htonl(vendor_id);
	cwmsg_vaddelem(cwmsg,CWMSGELEM_IMAGE_IDENTIFIER,2,&net_vendor_id,sizeof(net_vendor_id),img,len);
}

