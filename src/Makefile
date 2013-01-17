CC = g++
CFLAGS = -W -Wall -g
LDFLAGS = 
SRC = $(wildcard *.cpp)
OBJS = $(SRC:.cpp=.o)
AOUT = catchBallMLP

all : $(AOUT) 


catchBallMLP : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	@rm -f *.o
	@rm -f $(AOUT)