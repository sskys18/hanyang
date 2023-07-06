CC = gcc
OBJS = simulate.o
TARGET = simulate
 
.SUFFIXES : .c .o
 
all : $(TARGET)
 
$(TARGET): $(OBJS)
	$(CC) -o $(@) $(OBJS)

$(OBJS) : simulate.c
	$(CC) -c -o $(OBJS) simulate.c
 
clean :
	rm -f $(OBJS) $(TARGET)
