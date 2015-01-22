CC=gcc
CFLAGS="-Wall"

debug:clean
	$(CC) $(CFLAGS) -g -o btree main.c
stable:clean
	$(CC) $(CFLAGS) -o btree main.c
clean:
	rm -vfr *~ btree
