UIW_LIB     ?=uiw.a
UIW_HEADER  ?=uiw.h
UIW_DIRS    ?=
UIW_INC_DIR ?=inc

OBJDIR      ?=obj

CFLAGS+= -g -MMD -MP -Wall
CFLAGS+= -I. 

UIW_FILES= $(foreach d, $(UIW_DIRS), $(wildcard $(d)/*.h))
UIW_CODEGEN_OBJ= \
	$(foreach f, $(UIW_FILES) \
		,$(foreach template, $(wildcard core/template/*.c) \
			,$(OBJDIR)/codegen/$(f:%.h=%)_$(template:core/template/%.c=%).o))

UIW_SRC=  $(wildcard core/*.c core/combine_template/*.c)
UIW_SRC+= $(foreach d, $(UIW_DIRS), $(wildcard $(d)/*.c))
UIW_OBJ=  $(UIW_SRC:%.c=$(OBJDIR)/%.o) $(UIW_CODEGEN_OBJ)

.PHONY: build-all build-clean

uiw-all: $(UIW_HEADER) $(UIW_LIB)

uiw-clean:
	rm -rf $(OBJDIR)
	rm -rf $(UIW_LIB) $(UIW_HEADER)

$(UIW_HEADER): $(UIW_SRC)
	# create $@
	@cc $(CFLAGS) $(foreach i, $(UIW_FILES), -include $i) -E core/empty.c -o $@
	@mkdir -p $(OBJDIR)
	@sed 's/empty.o/$@/g' -i $(@:%.h=%.d)
	@mv $(@:%.h=%.d) $(OBJDIR)/
	@tools/code_compose $@

$(UIW_LIB): $(UIW_OBJ)
	# update $@
	@ar cr $@ $^
	
$(OBJDIR)/core/combine_template/%.o: core/combine_template/%.c $(UIW_HEADER)
	# create $@
	@mkdir -p $(@D)
	@cc $(CFLAGS) -D_UIW_TYPEDEF_H \
		-include $(UIW_HEADER) \
		-include $< \
		$(foreach i, $(UIW_FILES), -include $i) \
		-c core/empty.c -o $@

define codegen
$(OBJDIR)/codegen/%_$1.o: %.c core/template/$1.c
	# create $$@
	@mkdir -p $$(@D)
	@cc $(CFLAGS) -D_UIW_TYPEDEF_H \
		-include $(UIW_HEADER) \
		-include core/template/$1.c \
		-c $$< -o $$@
endef # codegen
$(foreach template, $(wildcard core/template/*.c), $(eval $(call codegen,$(template:core/template/%.c=%))))

$(OBJDIR)/%.o: %.c
	# create $@
	@mkdir -p $(@D)
	@cc $(CFLAGS) -c $< -o $@

-include $(shell [ -d $(OBJDIR) ] &&find $(OBJDIR) -name '*.d')