OBJDIR=obj

CFLAGS=  -g -MMD -MP -Wall
CFLAGS+= -I.

CODEGEN_OBJ=$(foreach template, $(wildcard core/template/*.c), $(foreach item, $(wildcard item/*.c), $(OBJDIR)/codegen/$(item:item/%.c=%)_$(template:core/template/%.c=%).o))

SRC=$(wildcard core/*.c item/*.c)
OBJ=$(SRC:%.c=$(OBJDIR)/%.o) $(CODEGEN_OBJ)
LIB=uiw.a 
BIN=test
HEADER=uiw.h

all: test

clean:
	rm -rf $(OBJDIR)
	rm -rf $(LIB) $(BIN) $(HEADER)

test: $(OBJDIR)/test.o $(LIB)
	# create $@
	@cc $(CFLAGS) $^ -o $@ $(LDFLAGS)
	
$(HEADER):
	# create $@
	@cc $(CFLAGS) $(foreach i, $(wildcard item/*.c), -include $i) -E core/template/empty.h -o $@
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
$(OBJDIR)/codegen/%_$1.o: item/%.c core/template/$1.c
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
$(OBJDIR)/test.o: $(HEADER)
