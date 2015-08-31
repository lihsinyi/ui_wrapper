#include "stdbool.h"

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
