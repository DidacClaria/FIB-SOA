#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

struct ring_buffer {
	int head;
	int tail;
	int size;
	char ring[4084];
};

#endif /* _RING_BUFFER_H */
