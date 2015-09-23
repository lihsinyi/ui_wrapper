#include <stdio.h>
#include <stdbool.h>

#define ENUM_VALUE(name, val) case name:

#define DEC_TYPE_ENUM_VALUE(type, list) \
bool uiw_check_##type(type *val) \
{ \
	if (val == NULL) {\
		return false; \
	} \
	switch(*val){ \
		list \
			return true; \
	} \
	return false; \
}
