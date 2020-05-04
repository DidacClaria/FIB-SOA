#include <libc.h>

char buff[24];

int pid;

int __attribute__ ((__section__(".text.main")))
  main(void)
{
	while(1) { 
		char direction;
		get_key(&direction);
		if (direction=='w'){
		 	write(1, "W", strlen("W"));
		}
		else if (direction=='a') {
			write(1, "A", strlen("A"));
		}
		else if (direction=='s') {
			write(1, "S", strlen("S"));
		}
		else if (direction=='d') {
			write(1, "D", strlen("D"));
		}
	}
}
