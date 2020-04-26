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

void ring_buffer_push_debug(struct ring_buffer* rb, char c) {
	printf("PUSH value=%c head=%d tail=%d size=%d\n", c, rb->head, rb->tail, rb->size);
	return ring_buffer_push(rb, c);
}

char ring_buffer_pop(struct ring_buffer* rb) {
	if (rb->size == 0)
		return ' ';
	rb->size = rb->size - 1;
	rb->tail = (rb->tail + 1) % 4084;
	if (rb->tail == 0)
		return rb->ring[4083];
	return rb->ring[rb->tail-1];
}

char ring_buffer_pop_debug(struct ring_buffer* rb) {
	char c = ring_buffer_pop(rb);
	printf("POP value=%c head=%d tail=%d size=%d\n", c, rb->head, rb->tail, rb->size);
	return c;
}

#endif /* _RING_BUFFER_H */
