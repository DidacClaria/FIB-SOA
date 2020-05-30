#include <stdio.h>
#include <ring_buffer.h>

void ring_buffer_push_debug(struct ring_buffer* rb, char c) {
	printf("PUSH value=%c head=%d tail=%d size=%d\n", c, rb->head, rb->tail, rb->size);
	return ring_buffer_push(rb, c);
}

char ring_buffer_pop_debug(struct ring_buffer* rb) {
	char c = ring_buffer_pop(rb);
	printf("POP value=%c head=%d tail=%d size=%d\n", c, rb->head, rb->tail, rb->size);
	return c;
}

void main() {
	struct ring_buffer rb;

	char chars[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
	for (int i = 0; i < 6; ++i)
		ring_buffer_push_debug(&rb, chars[i]);

	printf("\n");

	for (int i = 0; i < 4; ++i)
		ring_buffer_pop_debug(&rb);
}
