# toolchain configuration
CC ?= gcc
LD ?= ld
AR ?= ar
OBJCOPY ?= objcopy
OBJDUMP ?= objdump 

# compilation option configuration 
CFLAGS ?= -I. -I../esi_str 
LDFLAGS ?= -L. ../esi_str/libesi_str.a

# module file configuration
SRC = esi_err.c
OBJ = $(patsubst %.c, %.o, $(SRC))
TARGET_NAME = esi_err
TARGET_LIB = lib$(TARGET_NAME).a 

TEST_SRC = esi_err_test.c esi_err_test_launcher.c
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

test: $(TEST) $(TARGET_LIB)
	./$<
	
$(TEST): $(TEST_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@