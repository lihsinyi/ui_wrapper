#include <stdbool.h>

#define DEC_TYPE_NUM(new_type, old_type, min, max) \
bool _uiw_check_type_##new_type(new_type val) { \
	return (val >= min) && (val <= max); \
}
