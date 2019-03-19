bitcoin: bitcoin.o bitcoin_functions.o my_struct.o tree.o HashTable.o
	gcc bitcoin.o bitcoin_functions.o my_struct.o HashTable.o tree.o -o bitcoin

bitcoin.o: bitcoin.c
	gcc -c bitcoin.c

bitcoin_functions.o: bitcoin_functions.c
	gcc -c bitcoin_functions.c

my_struct.o: my_struct.c
	gcc -c my_struct.c

tree.o: tree.c
	gcc -c tree.c

HashTable.o: HashTable.c
	gcc -c HashTable.c

clean:
	rm -f bitcoin bitcoin.o bitcoin_functions.o my_struct.o tree.o HashTable.o
