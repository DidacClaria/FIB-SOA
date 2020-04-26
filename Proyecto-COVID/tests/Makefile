CFLAGS = -O2 -fno-omit-frame-pointer -ffreestanding -Wall -I.. -I../include

all: ring_buffer

ring_buffer:
	$(CC) $(CFLAGS) -o ring_buffer ring_buffer.c

clean:
	rm -f ring_buffer
