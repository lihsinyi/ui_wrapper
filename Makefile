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

SRC=$(wildcard core/*.c core/combine_template/*.c) $(ALL_ITEM)
OBJ=$(SRC:%.c=$(OBJDIR)/%.o) $(CODEGEN_OBJ)
LIB=uiw.a 
HEADER=uiw.h

.PHONY: all clean

all: $(HEADER) $(LIB)
	make $(BIN)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(LIB) $(BIN) $(HEADER)

$(BIN):%:$(OBJDIR)/%.o obj/core/combine_template/type_check.o $(LIB)
	# create $@
	@cc $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(HEADER): $(SRC)
	# create $@
	@cc $(CFLAGS) $(foreach i, $(ALL_ITEM), -include $i) -E core/empty.c -o $@
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
	
$(OBJDIR)/core/combine_template/%.o: core/combine_template/%.c $(HEADER)
	# create $@
	@mkdir -p $(@D)
	@cc $(CFLAGS) -D_UIW_TYPEDEF_H \
		-include $(HEADER) \
		-include $< \
		$(foreach i, $(ALL_ITEM), -include $i) \
		-c core/empty.c -o $@

define codegen
$(OBJDIR)/codegen/%_$1.o: %.c core/template/$1.c
	# create $$@
	@mkdir -p $$(@D)
	@cc $(CFLAGS) -D_UIW_TYPEDEF_H \
		-include $(HEADER) \
		-include core/template/$1.c \
		-c $$< -o $$@
endef # codegen
$(foreach template, $(wildcard core/template/*.c), $(eval $(call codegen,$(template:core/template/%.c=%))))

$(OBJDIR)/%.o: %.c
	# create $@
	@mkdir -p $(@D)
	@cc $(CFLAGS) -DIMP_HANDLER -c $< -o $@


-include $(shell [ -d $(OBJDIR) ] &&find $(OBJDIR) -name '*.d')