OBJDIR =obj
 
CFLAGS=  -g -MMD -MP -Wall
CFLAGS += -I.

ITEM_DIRS=item
BIN=test

ALL_ITEM= $(foreach d, $(ITEM_DIRS), $(wildcard $(d)/*.c))
CODEGEN_OBJ= \
	$(foreach f, $(ALL_ITEM) \
		,$(foreach template, $(wildcard core/template/*.c) \
			,$(OBJDIR)/codegen/$(f:%.c=%)_$(template:core/template/%.c=%).o))

SRC=$(wildcard core/*.c) $(ALL_ITEM)
OBJ=$(SRC:%.c=$(OBJDIR)/%.o) $(CODEGEN_OBJ)
LIB=uiw.a 
HEADER=uiw.h

.PHONY: all clean _force

all: $(HEADER) $(LIB)
	make $(BIN)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(LIB) $(BIN) $(HEADER)

$(BIN):%:$(OBJDIR)/%.o $(LIB)
	# create $@
	@cc $(CFLAGS) $^ -o $@ $(LDFLAGS)
	
$(HEADER): _force
	# create $@
	@cc $(CFLAGS) $(foreach i, $(ALL_ITEM), -include $i) -E core/template/empty.h -o $@
	@mkdir -p $(OBJDIR)
	@sed 's/empty.o/$@/g' -i $(@:%.h=%.d)
	@mv $(@:%.h=%.d) $(OBJDIR)/
	@sed '/^$$/d' -i $@
	@sed '/^# .*$$/d' -i $@
	@sed 's/;/;\n/g' -i $@
	@sed 's/ {/\n{\n/g' -i $@
	
$(LIB): $(OBJ)
	# update $@
	@ar cr $@ $^
	
define codegen
$(OBJDIR)/codegen/%_$1.o: %.c core/template/$1.c
	# create $$@
	@mkdir -p $$(@D)
	@cc $(CFLAGS) \
		-include $$< \
		-include core/template/clean.h \
		-include core/template/$1.c \
		-c $$< -o $$@
endef # codegen
$(foreach template, $(wildcard core/template/*.c), $(eval $(call codegen,$(template:core/template/%.c=%))))

$(OBJDIR)/%.o: %.c
	# create $@
	@mkdir -p $(@D)
	@cc $(CFLAGS) -DIMP_HANDLER -c $< -o $@
	

-include $(shell [ -d $(OBJDIR) ] &&find $(OBJDIR) -name '*.d')