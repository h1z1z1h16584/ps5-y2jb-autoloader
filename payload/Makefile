PS5_PAYLOAD_SDK ?= /opt/ps5-payload-sdk

TARGET := ../build/usb-y2jb-installer.elf
SRCS := main.c
OBJS := $(SRCS:.c=.o)

CFLAGS := -O2 -std=c11 -Wall -Wextra
LIBS := -lkernel_sys -lSceSystemService

all: $(TARGET)

include $(PS5_PAYLOAD_SDK)/toolchain/prospero.mk

$(TARGET): $(OBJS) | ../build
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

../build:
	mkdir -p ../build

clean:
	rm -f $(OBJS) $(TARGET)
