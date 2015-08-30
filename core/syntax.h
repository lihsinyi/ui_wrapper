// could be mutiple included in a file

#define _IMP_H /* prevent imp.h warking in syntax.c */
#include "default.h"
#include "syntax.c"

/***** clean macros *****/
#ifdef DEC_TYPE
#undef DEC_TYPE
#endif

#ifdef CONFIG_ARRAY
#undef CONFIG_ARRAY
#endif

#ifdef KEY
#undef KEY
#endif

#ifdef DEC_FIELD
#undef DEC_FIELD
#endif

#ifdef DEC_FIELD_NUM
#undef DEC_FIELD_NUM
#endif

#ifdef DEC_FIELD_FMT_STR
#undef DEC_FIELD_FMT_STR
#endif

#ifdef TYPE_NUM
#undef TYPE_NUM
#endif

#ifdef DEC_TYPE_NUM
#undef DEC_TYPE_NUM
#endif