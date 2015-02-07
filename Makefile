CC=g++
CFLAGS="-Wall"

debug:clean
	$(CC) $(CFLAGS) -g -o btree main.cpp btree.cpp
stable:clean
	$(CC) $(CFLAGS) -o btree main.cpp btree.cpp
clean:
	rm -vfr *~ btree
