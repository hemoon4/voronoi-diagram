LIB_DIR = ./dependencies/
INCLUDE_DIR = ./include/

LIBS = -lsfml-system -lsfml-window -lsfml-graphics -limgui_sfml -lGL
CXXFLAGS += -std=c++14

compile:
	@echo "Compiling..."
	@g++ $(CXXFLAGS) -Wall -Wextra src/*.cpp -I $(INCLUDE_DIR) -L $(LIB_DIR) $(LIBS) -o build/voronoi_diagrams
	@echo "Built."
	@echo "Type make run to run the program."
run:
	LD_LIBRARY_PATH=./dependencies ./build/voronoi_diagrams

