# toolchain configuration
CC ?= gcc
LD ?= ld
AR ?= ar
OBJCOPY ?= objcopy
OBJDUMP ?= objdump 

# compilation option configuration 
CFLAGS ?= -I. -I..
LDFLAGS ?= -L. -L../esi_str -lesi_str

# module file configuration
SRC = esi_iointerface.c
OBJ = $(patsubst %.c, %.o, $(SRC))
TARGET_NAME = esi_iointerface
TARGET_LIB = lib$(TARGET_NAME).a 

TEST_SRC = esi_iointerface_test.c esi_iointerface.c
TEST = esi_iointerface_test

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

test: $(TEST) $(TARGET_LIB)
	./$<
	
$(TEST): $(TEST_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@