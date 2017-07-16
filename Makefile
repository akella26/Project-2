# _*_ MakeFile _*_
# Authors : Sowmya Akella and Sreela Pavani
# Date : June 25 2017
#
# This is a make file for executing project2
# Output executable that is generated after build is project.elf
# Use : make [targets] [overrides]
#
# List of Targets:
# <FILE>.o 
# <FILE>.i 
# <FILE>.s
# build - Builds and links all source files
# compile-all - Compiles all the object files
# clean - Removes all generated files

# Include all the source files 
include sources.mk

# Name of the final executable
#BASENAME = project2

# Name of the final executable with the required extension
#TARGET = $(BASENAME).elf
CPPFLAGS = -g 
#-g compiles with debug information, O0 - do not optimize the code, use C99 compiler, Wall - Give verbose compiler warnings
CFLAGS =  -Wall \
          -O0 \
          -std=c99 \
          -D PROJECT2 \
          -D PROJECT1 \
          -D VERBOSE 
# define the PLATFORM to be used          
ifeq ($(PLATFORM),BBB) 
	CC = arm-linux-gnueabihf-gcc
else ifeq ($(PLATFORM),KL25Z)
	CC = arm-none-eabi-gcc 
	INCLUDES = -I../include/common/ -I../include/kl25z/ -I../include/CMSIS/ -I../platform
	CFLAGS:=-mcpu=cortex-m0plus
	CFLAGS +=-mthumb -march=armv6-m
	CFLAGS+=-mfpu=fpv4-sp-d16 
	CFLAGS+=--specs=nosys.specs 
  # -mfloat-abi=​ ???
else
	CC = gcc
	INCLUDES = -I../include/common/ 
endif 

#
# build third-party libraries
#
SUBDIRS = 3rd-party

ifdef SUBDIRS
.PHONY : $(SUBDIRS)
$(SUBDIRS) : 
	@if [ -d $@ ]; then \
		$(MAKE) --no-print-directory --directory=$@ \
			CC=$(CC) CFLAGS="$(CFLAGS)" $(MAKECMDGOALS); \
	fi	
endif

THIRD_PARTY_DIR = 3rd-party
CMOCKA_INCLUDE_DIR = $(THIRD_PARTY_DIR)/build-Debug/include
CMOCKA_LIBRARY = $(THIRD_PARTY_DIR)/build-Debug/lib/libcmocka.a

cmocka : $(SUBDIRS)

CFLAGS += -I $(CMOCKA_INCLUDE_DIR)

#Generating project2.map files
LDFLAGS = -Wl,-Map=$(BASENAME).map 

#
# library
#
LIB_SRCS = \
	project2.c circbuf.c debug.c conversion.c memory.c project1.c
LIB_OBJS = $(LIB_SRCS:%.c=%.o)
LIB_HEADERS = $(LIB_SRCS:%.c=%.h)
LIB = libutils.a

#
# main executable
#
EXE_SRCS = main.c main1.c
EXE_OBJS = $(EXE_SRCS:%.c=%.o)
EXE = main.out main1.out

#
# tests
#
TEST_PROJ2_SRCS = \
	unit_test.c
TEST_PROJ2_OBJS = $(TEST_PROJ2_SRCS:%.c=%.o)
TEST_PROJ2_EXE = test-proj2.out

TEST_PROJ11_SRCS = \
	unit_test1.c
TEST_PROJ11_OBJS = $(TEST_PROJ11_SRCS:%.c=%.o)
TEST_PROJ11_EXE = test-proj11.out

TEST_PROJ12_SRCS = \
	unit_test2.c
TEST_PROJ12_OBJS = $(TEST_PROJ12_SRCS:%.c=%.o)
TEST_PROJ12_EXE = test-proj12.out

# Creating object files with names same as .c filenames
OBJS = $(SRCS:.c=.o)

# Targets section #
# Building the target based on the PLATFORM given during compile time
.PHONY: build
build: $(TARGET) 

$(TARGET): $(OBJS) DEPENDS.dep
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LFLAGS)

# Generating dependency files for each source file
DEPENDS.dep:
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -M $(SRCS) $(DEPS) -o $@  $^  > DEPENDS
	objdump -a $(OBJS) 
	size -d $(OBJS)
	@echo  Build with .d files, .o files and .elf executable successful

$(LIB) : $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

all : $(LIB) $(EXE)

$(EXE) : $(EXE_OBJS) $(LIB)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -lm

test_circ : $(TEST_PROJ2_EXE)
	./$(TEST_PROJ2_EXE)

$(TEST_PROJ2_EXE) : $(TEST_PROJ2_SRCS) $(LIB)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(CMOCKA_LIBRARY) -lm

test_mem : $(TEST_PROJ11_EXE)
	./$(TEST_PROJ11_EXE)

$(TEST_PROJ11_EXE) : $(TEST_PROJ11_SRCS) $(LIB)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(CMOCKA_LIBRARY) -lm

test_conv : $(TEST_PROJ12_EXE)
	./$(TEST_PROJ12_EXE)

$(TEST_PROJ12_EXE) : $(TEST_PROJ12_SRCS) $(LIB)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(CMOCKA_LIBRARY) -lm


#Compiles all the source files
.PHONY: compile-all
compile-all: 
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -c $(SRCS)

#Cleaning all the executables, preprocessed files etc.

#To generate preprocessed files for the given .c files
%.i: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -E -o $@ $^  

#To generate object files for the given .c files
%.o:%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -c -o $@ $^ 

#To generate assembly(.s) files for the given .c files
%.asm: 
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -S $(SRCS) $(LFLAGS) 

.PHONY: asmdump
asmdump: $(TARGET)
	objdump -SD $(TARGET) > project2.dump

.PHONY: clean
clean:
	-rm -rf *~ *.o $(LIB) $(EXE) $(TEST_PROJ2_EXE) $(TEST_PROJ11_EXE) $(TEST_PROJ12_EXE) *.dSYM/ *.map *.asm *.i *.out *.s *.d *~ $(TARGET) 

.PHONY : clobber
clobber : $(SUBDIRS) clean

         


