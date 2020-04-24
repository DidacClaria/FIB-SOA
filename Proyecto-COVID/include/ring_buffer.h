#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

struct ring_buffer {
	char *current;
	char buffer[4096]; 
};

#endif /* _RING_BUFFER_H */