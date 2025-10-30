# =========================
# Makefile genérico
# =========================

# Compilador y opciones
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Archivos fuente y ejecutables
CLIENTE_SRC = cliente.c
SERVIDOR_SRC = servidor.c
CLIENTE_BIN = cliente
SERVIDOR_BIN = servidor

# =========================
# Reglas principales
# =========================

# Compila ambos programas
all: $(CLIENTE_BIN) $(SERVIDOR_BIN)

# Compila el cliente
$(CLIENTE_BIN): $(CLIENTE_SRC)
	$(CC) $(CFLAGS) -o $(CLIENTE_BIN) $(CLIENTE_SRC)

# Compila el servidor
$(SERVIDOR_BIN): $(SERVIDOR_SRC)
	$(CC) $(CFLAGS) -o $(SERVIDOR_BIN) $(SERVIDOR_SRC)

# =========================
# Reglas de ejecución
# =========================

run: ## Ejecuta el cliente o servidor según el argumento: make run cliente / make run servidor
	@if [ "$(ARG)" = "cliente" ]; then \
		echo "Ejecutando cliente..."; \
		./$(CLIENTE_BIN); \
	elif [ "$(ARG)" = "servidor" ]; then \
		echo "Ejecutando servidor..."; \
		./$(SERVIDOR_BIN); \
	else \
		echo "Uso: make run ARG=cliente   o   make run ARG=servidor"; \
	fi

# =========================
# Limpieza
# =========================

clean:
	rm -f $(CLIENTE_BIN) $(SERVIDOR_BIN)

# =========================
# Ayuda
# =========================

help:
	@echo "Comandos disponibles:"
	@echo "  make              -> Compila cliente y servidor"
	@echo "  make run ARG=cliente   -> Ejecuta el cliente"
	@echo "  make run ARG=servidor  -> Ejecuta el servidor"
	@echo "  make clean        -> Elimina binarios compilados"
