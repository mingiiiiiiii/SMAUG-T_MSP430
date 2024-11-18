# Makefile for SMAUG-T_NTT project

# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -O2 

# Source files
SRCS = PQCgenKAT_kem.c cbd.c ciphertext.c dg.c fips202.c hash.c hwt.c indcpa.c io.c kat_kem.c kem.c key.c pack.c poly.c randombytes.c rng.c toomcook.c verify.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = PQCgenKAT_kem

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lcrypto
	@$(MAKE) clean_objs  # 객체 파일을 바로 삭제

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean: clean_objs
	rm -f $(TARGET)

# Clean only object files
clean_objs:
	rm -f $(OBJS)

.PHONY: all clean clean_objs
