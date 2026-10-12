TARGET         := feather-browser

# GENERAL
CC             := clang
OSARCH         := amd64
OSNAME         := unix64
OSTYPE         := linux
BUILD_TYPE     := Release
BUILTIN_LIBC   := 0
BUILD64        := 1
PREFIX         := /usr/local
PREFIX_BIN     := $(PREFIX)/bin

ifeq ($(OSNAME),unix32)
	OSARCH  = i386
	OSTYPE  = linux
	BUILD64 = 0
endif

ifeq ($(OSNAME),unix64)
	OSARCH  = amd64
	OSTYPE  = linux
	BUILD64 = 1
endif

ifeq ($(OSNAME),mingw32)
	CC             = gcc
	OSARCH         = i386
	OSTYPE         = mingw
	BUILTIN_LIBC   = 0
	BUILD64        = 0
	PREFIX         = "\"\\Program Files (x86)\\$(TARGET)\""
	PREFIX_BIN     = "\"\\Program Files (x86)\\$(TARGET)\""
endif

ifeq ($(OSNAME),mingw64)
	CC             = gcc
	OSARCH         = amd64
	OSTYPE         = mingw
	BUILTIN_LIBC   = 0
	BUILD64        = 1
	PREFIX         = "\"\\Program Files\\$(TARGET)\""
	PREFIX_BIN     = "\"\\Program Files\\$(TARGET)\""
endif

# DIRECTORIES
SRC_DIR         := src
OBJ_DIR         := .obj
BIN_DIR         := bin
PREFIX          := /usr/local
PWD             := $(shell pwd)

# FILES
SOURCES := $(shell find $(SRC_DIR) -name '*.c' | sort)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
DIRS    := $(shell echo $(OBJECTS) | tr ' ' '\n' | xargs -n1 dirname | sort -u) bin
VENDOR  := gtk+-3.0 webkit2gtk-4.1 libsoup-3.0

# COMPILER AND LINKER
CFLAGS    := -DBUILD64=$(BUILD64) -Wall -Wextra
HEADERS   := $(shell echo $(SOURCES) | tr ' ' '\n' | xargs -n1 dirname | sort -u | sed 's|^|-I./|') -I./vendor/GTKE/include
LIBRARIES := -lgtke -lm
LDFLAGS   := -L./vendor/GTKE

ifeq ($(CC),tcc)
	CFLAGS += -std=c89
else
	CFLAGS += --std=c89
endif

ifeq ($(BUILD_TYPE),Release)
	ifneq ($(CC),tcc)
		CFLAGS += -O2
	endif
else ifeq ($(BUILD_TYPE),Debug)
	ifneq ($(CC),tcc)
		CFLAGS += -O0
	endif
	CFLAGS += -g3 -ggdb -Wall
endif

ifeq ($(BUILD64),0)
	CFLAGS += -m32
	LDFLAGS += -m32
endif

ifeq ($(BUILTIN_LIBC),1)
	HEADERS += -I./vendor/musl/$(OSARCH)-musl-$(OSTYPE)/include
	LDFLAGS += -static -L./vendor/musl/$(OSARCH)-musl-$(OSTYPE)/lib
endif

CFLAGS  += $(shell pkg-config --cflags $(VENDOR))
LDFLAGS += $(shell pkg-config --libs $(VENDOR))

# Avoid warnings from dependecy problem
CFLAGS += -Wno-typedef-redefinition -Wno-unused-function -Wno-unused-variable -Wno-unused-parameter

# COLOUR ESCAPE CODES
GREEN        := \033[32m
BOLD_GREEN   := \033[1;32m
BLUE         := \033[34m
BOLD_BLUE    := \033[1;34m
RESET_COLOUR := \033[0m

.PHONY: all

all: directories $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "[CC] $(GREEN)Building object '%s'$(RESET_COLOUR)\n" "$<"
	@$(CC) $(HEADERS) -c $< $(CFLAGS) -o $@

$(TARGET): $(OBJECTS)
	@printf "[LD] $(BOLD_GREEN)Linking binary '%s'$(RESET_COLOUR)\n" "$@"
	@$(CC) $(HEADERS) $^ $(LDFLAGS) $(LIBRARIES) -o $(BIN_DIR)/$@

directories: $(DIRS)

$(DIRS):
	@printf "[DIR] $(BLUE) Directory $(BOLD_BLUE)'%s'$(RESET_COLOUR)$(BLUE) created$(RESET_COLOUR).\n" "$@"
	@mkdir -p $(PWD)/$@

prefix:
	@mkdir -p $(PREFIX)/bin 2>/dev/null || true
	@mkdir -p $(HOME)/.local/share/$(TARGET)/assets/
	@mkdir -p $(PREFIX)/share/$(TARGET)/assets/

install: prefix
	@install -vm 755 $(BIN_DIR)/$(TARGET) $(PREFIX_BIN)
	@install -m 644 assets/icon.png $(PREFIX)/share/$(TARGET)/assets/
	@install -m 644 $(TARGET).desktop $(PREFIX)/share/applications/
	@find assets/launcher -type f -exec install -Dm 755 "{}" "$(PREFIX)/share/$(TARGET)/{}" \;

clean:
	@rm -rv $(BIN_DIR) $(OBJ_DIR) build 2>/dev/null || true

