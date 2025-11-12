# =========================================
# Makefile general para PPD4_x y CodigosPrueba (con MPI)
# =========================================

CC = mpicc
CFLAGS = -Wall -Wextra -O2

PPD_NUMS = 1 2 3 4
TEST_NUMS = 5 6 7 8

# =========================================
# Compilación
# =========================================

all:
	@echo "==== Compilando prácticas (MPI) ===="
	@for n in $(PPD_NUMS); do \
		SRC=../PPD4_$$n/P4-$$n.c; \
		OUT=../PPD4_$$n/P4-$$n; \
		if [ -f $$SRC ]; then \
			echo "Compilando $$SRC ..."; \
			if $(CC) $(CFLAGS) -o $$OUT $$SRC 2> /tmp/make_err.log; then \
				echo "✔ $$OUT compilado correctamente."; \
			else \
				echo "⚠ Error compilando $$SRC (probablemente sin main). Se omite."; \
				rm -f $$OUT; \
			fi; \
		else \
			echo "⚠ Archivo $$SRC no encontrado."; \
		fi; \
	done
	@echo "==== Compilando códigos de prueba (MPI) ===="
	@for n in $(TEST_NUMS); do \
		SRC=../CodigosPrueba/codigo4-$$n.c; \
		OUT=../CodigosPrueba/codigo4-$$n; \
		if [ -f $$SRC ]; then \
			echo "Compilando $$SRC ..."; \
			$(CC) $(CFLAGS) -o $$OUT $$SRC && echo "✔ $$OUT compilado."; \
		else \
			echo "⚠ Archivo $$SRC no encontrado."; \
		fi; \
	done
	@echo "==== Compilación finalizada ===="

# =========================================
# Ejecución
# =========================================

run:
	@if [ -z "$(DIR)" ]; then \
		echo "Uso: make run DIR=PPD4_X o DIR=CodigosPrueba/codigo4-Y [NP=n_procesos]"; \
	else \
		NP=$${NP:-4}; \
		if echo "$(DIR)" | grep -q "PPD4_"; then \
			NUM=$${DIR#PPD4_}; \
			EXE=../PPD4_$$NUM/P4-$$NUM; \
		elif echo "$(DIR)" | grep -q "CodigosPrueba/codigo4-"; then \
			NUM=$${DIR##*-}; \
			EXE=../CodigosPrueba/codigo4-$$NUM; \
		else \
			echo "⚠ Directorio o código no reconocido: $(DIR)"; \
			exit 1; \
		fi; \
		if [ -f $$EXE ]; then \
			echo "Ejecutando $$EXE con $$NP procesos..."; \
			(cd "$$(dirname $$EXE)" && mpirun -np $$NP "./$$(basename $$EXE)"); \
		else \
			echo "⚠ No existe el ejecutable $$EXE. Compílalo primero con: make"; \
		fi; \
	fi


# =========================================
# Limpieza
# =========================================

clean:
	@for n in $(PPD_NUMS); do rm -f ../PPD4_$$n/P4-$$n; done
	@for n in $(TEST_NUMS); do rm -f ../CodigosPrueba/codigo4-$$n; done
	@echo "Limpieza completa."

# =========================================
# Ayuda
# =========================================

help:
	@echo "================= AYUDA ================="
	@echo " make                -> Compila todas las prácticas y códigos de prueba"
	@echo " make run DIR=PPD4_X NP=4          -> Ejecuta una práctica (MPI)"
	@echo " make run DIR=CodigosPrueba/codigo4-Y NP=4 -> Ejecuta un código de prueba"
	@echo " make clean          -> Elimina ejecutables"
	@echo "========================================="

