TARGET = my_3ds_app
BUILD = build
SOURCES = .
DATA =
INCLUDES =

export PATH := $(DEVKITARM)/bin:$(PATH)

include $(DEVKITPRO)/3ds_rules
