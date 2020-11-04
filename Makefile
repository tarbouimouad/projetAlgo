CC = gcc
CFLAGS = -w 
EXEC = test1  test2 test3 test4
test1 : test1.o dico.o
	$(CC) $(CFLAGS)  -o $@ $^
test2 : test2.o dico.o
	$(CC)  $(CFLAGS) -o $@ $^
test3 : test3.o dico.o
	$(CC)  $(CFLAGS)-o $@ $^
test4 : test4.o dico.o
		$(CC) $(CFLAGS) -o $@ $^
%.o : %.c
	$(CC) $(CFLAGS)  -c $<
all: $(EXEC)
clean :
	rm -f *.o $(EXEC)
