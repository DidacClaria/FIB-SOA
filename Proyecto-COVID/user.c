#include <libc.h>

char buff[24];

int posx=0, posy=13;

// int esTablero(int posx, int posy){
// 	return posx>=0 && posx<80 && posy>=0 && posy<25;
// }

// char obstaculos[25][23]={
// 	"  |||||||||||||||||||||||",
// 	"|  ||||||||||||||||||||||",
// 	"|||  ||||||||||||||||||||",
// 	"||||  |||||||||||||||||||",
// 	"|||||  ||||||||||||||||||",
// 	"||||||  |||||||||||||||||",
// 	"|||||||  ||||||||||||||||",
// 	"||||||||  |||||||||||||||",
// 	"|||||||||  ||||||||||||||",
// 	"||||||||||  |||||||||||||",
// 	"|||||||||||  ||||||||||||",
// 	"||||||||||||  |||||||||||",
// 	"|||||||||||||  ||||||||||",
// 	"||||||||||||||  |||||||||",
// 	"|||||||||||||||  ||||||||",	
// 	"||||||||||||||||  |||||||",
// 	"|||||||||||||||||  ||||||",
// 	"||||||||||||||||||  |||||",
// 	"|||||||||||||||||||  ||||",
// 	"||||||||||||||||||||  |||",
// 	"|||||||||||||||||||||  ||",
// 	"||||||||||||||||||||||  |",
// 	"|||||||||||||||||||||||  "
// };

void creartablero(char tablero[80][25]){
	for (int i=2; i<80; i+=3){
		for (int j=0; j<25; j++){
			tablero[i][j]='|';
			if (j==3) tablero[i][j]=' ';
		}
	}
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
	write(1,"Syscalls checking:",strlen("Syscalls checking:"));
	char empty;

	//sys_get_key TESTS
	get_key(&empty); //si no hay ningun elemento en el ring buffer devuelve un error
	write(1,"\nget_key checking:",strlen("\nget_key checking:"));
	itoa(errno,buff);
	write(1,buff,strlen(buff));
	write(1,"//",strlen("//"));

	get_key(empty); //si no hubiera control de escritura en el parametro, saltaria un page fault,
	itoa(errno,buff); //como si que lo hay simplemente lo ignora
	write(1,buff,strlen(buff));

	//sys_put_screen TESTS
	put_screen(empty); //si no hubiera control de lectura en el parametro, saltaria un page fault,
	write(1,"\nput_screen checking:",strlen("\nput_screen checking:")); //como si que lo hay simplemente lo ignora
	itoa(errno,buff);
	write(1,buff,strlen(buff));

	//malloc TESTS
	void* addr = malloc(1024);
	write(1,"\nmalloc checking:",strlen("\nmalloc checking:"));
	itoa(errno,buff);
	write(1,buff,strlen(buff));
	addr = malloc(10);
	itoa(addr,buff);
	write(1,buff,strlen(buff));
	addr = malloc(10);
	itoa(addr,buff);
	write(1,buff,strlen(buff));

	//START GAME:

	char tablero[80][25]={{' '}};
	creartablero(tablero);
	write(1,"\nPRESS ANY KEY TO START!",strlen("\nPRESS ANY KEY TO START!"));
	while (get_key(&empty)){} //
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
