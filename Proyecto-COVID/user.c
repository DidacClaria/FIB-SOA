#include <libc.h>

char buff[24];

int posx=0, posy=13, cambio=1;

// int esTablero(int posx, int posy){
// 	return posx>=0 && posx<80 && posy>=0 && posy<25;
// }

char* obstaculos[23]={
	"  \10\10\10\10\10\10\10\10\10\10\11\12\13\14\10\10\10\10\10\10\10\10\10",
	"\10  \10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10",
	"\10\10\10  \10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10",
	"\10\10\10\10  \10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10",
	"\10\10\10\10\10  \10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10",
	"\10\10\10\10\10\10  \10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10",
	"\10\10\10\10\10\10\10  \10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10",
	"\10\10\10\10\10\10\10\10  \10\10\10\10\10\10\10\10\10\10\10\10\10\10\10",
	"\10\10\10\10\10\10\10\10\10  \10\10\10\10\10\10\10\10\10\10\10\10\10\10",
	"\10\10\10\10\10\10\10\10\10\10  \10\10\10\10\10\10\10\10\10\10\10\10\10",
	"\10\10\10\10\10\10\10\10\10\10\10  \10\10\10\10\10\10\10\10\10\10\10\10",
	"\10\10\10\10\10\10\10\10\10\10\10\10  \10\10\10\10\10\10\10\10\10\10\10",
	"\10\10\10\10\10\10\10\10\10\10\10\10\10  \10\10\10\10\10\10\10\10\10\10",
	"\10\10\10\10\10\10\10\10\10\10\10\10\10\10  \10\10\10\10\10\10\10\10\10",
	"\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10  \10\10\10\10\10\10\10\10",	
	"\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10  \10\10\10\10\10\10\10",
	"\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10  \10\10\10\10\10\10",
	"\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10  \10\10\10\10\10",
	"\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10  \10\10\10\10",
	"\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10  \10\10\10",
	"\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10  \10\10",
	"\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10  \10",
	"\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10  "
};

int get_rand(int seed){
	if (seed%2)	return (gettime()*seed+3)%23;
	return 4123124*seed%23;
}

void creartablero(char *tablero){
	int rand;
	for (int i=3; i<79; i+=5){
		rand=get_rand(rand);
		for (int j=0; j<25; ++j){
			tablero[i*25+j]=obstaculos[(rand*gettime())%23][j];
		}
	}
	if (cambio==1) tablero[79*25+(rand*gettime())%23]='\3';
	else tablero[0*25+(rand*gettime())%23]='\3';
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
	// write(1,"\nmalloc checking:",strlen("\nmalloc checking:"));
	// char* addr = malloc(4096*5);
	// itoa(addr,buff);
	// write(1,buff,strlen(buff));
	// char screen[25][80];
	// creartablero(screen);
	// *(addr) = &screen;
	// put_screen(&addr);

	// write(1,"//",strlen("//"));
	// addr = malloc(25*80);
	// itoa(addr,buff);
	// write(1,buff,strlen(buff));
	// write(1,"//",strlen("//"));
	// addr = malloc(10);
	// itoa(addr,buff);
	// write(1,buff,strlen(buff));
	// write(1,"//",strlen("//"));

	//START GAME:
	// int thr=0;
	char tablero[80][25]={{' '}};
	creartablero(&tablero);
	write(1,"\nPRESS ANY KEY TO START!",strlen("\nPRESS ANY KEY TO START!"));
	while (get_key(&empty)){} 
	while(1) { 
		tablero[posx][posy]=' ';
		char direction;
		get_key(&direction);
		if (direction=='w' && posx>=0 && posx<80 && posy-1>=0 && posy-1<25 && tablero[posx][posy-1]!='\10') --posy;
		else if (direction=='s' && posx>=0 && posx<80 && posy+1>=0 && posy+1<25 && tablero[posx][posy+1]!='\10') ++posy;
		else if (direction=='d'  && posx+1>=0 && posx+1<80 && posy>=0 && posy<25 && tablero[posx+1][posy]!='\10') ++posx;
		else if (direction=='a' && posx-1>=0 && posx-1<80 && posy>=0 && posy<25 && tablero[posx-1][posy]!='\10') --posx;
		// if (thr>=100){
		// 	creartablero(&tablero);
		// 	thr=0;
		// }
		// ++thr;
		tablero[posx][posy]='A';
		put_screen(&tablero);
	}
}
