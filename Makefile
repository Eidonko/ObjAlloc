CC=gcc

all:		liboa.a oatest.cgi

liboa.a:	ObjAlloc.o
	ar -ruv liboa.a ObjAlloc.o
	ranlib  liboa.a

ObjAlloc.o:	ObjAlloc.c
	$(CC) -c ObjAlloc.c
	
oatest.cgi:		oatest.c liboa.a
	$(CC) -o oatest.cgi oatest.c liboa.a
