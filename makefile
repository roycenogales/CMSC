
lesson1.o:   lesson1.asm
	nasm -f elf32 -g -F dwarf -o lesson1.o lesson1.asm

lesson1:     lesson1.o
	ld -m elf_i386 -o lesson1 lesson1.o

lesson2.o:   lesson2.asm
	nasm -f elf32 -g -F dwarf -o lesson2.o lesson2.asm

lesson2:     lesson2.o
	ld -m elf_i386 -o lesson2 lesson2.o

run:
	./lesson1

val:
	valgrind ./lesson1
