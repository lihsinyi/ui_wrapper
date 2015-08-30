#include<stdio.h>
#include"snmp_trap.h"

int main()
{
	snmp_trap_t snmp = {
		.ip = 0x04030201,
		.port = 1234,
		.name = "server_1"
	};
	
	if(uiw_snmp_trap_set(&snmp) < 0){
		printf("failed");
	}
    return 0;
}