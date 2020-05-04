/*
 * ring_buffer.c 
 */

#include <ring_buffer.h>

void ring_buffer_push(struct ring_buffer* rb, char c) {
	rb->ring[rb->head] = c;
	if (rb->size < 256)
		rb->size = rb->size + 1;
	rb->head = (rb->head + 1) % 256;
}

char ring_buffer_pop(struct ring_buffer* rb) {
	if (rb->size == 0)
		return '\0';
	rb->size = rb->size - 1;
	rb->tail = (rb->tail + 1) % 256;
	if (rb->tail == 0)
		return rb->ring[255];
	return rb->ring[rb->tail-1];
}
