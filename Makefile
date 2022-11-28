# Directories
SRC_DIR := src
BUILD_DIR := build

# SFML Directories
LIB_DIR := -L./lib/linux/SFML-2.5.1/lib
LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INC_DIR := -I./lib/linux/SFML-2.5.1/include -I$(SRC_DIR)

# Find Cpp and Header files
SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')
HEADERS := $(shell find $(SRC_DIR) -name '*.h')

# Create paths for object files relative to source files
OBJ_FILES := $(patsubst $(SRC_DIR)%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Creates an executable from object files as well as setting the correct environmental variable.
factory: $(OBJ_FILES)
	g++ -std=c++17 -o $@ $(OBJ_FILES) $(LIB_DIR) $(LIBS)
	echo 'export LD_LIBRARY_PATH=./shared && ./factory' > LaunchGame.out
	chmod +x ./LaunchGame.out

# Creates required build/ directories and then creates the object file to go inside.
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp $(HEADERS)
	mkdir -p $(shell dirname $@)
	g++ -std=c++17 $(INC_DIR) -c $< -o $@ 
	
# Deletes all the build files, or if they don't exist, do nothing
.PHONY: clean
clean: 
	rm -r $(BUILD_DIR) || true
	rm factory || true
	rm LaunchGame.out || true
	
