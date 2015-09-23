#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <regex.h>

#define DEC_TYPE_STR(type, size, fmt) \
bool uiw_check_##type(type *val) \
{ \
    regex_t re; \
    int ret; \
    if(val == NULL) { \
    	return false; \
    } \
    if(strnlen(*val, size) >= size) \
    	return false; \
    ret = regcomp(&re, fmt, REG_EXTENDED|REG_NOSUB); \
    assert(ret == 0); \
    if(ret != 0){ \
        return false; \
    } \
    ret = regexec(&re, *val, (size_t) 0, NULL, 0); \
    regfree(&re); \
    return (ret == 0); \
}
