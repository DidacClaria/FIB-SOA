#include <stdio.h>
#include <ring_buffer.h>

void main() {
	struct ring_buffer rb;

	char chars[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
	for (int i = 0; i < 6; ++i)
		ring_buffer_push_debug(&rb, chars[i]);

	printf("\n");

	for (int i = 0; i < 4; ++i)
		ring_buffer_pop_debug(&rb);
}
