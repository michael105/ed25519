# Minimal Makefile for building a small ed25519 keypair tool from the ref10 sources.
# Place this Makefile inside /ref10build/ (the directory that contains the ref10 tree).
#
# Usage:
#   make            # builds ./ed25519-keypair
#   make run        # runs the keypair tool and prints keys (hex)
#   make clean
#
# Notes:
# - Assumes the ref10 sources and generated headers are present in the current tree.
# - A small header crypto_namespace.h is expected to be present (added below).
# - Produces a compact binary with section- and data-elision and stripping.
# - Tune CC/CFLAGS/LDFLAGS as you like.

CC ?= gcc
# Minimal, size-focused flags
CFLAGS ?= -Os -march=x86-64 -ffunction-sections -fdata-sections -fno-common \
          -Wall -Wextra -I. -std=c11
# Hide symbols by default; rely on explicit attribute((visibility("default"))) in sources for exported API, if any.
CFLAGS += -fvisibility=hidden 

LDFLAGS ?= -Wl,--gc-sections -s

# Collect all .c files under the current directory. (ref10 tree only)
SRCS := $(shell find . -name '*.c' -print)
OBJS := $(SRCS:.c=.o)

TARGET := ed25519-keypair

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -D'CRYPTO_NAMESPACE(name)=ed_##name' \
		-D'CRYPTO_SHARED_NAMESPACE(name)=edshared_##name' \
		-Dcrypto_hash_sha512=crypto_hash 


# Generic compile rule
%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@  -D'CRYPTO_NAMESPACE(name)=ed_##name' \
		-D'CRYPTO_SHARED_NAMESPACE(name)=edshared_##name' \
		-Dcrypto_hash_sha512=crypto_hash 


run: all
	./$(TARGET)

clean:
	-find . -name '*.o' -type f -delete
	-rm -f $(TARGET)

# A tiny convenience to show what will be compiled
show-sources:
	@echo "Will compile the following .c files:"
	@printf "%s\n" $(SRCS)
