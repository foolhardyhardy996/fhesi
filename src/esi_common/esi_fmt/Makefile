# toolchain configuration
CC ?= gcc
LD ?= ld
AR ?= ar
OBJCOPY ?= objcopy
OBJDUMP ?= objdump 

# compilation option configuration 
# those feature disable flag is add for shrinking memory image and binary size
CFLAGS ?= -I. -DPRINTF_DISABLE_SUPPORT_FLOAT -DPRINTF_DISABLE_SUPPORT_EXPONENTIAL \
-DPRINTF_DISABLE_SUPPORT_LONG_LONG
LDFLAGS ?= -L.

# module file configuration
SRC = printf.c esi_fmt.c esi_putchar.c
OBJ = $(patsubst %.c, %.o, $(SRC))
TARGET_NAME = esi_fmt
TARGET_LIB = lib$(TARGET_NAME).a 

TEST_SRC = esi_fmt_test.c 
TEST = esi_str_test

# target configuration 
MAKE_TARGET = all clean debug test 
.PHONY: $(MAKE_TARGET)

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJ)
	$(AR) rcs $@ $^

clean: 
	rm -f $(OBJ) $(TARGET_LIB) $(TEST)

debug:
	echo toolchain: 
	echo CC = $(CC)
	echo LD = $(LD)
	echo AR = $(AR)
	echo OBJCOPY = $(OBJCOPY)
	echo OBJDUMP = $(OBJDUMP)
	echo module files:
	echo OBJ = $(OBJ)
	echo TARGET_LIB = $(TARGET_LIB)

test: $(TEST) 
	./$<
	
$(TEST): $(TARGET_LIB)
	$(CC) $(TEST_SRC) $^ -o $@