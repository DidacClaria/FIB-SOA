#include <libc.h>

char buff[24];

int posx=0, posy=13, cambio=1;

// int esTablero(int posx, int posy){
// 	return posx>=0 && posx<80 && posy>=0 && posy<25;
// }

char* obstaculos[23]={
	"  \10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10\10",
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
	seed=(int)seed&0xFFFFFF;
	if (seed%2)	return (seed*3+5)%0xFFFFFF;
	return ((seed+1)*2)%0xFFFFFF;
}

void creartablero(char *tablero){
	int rand=(int)tablero&0xFFFFFF;
	for (int i=3; i<79; i+=6){
		rand=get_rand(rand);
		for (int j=0; j<25; ++j){
			tablero[i*25+j]=obstaculos[rand%23][j];
		}
	}
}

void asignartablero(char* old, char* new){
	for (int i=0; i<2000; ++i) old[i]=new[i];
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
	write(1,"Syscalls checking:",strlen("Syscalls checking:"));
	char empty;

	//sys_get_key TESTS
	get_key(&empty);
	write(1,"\nget_key checking:",strlen("\nget_key checking:"));
	itoa(errno,buff);
	write(1,buff,strlen(buff));
	write(1,"//",strlen("//"));
	//si no hay ningun elemento en el ring buffer devuelve un error

	get_key(empty);
	itoa(errno,buff);
	write(1,buff,strlen(buff));
	//si no hubiera control de escritura en el parametro, saltaria un page fault,
	//como si que lo hay simplemente lo ignora

	//sys_put_screen TESTS
	put_screen(empty); 
	write(1,"\nput_screen checking:",strlen("\nput_screen checking:"));
	itoa(errno,buff);
	write(1,buff,strlen(buff));
	//si no hubiera control de lectura en el parametro, saltaria un page fault,
	//como si que lo hay simplemente lo ignora

	char fps_screen[80][25];
	int n_put_screens=0;
	while(1){
		++n_put_screens;
		put_screen(&fps_screen);
		int time=gettime();
		time=n_put_screens/time;
		itoa(time,buff);
		write(1,buff,strlen(buff));
	}

	//malloc TESTS	
	write(1,"\nmalloc checking:",strlen("\nmalloc checking:"));
	char* addr=malloc(0);
	itoa((int)addr,buff);
	write(1,buff,strlen(buff)); 
	write(1,"//",strlen("//"));
	//esta syscall nos devolvera la direccion donde empieza el heap del proceso, ya que no se ha ejecutado otro malloc previamente
	//por tanto el resultado que debemos ver por pantalla és (PAG_LOG_INIT_DATA+NUM_PAG_DATA)*PAGE_SIZE

	addr = malloc(4096*5);
	itoa((int)addr,buff);
	write(1,buff,strlen(buff));
	write(1,"//",strlen("//"));
	//esta syscall nos allocata 5 páginas nuevas i nos incrementa el heap a base+4096*5
	
	addr = malloc(1);
	itoa((int)addr,buff);
	write(1,buff,strlen(buff));
	write(1,"//",strlen("//"));
	//esta syscall alocata una página nueva i nos incrementa el heap en 1 ya que estamos en el inicio de una nueva pagina

	addr = malloc(-20);
	itoa((int)addr,buff);
	write(1,buff,strlen(buff));
	write(1,"//",strlen("//"));
	//esta syscall libera una página i decrementa el heap en 20

	addr = malloc(10);
	itoa((int)addr,buff);
	write(1,buff,strlen(buff));
	write(1,"//",strlen("//"));
	//esta syscall no necesita una nueva página por lo que solo incrementa el heap

	addr = malloc(25*80);
	itoa((int)addr,buff);
	write(1,buff,strlen(buff));
	write(1,"//",strlen("//"));	
	//esta syscall si que necesita una nueva página por lo que la alocata i incrementa el heap

	addr= malloc(1024*4096);
	itoa(errno,buff);
	write(1,buff,strlen(buff));
	write(1,"//",strlen("//"));
	//esta syscall devuelve un error (ENOMEM) ya que intenta pedir más memória de la que hay en total

	addr= malloc(-1024*4096);
	itoa(errno,buff);
	write(1,buff,strlen(buff));
	write(1,"//",strlen("//"));
	//esta syscall devuelve un error (EPERM) ya que no hay tantas páginas alocatadas en el heap

	addr=malloc(-4096*5); 
	addr=malloc(-(25*80-9));
	itoa((int)addr,buff);
	write(1,buff,strlen(buff));
	write(1,"//",strlen("//"));
	//volvemos a estar como antes de los juegos de prueba

	char* screen2=(char*)malloc(25*80);
	creartablero(screen2);
	char* screen3=(char*)malloc(25*80);
	creartablero(screen3);
	char* screen4=(char*)malloc(25*80);
	creartablero(screen4);
	char* screen5=(char*)malloc(25*80);
	creartablero(screen5);

	//START GAME:
	int thr=18*2,num=0,rand;
	rand=get_rand(&rand);
	char tablero[80][25];
	creartablero(&tablero);
	write(1,"\nPRESS ANY KEY TO START!",strlen("\nPRESS ANY KEY TO START!"));
	while (get_key(&empty)){} 
	while(1) { 
		if (cambio==1) tablero[78][rand%25]='\3';
		else tablero[1][rand%25]='\3';
		tablero[posx][posy]=' ';
		char direction;
		get_key(&direction);
		if (direction=='w' && posx>=0 && posx<80 && posy-1>=0 && posy-1<25 && tablero[posx][posy-1]!='\10'){
			if (tablero[posx][posy-1]=='\3') cambio=!cambio;
			--posy;
		} 
		else if (direction=='s' && posx>=0 && posx<80 && posy+1>=0 && posy+1<25 && tablero[posx][posy+1]!='\10'){
			if (tablero[posx][posy+1]=='\3') cambio=!cambio;
			++posy;
		} 
		else if (direction=='d'  && posx+1>=0 && posx+1<80 && posy>=0 && posy<25 && tablero[posx+1][posy]!='\10'){
			if (tablero[posx+1][posy]=='\3') cambio=!cambio;
			++posx;
		} 
		else if (direction=='a' && posx-1>=0 && posx-1<80 && posy>=0 && posy<25 && tablero[posx-1][posy]!='\10'){
			if (tablero[posx-1][posy]=='\3') cambio=!cambio;
			--posx;
		} 
		tablero[posx][posy]='A';
		put_screen(&tablero);
		++thr;
		if (thr>=18){
			thr=0;
			if (num==1) asignartablero(&tablero,screen2);
			else if (num==2) asignartablero(&tablero,screen3);
			else if (num==3) asignartablero(&tablero,screen4);
			else asignartablero(&tablero,screen5);
			num++;
			num=num%4;
		}
	}
}
