# toolchain configuration
CC ?= gcc
LD ?= ld
AR ?= ar
OBJCOPY ?= objcopy
OBJDUMP ?= objdump 

# compilation option configuration 
CFLAGS ?= -I. -I..
LDFLAGS ?= -L. 

# module file configuration
SRC = esi_rrserver.c
OBJ = $(patsubst %.c, %.o, $(SRC))
TARGET_NAME = esi_rrserver
TARGET_LIB = lib$(TARGET_NAME).a 

TEST_SRC = esi_rrserver_test.c esi_rrserver.c
TEST = esi_rrserver_test

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