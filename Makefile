BUILD_DIR := build
SRC_DIR := src
LIB := wheelib

# $@：表示目标文件
# $^：表示所有依赖文件
# $<：表示第一个依赖文件

EXE_SRC = $(wildcard *.c)
EXE_OBJ = $(EXE_SRC:%.c=$(BUILD_DIR)/obj/%.o)
EXE_DEP = $(EXE_OBJ:.o=.d)
EXES = $(EXE_SRC:%.c=%)

all: $(EXES) 

$(EXES): %:$(BUILD_DIR)/obj/%.o $(BUILD_DIR)/lib/lib$(LIB).so
	gcc -L$(BUILD_DIR)/lib -lwheelib $< -o $@

###############################################
#            Build dynamic library           ##
###############################################
LIB_SRC = $(shell find src -name '*.c')	# all source files
LIB_OBJ = $(LIB_SRC:%.c=$(BUILD_DIR)/obj/%.o)				# all object files
LIB_DEP = $(LIB_OBJ:.o=.d)								# all dependencies

# all .o => .so
$(BUILD_DIR)/lib/lib$(LIB).so: $(LIB_OBJ)
	@mkdir -p $(dir $@)
	gcc -shared $^ -o $@

# all .c => .o + .d
$(BUILD_DIR)/obj/%.o: %.c
	@mkdir -p $(dir $@)
	gcc -MMD -MP -I$(SRC_DIR) -g -Wall -fPIC -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(EXES)

# dependencies
-include $(LIB_DEP)
-include $(EXE_DEP)

