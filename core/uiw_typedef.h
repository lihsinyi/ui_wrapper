#ifndef _UIW_TYPEDEF_H
#define _UIW_TYPEDEF_H

#include <stdbool.h>
#include "core/uiw_ret.h"

#define DEC_TYPE_NUM(new_type, old_type, min, max) \
typedef old_type new_type; \
bool _uiw_check_type_##new_type(new_type val);

#define TYPE_NUM(type, min, max) type

#define DEC_FIELD(field, type) \
	type field;
	
#define DEC_FIELD_NUM(field, type, min, max) \
	type field;
	
#define DEC_FIELD_FMT_STR(field, size, fmt) \
	char field[size];

#define CONFIG_ARRAY(cfg, size, fields) \
typedef struct { \
	fields \
} cfg##_t; \
uiw_ret_t uiw_##cfg##_set(cfg##_t *val); \
bool uiw_##cfg##_check(cfg##_t *val);


#endif /* uiw_typedef.h */


/* default.h *

#ifndef DEC_TYPE_NUM
#define DEC_TYPE_NUM(new_type, old_type, min, max)
#endif

#ifndef CONFIG_ARRAY
#define CONFIG_ARRAY(cfg, size, fields)
#endif

#ifndef KEY
#define KEY
#endif

#ifndef DEC_FIELD
#define DEC_FIELD(field, type)
#endif

#ifndef DEC_FIELD_FMT_STR
#define DEC_FIELD_FMT_STR(field, size, fmt)
#endif

#ifndef DEC_FIELD_NUM
#define DEC_FIELD_NUM(field, type, min, max)
#endif