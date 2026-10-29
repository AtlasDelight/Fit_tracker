# Compilateur et options de compilation strictes
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -Iinclude -g

# Récupération automatique des fichiers sources et objets
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = fit_tracker

# Règle par défaut
all: $(EXEC)

# Édition des liens (création de l'exécutable)
$(EXEC): $(OBJ)$(CXX) $(OBJ) -o$(EXEC)

# Compilation des fichiers sources en fichiers objets
%.o: %.cpp
	$(CXX)$(CXXFLAGS) -c $< -o$@

# Nettoyage des fichiers compilés
clean:
	rm -f src/*.o $(EXEC)

# Recompilation complète
rebuild: clean all

# Vérification des fuites mémoire avec Valgrind (très utile pour vos pointeurs)
valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)