#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <regex.h>

#define DEC_TYPE_STR(type, size, fmt) \
extern bool _uiw_check_##type(type *val) __attribute__((weak)); \
bool uiw_check_##type(type *val) \
{ \
    regex_t re; \
    int ret; \
    if(val == NULL || strnlen(*val, size) >= size) { \
    	return false; \
    } \
    ret = regcomp(&re, fmt, REG_EXTENDED|REG_NOSUB); \
    assert(ret == 0); \
    if(ret != 0){ \
        return false; \
    } \
    ret = regexec(&re, *val, (size_t) 0, NULL, 0); \
    regfree(&re); \
    if (ret != 0) { \
    	return false; \
    } \
    if(_uiw_check_##type && !_uiw_check_##type(val)) { \
    	return false; \
    } \
    return true; \
}
