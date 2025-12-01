# Compilador
CXX = g++

# Flags de Compilação (O3 para velocidade é essencial)
CXXFLAGS = -O3 -std=c++17 -Wall

# Flags do Linker (AQUI ESTÁ A CORREÇÃO: -lSDL2)
LDFLAGS = -lSDL2

# Nome do executável
TARGET = raytracer

# Arquivos fonte
SRC = main.cpp sphere.cpp hittable_list.cpp

# Regra padrão
all: $(TARGET)

# Regra de compilação
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe imagem.ppm