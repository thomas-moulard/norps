include ../Makefile.rules

OBJS = main.o io.o parser.o open.o close.o exit.o libs.o call.o \
	get.o errors.o utils.o

all: ${OUT}

${OUT}: ${OBJS}
	${CC} ${OBJS} -o $@ && mv $@ ..

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *.o *~ \#*\#

distclean:
	rm -f *.o *~ \#*\# ../${OUT}

debug: ${OBJS}
	${CC} ${OBJS} -g -o dbg-${OUT} && mv dbg-${OUT} ..

TAGS:
	emacs-etags *.c *.h

depends:
	gcc -M *.c > '.depends'

include .depends