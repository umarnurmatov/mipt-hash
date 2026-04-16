# PROGRAM CONFIG
BUILD_DIR    := build
SRC_DIR      := src
INCLUDE_DIRS := include
EXECUTABLE   := hashtable.out

-include $(SRC_DIR)/sources.mk
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SOURCES)))
DEPS := $(patsubst %.o,%.d,$(OBJS))

# LIBRARIES
LIBCUTILS_INCLUDE_DIR  := ../cutils/include
LIBCUTILS              := -L../cutils/build/ -lcutils
LIBSDL3 			   			 := -lSDL3

LIBS := $(LIBCUTILS)

# INCLUDE
INCLUDE_DIRS_ALL = $(INCLUDE_DIRS) $(LIBCUTILS_INCLUDE_DIR)

# COMPILER CONFIG
CC := gcc

CXXFLAGS_DEBUG 	 := -D _DEBUG -ggdb3 -O0 -g

CXXFLAGS_RELEASE := -DNDEBUG -O2 -march=native

CXXFLAGS_ASAN := -fcheck-new -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

ifeq "$(TARGET)" "Release"
CXXFLAGS_TARGET := $(CXXFLAGS_RELEASE)
else
CXXFLAGS_TARGET := $(CXXFLAGS_DEBUG) $(CXXFLAGS_ASAN)
endif

CXXFLAGS_WARNINGS := -Wall -Wextra -Waggressive-loop-optimizations -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wopenmp-simd -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-varargs -Wstack-protector -Wlarger-than=8192 -Werror=vla -Wstack-usage=8192 

CXXFLAGS_DEFINES = $(addprefix -D,$(DEFINE)) -DLOG_DIR='"log"' -DIMG_DIR='"img"'

CXXFLAGS := -std=c11 $(addprefix -I,$(INCLUDE_DIRS_ALL)) $(CXXFLAGS_WARNINGS) $(CXXFLAGS_DEFINES) $(CXXFLAGS_TARGET) 


# PROGRAM
$(BUILD_DIR)/$(EXECUTABLE): $(OBJS)
	@echo -n Linking $@...
	@$(CC) $(CXXFLAGS) -o $@ $(OBJS) $(LIBS)
	@echo done

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Building $@...
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CXXFLAGS) -c -o $@ $< $(LIBS)

.PHONY: run
run: $(BUILD_DIR)/$(EXECUTABLE)
	@./$<

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

-include $(DEPS)
