#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

struct ring_buffer {
	int head;
	int tail;
	int size;
	char ring[4084];
};

void ring_buffer_push(struct ring_buffer* rb, char c) {
	rb->ring[rb->head] = c;
	if (rb->size < 4084)
		rb->size = rb->size + 1;
	rb->head = (rb->head + 1) % 4084;
}

char ring_buffer_pop(struct ring_buffer* rb) {
	if (rb->size == 0)
		return '\0';
	rb->size = rb->size - 1;
	rb->tail = (rb->tail + 1) % 4084;
	if (rb->tail == 0)
		return rb->ring[4083];
	return rb->ring[rb->tail-1];
}

#endif /* _RING_BUFFER_H */
