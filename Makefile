COMPILER = g++
WIN = x86_64-w64-mingw32-g++
I_DIR = -ISFML/include
L_DIR = -LSFML/lib
SFML_WIN = -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lfreetype -lwinmm -lgdi32
RESULT = mandelbrot_set

all: main.cpp
	$(COMPILER) main.cpp $(I_DIR) $(L_DIR) $(SFML_WIN) -o $(RESULT)

MAC: main.cpp
	$(COMPILER) main.cpp -lsfml-window -lsfml-graphics -lsfml-system -lGl -o $(RESULT)

linux: main.cpp
	$(COMPILER) main.cpp -lsfml-window -lsfml-graphics -lsfml-system -lGL -o linux_$(RESULT)
