#ifndef _UIW_TYPEDEF_H
#define _UIW_TYPEDEF_H

#include <stdbool.h>
#include "core/uiw_ret.h"

#define DEC_TYPE_NUM(type , base_type, min, max) \
typedef base_type type ; \
inline static bool uiw_check_##type(type *val) \
{ \
	return (val && *val >= min && *val <= max);\
}

#define DEC_TYPE_STR(type, size, fmt) \
typedef char type[size]; \
bool uiw_check_##type(type *val);

#define ENUM_VALUE(name, val) name = val,
#define DEC_TYPE_ENUM_VALUE(type, list) \
typedef enum { list } type; \
char *uiw_enum2str_##type(type val); \
bool uiw_check_##type(type *val);

#define DEC_TYPE_ENUM(type, ...) \
typedef enum { __VA_ARGS__, uiw_##type##_cnt } type; \
char *uiw_enum2str_##type(type val); \
inline static bool uiw_check_##type(type *val) \
{ \
	return (val && *val >= 0 && *val < uiw_##type##_cnt);\
}


/* prototype */

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


/* default.h */

#ifndef DEC_TYPE_NUM
#define DEC_TYPE_NUM(type, base_type, min, max)
#endif

#ifndef DEC_TYPE_STR
#define DEC_TYPE_STR(type, size, fmt)
#endif

#ifndef DEC_TYPE_ENUM_VALUE
#define DEC_TYPE_ENUM_VALUE(type, list)
#endif

#ifndef ENUM_VALUE
#define ENUM_VALUE(name, val)
#endif

#ifndef DEC_TYPE_ENUM
#define DEC_TYPE_ENUM(type, ...)
#endif


/* prototype */

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