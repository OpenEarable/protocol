# Generated protocol source manifest. Do not edit by hand.
OPEN_EARABLE_PROTOCOLS_DIR ?= $(dir $(lastword $(MAKEFILE_LIST)))

OPEN_EARABLE_PROTOCOLS_SOURCES := \
  $(OPEN_EARABLE_PROTOCOLS_DIR)/protocol_runtime.c \
  $(OPEN_EARABLE_PROTOCOLS_DIR)/audio_response_protocol.c

OPEN_EARABLE_PROTOCOLS_HEADERS := \
  $(OPEN_EARABLE_PROTOCOLS_DIR)/protocol_runtime.h \
  $(OPEN_EARABLE_PROTOCOLS_DIR)/audio_response_protocol.h
