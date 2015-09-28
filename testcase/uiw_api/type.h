#include <stdint.h>
#include "core/uiw_typedef.h"

DEC_TYPE_NUM(ip_port_t, int, 0, 65535)

/* ipv4 format 12.234.56.78 */
DEC_TYPE_STR(ip4_str_t, 16, "^[12]?[0-9]{0,2}\\.[12]?[0-9]{0,2}\\.[12]?[0-9]{0,2}\\.[12]?[0-9]{0,2}$")

DEC_TYPE_ENUM_VALUE(ip_protocol_t,
	ENUM_VALUE(IP_PROT_TCP,6)
	ENUM_VALUE(IP_PROT_UDP,7)
	ENUM_VALUE(IP_PROT_IP, 4)
)

DEC_TYPE_ENUM(test_et, ITEM0,	  ITEM1, ITEM2)

DEC_TYPE(ip_msg_t,
	FIELD(ip4_str_t, addr)
	FIELD(ip_port_t, port)
	FIELD(ip_protocol_t, protocol)
	FIELD(test_et, test_e)
	FIELD(int, hi_thresh)
	FIELD(uint16_t, lo_thresh)
)
