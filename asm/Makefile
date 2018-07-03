EXE=summer
OBJ=summer.o
FLAGS=-gstabs
AS=as -- 32 		# Opzioni per lo stacK per architetture a 32bit
LD=ld -m elf_i386	# Opzioni per lo stacK per architetture a 32bit

$(EXE): $(OBJ)
    $(LD) $(OBJ) -o $(EXE)
$(OBJ): summer.s
    $(AS) summer.s -o $(OBJ) $(FLAGS)
clean:
    rm -f *.o $(EXE) core