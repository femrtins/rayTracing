# Compilador
CXX = g++

# Flags de Compilação
CXXFLAGS = -O3 -std=c++17 -Wall

# Flags do Linker
LDFLAGS = -lSDL2

# Nome do executável
TARGET = raytracer

# --- MUDANÇA AQUI: Adicionado window.cpp ---
SRC = main.cpp sphere.cpp hittable_list.cpp camera.cpp window.cpp

# Regra padrão
all: $(TARGET)

# Regra de compilação
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe imagem.ppm