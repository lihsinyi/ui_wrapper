
#include "types.h"

CONFIG_ARRAY(snmp_trap2, 6,
        KEY DEC_FIELD(ip, TYPE_IP4)
        KEY DEC_FIELD_NUM(port, int, 0, 65536)
        DEC_FIELD_FMT_STR(name, 16, "*")
)

#ifdef IMP_HANDLER

#include <stdio.h>

bool _uiw_snmp_trap2_check(snmp_trap2_t *val)
{
	return true;
}

bool _uiw_snmp_trap2_set(snmp_trap2_t *val)
{
	printf("hello\n");
	return true;
}

#endif // IMP_HANDLER