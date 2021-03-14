

a.out: life.c x.c
	gcc life.c x.c -g -lX11

# set your indent to tab silly



run: a.out
	./a.out
