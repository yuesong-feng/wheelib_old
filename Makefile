BUILD_DIR := ./build

EXE_SRCS := $(wildcard *.c)
EXES := $(EXE_SRCS:%.c=%)
EXE_OBJS := $(EXE_SRCS:%=$(BUILD_DIR)/obj/%.o)
EXE_DEPS := $(EXE_OBJS:.o=.d)

all: $(EXES) 

# link exe object and dynamic library
LDFLAGS := -L$(BUILD_DIR)/lib

$(EXES): % : $(BUILD_DIR)/obj/%.c.o $(BUILD_DIR)/lib/libwheelib.so
	@mkdir -p $(dir $(BUILD_DIR)/bin/$@)
	$(CC) $(LDFLAGS) -lwheelib $< -o $(BUILD_DIR)/bin/$@

# build exe object
EXE_INC := -I./
EXE_CPP_FLAGS := $(EXE_INC) -MMD -MP 

$(EXE_OBJS): $(BUILD_DIR)/obj/%.c.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(EXE_CPP_FLAGS) $< -c -o $@ 


###############################################
#            Build dynamic library           ##
###############################################
LIB_SRCS := $(shell find src -name '*.c' -or -name '*.cpp')
LIB_OBJS := $(LIB_SRCS:%=$(BUILD_DIR)/obj/%.o)
LIB_DEPS := $(LIB_OBJS:.o=.d)
# LIB_INC := $(addprefix -I,$(shell find ./src -type d))
LIB_INC := -I.

$(BUILD_DIR)/lib/libwheelib.so: $(LIB_OBJS)
	@mkdir -p $(dir $@)
	$(CC) -shared $^ -o $@

# -MMD and -MP generate .d
# for both c and cpp
LIB_CPPFLAGS := $(LIB_INC) -MMD -MP  -fPIC

LIB_CFLAGS := -g
# all .c => .o + .d
$(BUILD_DIR)/obj/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(LIB_CPPFLAGS) $(LIB_CFLAGS) -c $< -o $@

LIB_CXXFLAGS := -g =std=c++11
# all .cpp => .o + .d
$(BUILD_DIR)/obj/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(LIB_CPPFLAGS) $(CXXFLAGS) -c $< -o $@


clean:
	rm -r $(BUILD_DIR)

# dependencies
-include $(LIB_DEPS)
-include $(EXE_DEPS)
