# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++11 `pkg-config --cflags opencv4`
LDFLAGS = `pkg-config --libs opencv4`

# Nome do executável
TARGET = image_foresting_transform

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos fonte e objeto
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Regra padrão
all: $(BIN_DIR)/$(TARGET)

# Regra para criar o diretório de objetos
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Regra para criar o diretório bin
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regra para compilar o programa
$(BIN_DIR)/$(TARGET): $(OBJ_DIR) $(BIN_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Regra para compilar os arquivos fonte
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Regra para executar o programa
run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET) image.png

# Definir como phony as regras que não são arquivos
.PHONY: all clean run
