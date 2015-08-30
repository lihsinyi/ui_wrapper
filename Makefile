OBJDIR=obj

CFLAGS=-g -MMD -MP -Wall

SRC=$(wildcard core/*.c)
OBJ=$(SRC:%.c=$(OBJDIR)/%.o)
LIB=ulw.a
BIN=test


all: test

test: $(OBJDIR)/test.o $(LIB)
	# create $@
	@cc $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(LIB): $(OBJ)
	# create $@
	@ar cr $@ $^

${OBJDIR}/%.o: %.c
	# create $@
	@mkdir -p $(@D)
	@cc $(CFLAGS) -c $< -o $@

-include $(shell find $(OBJDIR) -name '*.d')
