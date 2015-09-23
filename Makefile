UIW_DIRS=testcase/uiw_api
UIW_LIB=testcase.a
UIW_HEADER=testcase.h
UIW_INC_DIR=testcase/inc
UIW_DIRS=testcase/uiw_api

SRC=$(wildcard testcase/prog/*.c)
BIN=$(SRC:%.c=%)

all: uiw-all $(BIN)

clean: uiw-clean
	rm -f $(BIN) $(BIN:%=%.d)
	
check: all 
	@for i in $(BIN); do echo "# testing $$i" ; $$i | diff $$i.ans - || exit 1; done
	# all passed

$(BIN):%:%.c
	# create $@
	@cc $(CFLAGS) $< $(UIW_LIB) -o $@ $(LDFLAGS)

include uiw.mk
-include $(wildcard testcase/prog/*.d)
