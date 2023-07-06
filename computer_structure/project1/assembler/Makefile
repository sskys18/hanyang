CC = gcc
OBJS = assembler.o
TARGET = assembler
 
.SUFFIXES : .c .o
 
all : $(TARGET)
 
$(TARGET): $(OBJS)
	$(CC) -o $(@) $(OBJS)

$(OBJS) : assembler.c
	$(CC) -c -o $(OBJS) assembler.c
 
clean :
	rm -f $(OBJS) $(TARGET)
