CC = g++
OBJS = main.o DocMap.o PostingList.o HelperFunctions.o Commands.o List.o
FLAGS = -g3 -Wall

minisearch: $(OBJS)
	$(CC) $(OBJS) -o minisearch $(FLAGS)

main.o: main.cc
	$(CC) -c main.cc $(FLAGS)

DocMap.o: DocMap.cc
	$(CC) -c DocMap.cc $(FLAGS)

PostingList.o:PostingList.cc
	$(CC) -c PostingList.cc $(FLAGS)

HelperFunctions.o:HelperFunctions.cc
	$(CC) -c HelperFunctions.cc $(FLAGS)

Commands.o:Commands.cc
	$(CC) -c Commands.cc $(FLAGS)

List.o:List.cc
	$(CC) -c List.cc $(FLAGS)

clean:
	rm -rf $(OBJS) minisearch a.out
