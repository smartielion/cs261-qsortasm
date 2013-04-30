all: frequencyCount clean

FORMAT = elf
SYMFORMAT = dwarf

frequencyCount: hashTable.o  frequencyCount.o qsortASM.o stringCompASM.o
	gcc  -std=c99 -Wall -pedantic -g hashTable.o frequencyCount.o qsortASM.o stringCompASM.o -o frequencyCount


frequencyCount.o: frequencyCount.c hashTable.c hashTable.h
	gcc -c -Wall -pedantic -g -std=c99 frequencyCount.c


hashTable.o: hashTable.c hashTable.h
	gcc -c -Wall -pedantic -g -std=c99 hashTable.c

stringCompASM.o: stringCompASM.asm
	nasm -f $(FORMAT) -g -F $(SYMFORMAT) stringCompASM.asm

qsortASM.o: qsortASM.asm
	nasm -f $(FORMAT) -g -F $(SYMFORMAT) qsortASM.asm

clean:
	rm *.o
	rm *~

