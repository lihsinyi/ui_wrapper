#include "stdbool.h"

/***** type define *****/

#include "typedef.h"
#include "syntax.h"

/***** check type *****/

#define DEC_TYPE_NUM(new_type, old_type, min, max) \
inline bool _uiw_check_type_##new_type(new_type val) { \
	return (val >= min) && (val <= max); \
}

#include "syntax.h"

/***** check config *****/

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

#include "syntax.h"

/***** set *****/

#define DEC_FIELD(field, type)

#define CONFIG_ARRAY(cfg, size, fields) \
bool _uiw_##cfg##_set(cfg##_t *val); \
uiw_ret_t uiw_##cfg##_set(cfg##_t *val) \
{ \
	if (!uiw_##cfg##_check(val)) { \
	 return UIW_RET_INVALID_PARAM; \
	} \
	if (!_uiw_##cfg##_set(val)) { \
	 return UIW_RET_FAILED; \
	} \
	return UIW_RET_SUCCESS; \
}

#include "syntax.h"

