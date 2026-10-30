# Compilateur et options de compilation strictes
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -Iinclude -g

# Récupération automatique de tous les fichiers .cpp dans src/ (y compris main.cpp)
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = fit_tracker.exe

# Déclaration des cibles fictives
.PHONY: all clean rebuild valgrind

# Règle par défaut
all: $(EXEC)

# Édition des liens
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC)

# Compilation des .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage compatible Windows PowerShell / CMD
clean:
	del /Q src\*.o $(EXEC) 2>nul || rm -f $(OBJ) $(EXEC)

# Recompilation complète
rebuild: clean all

# Valgrind (si exécuté sous WSL / Linux)
valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)