BUILD_DIR := ./build

C_EXE_SRCS := $(wildcard *.c)
C_EXES := $(C_EXE_SRCS:%.c=%)
C_EXE_OBJS := $(C_EXE_SRCS:%=$(BUILD_DIR)/obj/%.o)

SRCS := $(shell find src -name '*.c' -or -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/obj/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find ./src -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
INC_FLAGS += -I./

LDFLAGS := -L$(BUILD_DIR)/lib

all: $(C_EXES) 

$(C_EXES): % : $(BUILD_DIR)/obj/%.c.o $(BUILD_DIR)/lib/libwheelib.so
	@mkdir -p $(dir $(BUILD_DIR)/bin/$@)
	$(CC) $(LDFLAGS) -lwheelib $< -o $(BUILD_DIR)/bin/$@

$(C_EXE_OBJS): $(BUILD_DIR)/obj/%.c.o : %.c
	@mkdir -p $(dir $@)
	$(CC) -MMD -MP $(INC_FLAGS) $< -c -o $@ 


$(BUILD_DIR)/lib/libwheelib.so: $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) -shared $^ -o $@

CPPFLAGS := -MMD -MP $(INC_FLAGS) -fPIC

CFLAGS := -g
$(BUILD_DIR)/obj/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

CXXFLAGS := -g -std=c++11
$(BUILD_DIR)/obj/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)