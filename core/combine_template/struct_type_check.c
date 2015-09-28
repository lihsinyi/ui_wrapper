#include <stdio.h>
#include <stdbool.h>

#define FIELD(type, field) \
{ \
	extern bool uiw_check_##type(type*); \
	if(!uiw_check_##type(&val->field)){ \
		return false; \
	} \
}

#define DEC_TYPE(type, fields) \
extern bool _uiw_check_##type(type *val) __attribute__((weak)); \
bool uiw_check_##type(type *val) \
{ \
	if(val == NULL) { \
		return false; \
	} \
	fields \
	if(_uiw_check_##type && !_uiw_check_##type(val)) { \
		return false; \
	} \
	return true; \
}
