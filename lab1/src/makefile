C=gcc
all: libtest.a
	$(C) main.c -L. -ltest -o res
libtest.a: test
	ar rc -o libtest.a b.o f.o
test:
	$(C) -c f.c b.c
clean:
	rm b.o f.o
