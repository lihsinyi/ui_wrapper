#!/bin/bash
for UIW_DIR in $*; do
UIW_DIR=${UIW_DIR%/}

# get all used
DEFS='-DDEC_TYPE(type,fields)=fields -DFIELD(type,name)=type'
TYPES="`cat $UIW_DIR/*.h |
        grep -v include |
        gcc -I. -D_UIW_TYPEDEF_H $DEFS -include core/uiw_typedef.h -c -E -P -x c - -o -`"
USED="`for i in $TYPES; do echo $i ; done | sort | uniq`"

# get all declared
DEFS=
DEFS="$DEFS -DDEC_TYPE(type,...)=type"
DEFS="$DEFS -DDEC_TYPE_NUM(type,...)=type"
DEFS="$DEFS -DDEC_TYPE_STR(type,...)=type"
DEFS="$DEFS -DDEC_TYPE_ENUM(type,...)=type"
DEFS="$DEFS -DDEC_TYPE_ENUM_VALUE(type,...)=type"
TYPES="`cat $UIW_DIR/*.h |
        grep -v include |
        gcc -I. -D_UIW_TYPEDEF_H $DEFS -c -E -P -x c - -o -`"
DEFINED="`for i in $TYPES; do echo $i ; done | sort | uniq`"

# get not declared
for i in $USED; do
	if [[ $DEFINED != *"$i"* ]]; then
		TO_GEN="$TO_GEN $i"
	fi
done

# gen code
if [ ! -z "$TO_GEN" ]; then
	echo "#include <stdbool.h>"
	echo "bool uiw_ret_true(void *val) { return true; }"
	for i in $TO_GEN; do
		echo "bool uiw_check_$i(void*) __attribute__ ((weak, alias (\"uiw_ret_true\")));"
	done
fi

done