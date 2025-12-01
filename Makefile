# Compilador
CXX = g++

# Flags (O3 para velocidade é essencial)
CXXFLAGS = -O3 -std=c++17 -Wall

# Nome do executável
TARGET = raytracer

# --- AQUI ESTÁ A MUDANÇA ---
# Listamos todos os arquivos .cpp
SRC = main.cpp sphere.cpp hittable_list.cpp

# Regra padrão
all: $(TARGET)

# Regra de compilação
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)
	display imagem.ppm

clean:
	rm -f $(TARGET) $(TARGET).exe imagem.ppm