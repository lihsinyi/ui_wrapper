UIW_DIRS=testcase/uiw_api
UIW_LIB=testcase.a
UIW_HEADER=testcase.h
UIW_INC_DIR=testcase/inc
UIW_DIRS=testcase/uiw_api

SRC=$(wildcard testcase/prog/*.c)
BIN=$(SRC:%.c=%)

all: uiw-all $(BIN)

clean: uiw-clean
	rm -f $(BIN)

$(BIN):%:%.c
	# create $@
	@cc $(CFLAGS) $< $(LIB) -o $@ $(LDFLAGS)

include uiw.mk
