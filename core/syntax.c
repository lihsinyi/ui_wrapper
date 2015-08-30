#include <stdio.h>
#include <stdbool.h>
#include "imp.h"

DEC_TYPE_NUM(TYPE_IP4, int, 0, 0xffffffff)

CONFIG_ARRAY(snmp_trap, 6,
        KEY DEC_FIELD(ip, TYPE_IP4)
        KEY DEC_FIELD_NUM(port, int, 0, 65536)
        DEC_FIELD_FMT_STR(name, 16, "*")
)

#ifdef IMP_HANDLER

bool _uiw_snmp_trap_check(snmp_trap_t *val)
{
	return true;
}

bool _uiw_snmp_trap_set(snmp_trap_t *val)
{
	printf("hello\n");
	return true;
}

#endif // IMP_HANDLER