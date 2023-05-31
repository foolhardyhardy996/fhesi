# toolchain configuration
CC ?= gcc
LD ?= ld
AR ?= ar
OBJCOPY ?= objcopy
OBJDUMP ?= objdump 

# compilation option configuration 
CFLAGS ?= -I.
LDFLAGS ?= -L.

# module file configuration
SRC = memmove.c	strcmp.c strncpy.c	strstr.c memset.c strcpy.c strnlen.c \
strtok.c memchr.c strcat.c strcspn.c strnstr.c memcmp.c	strchr.c strlen.c \
strpbrk.c memcpy.c strchrnul.c strncat.c strrchr.c memmem.c strncmp.c strspn.c
OBJ = $(patsubst %.c, %.o, $(SRC))
TARGET_NAME = esi_str
TARGET_LIB = lib$(TARGET_NAME).a 

TEST_SRC = esi_str_test.c
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