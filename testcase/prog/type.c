#include <stdio.h>
#include "testcase.h"

int main()
{
	int i;
	
	ip_port_t ports[] = {-1, 0, 65535, 65536};
	ip4_str_t ip_str[] = {"0", "0.", "0.0", "127.0.0.1", "0.0.0.0", "0.0.0.300"};
	ip_protocol_t ip_prot[] = {IP_PROT_TCP, IP_PROT_UDP, IP_PROT_IP, 0, 6, 5, 100, -1};
	test_et test_e[] = {ITEM0, ITEM1, ITEM2, -1, 0, 1, 2, 3, 4};
	ip_msg_t msg[] = {
		{ .addr = "127.0.0.1", .port = 1000,  .protocol = IP_PROT_TCP, .test_e = ITEM2 },
		{ .addr = "300.0.0.1", .port = 1000,  .protocol = IP_PROT_TCP, .test_e = ITEM2 },
		{ .addr = "127.0.0.1", .port = 99999, .protocol = IP_PROT_TCP, .test_e = ITEM2 },
		{ .addr = "127.0.0.1", .port = 1000,  .protocol = 1,           .test_e = ITEM2 },
		{ .addr = "127.0.0.1", .port = 1000,  .protocol = IP_PROT_TCP, .test_e = 100   }
	};
	
	printf("check ip_port_t (DEC_TYPE_NUM)\n");
	for(i=0; i<(sizeof(ports)/sizeof(ports[0])); i++){
		printf("%d %d\n", ports[i], uiw_check_ip_port_t(&ports[i]));
	}
	printf("\n");
		
	printf("check ip4_str_t (DEC_TYPE_STR)\n");
	for(i=0; i<(sizeof(ip_str)/sizeof(ip_str[0])); i++){
		printf("%s %d\n", ip_str[i], uiw_check_ip4_str_t(&ip_str[i]));
	}
	printf("\n");
	
	printf("check ip_protocol_t (DEC_TYPE_ENUM_VALUE)\n");
	for(i=0; i<(sizeof(ip_prot)/sizeof(ip_prot[0])); i++){
		if (uiw_check_ip_protocol_t(&ip_prot[i])){
			printf("%d - %s\n", ip_prot[i], uiw_enum2str_ip_protocol_t(ip_prot[i]));
		}else{
			printf("%d - invalid\n", ip_prot[i]);
		}
	}
	printf("\n");
	
	printf("check test_et (DEC_TYPE_ENUM)\n");
	for(i=0; i<(sizeof(test_e)/sizeof(test_e[0])); i++){
		if (uiw_check_test_et(&test_e[i])){
			printf("%d - %s\n", test_e[i], uiw_enum2str_test_et(test_e[i]));
		}else{
			printf("%d - invalid\n", test_e[i]);
		}
	}
	printf("\n");
	
	printf("check ip_msg (DEC_TYPE)\n");
	for(i=0; i<(sizeof(msg)/sizeof(msg[0])); i++){
		if (uiw_check_ip_msg_t(&msg[i])){
			printf("valid\n");
		}else{
			printf("invalid\n");
		}
	}
		
	return 0;
}