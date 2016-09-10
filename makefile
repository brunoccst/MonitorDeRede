CC=gcc
CFile=socket.c
OUTPUT=Socket

all:
	$(CC) $(CFile) -o $(OUTPUT)

clean:
	rm $(OUTPUT)
