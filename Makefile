SRC_DIR := ./src
BUILD_DIR := ./build

LIB_DIR := -L./lib/linux/SFML-2.5.1/lib
LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INC_DIR := -I./lib/linux/SFML-2.5.1/include -I$(SRC_DIR)

SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')
HEADERS := $(shell find $(SRC_DIR) -name '*.h')

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

factory: $(OBJ_FILES)
	g++ -o $@ $(OBJ_FILES) $(LIB_DIR) $(LIBS)
	echo 'export LD_LIBRARY_PATH=./shared && ./factory' > LaunchGame.out
	chmod +x ./LaunchGame.out


$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp $(HEADERS)
	g++ $(INC_DIR) -c $< -o $@ 

.PHONY: clean
clean: 
	find $(BUILD_DIR) -name '*.o' -delete
	rm factory
	rm LaunchGame.out
