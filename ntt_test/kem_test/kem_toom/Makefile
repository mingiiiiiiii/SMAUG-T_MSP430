# Makefile for SMAUG-T_NTT project

# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -O2 

# Source files
SRCS = main.c cbd.c ciphertext.c dg.c fips202.c hash.c hwt.c indcpa.c io.c kem.c key.c pack.c poly.c randombytes.c verify.c toomcook.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = main

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
	@$(MAKE) clean_objs  # 객체 파일을 바로 삭제

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean: clean_objs clean_facts
	rm -f $(TARGET)

# Clean only object files
clean_objs:
	rm -f $(OBJS)

# Clean *.rsp, *.req
clean_facts:
	rm -f *.rsp *.req

.PHONY: all clean clean_objs clean_facts

