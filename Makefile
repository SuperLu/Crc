CC=gcc
INC=-I./inc -I./src
C_FILES=main.c src/Crc.c src/Crc_8.c src/Crc_16.c src/Crc_32.c src/Crc_32P4.c src/Crc_64.c
OBJECTS=$(C_FILES:%.c=%.o)
TARGET=crc
%.o:%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
$(TARGET):$(OBJECTS)
	$(CC) -o $@ $^
all:$(TARGET)
	
clean:
	rm -rf $(TARGET) $(OBJECTS)
