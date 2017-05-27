CC = clang
CFLAGS = -W -Wall -g
#CFLAGS = -O2 -DNDEBUG
OBJS = main.o differentiateNodes.o createNode.o calculateNodes.o newton.o

a.out:	$(OBJS)
	$(CC) $(OBJS)

clean:
	rm -f *~ *.o a.out
