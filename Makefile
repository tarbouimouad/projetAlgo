CC = gcc


EXEC = test1  test2 test3 test4
test1 : test1.o dico.o
	$(CC)  -o $@ $^
test2 : test2.o dico.o
	$(CC)  -o $@ $^
test3 : test3.o dico.o
	$(CC)  -o $@ $^
test4 : test4.o dico.o
		$(CC)  -o $@ $^
%.o : %.c
	$(CC)   -c $<
all: $(EXEC)
clean :
	rm -f *.o $(EXEC)
