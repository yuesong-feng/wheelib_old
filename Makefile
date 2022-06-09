BUILD_DIR := ./build

EXE_SRCS := $(wildcard *.c)
TARGETS = $(EXE_SRCS:.c=)
TARGETS_PATH := $(BUILD_DIR)/bin
# EXE := $(EXE_SRCS:%.cpp=$(BUILD_DIR)/bin/%)

# if cpp, use the following
# EXE_SRCS := program.cpp
# EXE := $(EXE_SRCS:%.cpp=$(BUILD_DIR)/bin/%)

# name of lib
LIB := libwheelib.so 

LIB_SRCS := $(wildcard src/*.c src/*.cpp)
LIB_OBJS := $(LIB_SRCS:%=$(BUILD_DIR)/%.o)
LIB_DEPS := $(LIB_OBJS:.o=.d)

INC_DIRS := $(shell find ./src -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS := $(INC_FLAGS) -MMD -MP

LDFLAGS := -L$(BUILD_DIR)
CFLAGS := -g

all: $(TARGETS)

$(TARGETS): % : %.c $(BUILD_DIR)/$(LIB) $(LIB_OBJS)
	@echo $(TARGETS_PATH)
	mkdir -p $(dir $(TARGETS_PATH)/$@)
	$(CC)  $^ -o $(TARGETS_PATH)/$@ $(CXXFLAGS) $(INC_FLAGS) $(LDFLAGS)

$(BUILD_DIR)/$(LIB): $(LIB_OBJS)
	$(CC) $(CXXFLAGS) $(INC_FLAGS) -shared -fPIC -o $@ $^

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -r $(BUILD_DIR)

-include $(LIB_DEPS)