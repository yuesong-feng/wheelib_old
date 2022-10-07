BUILD_DIR := ./build

# $@：表示目标文件
# $^：表示所有依赖文件
# $<：表示第一个依赖文件

EXE_SRCS = $(wildcard test/*.c)
EXE_OBJS = $(EXE_SRCS:%=$(BUILD_DIR)/obj/%.o)
EXE_DEPS = $(EXE_OBJS:.o=.d)
EXES = $(EXE_SRCS:test/%.c=%)

all: $(EXES) 

$(EXES): % : $(EXE_OBJS) $(BUILD_DIR)/lib/libwheelib.so
	@mkdir -p $(dir $(BUILD_DIR)/bin/$@)
	gcc -L./build/lib -lwheelib $< -o $(BUILD_DIR)/bin/$@

$(BUILD_DIR)/obj/%.c.o : %.c
	@mkdir -p $(dir $@)
	gcc -MMD -MP -g -c $< -o $@

###############################################
#            Build dynamic library           ##
###############################################
LIB_SRCS = $(shell find src -name '*.c' -or -name '*.cpp')	# all source files
LIB_OBJS = $(LIB_SRCS:%=$(BUILD_DIR)/obj/%.o)				# all object files
LIB_DEPS = $(LIB_OBJS:.o=.d)								# all dependencies

# all .o => .so
$(BUILD_DIR)/lib/libwheelib.so: $(LIB_OBJS)
	@mkdir -p $(dir $@)
	gcc -shared $^ -o $@

# all .c => .o + .d
$(BUILD_DIR)/obj/%.c.o: %.c
	@mkdir -p $(dir $@)
	gcc -MMD -MP -I./src -g -fPIC -c $< -o $@

# all .cpp => .o + .d
$(BUILD_DIR)/obj/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	g++ -MMD -MP -I./src -g -std=c++11 -fPIC -c $< -o $@

clean:
	rm -r $(BUILD_DIR)

# dependencies
-include $(LIB_DEPS)
-include $(EXE_DEPS)