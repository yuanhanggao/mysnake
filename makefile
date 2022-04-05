CC = gcc
CFLAG = -g -lncurses -lpthread
PWD = $(shell pwd)
SRC = $(shell find ./src/ -name "*.c") 
INC = -I$(PWD)/include 
PROM = game
OBJ = $(PROM).o
OSRC = $(shell find ./ -name "*.o")

$(PROM) : $(OBJ) 
	$(CC) $(OSRC) -o $(PROM) $(CFLAG)

$(OBJ) : $(SRC)
	$(CC) -c $(SRC) $(INC) $(CFLAG)  
clean: 
	rm -rf $(PROM) *.o
