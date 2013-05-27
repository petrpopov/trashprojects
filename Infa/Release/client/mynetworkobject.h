#ifndef MYNETWORKOBJECT_H
#define MYNETWORKOBJECT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>

#define GAME_NUM 10		//предельное число игр в списке, возвращаемом сервером
#define NAME_LENGTH 30		//предельная длина описания игры
#define LOGIK_LENGTH 2500	//предельная длина файла логики
#define MAP_SIZE 2500		//размер файла карты
#define COLS 20
#define ROWS 20

//В списке таких структур хранятся данные по доступным играм
struct game{
	char pid[7];		//pid процесса, ведущего данную игру
	char maxnum;		//предельное число игроков
	char curnum;		//текущее число игроков
	char name[NAME_LENGTH];	//описание игры
	struct game *next;	//ссылка на следующую игру
};

class MyNetworkObject {
	int sockfd;
	char *mapfile;
	char *vismap;
	char *printmap;
	unsigned short *robots;
	unsigned short *robots2;
	unsigned short *robots_old;
	int clearflag;
	
	void CreatePrintMap()
	{
		int xt,yt,n,N,k1,k2,i,j,dx=0,dy=0;
		for(i = 0; i < COLS*ROWS*2; i+=2){
			vismap[i] = '?';
			vismap[i+1] = '1';
		}
		vismap[((ROWS-robots[1])*COLS+robots[0]-1)*2] = mapfile[((ROWS-robots[1])*COLS+robots[0]-1)*2];
		vismap[((ROWS-robots[1])*COLS+robots[0]-1)*2+1] = mapfile[((ROWS-robots[1])*COLS+robots[0]-1)*2+1];
		for(j = 0; j < 4; j++){
			//printf("%d 1\n",j);
			if(j == 0){
				dx = 1;
				dy = 1;
			}else if(j == 1){
				dx = 1;
				dy = -1;
			}else if(j == 2){
				dx = -1;
				dy = 1;
			}else if(j == 3){
				dx = -1;
				dy = -1;
			}
			k1 = 6;
			k2 = 1;
			N = 6;
			do{
				k1--;
				n = 0;
				xt = robots[0];
				yt = robots[1];
				if(k1 == 1)
					N = 7;
				//
				//printf("luch: dx %d dy %d N %d k1 %d k2 %d\n",dx,dy,N,k1,k2);
				//
				while((n < N)&&(mapfile[((ROWS-yt)*COLS+xt-1)*2] != '#')){
					i = 0;
					while((i < k1)&&(mapfile[((ROWS-yt)*COLS+xt-1)*2] != '#')&&(n < N)){
						xt += dx;
						n++;
						i++;
						vismap[((ROWS-yt)*COLS+xt-1)*2] = mapfile[((ROWS-yt)*COLS+xt-1)*2];
						//printf("%c",mapfile[((ROWS-yt)*COLS+xt-1)*2]);
						vismap[((ROWS-yt)*COLS+xt-1)*2+1] = mapfile[((ROWS-yt)*COLS+xt-1)*2+1];
					}
					i = 0;
					while((i < k2)&&(mapfile[((ROWS-yt)*COLS+xt-1)*2] != '#')&&(n < N)){
						yt += dy;
						n++;
						i++;
						vismap[((ROWS-yt)*COLS+xt-1)*2] = mapfile[((ROWS-yt)*COLS+xt-1)*2];
						//printf("%c",mapfile[((ROWS-yt)*COLS+xt-1)*2]);
						vismap[((ROWS-yt)*COLS+xt-1)*2+1] = mapfile[((ROWS-yt)*COLS+xt-1)*2+1];
					}
				}
				//printf("\n");
				
				n = 0;
				xt = robots[0];
				yt = robots[1];
				//printf("luch: dx %d dy %d N %d k1 %d k2 %d\n",dx,dy,N,k1,k2);
				while((n < N)&&(mapfile[((ROWS-yt)*COLS+xt-1)*2] != '#')){
					i = 0;
					while((i < k1)&&(mapfile[((ROWS-yt)*COLS+xt-1)*2] != '#')&&(n < N)){
						yt += dy;
						n++;
						i++;
						vismap[((ROWS-yt)*COLS+xt-1)*2] = mapfile[((ROWS-yt)*COLS+xt-1)*2];
						//printf("%c",mapfile[((ROWS-yt)*COLS+xt-1)*2]);
						vismap[((ROWS-yt)*COLS+xt-1)*2+1] = mapfile[((ROWS-yt)*COLS+xt-1)*2+1];
					}
					i = 0;
					while((i < k2)&&(mapfile[((ROWS-yt)*COLS+xt-1)*2] != '#')&&(n < N)){
						xt += dx;
						n++;
						i++;
						vismap[((ROWS-yt)*COLS+xt-1)*2] = mapfile[((ROWS-yt)*COLS+xt-1)*2];
						//printf("%c",mapfile[((ROWS-yt)*COLS+xt-1)*2]);
						vismap[((ROWS-yt)*COLS+xt-1)*2+1] = mapfile[((ROWS-yt)*COLS+xt-1)*2+1];
					}
				}
				//printf("\n");
			}while(k1>1);
		}
		xt = robots[0];
		yt = robots[1];
		
		vismap[((ROWS-yt-1)*COLS+xt+1-1)*2] = mapfile[((ROWS-yt-1)*COLS+xt+1-1)*2];
		vismap[((ROWS-yt-1)*COLS+xt+1-1)*2+1] = mapfile[((ROWS-yt-1)*COLS+xt+1-1)*2+1];
		
		vismap[((ROWS-yt-1)*COLS+xt-1-1)*2] = mapfile[((ROWS-yt-1)*COLS+xt-1-1)*2];
		vismap[((ROWS-yt-1)*COLS+xt-1-1)*2+1] = mapfile[((ROWS-yt-1)*COLS+xt-1-1)*2+1];
		
		vismap[((ROWS-yt+1)*COLS+xt-1-1)*2] = mapfile[((ROWS-yt+1)*COLS+xt-1-1)*2];
		vismap[((ROWS-yt+1)*COLS+xt-1-1)*2+1] = mapfile[((ROWS-yt+1)*COLS+xt-1-1)*2+1];
		
		vismap[((ROWS-yt+1)*COLS+xt+1-1)*2] = mapfile[((ROWS-yt+1)*COLS+xt+1-1)*2];
		vismap[((ROWS-yt+1)*COLS+xt+1-1)*2+1] = mapfile[((ROWS-yt+1)*COLS+xt+1-1)*2+1];
		
		/*for(i = 0; i < ROWS; i++){
			for(j = 0; j < COLS; j++)
				printf("%c",vismap[(i*COLS+j)*2]);
			printf("\n");
		}*/
		
		for(i = 0; i < COLS*ROWS*2; i+=2){
			if((printmap[i] == 'H')||(printmap[i] == 'R')||(printmap[i] == 'F')){
				printmap[i] = mapfile[i];
				printmap[i+1] = mapfile[i+1];
			}
			if((printmap[i] == '?')&&(vismap[i] != '?')){
				printmap[i] = vismap[i];
				printmap[i+1] = vismap[i+1];
			}
		}
		/*
		for(i = 0; i < ROWS; i++){
			for(j = 0; j < COLS; j++)
				printf("%c",printmap[(i*COLS+j)*2]);
			printf("\n");
		}*/
	}
	public:
	MyNetworkObject():
		sockfd(0),
	mapfile(new char[COLS*ROWS*2]),
	vismap(new char[COLS*ROWS*2]),
	printmap(new char[COLS*ROWS*2]),
	robots(new unsigned short[8*2]),
	robots2(new unsigned short[8*2]),
	robots_old(new unsigned short[8*2]),
	clearflag(0)
	{
		for(int i = 0; i < COLS*ROWS*2; i+=2){
			mapfile[i] = '?';
			mapfile[i+1] = '1';
		}
		for(int i = 0; i < COLS*ROWS*2; i+=2){
			vismap[i] = '?';
			vismap[i+1] = '1';
		}
		for(int i = 0; i < COLS*ROWS*2; i+=2){
			printmap[i] = '?';
			printmap[i+1] = '1';
		}
		for(int i = 0; i < 16; i++){
			robots[i] = 0;
			robots2[i] = 0;
			robots_old[i] = 0;
		}
	}
	~MyNetworkObject()
	{
		delete(mapfile);
		delete(vismap);
		delete(printmap);
		delete(robots);
		delete(robots2);
		delete(robots_old);
	}
	int getData(char *map, int n)
	{
		unsigned short tmp = 100;
		fcntl(sockfd,F_SETFL,O_NONBLOCK);
		if(clearflag == 1){
			for(int i = 0; i < COLS*ROWS*2; i+=2){
				printmap[i] = '?';
				printmap[i+1] = '1';
			}
			for(int i = 0; i < 16; i++){
				robots[i] = 0;
				robots_old[i] = 0;
			}
			clearflag = 0;
		}
		//sleep(2);
		read(sockfd,&tmp,sizeof(unsigned short));
		ntohs(tmp);
		if(tmp == 100)
			return -1;
		if(tmp == 0){
			read(sockfd,&tmp,sizeof(unsigned short));
			ntohs(tmp);
			tmp++;
			//printf("Winner bot %d\n",tmp);
			clearflag = 1;
			return tmp;
		}
		//printf("Recieved:\n");
		for(int i = 0; i < tmp; i++){
			read(sockfd,&robots[2*i],sizeof(unsigned short));
			ntohs(robots[2*i]);
			read(sockfd,&robots[2*i+1],sizeof(unsigned short));
			ntohs(robots[2*i+1]);
			read(sockfd,&robots2[2*i],sizeof(unsigned short));
			ntohs(robots2[2*i]);
			read(sockfd,&robots2[2*i+1],sizeof(unsigned short));
			ntohs(robots2[2*i+1]);
			//printf("%d %d %d %d\n",robots[2*i],robots[2*i+1],robots2[2*i],robots2[2*i+1]);
		}
		//
		CreatePrintMap();
		//
		if((robots[0] != 0)&&(printmap[((ROWS-robots[1])*COLS+robots[0]-1)*2] != '?')){
			if(robots2[1] != 1){
				printmap[((ROWS-robots[1])*COLS+robots[0]-1)*2] = 'H';
				printmap[((ROWS-robots[1])*COLS+robots[0]-1)*2+1] = robots2[0] + '0';
			}else{
				printmap[((ROWS-robots[1])*COLS+robots[0]-1)*2] = 'F';
				printmap[((ROWS-robots[1])*COLS+robots[0]-1)*2+1] = robots2[0] + '0';
			}
		}
		for(int i = 1; i < tmp; i++){
			if((robots[2*i] != 0)&&(vismap[((ROWS-robots[2*i+1])*COLS+robots[2*i]-1)*2] != '?')){
				if(robots2[2*i+1] != 1){
					printmap[((ROWS-robots[2*i+1])*COLS+robots[2*i]-1)*2] = 'R';
					printmap[((ROWS-robots[2*i+1])*COLS+robots[2*i]-1)*2+1] = robots2[2*i] + '0';
				}else{
					printmap[((ROWS-robots[2*i+1])*COLS+robots[2*i]-1)*2] = 'F';
					printmap[((ROWS-robots[2*i+1])*COLS+robots[2*i]-1)*2+1] = robots2[2*i] + '0';
				}
			}
		}
		
		for(int i = 0; i < n; i++){
			map[i] = printmap[i];
		}
		return 0;
	}
	int create_game(char gtype, char pnum, char *gamename, char *logik, char* servIP, int servport)
	{
		//Проверка данных на входе
		if(((gtype != '1')&&(gtype != '2'))||((pnum < '1')&&(pnum > '4'))||(strlen(gamename) > NAME_LENGTH)||(strlen(logik) > LOGIK_LENGTH))
			return -8;
		int n,fd,i;
		char line[10];
		char map[20];
		char path[30];
		struct sockaddr_in servaddr;
		DIR *curdir;
		struct dirent *curfile;
		unsigned short size;
		
		//Создаём сокет
		if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
			return -1;
		}
		//Заполняем структуру, содержащую адрес сервера
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(servport);
		if(inet_aton(servIP,&servaddr.sin_addr) == 0){
			close(sockfd);
			return -2;
		}
		//Подключаемся к серверу
		if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
			close(sockfd);
			return -3;
		}
		//Создаём строку для отправки
		line[0] = 'c';	//Create
		line[1] = gtype;
		line[2] = pnum;
		line[3] = '\0';
		//Считаем длину строки и отправляем её
		size = strlen(line) + 1;
		htons(size);
		if((n = write(sockfd, &size, sizeof(unsigned short))) < 0){
			close(sockfd);
			return -4;
		}
		//Посылаем заявку на создание игры серверу
		if((n = write(sockfd, line, strlen(line)+1)) < 0){
			close(sockfd);
			return -4;
		}
		//Получаем от сервера ответ - имя карты
		if((n = read(sockfd, map, 20)) < 0){
			close(sockfd);
			return -5;
		}
		if(strcmp(map,"busy") == 0){
			close(sockfd);
			return -9;
		}
		//Открываем директорию с картами
		if(gtype == '1'){
			curdir = opendir("./.client_data/kmaps/find");
			strcpy(path,"./.client_data/kmaps/find/");
		}else if(gtype == '2'){
			curdir = opendir("./.client_data/kmaps/fight");
			strcpy(path,"./.client_data/kmaps/fight/");
		}else{
			return -8;
		}
		
		if(curdir == NULL){
			if(gtype == '1'){
				curdir = opendir("/.client_data/kmaps/find");
				strcpy(path,"/.client_data/kmaps/find/");
			}else if(gtype == '2'){
				curdir = opendir("/.client_data/kmaps/fight");
				strcpy(path,"/.client_data/kmaps/fight/");
			}else{
				return -8;
			}
		}
		
		if(curdir == NULL)
			return -10;
		//Ищем в ней нужную карту
		n = 0;
		while((curfile = readdir(curdir)) != NULL){
			if(strcmp(curfile->d_name,map) == 0)
				n = 1;
		}
		strcat(path,map);
		if(n == 1){	//Если карта не нужна, то говорим об этом
			strcpy(line,"r");
			//Считаем длину строки и отправляем её
			size = strlen(line) + 1;
			htons(size);
			if((n = write(sockfd, &size, sizeof(unsigned short))) < 0){
				close(sockfd);
				return -4;
			}
			//Отправляем саму строку
			if((n = write(sockfd, line, strlen(line)+1)) < 0){
				close(sockfd);
				return -4;
			}
			//Читаем карту
			if((fd = open(path,O_RDONLY)) < 0){
				close(sockfd);
				return -7;
			}
			i = 0;
			while((n = read(fd,mapfile+i,1)) != 0)
				i++;
			close(fd);
		//Синхронизация
			if((n = read(sockfd, line, 10)) < 0){
				close(sockfd);
				return -5;
			}
		}else{		//Если нужна, запрашиваем подкачку;
			strcpy(line,"n");
			//Считаем длину строки и отправляем её
			size = strlen(line) + 1;
			htons(size);
			if((n = write(sockfd, &size, sizeof(unsigned short))) < 0){
				close(sockfd);
				return -4;
			}
			//Отправляем саму строку
			if((n = write(sockfd, line, strlen(line)+1)) < 0){
				close(sockfd);
				return -4;
			}
			//Читаем данные карты
			if((n = read(sockfd, mapfile, MAP_SIZE*2)) < 0){
				close(sockfd);
				return -5;
			}
		//Создаём ей файл
			if((fd = open(path,O_WRONLY|O_CREAT,0666)) < 0){
				close(sockfd);
				return -7;
			}
		//Пишем в него
			if((n = write(fd,mapfile,strlen(mapfile))) < (int)strlen(mapfile)){
				close(sockfd);
				return -7;
			}
			close(fd);
		}
		for(int i = 0; i < COLS*ROWS*2; i+=2){
			if(mapfile[i] == '@'){
				mapfile[i] = ' ';
				mapfile[i+1] = '1';
			}
		}
		//Считаем длину строки и отправляем её
		size = strlen(logik) + 1;
		htons(size);
		if((n = write(sockfd, &size, sizeof(unsigned short))) < 0){
			close(sockfd);
			return -4;
		}
		//Посылвем логику серверу
		if((n = write(sockfd, logik, strlen(logik)+1)) < 0){
			perror(NULL);
			close(sockfd);
			return -4;
		}
	
		//Синхронизация
		if((n = read(sockfd, line, 10)) < 0){
			perror(NULL);
			close(sockfd);
			return -5;
		}
		
		//Считаем длину строки и отправляем её
		size = strlen(gamename) + 1;
		htons(size);
		if((n = write(sockfd, &size, sizeof(unsigned short))) < 0){
			close(sockfd);
			return -4;
		}
		//Посылаем имя игры
		if((n = write(sockfd, gamename, strlen(gamename)+1)) < 0){
			close(sockfd);
			return -4;
		}
		for(i = 0; i < COLS*ROWS; i+=2)
			if(mapfile[i] == '@'){
			mapfile[i] = ' ';
			mapfile[i+1] = '1';
			}
		
		//printf("Map:\n%s\n",mapfile);
		//Закрываем сокет
			return 0;
	}

/*Функция осуществляет поиск доступных игр
На входе:
	gtype - тип игры, 1 - поиск в лабиринте, 2 - схватка в лабиринте
	servIP - указатель на строку, содержащую IP сервера
	servport - порт сервера(51000)
	retroot - указатель на указатель на корень списка, куда всё и будет положено
	 
	Возвращает 0 в случае удачи, отрицательное чмсло в случае возникновения ошибки
	-1 - невозмодно создать сокет
	-2 - IP в недопустимом формате
	-3 - невозможно подключиться к серверу
	-4 - невозможно произвести запись в сокет
	-5 - невохможно читать из сокета
	-8 - ошибка в данных на входе*/
	int find_game(char gtype, char* servIP, int servport, struct game **retroot)
	{
		if((gtype != '1')&&(gtype != '2'))
			return -8;
		int n;
		char line[5];
		struct sockaddr_in servaddr;
		char recline[GAME_NUM*(NAME_LENGTH + 12)];
		unsigned short size;

		//Создаём сокет
		if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
			return -1;
		}
		//Заполняем структуру, содержащую адрес сервера
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(servport);
		if(inet_aton(servIP,&servaddr.sin_addr) == 0){
			close(sockfd);
			return -2;
		}
		//Подключаемся к серверу
		if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
			close(sockfd);
			return -3;
		}
		//Создаём строку для отправки
		line[0] = 'f';
		line[1] = gtype;
		line[2] = '\0';
		//Считаем длину строки и отправляем её
		size = strlen(line) + 1;
		htons(size);
		if((n = write(sockfd, &size, sizeof(unsigned short))) < 0){
			close(sockfd);
			return -4;
		}
		//Посылаем запрос данных
		if((n = write(sockfd, line, strlen(line)+1)) < 0){
			close(sockfd);
			return -4;
		}
		//Получаем от сервера строку - данные по имеющимся играм 
		if((n = read(sockfd, recline, GAME_NUM*(NAME_LENGTH + 5))) < 0){
			close(sockfd);
			return -5;
		}
		//Распарсиваем строку в список и возвращаем ссылку
		*retroot = create_game_list(recline);
		//Закрываем сокет
		close(sockfd);
		return 0;
	}

/*Разбирает поданную на вход строку (полученную от сервера)
	Создаёт из неё список структур game и возвращает указатель на его корень*/
	struct game *create_game_list(char *data){
		struct game *root = NULL, *p;
		int i;
		while(*data != '\0'){
			p = (struct game *)malloc(sizeof(struct game));
			i = 0;
			//for(data;*data != '\n';data++){
			while(*data != '\n'){
				p->name[i] = *data;
				i++;
				data++;
			}
			p->name[i] = '\0';
			data++;
			p->maxnum = *data;
			data++;
			p->curnum = *data;
			data++;
			for(i = 0;i < 6; i++){
				p->pid[i] = *data;
				data++;
			}
			p->pid[i] = '\0';
			data++;
			if(root == NULL){
				root = p;
				root->next = NULL;
			}else{
				p->next = root->next;
				root->next = p;
			}
		}
		return root;
	}

/*Функция осуществляет подключение к выбранной игре
На входе:
	gtype - тип игры, 1 - поиск в лабиринте, 2 - схватка в лабиринте
	pid - ссылка на строку, содержащую pid процесса, ведущего данную игру
	(строка лежит в поле pid структуры game, которую заполняет find_game)
	servIP - указатель на строку, содержащую IP сервера
	servport - порт сервера(51000)
	По ходу работы функция обращается к функции getlogik

	Возвращает 0 в случае удачи, отрицательное чмсло в случае возникновения ошибки
	-1 - невозмодно создать сокет
	-2 - IP в недопустимом формате
	-3 - невозможно подключиться к серверу
	-4 - невозможно произвести запись в сокет
	-5 - невохможно читать из сокета
	-8 - ошибка в данных на входе*/
	int join_game(char gtype, char *pid, char *logik, char *servIP, int servport)
	{
		int n,fd,i;
		char line[10];
		char map[20];
		char path[30];
		struct sockaddr_in servaddr;
		DIR *curdir = NULL;
		struct dirent *curfile;
		unsigned short size;
		
		//Проверка данных на входе
		if(((gtype != '1')&&(gtype != '2'))||((strlen(logik) > LOGIK_LENGTH)))
			return -8;
		
		//Создаём сокет
		if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
			return -1;
		}
		//Заполняем структуру, содержащую адрес сервера
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(servport);
		if(inet_aton(servIP,&servaddr.sin_addr) == 0){
			close(sockfd);
			return -2;
		}

		//Подключаемся к серверу
		if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
			close(sockfd);
			return -3;
		}

		//Создаём строку для отправки
		strcpy(line,"j");
		strcat(line,pid);
		//Считаем длину строки и отправляем её
		size = strlen(line) + 1;
		htons(size);
		if((n = write(sockfd, &size, sizeof(unsigned short))) < 0){
			close(sockfd);
			return -4;
		}
		//Посылаем запрос на присоединение к игре
		if((n = write(sockfd, line, strlen(line)+1)) < 0){
			close(sockfd);
			return -4;
		}

		//Получаем от сервера ответ - имя карты
		if((n = read(sockfd, map, 20)) < 0){
			close(sockfd);
			return -5;
		}
		//Открываем директорию с картами
		if(gtype == '1'){
			curdir = opendir("./.client_data/kmaps/find");
			strcpy(path,"./.client_data/kmaps/find/");
		}else if(gtype == '2'){
			curdir = opendir("./.client_data/kmaps/fight");
			strcpy(path,"./.client_data/kmaps/fight/");
		}else{
			return -8;
		}
		
		if(curdir == NULL){
			if(gtype == '1'){
				curdir = opendir("/.client_data/kmaps/find");
				strcpy(path,"/.client_data/kmaps/find/");
			}else if(gtype == '2'){
				curdir = opendir("/.client_data/kmaps/fight");
				strcpy(path,"/.client_data/kmaps/fight/");
			}else{
				return -8;
			}
		}
		
		if(curdir == NULL)
			return -10;
		//Ищем в ней нужную карту
		n = 0;
		while((curfile = readdir(curdir)) != NULL){
			if(strcmp(curfile->d_name,map) == 0)
				n = 1;
		}
		strcat(path,map);
		if(n == 1){	//Если карта не нужна, то говорим об этом
			strcpy(line,"r");
			//Считаем длину строки и отправляем её
			size = strlen(line) + 1;
			htons(size);
			if((n = write(sockfd, &size, sizeof(unsigned short))) < 0){
				close(sockfd);
				return -4;
			}
			if((n = write(sockfd, line, strlen(line)+1)) < 0){
				close(sockfd);
				return -4;
			}
			//Читаем карту
			if((fd = open(path,O_RDONLY)) < 0){
				close(sockfd);
				return -7;
			}
			i = 0;
			while((n = read(fd,mapfile+i,1)) != 0)
				i++;
			close(fd);
			//Синхронизация
			if((n = read(sockfd, line, 10)) < 0){
				close(sockfd);
				return -5;
			}
		}else{		//Если нужна, запрашиваем подкачку;
			strcpy(line,"n");
			//Считаем длину строки и отправляем её
			size = strlen(line) + 1;
			htons(size);
			if((n = write(sockfd, &size, sizeof(unsigned short))) < 0){
				close(sockfd);
				return -4;
			}
			if((n = write(sockfd, line, strlen(line)+1)) < 0){
				close(sockfd);
				return -4;
			}
			//Читаем данные карты
			if((n = read(sockfd, mapfile, MAP_SIZE*2)) < 0){
				close(sockfd);
				return -5;
			}
			//Создаём ей файл
			if((fd = open(path,O_WRONLY|O_CREAT,0666)) < 0){
				close(sockfd);
				return -7;
			}
			//Пишем в него
			if((n = write(fd,mapfile,strlen(mapfile))) < (int)strlen(mapfile)){
				close(sockfd);
				return -7;
			}
			close(fd);
		}
		for(int i = 0; i < COLS*ROWS*2; i+=2){
			if(mapfile[i] == '@'){
				mapfile[i] = ' ';
				mapfile[i+1] = '1';
			}
		}
		//Считаем длину строки и отправляем её
		size = strlen(logik) + 1;
		htons(size);
		if((n = write(sockfd, &size, sizeof(unsigned short))) < 0){
			close(sockfd);
			return -4;
		}
		//Посылвем логику серверу
		if((n = write(sockfd, logik, strlen(logik)+1)) < 0){
			perror(NULL);
			close(sockfd);
			return -4;
		}
		for(i = 0; i < COLS*ROWS; i+=2)
			if(mapfile[i] == '@'){
			mapfile[i] = ' ';
			mapfile[i+1] = '1';
			}
		//printf("Map:\n%s\n",mapfile);
		//Закрываем сокет
			return 0;
	}
};
#endif
