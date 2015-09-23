#include <stdio.h>
#include <string.h>

#define ENUM_VALUE(name, val) \
	case name: \
		return #name;

#define DEC_TYPE_ENUM_VALUE(type, list) \
char *uiw_enum2str_##type(type val) \
{ \
	switch(val){ \
		list \
		default: \
			return ""; \
	} \
}

#define DEC_TYPE_ENUM(type, ...) \
char *uiw_enum2str_##type(type val) \
{ \
	int i; \
	static char str[] = #__VA_ARGS__; \
	static char *name[uiw_##type##_cnt] = {NULL}; \
	if (!uiw_check_##type(&val)) { \
		return ""; \
	} \
	if (name[0] == NULL){ \
		name[0] = strtok(str, ", ");\
		for(i=1; i<uiw_##type##_cnt; i++){ \
			name[i] = strtok(NULL, ", "); \
		} \
	} \
	return name[val]; \
}
