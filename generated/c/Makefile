CC ?= cc
AR ?= ar
CFLAGS ?= -O2
CPPFLAGS ?=
BUILD_DIR ?= build

include protocol_sources.mk

CPPFLAGS += -I$(OPEN_EARABLE_PROTOCOLS_DIR)
CFLAGS += -std=c99

OBJECTS := $(patsubst $(OPEN_EARABLE_PROTOCOLS_DIR)/%.c,$(BUILD_DIR)/%.o,$(OPEN_EARABLE_PROTOCOLS_SOURCES))
LIBRARY := $(BUILD_DIR)/libopen_earable_protocols.a

.PHONY: all clean

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(AR) rcs $@ $^

$(BUILD_DIR)/%.o: $(OPEN_EARABLE_PROTOCOLS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
