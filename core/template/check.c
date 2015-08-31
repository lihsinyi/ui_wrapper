#include <stdbool.h>

#define TYPE_NUM(type, min, max) \
	type##_##min##_##max

#define DEC_FIELD(field, type) \
if (!_uiw_check_type_##type(val->field)) { \
	return false; \
}

#define DEC_FIELD_NUM(field, type, min, max) \
if ((val->field < min) || (val->field > max)) { \
	return false; \
}

bool _uiw_check_type_fmt_str(const char *val, int size, const char *fmt);
#define DEC_FIELD_FMT_STR(field, size, fmt) \
if (!_uiw_check_type_fmt_str(val->field, size, fmt)) { \
	return false; \
}

#define CONFIG_ARRAY(cfg, size, fields) \
bool _uiw_##cfg##_check(cfg##_t *val); \
bool uiw_##cfg##_check(cfg##_t *val) \
{ \
	fields \
	if (!_uiw_##cfg##_check(val)) { \
		return false; \
	} \
	return true; \
}
