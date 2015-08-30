OBJDIR=obj

CFLAGS=  -g -MMD -MP -Wall
CFLAGS+= -Icore -Iitem

SRC=$(wildcard core/*.c item/*.c)
OBJ=$(SRC:%.c=$(OBJDIR)/%.o)
LIB=ulw.a
BIN=test


all: test

clean:
	rm -rf $(OBJDIR)
	rm -rf $(LIB) $(BIN)

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
