include ../Makefile.rules

check:
	./moulinette.sh

clean:
	rm -f *.o \#*\# *~

distclean:
	rm -f *.o \#*\# *~

test_base:
	cd ../src && make all
	${CC} ${CFLAGS} test_base.c -lmalloc_NetBSD -L ..

test_align:
	cd ../src && make all
	${CC} ${CFLAGS} test_align.c -lmalloc_Linux -L ..

test_malloc:
	cd ../src && make all
	${CC} ${CFLAGS} test_malloc.c -lmalloc_NetBSD -L ..

test_free:
	cd ../src && make all
	${CC} ${CFLAGS} test_free.c -lmalloc_NetBSD -L ..

test2_free:
	cd ../src && make all
	${CC} ${CFLAGS} test2_free.c -lmalloc_NetBSD -L ..

test_calloc:
	cd ../src && make all
	${CC} ${CFLAGS} test_calloc.c -lmalloc_NetBSD -L ..

test_fcts:
	cd ../src && make all
	${CC} ${CFLAGS} test_fcts.c -lmalloc_NetBSD -L ..