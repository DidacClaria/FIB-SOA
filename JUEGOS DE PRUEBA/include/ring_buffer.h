#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

struct ring_buffer {
	int head;
	int tail;
	int size;
	char ring[256];
};

void ring_buffer_push(struct ring_buffer* rb, char c);

char ring_buffer_pop(struct ring_buffer* rb);

#endif /* _RING_BUFFER_H */
