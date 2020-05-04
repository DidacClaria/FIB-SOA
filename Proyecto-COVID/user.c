#include <libc.h>

char buff[24];

int posx=0, posy=1;

// int esTablero(int posx, int posy){
// 	return posx>=0 && posx<80 && posy>=0 && posy<25;
// }

int __attribute__ ((__section__(".text.main")))
  main(void)
{
	//sys_get_key tests

	//sys_put_screen tests
	char *empty;
	put_screen(empty);
	
	char tablero[80][25]={{' '}};
	while(1) { 
		tablero[posx][posy]=' ';
		char direction;
		get_key(&direction);
		if (direction=='w' && posx>=0 && posx<80 && posy-1>=0 && posy-1<25) --posy;
		else if (direction=='s' && posx>=0 && posx<80 && posy+1>=0 && posy+1<25) ++posy;
		else if (direction=='d'  && posx+1>=0 && posx+1<80 && posy>=0 && posy<25) ++posx;
		else if (direction=='a' && posx-1>=0 && posx-1<80 && posy>=0 && posy<25) --posx;
		tablero[posx][posy]='A';
		put_screen(&tablero);
	}
}
