# Compilador y flags
CC = gcc
CFLAGS = -fopenmp -Wall -O2

# Directorios
PRUEBA_DIR = ../CodigosPrueba
PPD1_DIR = ../PPD3_1
PPD2_DIR = ../PPD3_2

# Archivos fuente
PRUEBA_SRC = $(wildcard $(PRUEBA_DIR)/*.c)
PPD1_SRC = $(wildcard $(PPD1_DIR)/*.c)
PPD2_SRC = $(wildcard $(PPD2_DIR)/*.c)
PPD3_SRC = $(wildcard $(PPD3_DIR)/*.c)

# Ejecutables
PRUEBA_EXE = $(PRUEBA_SRC:.c=)
PPD1_EXE = $(PPD1_SRC:.c=)
PPD2_EXE = $(PPD2_SRC:.c=)

# Regla principal
all: $(PRUEBA_EXE) $(PPD1_EXE) $(PPD2_EXE)

# Reglas para compilar cada ejecutable
$(PRUEBA_DIR)/%: $(PRUEBA_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(PPD1_DIR)/%: $(PPD1_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(PPD2_DIR)/%: $(PPD2_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

# Limpieza
clean:
	rm -f $(PRUEBA_EXE) $(PPD1_EXE) $(PPD2_EXE) $(PPD3_EXE)

# Ejecución rápida de ejemplo
run1:
	$(PPD1_DIR)/P3-1

run2:
	$(PPD2_DIR)/P3-2

# Reglas para compilar y ejecutar los ejercicios
runall1: $(PPD1_DIR)/P3-1
	$(PPD1_DIR)/P3-1

runall2: $(PPD2_DIR)/P3-2
	$(PPD2_DIR)/P3-2

