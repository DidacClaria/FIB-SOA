#include <libc.h>

char buff[24];

int posx=0, posy=1;

// int esTablero(int posx, int posy){
// 	return posx>=0 && posx<80 && posy>=0 && posy<25;
// }

int __attribute__ ((__section__(".text.main")))
  main(void)
{
	char *empty;
	//sys_get_key tests
	get_key(empty); //si no comprovamos que le pasamos un puntero inicializado daria un page fault
	get_key(empty);
	get_key(empty); //aunque se pidan más teclas que las que pueda haber en el ring buffer,
					//sigue funcionando y simplemente lo ignora

	//sys_put_screen tests
	put_screen(empty); //si no hubiera el control de paràmetros daria un page fault 

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
