# =========================================
# Makefile general para PPD1_x
# Ubicación: Práctica1/script/Makefile
# =========================================

# Compilador y opciones
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Directorios de prácticas
DIRS = ../PPD1_2 ../PPD1_3 ../PPD1_4 ../PPD1_5 ../PPD1_6 ../PPD1_7 ../PPD1_8

# Nombres de los ejecutables
CLIENTE = cliente
SERVIDOR = servidor

# =========================================
# Reglas principales
# =========================================

# Compila todos los clientes y servidores
all: $(DIRS:%=%/$(CLIENTE)) $(DIRS:%=%/$(SERVIDOR))

# Regla genérica para compilar cliente.c y servidor.c en cada carpeta
../PPD1_%/$(CLIENTE): ../PPD1_%/cliente.c
	@echo "Compilando cliente en PPD1_$*..."
	$(CC) $(CFLAGS) -o $@ $<

../PPD1_%/$(SERVIDOR): ../PPD1_%/servidor.c
	@echo "Compilando servidor en PPD1_$*..."
	$(CC) $(CFLAGS) -o $@ $<

# =========================================
# Reglas de ejecución
# =========================================

# Ejecuta un cliente o servidor específico
run:
	@if [ -z "$(DIR)" ] || [ -z "$(ARG)" ]; then \
		echo "Uso: make run DIR=PPD1_X ARG=cliente|servidor"; \
	else \
		if [ "$(ARG)" = "cliente" ]; then \
			echo "Ejecutando cliente en $(DIR)..."; \
			(cd ../$(DIR) && ./$(CLIENTE)); \
		elif [ "$(ARG)" = "servidor" ]; then \
			echo "Ejecutando servidor en $(DIR)..."; \
			(cd ../$(DIR) && ./$(SERVIDOR)); \
		else \
			echo "Argumento inválido. Usa ARG=cliente o ARG=servidor."; \
		fi \
	fi

# =========================================
# Limpieza
# =========================================

clean:
	@for d in $(DIRS); do \
		echo "Eliminando binarios en $$d..."; \
		rm -f $$d/$(CLIENTE) $$d/$(SERVIDOR); \
	done

# =========================================
# Ayuda
# =========================================

help:
	@echo "================= AYUDA ================="
	@echo " make                -> Compila todos los cliente.c y servidor.c"
	@echo " make run DIR=PPD1_X ARG=cliente   -> Ejecuta el cliente de una práctica"
	@echo " make run DIR=PPD1_X ARG=servidor  -> Ejecuta el servidor de una práctica"
	@echo " make clean          -> Limpia todos los binarios"
	@echo "========================================="
