#ifndef _TYPEDEF_H
#define _TYPEDEF_H

#include "ret.h"

#define DEC_TYPE_NUM(new_type, old_type, min, max) \
typedef old_type new_type;

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
} cfg##_t;

#endif /* typedef.h */