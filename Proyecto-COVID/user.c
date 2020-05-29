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
	char* test_screen = (char*)malloc(2000);
	put_screen(test_screen);
	write(1,"Syscalls checking (press any key to execute tests):",strlen("Syscalls checking (press any key to execute tests):"));
	char empty;

	//sys_get_key TESTS
	write(1,"\nget_key checking:",strlen("\nget_key checking:"));
	write(1,"\nSi no hay ningun elemento en el ring buffer devuelve un error (-ENOKEY == 126):\n",strlen("\nSi no hay ningun elemento en el ring buffer devuelve un error (-ENOKEY == 126):\n"));
	while (get_key(&empty)){} 
	get_key(&empty);
	itoa(errno,buff);
	write(1,buff,strlen(buff));
	write(1,"\n",strlen("\n"));

	write(1,"\nSi no hubiera control de escritura en el parametro, saltaria un page fault, como si que lo hay devuelve un error (-EFAULT == 14):\n",strlen("\nSi no hubiera control de escritura en el parametro, saltaria un page fault, como si que lo hay devuelve un error (-EFAULT == 14):\n"));
	while (get_key(&empty)){} 
	get_key(empty);
	itoa(errno,buff);
	write(1,buff,strlen(buff));
	write(1,"\n",strlen("\n"));

	write(1,"\nEsperamos a que mediante la interrupcion de teclado se anada una tecla al ring buffer y la printamos por pantalla:\n",strlen("\nEsperamos a que mediante la interrupcion de teclado se anada una tecla al ring buffer y la printamos por pantalla:\n"));
	while (get_key(&empty)){} 
	write(1,&empty,1);
	write(1,"\n",strlen("\n"));
	
	//sys_put_screen TESTS
	write(1,"\nput_screen checking:",strlen("\nput_screen checking:"));
	write(1,"\nSi no hubiera control de lectura en el parametro, saltaria un page fault, como si que lo hay devuelve un error (-EFAULT == 14):\n",strlen("\nSi no hubiera control de lectura en el parametro, saltaria un page fault, como si que lo hay devuelve un error (-EFAULT == 14):\n"));
	while (get_key(&empty)){} 
	put_screen(empty); 
	itoa(errno,buff);
	write(1,buff,strlen(buff));
	write(1,"\n",strlen("\n"));

	write(1,"\nAhora comprovaremos si imprime un tablero generado pseudo-aleatoriamente: ",strlen("\nAhora comprovaremos si imprime un tablero generado pseudo-aleatoriamente: "));
	creartablero(test_screen);
	while (get_key(&empty)){} 
	put_screen(test_screen);

	// MAX FPS CHECKING
	// char fps_screen[80][25];
	// creartablero(&fps_screen);
	// int n_put_screens=0;
	// int time=gettime();
	// while(1){
	// 	if (n_put_screens<=30){
	// 		++n_put_screens;
	// 		put_screen(&fps_screen);
	// 	}
	// 	int actual_time=gettime();
	// 	if (time+18<=actual_time){
	// 		time=actual_time;
	// 		itoa(n_put_screens,buff);
	// 		write(1,buff,strlen(buff));
	// 		n_put_screens=0;
	// 	}
	// }

	//malloc TESTS	
	while (get_key(&empty)){} 
	char empty_screen[80][25]={' '};
	put_screen(empty_screen);	
	malloc(-2000);
	write(1,"\nmalloc checking:",strlen("\nmalloc checking:"));
	write(1,"\nEsta syscall nos devolvera la direccion donde empieza el heap del proceso, el resultado que debemos ver por pantalla es (PAG_LOG_INIT_DATA+NUM_PAG_DATA)*PAGE_SIZE = 1163264\n",strlen("\nEsta syscall nos devolvera la direccion donde empieza el heap del proceso, el resultado que debemos ver por pantalla es (PAG_LOG_INIT_DATA+NUM_PAG_DATA)*PAGE_SIZE = 1163264\n"));
	while (get_key(&empty)){} 
	char* addr=malloc(0);
	itoa((int)addr,buff);
	write(1,buff,strlen(buff)); 
	write(1,"\n",strlen("\n"));

	write(1,"\nEsta syscall nos allocata 5 paginas nuevas i nos incrementa el heap a base+4096*5, nos devuelve la direccion donde empieza esta nueva zona\n",strlen("\nEsta syscall nos allocata 5 paginas nuevas i nos incrementa el heap a base+4096*5, nos devuelve la direccion donde empieza esta nueva zona\n"));
	while (get_key(&empty)){} 
	addr = malloc(4096*5);
	itoa((int)addr,buff);
	write(1,buff,strlen(buff));
	write(1,"\n",strlen("\n"));
	
	write(1,"\nEsta syscall alocata una pagina nueva i nos incrementa el heap en 1 ya que estamos en el inicio de una nueva pagina\n",strlen("\nEsta syscall alocata una pagina nueva i nos incrementa el heap en 1 ya que estamos en el inicio de una nueva pagina\n"));
	while (get_key(&empty)){} 
	addr = malloc(1);
	itoa((int)addr,buff);
	write(1,buff,strlen(buff));
	write(1,"\n",strlen("\n"));

	write(1,"\nEsta syscall libera una pagina i decrementa el heap en 20\n",strlen("\nEsta syscall libera una pagina i decrementa el heap en 20\n"));
	while (get_key(&empty)){} 
	addr = malloc(-20);
	itoa((int)addr,buff);
	write(1,buff,strlen(buff));
	write(1,"\n",strlen("\n"));

	write(1,"\nEsta syscall no necesita una nueva pagina por lo que solo incrementa el heap\n",strlen("\nEsta syscall no necesita una nueva pagina por lo que solo incrementa el heap\n"));
	while (get_key(&empty)){} 
	addr = malloc(10);
	itoa((int)addr,buff);
	write(1,buff,strlen(buff));
	write(1,"\n",strlen("\n"));

	put_screen(empty_screen);	
	write(1,"\nEsta syscall si que necesita una nueva pagina por lo que la alocata i incrementa el heap\n",strlen("\nEsta syscall si que necesita una nueva pagina por lo que la alocata i incrementa el heap\n"));
	while (get_key(&empty)){} 
	addr = malloc(25*80);
	itoa((int)addr,buff);
	write(1,buff,strlen(buff));
	write(1,"\n",strlen("\n"));	

	write(1,"\nEsta syscall devuelve un error (ENOMEM) ya que intenta pedir mas memoria de la que hay en total\n",strlen("\nEsta syscall devuelve un error (ENOMEM) ya que intenta pedir mas memoria de la que hay en total\n"));
	while (get_key(&empty)){} 
	addr= malloc(1024*4096);
	itoa(errno,buff);
	write(1,buff,strlen(buff));
	write(1,"\n",strlen("\n"));

	write(1,"\nEsta syscall devuelve un error (EPERM) ya que no hay tantas paginas alocatadas en el heap\n",strlen("\nEsta syscall devuelve un error (EPERM) ya que no hay tantas paginas alocatadas en el heap\n"));
	while (get_key(&empty)){} 
	addr= malloc(-1024*4096);
	itoa(errno,buff);
	write(1,buff,strlen(buff));
	write(1,"\n",strlen("\n"));

	write(1,"\nVolvemos a estar como antes de los juegos de prueba\n",strlen("\nVolvemos a estar como antes de los juegos de prueba\n"));
	while (get_key(&empty)){} 
	addr=malloc(-4096*5); 
	addr=malloc(-(25*80-9));
	itoa((int)addr,buff);
	write(1,buff,strlen(buff));
	write(1,"\n",strlen("\n"));

	char* screen2=(char*)malloc(25*80);
	creartablero(screen2);
	char* screen3=(char*)malloc(25*80);
	creartablero(screen3);
	char* screen4=(char*)malloc(25*80);
	creartablero(screen4);
	char* screen5=(char*)malloc(25*80);
	creartablero(screen5);

	//START GAME:
	int num=0,rand;
	int n_put_screens=0, time=gettime(), actual_time;
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
		if (n_put_screens<=180){
			++n_put_screens;
			put_screen(&tablero);
		}
		actual_time=gettime();
		if (time+18<=actual_time){
			time=actual_time;
			n_put_screens=0;
			if (num==1) asignartablero(&tablero,screen2);
			else if (num==2) asignartablero(&tablero,screen3);
			else if (num==3) asignartablero(&tablero,screen4);
			else asignartablero(&tablero,screen5);
			num++;
			num=num%4;
		}
	}
}
