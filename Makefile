# CORE (needed to compile)

ifndef CC
$(warning C compiler not detected. Setting default compiler to GCC...)
	CC :=	gcc
endif

# CORE OPTIONAL (compiler flags)

ifndef CFLAGS
	ifndef BUILD_TYPE
		BUILD_TYPE = Debug
	endif

	ifeq ($(CC), tcc)
		CFLAGS += -std=c89
	else
		CFLAGS += --std=c89
	endif

	ifeq ($(BUILD_TYPE), Release)
		CFLAGS += -O2
	else ifeq ($(BUILD_TYPE), Debug)
		CFLAGS += -O0 -g3 -ggdb -Wall
	endif
endif

CFLAGS += $(shell pkg-config --cflags gtk+-3.0 webkit2gtk-4.0 libsoup-2.4)

# Avoid warnings from dependecy problem
CFLAGS += -Wno-typedef-redefinition

ifndef INSTALL_PREFIX
	INSTALL_PREFIX := /usr
endif

ESCAPE        := \033
RED           := $(ESCAPE)[31m
BOLD_RED      := $(ESCAPE)[1;31m
GREEN         := $(ESCAPE)[32m
BOLD_GREEN    := $(ESCAPE)[1;32m
YELLOW        := $(ESCAPE)[33m
BOLD_YELLOW   := $(ESCAPE)[1;33m
BLUE          := $(ESCAPE)[34m
BOLD_BLUE     := $(ESCAPE)[1;34m
PURPLE        := $(ESCAPE)[35m
BOLD_PURPLE   := $(ESCAPE)[1;35m
CYAN          := $(ESCAPE)[36m
BOLD_CYAN     := $(ESCAPE)[1;36m
RESET_COLOUR  := $(ESCAPE)[0m

PWD           := $(shell pwd | sed 's/ /\\ /g')
OBJ_DIR       := $(PWD)/.obj
SRC_DIR       := $(PWD)/src
BIN_DIR       := $(PWD)/bin
DIRS          := bin .obj
HEADERS       := -I./src
LIBRARIES     := $(shell pkg-config --libs gtk+-3.0 webkit2gtk-4.0 libsoup-2.4)

ifndef MINGW_CHOST
	LIBRARIES   +=
else
	LIBRARIES   +=
endif

_TARGETS      := feather_browser
_SOURCES      := $(shell find $(SRC_DIR) -name "*.c")
_SOURCES      := $(patsubst $(SRC_DIR)/%,%,$(_SOURCES))
_OBJECTS      := $(patsubst %.c,%.o,$(_SOURCES))

TARGETS       := $(addprefix $(BIN_DIR)/, $(_TARGETS))
SOURCES       := $(addprefix $(SRC_DIR)/, $(_SOURCES))
OBJECTS       := $(addprefix $(OBJ_DIR)/, $(_OBJECTS))

.PHONY: all

all: directories $(TARGETS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "[CC] ""$(GREEN)""Building object '$<'""$(RESET_COLOUR)""\n"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(TARGETS): $(OBJECTS)
	@printf "[BIN] ""$(BOLD_GREEN)""Linking binary '$@'""$(RESET_COLOUR)""\n"
	@$(CC) $^ $(LIBRARIES) $(HEADERS) -o $@

directories: $(DIRS)

$(DIRS):
	@printf "[DIR] ""$(BLUE)""Directory ""$(BOLD_BLUE)""'$@'""$(RESET_COLOUR)$(BLUE)"" created""$(RESET_COLOUR).""\n"
	@mkdir -p $(PWD)/$@

install:
	@mkdir -p $(HOME)/.local/share/feather_browser/assets/
	@mkdir -p $(INSTALL_PREFIX)/share/feather_browser/assets/
	@install -m 755 bin/feather_browser $(INSTALL_PREFIX)/bin/
	@install -m 644 assets/icon.png $(INSTALL_PREFIX)/share/feather_browser/assets/
	@install -m 644 Feather_Browser.desktop $(INSTALL_PREFIX)/share/applications/
	@find assets/launcher -type f -exec install -Dm 755 "{}" "$(INSTALL_PREFIX)/share/feather_browser/{}" \;

clean:
	@rm -rv $(BIN_DIR)/$(_TARGETS) 2>/dev/null || true
	@rm -rv $(BIN_DIR) 2>/dev/null || true
	@rm -rv $(OBJ_DIR) 2>/dev/null || true

