# Nom de l'exécutable
EXEC = cyfighters

# Fichiers source
SRC = main.c combat.c

# Fichiers d'en-tête
HEADERS = combat.h

# Options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Règle principale
all: $(EXEC)

$(EXEC): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

# Nettoyer les fichiers compilés
clean:
	rm -f $(EXEC)

# Tout nettoyer
fclean: clean

