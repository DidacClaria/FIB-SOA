#include <ring_buffer.h>

void ring_buffer_push(struct ring_buffer* rb, char c) {
	rb->ring[rb->head] = c;
	if (rb->size < 4)
		rb->size = rb->size + 1;
	rb->head = (rb->head + 1) % 4;
}

char ring_buffer_pop(struct ring_buffer* rb) {
	if (rb->size == 0)
		return ' ';
	rb->size = rb->size - 1;
	rb->tail = (rb->tail + 1) % 4;
	if (rb->tail == 0)
		return rb->ring[4-1];
	return rb->ring[rb->tail-1];
}
