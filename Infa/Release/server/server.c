#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <sys/shm.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <math.h>
#include "parser.h"

#define GAME_NUM 10	//Число игр в отсылаемом списке
#define NAME_LENGTH 30
#define MAP_SIZE 2500

//В списке таких структур хранятся данные о имеющихся картах
struct maps{
	char *file;
	struct maps *next;
};

//Лидер хранит в списке таких структур pid` ы подчинённых
struct pids{
	int pid;
	struct pids *next;
};

//Шаблон сообщения от игрового процесса к координатору
struct msg1{
	long mtype;
	struct{
		char code;	//состояние
		int pid;	//pid игрового процесса
		int type;	//тип игры
		int maxnum;	//число игроков
		int curnum;	//текущее число игроков
		char name[NAME_LENGTH];	//имя игры
	} data;
};

//Шаблон сообщения от координатора к игровому процессу
struct msg2{
	long mtype;
	int pid;	//pid нового подчинённого
};

//Шаблон стартового сообщения от лидера к подчинённому
struct msg3{
	long mtype;
	struct{
		int type;
		int num;
		int shmid1;	//shmid для карты
		int shmid2;	//shmid для объектов
		char map[20];	//имя карты
	} data;
};

//Шаблон сообщения с докладом статуса
struct msg4{
	long mtype;
	char status;	//состояние
};

//Шаблон сообщения с данными сделанного хода
struct msg5{
	long mtype;
	struct{
		char number;
		char action[20];
	} data;
};

//Структура описывает недособранную игру в процессе-координаторе
struct game{
	int pid;
	int maxnum;
	int curnum;
	char name[NAME_LENGTH];
	struct game *next;
};


/*Отвечает за создание новой игры
На входе:
	newsock - сокет, через который ведётся общение с клиентом
	msqid - идентификатор очереди сообщений для общения
	type - тип игры
	num - число игроков
	maps - указатель на список карт соответствующего типа
	nmap - число карт в списке, чтобы лишний раз не считать*/
int new_game(int newsock, int msqid, char type, char num, struct maps *maps, int nmaps, float timeout);

/*Отвечает за получение данных для инициализации игры
На входе:
	newsock - сокет для общения
	mapname - имя карты, выбранной для игры
	map - ссылка на массив с данными карты
	logik - адрес, куда будет загружена логика 1 игрока
	gamename - адрес, куда будет загружено описание игры*/
int getstartdata(int newsock, char *mapname, char *map, char *logik, char *gamename, float timeout);

//Вставляет в список root новую игру, беря данные из buf
struct game *addgame(struct game *root, struct msg1 *buf);

//Изменяет число игроков в игре, описанной в buf
int updgame(struct game *root, struct msg1 *buf);

//Удаляет из списка игру, описанную вbuf
int delgame(struct game **root, struct msg1 *buf);

//Собирает из списка игр строку и отсылает её клиенту
int send_game_list(struct game *pg, int newsockfd);

void CreateKnownMap(int x, int y, int pid, char *mapdata);

void CreateEnemiesList(int number, int mynum, int x, int y, int *obj, struct enemy *enemy);

void SetEnemiesStat(int number, struct enemy *enemy, struct enemies *enemies);

void CreateWaypointsList(int x, int y);

void SetWaypointsStat();

//Читает очередное число из файла fd
int getconfig(int fd);

/*Читает из сокета socket блок данных не более maxsize в массив line*/
int safelygetdata(int socket, char *line, int maxsize, float timeout);

/*Отвечает за получение данных от подключившегося игрока
На входе:
	newsock - сокет для общения
	mapname - имя карты, выбранной для игры
	map - ссылка на массив с данными карты
	logik - адрес, куда будет загружена логика*/
int getdata(int newsock, char *mapname, char *map, char *logik, float timeout);

/*Отвечает зв введение нового игрока в игру
На входе:
	neswock - сокет для общения
	msqid - идентифик очереди сообщений для общения
	leadpid - pid процесаа-лидера*/
int join_game(int newsock, int msqid, int leadpid, float timeout);

int main()
{
	struct msg2 mestogp;
	struct msg1 mesforsup;
	struct game *rootfind = NULL,*rootfight = NULL,*gr;
	struct sockaddr_in servaddr,cliaddr;
	DIR *curdir;
	struct dirent *mapfile;
	int nummap1=0,nummap2=0;
	int n,clilen,i,j,res,msqid,maxlen = NAME_LENGTH + 3 + sizeof(char) + 4*sizeof(int);
	key_t key;
	int sockfd,newsockfd;
	char line[10],exbyte;
	char *tline;
	pid_t pid;
	struct maps *maps1,*maps2,*p;
	int fd, port, childnum, childcur = 0;
	float timeout;
	
	//Получаем очередь сообщений
	if((msqid = msgget(IPC_PRIVATE, 0666|IPC_CREAT)) < 0){
		printf("Can`t get msqid!\n");
		exit(-1);
	}

	//Открываем конфигурационный файл
	if((fd = open("gameserv.conf",O_RDONLY)) < 0){
		printf("Can`t open config file!\n");
		exit(-1);
	}
	
	//Читаем из него настройки
	port = getconfig(fd);
	childnum = getconfig(fd);
	timeout = (float)getconfig(fd)/10;

	//И закрываем
	if(close(fd) < 0){
		printf("Can`t close config file!\n");
		exit(-1);
	}
	
	printf("Looking for maps...\n");
	//Сканируем директорию с картами для игры первого типа и создаем список
	curdir = opendir("./smaps/find");
	if(curdir == NULL){
		printf("Error on opening /smaps/find\n");
		exit(-1);
	}
	maps1 = NULL;
	while((mapfile = readdir(curdir)) != NULL){
		if(mapfile->d_name[0] != '.'){
			nummap1++;
			if(maps1 == NULL){
				maps1 = (struct maps *)malloc(sizeof(struct maps));
				maps1->file = mapfile->d_name;
				maps1->next = NULL;
			}else{
				p = (struct maps *)malloc(sizeof(struct maps));
				p->file = mapfile->d_name;
				p->next = maps1->next;
				maps1->next = p;
			}
		}
	}
	//Сканируем директорию с картами для игры второго типа м создаем список
	curdir = NULL;
	curdir = opendir("./smaps/fight");
	if(curdir == NULL){
		printf("Error on opening /smaps/fight\n");
		exit(-1);
	}
	maps2 = NULL;
	while((mapfile = readdir(curdir)) != NULL){
		if(mapfile->d_name[0] != '.'){
			nummap2++;
			if(maps2 == NULL){
				maps2 = (struct maps *)malloc(sizeof(struct maps));
				maps2->file = mapfile->d_name;
				maps2->next = NULL;
			}else{
				p = (struct maps *)malloc(sizeof(struct maps));
				p->file = mapfile->d_name;
				p->next = maps2->next;
				maps2->next = p;
			}
		}
	}
	//печатаем отчёт о найденных картах
	printf("Available maps:\n");
	p = maps1;
	while(p != NULL){
		printf("%s\n",p->file);
		p = p->next;
	}
	printf("Total %d finding maps\n",nummap1); 
	p = maps2;
	while(p != NULL){
		printf("%s\n",p->file);
		p = p->next;
	}
	printf("Total %d fighting maps\n",nummap2);
	
	//Создаём сокет
	if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror(NULL);
		exit(-1);
	}
	//Заполняем структуру адреса сервера
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//Биндим сокет
	if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
		perror(NULL);
		close(sockfd);
		exit(-1);
	}
	//Переводим его в слушающий режим
	if(listen(sockfd, 5) < 0){
		perror(NULL);
		close(sockfd);
		exit(-1);
	}
	printf("Server succesfully started.\n\n");
	
	while(1){
		clilen = sizeof(cliaddr);
		//Ловим вызов, создаём присоединённый сокет
		if((newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) < 0){
			perror(NULL);
			close(sockfd);
			exit(-1);
		}
		//Читаем сообщение
		if((n = safelygetdata(newsockfd, line, 8, timeout)) < 0){
			close(newsockfd);
		}else{
			//printf("SUPERVISOR: recieved from client '%s'\n",line);
			//Убиваем всех наплодившихся зомби
			while((n = waitpid(-1,NULL,WNOHANG)) > 0);
			//Получаем сообщения от игровых процессов
			while((n = msgrcv(msqid, (struct msgbuf *)&mesforsup,maxlen,1,IPC_NOWAIT)) > 0){
				//Если там сообщение о создании новой игры, то добавляем её
				switch(mesforsup.data.code){
				case 'n':
					{
						//увеличиваем число задействованных процессов
						childcur += mesforsup.data.maxnum;
						//добавляем игру в список
						switch(mesforsup.data.type){
						case 1:
							rootfind = addgame(rootfind,&mesforsup);
							break;
						case 2:
							rootfight = addgame(rootfight,&mesforsup);
							break;
						default:
							//printf("SUPERVISOR: unknown type of game created!\n");
							break;
						}
					}
					break;
				//Если сообщение о новых игроках, вносим изменения в данные
				case 'u':
					{
						switch(mesforsup.data.type){
						case 1:
							updgame(rootfind,&mesforsup);
							break;
						case 2:
							updgame(rootfight,&mesforsup);
							break;
						default:
							//printf("SUPERVISOR: unknown type of game to update!\n");
							break;
						}
					}
					break;
				//Если сообщение о старте игры - удаляем её из списка
				case 'e':
					{
						//уменьшаем число задействованных процессов
						childcur -= mesforsup.data.maxnum;
						//удаляем игру из списка
						switch(mesforsup.data.type){
						case 1:
							delgame(&rootfind,&mesforsup);
							break;
						case 2:
							delgame(&rootfight,&mesforsup);
							break;
						default:
							//printf("SUPERVISOR: unknown type of game to delete!\n");
							break;
						}
					}
					break;
				default:
					//printf("SUPERVISOR: unknown type of message!\n");
					break;
				}
			}
		
			printf("SUPERVISOR: children %d / %d\n",childcur,childnum);
			switch(line[0]){
			//Если в сообщении от клиента заявка на создание игры
			case 'c':
				{
					//printf("SUPERVISOR: user wants to create new game\n");
					//Если не хватает лимита процессов, сообщаем об этом
					if((line[2]-'0' < 1)||(line[2]-'0' > 4)){
						printf("SUPERVISOR: user wants to create game for %c players! Rejecting.\n",line[2]);
						close(newsockfd);
					}else if((childnum - childcur) < (line[2] - '0')){
						printf("SUPERVISOR: rejecting to user - too many processes\n");
						write(newsockfd, "busy", 5);
						close(newsockfd);
					}else{
					//Иначе работаем
						pid = fork();
						if(pid < 0){
							printf("SUPERVISOR: Can`t fork child!\n");
							exit(-1);
						}else if(pid == 0){
							//Ребёнок обрабатывает запрос
							close(sockfd);
							//Определяем тип игры и вызов функции обработки
							switch(line[1]){
							case '1':
								new_game(newsockfd, msqid, line[1], line[2], maps1, nummap1, timeout);
								break;
							case '2':
								new_game(newsockfd, msqid, line[1], line[2], maps2, nummap2, timeout);
								break;
							default:
								printf("SUPERVISOR: user wants to create game of unknown type!\n");
								close(newsockfd);
								break;
							}
							return 0;
						}else if(pid > 0){
							//Родитель уходит дальше слушать порт
							close(newsockfd);
						}
					}
				}
				break;
			case 'f':	//Если запрос на поиск игры
				{
					//printf("SUPERVISOR: user wants to find game\n");
					//Определяем, какой список нам нужен и посылаем
					switch(line[1]){
					case '1':
						send_game_list(rootfind, newsockfd);
						break;
					case '2':
						send_game_list(rootfight, newsockfd);
						break;
					default:
						printf("SUPERVISOR: user wants to find game of unknown type!\n");
						break;
					}
					close(newsockfd);
				}
				break;
			case 'j':	//Если заявка на присоединение к игре
				{
					//printf("SUPERVISOR: user wants to join game\n");
					tline = line;	//Подсчитываем pid нужного процесса по строке
					tline++;
					n = 0;
					for(i = 0; i < 6; i++){
						n = n*10;
						n = n + (*tline - '0');
						tline++;
					}			//теперь в n pid
					pid = fork();
					if(pid < 0){
						printf("SUPERVISOR: Can`t fork child!\n");
						exit(-1);
					}else if(pid > 0){
					//Родитель посылает сообщение лидеру о новом подключении
						close(newsockfd);
						mestogp.mtype = n;
						mestogp.pid = pid;
						msgsnd(msqid, (struct msgbuf *)&mestogp, sizeof(int),0);
					}else if(pid == 0){
					//Ребёнок подключается к игре
						close(sockfd);
						join_game(newsockfd, msqid, n, timeout);
						return 0;
					}
				}
				break;
			default:
				{
					printf("SUPERVISOR: can`t understand what user wants\n");
					close(newsockfd);
				}
				break;
			}
		}
	}
	return 0;
}


int new_game(int newsock, int msqid, char type, char num, struct maps *maps, int nmaps, float timeout)
{
	struct pids *pw,*pp,*firstworker = NULL;
	struct msg5 mesact[8];
	struct msg4 mesforl;
	struct msg3 mestow;
	struct msg2 mesforgp;
	struct msg1 mestosup;
	char line [10];
	int n,i,j,number,len,fd;
	pid_t pid;
	struct maps *p;
	char mapname[30];
	char gamename[NAME_LENGTH];
	int curnumber = 0;
	int shmid_map, shmid_obj;
	char *mapdata;
	int *obj;
	char tmp;
	char *fullmap = (char *)malloc(MAP_SIZE*2);
	int mcount,ocount;
	int winner = -1;
	int aliveflag,alivenum;
	char myaction[20];
	int timeleft = 1000;
	waypoints  = (struct waypoints*)malloc(sizeof(struct waypoints));

	number = num - '0';
	//Получаем свой PID
	pid = getpid();
	//Инициализируем им генератор случайных чисел
	srand((unsigned int)pid);
	//Получаем случайное число от 1 до nmaps
	n = 1 + (int)(nmaps*(float)(rand()-1)/RAND_MAX);
	
	if(type == '1'){
		strcpy(mapname,"./smaps/find/");
	}else if(type == '2'){
		strcpy(mapname,"./smaps/fight/");
	}
	
	//Определяем карту с соответствующим номером
	p = maps;
	for(i = 1; i < n; i++)
		p = p->next;
	strcat(mapname,p->file);
	
	//Создаём  и аттачим разделяемую память
	if((shmid_map = shmget(IPC_PRIVATE, MAP_SIZE, 0666)) < 0){
		printf("Can`t create shared memmory!\n");
		exit(-1);
	}
	if((shmid_obj = shmget(IPC_PRIVATE, 50*sizeof(int), 0666)) < 0){
		printf("Can`t create shared memmory!\n");
		exit(-1);
	}
	if((mapdata = (char *)shmat(shmid_map,NULL,0)) == (char *)(-1)){
		printf("Can`t attach shm!\n");
		exit(-1);
	}
	if((obj = (int *)shmat(shmid_obj,NULL,0)) == (int *)(-1)){
		printf("Can`t attach shm!\n");
		exit(-1);
	}
	//Открываем карту
	if((fd = open(mapname,O_RDONLY)) < 0){
		printf("Can`t open map file!\n");
		close(newsock);
		exit(-1);
	}
	//Читаем в shared memmory только объекты
	//И полностью в массив
	i = 0;
	j = 0;
	while((n = read(fd,mapdata + i,1)) != 0){
		*(fullmap+j) = *(mapdata+i);
		i++;
		j++;
		n = read(fd,fullmap+j,1);
		j++;
	}
	close(fd);
	
	//Если удалось инициализировать игру
	if((i = getstartdata(newsock, p->file, fullmap, bot.logik, gamename, timeout)) == 0){
	//Посылаем отчёт координатору
		curnumber = 1;
		mestosup.mtype = 1;
		mestosup.data.code = 'n';
		mestosup.data.pid = (int)pid;
		mestosup.data.type = type - '0';
		strcpy(mestosup.data.name,gamename);
		mestosup.data.maxnum = number;
		mestosup.data.curnum = 1;
		len = strlen(mestosup.data.name) + 1 + 5*sizeof(int);
		msgsnd(msqid, (struct msgbuf *)&mestosup,len,0);			
		//printf("\nGAME LEADER %d: game created.\n\tname - %s\n\ttype - %c\n\tplayers - %c\n\tmap - %s\n",(int)pid,gamename,type,num,mapname);
	}
	//Инициализируем бота
	bot.health = 100;
	bot.drivemode = 1;
	mcount = 0;
	ocount = 0;
	while(*(mapdata+mcount) != '@')
		mcount++;
	bot.x = ((mcount+1)% COLS);
	bot.y = ROWS - (int)((mcount+1)/COLS);
	bot.dir = *(fullmap+mcount*2+1) - '0';
	//И заносим эти данные в общее пользование
	*(obj + ocount++) = bot.x;
	*(obj + ocount++) = bot.y;
	*(obj + ocount++) = bot.health;
	*(obj + ocount++) = bot.dir;
	*(obj + ocount++) = bot.drivemode;
	*(obj + ocount++) = 0;	//Флаг повреждений
	mcount++;
	
	//Пока игра недособрана
	while(number > curnumber){
	//Получаем сообщения от координатора с pid`ами подчинённых
		if((i = msgrcv(msqid, (struct msgbuf *)&mesforgp,sizeof(int),(int)pid,0)) > 0){
			//Заносим данные в новую структуру
			pw = (struct pids *)malloc(sizeof(struct pids));
			pw->next = NULL;
			pw->pid = mesforgp.pid;
			//Посылаем подчинённому стартовое сообщение
			mestow.mtype = mesforgp.pid;
			mestow.data.shmid1 = shmid_map;
			mestow.data.shmid2 = shmid_obj;
			mestow.data.type = type - '0';
			mestow.data.num = number;
			strcpy(mestow.data.map,p->file);
			len = strlen(mestow.data.map) + 1 + 4*sizeof(int);
			msgsnd(msqid, (struct msgbuf *)&mestow, len, 0);
			//И ждём от него отчёт о статусе
			msgrcv(msqid, (struct msgbuf *)&mesforl,sizeof(int),(int)pid,0);
			//Если он 'r'eady
			if(mesforl.status == 'r'){
				//добавляем его
				curnumber++;
				if(firstworker == NULL){
					firstworker = pw;
				}else{
					pp = firstworker;	//В конец списка!!!
					while(pp->next != NULL)
						pp = pp->next;
					//pw->next = firstworker->next;
					pp->next = pw;
				}
				//Ставим его на карту
				while(*(mapdata+mcount) != '@')
					mcount++;
				*(obj + ocount++) = ((mcount+1) % COLS);
				*(obj + ocount++) = ROWS - (int)((mcount+1)/COLS);
				*(obj + ocount++) = 100;
				*(obj + ocount++) = *(fullmap+mcount*2+1) - '0';
				*(obj + ocount++) = 1;
				*(obj + ocount++) = 0;
				mcount++;
				//Сообщаем ему его номер
				mesforl.status = curnumber - 1 + '0';
				mesforl.mtype = pw->pid;
				msgsnd(msqid, (struct msgbuf *)&mesforl,1,0);
				//и сообщаем об этом координатору
				mestosup.data.code = 'u';
				mestosup.data.curnum = curnumber;
				len = strlen(mestosup.data.name) + 1 + 5*sizeof(int);
				msgsnd(msqid, (struct msgbuf *)&mestosup,len,0);
			//иначе просто сбрасываем
			}else{
				free(pw);
			}
		}
	}
	free(fullmap);
	//по завершении сообщаем об этом координатору
	mestosup.data.code = 'e';
	len = strlen(mestosup.data.name) + 1 + 5*sizeof(int);
	msgsnd(msqid, (struct msgbuf *)&mestosup,len,0);
	//Убиваем лишние точки старта
	while(mcount < ROWS*COLS){
		if(*(mapdata+mcount) == '@')
			*(mapdata+mcount) = ' ';
		mcount++;
	}
	
	for(i = 0; i < ROWS; i++)
		for(j = 0; j < COLS; j++){
			tmpmap[i][j] = mapdata[i*COLS+j];
			map[i][j] = '?';
		}

	SendSituation(newsock,obj,number,0);
	while(winner < 0){
		SendSituation(newsock,obj,number,0);
		//Рассылаем всем сообщение, что пора гамать
		pw = firstworker;
		while(pw != NULL){
			mesforl.mtype = pw->pid;
			mesforl.status = 't';	//turn
			msgsnd(msqid, (struct msgbuf *)&mesforl,1,0);
			pw = pw->next;
		}

		/*for(i = 0; i < ROWS; i++){
			for(j = 0; j < COLS; j++){
				printf("%c",mapdata[COLS*i+j]);
			}
			printf("\n");
		}*/
		
		CreateKnownMap(*obj,*(obj+1),(int)pid,mapdata);
		CreateEnemiesList(number, 0, *obj, *(obj+1), obj, enemy);
		//for(i = 0; i < number; i++)
		//	printf("Game leader %d Enemy %d: x %d y %d health %d timesee %d timefight %d probability %d distance %d PRI %d\n", (int)pid, i,enemy[i].x, enemy[i].y, enemy[i].health, enemy[i].timesee, enemy[i].timefight, enemy[i].probability, enemy[i].distance, enemy[i].priority);
		SetEnemiesStat(number, enemy, &enemies);
		//printf("Game leader %d Enemies %d Hmin %d: Hmax %d Havg %d Dmin %d Dmax %d Davg %d TSmin %d TSmax %d TSavg %d TFmin %d TFmax %d TFavg %d\n", (int)pid, enemies.Number, enemies.HealthMin,enemies.HealthMax,enemies.HealthAvg, enemies.DistanceMin,enemies.DistanceMax,enemies.DistanceAvg, enemies.TimeSeeMin,enemies.TimeSeeMax,enemies.TimeSeeAvg, enemies.TimeFightMin,enemies.TimeFightMax,enemies.TimeFightAvg);
		CreateWaypointsList(*obj, *(obj+1));
		SetWaypointsStat();
			
		bot.x = *obj;
		bot.y = *(obj+1);
		bot.health = *(obj+2);
		bot.dir = *(obj+3);
		bot.drivemode = *(obj+4);
		bot.num = 0;
		
		//printf("Game leader %d:\nMy x: %d. My y: %d. My health %d. My dir %d. My drivemode %d\n",(int)pid,bot.x,bot.y,bot.health,bot.dir,bot.drivemode);
		
		/*struct waypoint *wp;
		wp = waypoint;
		while(wp != NULL){
			printf("Game leader %d Waypoint x %d y %d dist %d min %d max %d avg %d PRI %d\n",(int)pid,wp->x,wp->y,wp->distance,wp->MinNewDist,wp->MaxNewDist,wp->AvgNewDist,wp->priority);
			wp = wp->next;
		}
		*/
		//printf("Game leader %d Waypoints distmin %d distmax %d distavg %d MinND %d MaxND %d AND %d Num %d\n",(int)pid,waypoints->DistMin,waypoints->DistMax,waypoints->DistAvg,waypoints->MinNewDist,waypoints->MaxNewDist,waypoints->AvgNewDist,waypoints->Number);
		
		if(bot.health > 0){
			n = parse(myaction);
			if(n < 0)
				strcpy(myaction,"wa");
		}else{
			strcpy(myaction,"wa");
		}
		//printf("0 %s\n",myaction);
		
		for(i = 1; i < number; i++){
			msgrcv(msqid, (struct msgbuf *)&mesact[i],50,(int)pid,0);
			//printf("%c %s\n",mesact[i].data.number,mesact[i].data.action);
		}
		
		for(i = 0; i < number; i++){
			*(obj + i*6+5) = 0;
		}
		
		for(i = 1; i < number; i++){
			bot.num = mesact[i].data.number - '0';
			bot.x = *(obj+bot.num*6);
			bot.y = *(obj+bot.num*6+1);
			bot.health = *(obj+bot.num*6+2);
			bot.dir = *(obj+bot.num*6+3);
			j = UpdateMap(mesact[i].data.action,&winner,obj,type);
			*(obj + bot.num*6) = bot.x;
			*(obj + bot.num*6+1) = bot.y;
			*(obj + bot.num*6+2) = bot.health;
			*(obj + bot.num*6+3) = bot.dir;
			*(obj + bot.num*6+4) = bot.drivemode;
			if(j == 1){
				*(obj + bot.num*6+5) = 1;
			}
		}
		
		bot.x = *obj;
		bot.y = *(obj+1);
		bot.health = *(obj+2);
		bot.dir = *(obj+3);
		bot.drivemode = *(obj+4);
		bot.num = 0;
			
		j = UpdateMap(myaction,&winner,obj,type);
		*(obj + bot.num*6) = bot.x;
		*(obj + bot.num*6+1) = bot.y;
		*(obj + bot.num*6+2) = bot.health;
		*(obj + bot.num*6+3) = bot.dir;
		*(obj + bot.num*6+4) = bot.drivemode;
		if(j == 1){
			*(obj + bot.num*6+5) = 1;
		}
		
		for(i = 0; i < ROWS; i++)
			for(j = 0; j < COLS; j++)
				mapdata[i*COLS+j] = tmpmap[i][j];
		
		//Проверка выживших
		aliveflag = 0;
		for(i = 0; i < number; i++)
			if(*(obj+i*6+2) > 0){
				aliveflag++;
				alivenum = i;
			}
		if(aliveflag == 0){
			winner = 49;	//Draw!
		}
		if((aliveflag == 1)&&(type == '2')){
			winner = alivenum;
		}
		timeleft--;
		if(timeleft == 0)
			winner = 49;
	}
	//winner = 49 - draw!
	if(winner != 0){
		SendSituation(newsock,obj,0,winner);
		//printf("Winner: bot %d!!!\n",winner);
	}else{
		SendSituation(newsock,obj,0,99);
		//printf("I win!!!\n");
	}
	
	pw = firstworker;
	while(pw != NULL){
		mesforl.mtype = pw->pid;
		mesforl.status = winner + '0';	//номер победителя
		msgsnd(msqid, (struct msgbuf *)&mesforl,1,0);
		pw = pw->next;
	}
	
	//удаляем shared memmory
	shmdt(mapdata);
	shmdt(obj);
	shmctl(shmid_map,IPC_RMID,(struct shmid_ds *)NULL);
	shmctl(shmid_obj,IPC_RMID,(struct shmid_ds *)NULL);
	close(newsock);
	return 0;
}

int join_game(int newsock, int msqid, int leadpid, float timeout)
{
	struct msg4 mestol;
	struct msg3 mesforw;
	struct msg5 mesact;
	int maxlen = 11 + 4*sizeof(int);
	int len;
	pid_t pid;
	char *mapdata;
	int *obj;
	int stat;
	char mynum;
	int number;
	int i,j,n,fd;
	char mappath[25];
	char *fullmap = (char*)malloc(MAP_SIZE*2);
	unsigned short finflg = 0;
	waypoints  = (struct waypoints*)malloc(sizeof(struct waypoints));
	
	pid = getpid();
	srand((unsigned int)pid);
	//Ждём сообщения от лидера с необходимыми данными
	msgrcv(msqid, (struct msgbuf *)&mesforw,maxlen,(int)pid,0);
	//Аттачим shared memmory
	if((mapdata = (char *)shmat(mesforw.data.shmid1,NULL,SHM_RDONLY)) == (char *)(-1)){
		printf("Can`t attach shm!\n");
		exit(-1);
	}
	if((obj = (int *)shmat(mesforw.data.shmid2,NULL,SHM_RDONLY)) == (int *)(-1)){
		printf("Can`t attach shm!\n");
		exit(-1);
	}
	
	number = mesforw.data.num;
	if(mesforw.data.type == 1){
		strcpy(mappath,"./smaps/find/");
		strcat(mappath,mesforw.data.map);
	}else if(mesforw.data.type == 2){
		strcpy(mappath,"./smaps/fight/");
		strcat(mappath,mesforw.data.map);
	}
	
	//Открываем карту
	if((fd = open(mappath,O_RDONLY)) < 0){
		printf("Can`t open map file!\n");
		close(newsock);
		exit(-1);
	}
	//Читаем в shared memmory только объекты
	//И полностью в массив
	i = 0;
	while((n = read(fd,fullmap + i,1)) != 0)
		i++;
	close(fd);
	
	//Получаем данные от клиента
	if((stat = getdata(newsock, mesforw.data.map, fullmap, bot.logik, timeout)) < 0){
		printf("GAME WORKER %d: can`t get data. Informing leader.\n",(int)pid);
		mestol.mtype = leadpid;
		mestol.status = 'e';
		msgsnd(msqid, (struct msgbuf *)&mestol,1,0);
		return -1;
	}
	free(fullmap);
	//Сообщаем лидеру о своей готовности
	mestol.mtype = leadpid;
	mestol.status = 'r';
	msgsnd(msqid, (struct msgbuf *)&mestol,1,0);
	
	//Получаем от него свой номер
	msgrcv(msqid, (struct msgbuf *)&mestol,1,(int)pid,0);
	mynum = mestol.status;
	
	mesact.mtype = leadpid;
	mesact.data.number = mynum;
	mynum -= '0';
	for(i = 0; i < ROWS; i++)
		for(j = 0; j < COLS; j++)
			map[i][j] = '?';
	
	msgrcv(msqid, (struct msgbuf *)&mestol,1,(int)pid,0);
	SendSituation(newsock,obj,mesforw.data.num,mynum);
	while(mestol.status == 't'){
		SendSituation(newsock,obj,mesforw.data.num,mynum);
		//printf("Game worker %d %c:\nMy x: %d. My y: %d. My health %d. My dir %d. My drivemode %d\n",(int)pid,mynum,*(obj+mynum*6),*(obj+mynum*6+1),*(obj+mynum*6+2),*(obj+mynum*6+3),*(obj+mynum*6+4));
		if(*(obj+mynum*6+2) > 0){//Если жив
			//Заполнение данными всего, что надо парсеру
			bot.x = *(obj+mynum*6);
			bot.y = *(obj+mynum*6+1);
			bot.health = *(obj+mynum*6+2);
			bot.dir = *(obj+mynum*6+3);
			bot.drivemode = *(obj+mynum*6+4);
			CreateKnownMap(*(obj+mynum*6),*(obj+mynum*6+1),(int)pid,mapdata);
			CreateEnemiesList(number, mynum, *(obj+mynum*6), *(obj+mynum*6+1), obj, enemy);
			SetEnemiesStat(number, enemy, &enemies);
			CreateWaypointsList(*(obj + mynum*6), *(obj+mynum*6+1));
			SetWaypointsStat();
			
			/*for(i = 0; i < number; i++)
				printf("Game process %d Enemy %d: x %d y %d health %d timesee %d timefight %d probability %d distance %d PRI %d\n", (int)pid, i,enemy[i].x, enemy[i].y, enemy[i].health, enemy[i].timesee, enemy[i].timefight, enemy[i].probability, enemy[i].distance, enemy[i].priority);
			printf("Game process %d Enemies %d Hmin %d: Hmax %d Havg %d Dmin %d Dmax %d Davg %d TSmin %d TSmax %d TSavg %d TFmin %d TFmax %d TFavg %d\n", (int)pid, enemies.Number, enemies.HealthMin,enemies.HealthMax,enemies.HealthAvg, enemies.DistanceMin,enemies.DistanceMax,enemies.DistanceAvg, enemies.TimeSeeMin,enemies.TimeSeeMax,enemies.TimeSeeAvg, enemies.TimeFightMin,enemies.TimeFightMax,enemies.TimeFightAvg);
			
			struct waypoint *wp;
			wp = waypoint;
			while(wp != NULL){
				printf("Game process %d Waypoint x %d y %d dist %d min %d max %d avg %d PRI %d\n",(int)pid,wp->x,wp->y,wp->distance,wp->MinNewDist,wp->MaxNewDist,wp->AvgNewDist,wp->priority);
				wp = wp->next;
			}
			printf("Game worker %d Waypoints distmin %d distmax %d distavg %d MinND %d MaxND %d AND %d Num %d \n",(int)pid,waypoints->DistMin,waypoints->DistMax,waypoints->DistAvg,waypoints->MinNewDist,waypoints->MaxNewDist,waypoints->AvgNewDist,waypoints->Number);
			*/
			//Вызов парсера
			stat = parse(mesact.data.action);
			if(stat < 0)
				strcpy(mesact.data.action,"wa");
		}else{
			strcpy(mesact.data.action,"wa");
		}
		len = strlen(mesact.data.action) + 1 + sizeof(char);
		msgsnd(msqid, (struct msgbuf *)&mesact,len,0);
		msgrcv(msqid, (struct msgbuf *)&mestol,1,(int)pid,0);
	}
	if(mestol.status-'0' != mynum){
		SendSituation(newsock,obj,0,mestol.status-'0');
	}else{
		SendSituation(newsock,obj,0,99);
	}
	//write(newsock,&finflg,sizeof(unsigned short));
	//Отдетачиваем shared memmory
	shmdt(mapdata);
	shmdt(obj);
	close(newsock);
	
	return 0;
}

int getstartdata(int newsock, char *mapname, char *map, char *logik, char *gamename, float timeout)
{
	char line[10],exbyte;
	int n,i,fd;
	pid_t pid = getpid();
	
	//printf("GAME LEADER %d: sending map name: %s\n",(int)pid,mapname);
	//Посылаем имя выбранной карты клиенту
	if(n = write(newsock, mapname, strlen(mapname)+1) < 0){
		printf("Can`t write to socket!\n");
		close(newsock);
		exit (-1);
	}
	//printf("GAME LEADER %d: waiting for answer\n",(int)pid);
	
	if((n = safelygetdata(newsock, line, 2, timeout)) < 0){
		close(newsock);
		exit(-1);
	}
	
	if(line[0] == 'r'){	//Если нет
		//printf("GAME LEADER %d: client has this map\n",(int)pid);
		//Подтверждаем приём (исключительно для синхронизации)
		if(n = write(newsock, line, strlen(line)+1) < 0){
			printf("Can`t write to socket!\n");
			close(newsock);
			exit (-1);
		}
	}else if(line[0] == 'n'){	//Если да
		//printf("GAME LEADER %d: client needs to download map\n",(int)pid);
		//отсылаем
		if((n = write(newsock, map, strlen(map)+1)) < 0){
			printf("Can`t write to socket!\n");
			close(newsock);
			exit(-1);
		}
		//printf("GAME LEADER %d: map sended\n",(int)pid);
	}
	
	//printf("GAME LEADER %d: waiting for logik\n",(int)pid);
	if((n = safelygetdata(newsock, logik, LOGIK_LENGTH + 1, timeout)) < 0){
		close(newsock);
		exit(-1);
	}
	
	//printf("GAME LEADER %d: logik recieved\n",(int)pid);
	//Подтверждаем приём (исключительно для синхронизации)
	if(n = write(newsock, line, strlen(line)+1) < 0){
		printf("Can`t write to socket!\n");
		close(newsock);
		exit (-1);
	}
	
	//printf("GAME LEADER %d: waiting for game name\n",(int)pid);

	if((n = safelygetdata(newsock, gamename, NAME_LENGTH + 1, timeout)) < 0){
		close(newsock);
		exit(-1);
	}
	
	//printf("GAME LEADER %d: name recieved\n",(int)pid);
	return 0;
}

int getdata(int newsock, char *mapname, char *map, char *logik, float timeout)
{
	char line[10],exbyte;
	int n,i,fd;
	pid_t pid = getpid();
	
	//printf("GAME WORKER %d: sending map name: %s\n",(int)pid,mapname);
	//Посылаем имя выбранной карты клиенту
	if(n = write(newsock, mapname, strlen(mapname)+1) < 0){
		printf("Can`t write to socket!\n");
		close(newsock);
		return -1;
	}
	//printf("GAME WORKER %d: waiting for answer\n",(int)pid);
	
	if((n = safelygetdata(newsock, line, 2, timeout)) < 0){
		close(newsock);
		return -1;
	}
	
	if(line[0] == 'r'){	//Если нет
		//printf("GAME WORKER %d: client has this map\n",(int)pid);
		//Подтверждаем приём (исключительно для синхронизации)
		if(n = write(newsock, line, strlen(line)+1) < 0){
			printf("Can`t write to socket!\n");
			close(newsock);
			return -1;
		}
	}else if(line[0] == 'n'){	//Если да
		//printf("GAME WORKER %d: client needs to download map\n",(int)pid);
		//отсылаем
		if((n = write(newsock, map, strlen(map)+1)) < 0){
			printf("Can`t write!\n");
			close(newsock);
			return -1;
		}
		//printf("GAME WORKER %d: map sended\n",(int)pid);
	}
	
	//printf("GAME WORKER %d: waiting for logik\n",(int)pid);

	if((n = safelygetdata(newsock, logik, LOGIK_LENGTH + 1, timeout)) < 0){
		close(newsock);
		return -1;
	}
	
	//printf("GAME WORKER %d: logik recieved\n",(int)pid);
	return 0;
}

struct game *addgame(struct game *root, struct msg1 *buf){
	struct game *p;
	if(root == NULL){
		root = (struct game *)malloc(sizeof(struct game));
		root->pid = buf->data.pid;
		root->maxnum = buf->data.maxnum;
		root->curnum = buf->data.curnum;
		strcpy(root->name,buf->data.name);
		root->next = NULL;
	}else{
		p = (struct game *)malloc(sizeof(struct game));
		p->pid = buf->data.pid;
		p->maxnum = buf->data.maxnum;
		p->curnum = buf->data.curnum;
		strcpy(p->name,buf->data.name);
		p->next = root->next;
		root->next = p;
	}
	return root;
}

int updgame(struct game *root, struct msg1 *buf){
	struct game *p;
	p = root;
	while(p->pid != buf->data.pid){
		p = p->next;
	}
	p->curnum = buf->data.curnum;
	return 0;
}

int delgame(struct game **root, struct msg1 *buf){
	struct game *p,*p1;
	p = *root;
	while(p->pid != buf->data.pid){
		p1 = p;
		p = p->next;
	}
	if(p != *root){
		p1->next = p->next;
		free(p);
	}else{
		*root = p->next;
		free(p);
	}
	return 0;
}

int send_game_list(struct game *pg, int newsockfd){
	int n = 0,i,j;
	char tmp[2],tmp1[7];
	char sendline[GAME_NUM*(NAME_LENGTH + 12)] = "";
	tmp[1] = '\0';
	while((pg != NULL)&&(n < 10)){
		strcat(sendline,pg->name);
		strcat(sendline,"\n");
		tmp[0] = '0' + pg->maxnum;
		strcat(sendline,tmp);
		tmp[0] = '0' + pg->curnum;
		strcat(sendline,tmp);
		j = pg->pid;
		for(i = 0;i < 6;i++){
			tmp1[5-i] = '0' + (j % 10);
			j = (int)(j/10);
		}
		tmp1[6] = '\0';
		strcat(sendline,tmp1);
		strcat(sendline,"\n");
		pg = pg->next;
		n++;
	}
	if(n = write(newsockfd, sendline, strlen(sendline)+1) < 0){
		close(newsockfd);
		exit (-1);
	}
	//printf("### send %s\n",sendline);
	return 0;
}

int getconfig(int fd)
{
	char a,state = 'g';
	int res = 0;
	while(read(fd,&a,1) > 0){
		if(isdigit(a)){
			state = 'w';
			res = res * 10;
			res = res + a - '0';
		}else if((!isdigit(a))&&(state == 'w')){
			return res;
		}
	}
	return 0;
}

int safelygetdata(int socket, char *line, int maxsize, float timeout)
{
	short int size;
	int n,i;
	char *oldline;
	char tmp;
	oldline = line;
	strcpy(line,"");
	fcntl(socket,F_SETFL,O_NONBLOCK);
	sleep(5*timeout);
	//for(i = 0; i < timeout; i++)
	//	for(n = 0; n < timeout; n++){}
	
	if((n = read(socket, &size, sizeof(unsigned short))) < 0){
		printf("Can`t get size of network message!\n");
		return -1;
	}
	ntohs(size);
	//printf("### size %d\n",size);
	if(size > maxsize){
		printf("Too big network message!\n");
		return -1;
	}
	sleep(timeout);
	//for(i = 0; i < timeout; i++)
	//	for(n = 0; n < timeout; n++){}
	while((size > 0)&&((n = read(socket,line,size)) > 0)){
		size = size - n;
		line = line + n;
		sleep(timeout);
		//for(i = 0; i < timeout; i++)
		//	for(n = 0; n < timeout; n++){}
	}
	if(size > 0){
		printf("Connection interrupted!\n");
		return -1;
	}
	n = read(socket,&tmp,1);
	if((size == 0)&&(n > 0)){
		printf("Extra data found!\n");
		return -1;
	}
	//printf("### line %s\n",oldline);
	return 0;
}

int SendSituation(int newsock,int *obj,int num,int mynum)
{
	int n,i;
	unsigned short tmp;
	tmp = num;
	htons(tmp);
	if((n = write(newsock, &tmp, sizeof(unsigned short))) < 0){
		close(newsock);
		printf("Can`t write to socket!\n");
		return -1;
	}
	
	//если конец игры - посылаем номер победителя
	if(num == 0){
		tmp = mynum;
		htons(tmp);
		if((n = write(newsock, &tmp, sizeof(unsigned short))) < 0){
			close(newsock);
			printf("Can`t write to socket!\n");
			return -1;
		}
		return 0;
	}
	
	n = *(obj + mynum*6);
	tmp = n;
	htons(tmp);
	if((n = write(newsock, &tmp, sizeof(unsigned short))) < 0){
		close(newsock);
		printf("Can`t write to socket!\n");
		return -1;
	}
	n = *(obj + mynum*6 + 1);
	tmp = n;
	htons(tmp);
	if((n = write(newsock, &tmp, sizeof(unsigned short))) < 0){
		close(newsock);
		printf("Can`t write to socket!\n");
		return -1;
	}
	n = *(obj + mynum*6 + 3);
	tmp = n;
	htons(tmp);
	if((n = write(newsock, &tmp, sizeof(unsigned short))) < 0){
		close(newsock);
		printf("Can`t write to socket!\n");
		return -1;
	}
	n = *(obj + mynum*6 + 5);
	tmp = n;
	htons(tmp);
	if((n = write(newsock, &tmp, sizeof(unsigned short))) < 0){
		close(newsock);
		printf("Can`t write to socket!\n");
		return -1;
	}
	
	for(i = 0; i < num ; i++){
		if(i != mynum){
			n = *(obj + i*6);
			tmp = n;
			htons(tmp);
			if((n = write(newsock, &tmp, sizeof(unsigned short))) < 0){
				close(newsock);
				printf("Can`t write to socket!\n");
				return -1;
			}
			n = *(obj + i*6 + 1);
			tmp = n;
			htons(tmp);
			if((n = write(newsock, &tmp, sizeof(unsigned short))) < 0){
				close(newsock);
				printf("Can`t write to socket!\n");
				return -1;
			}
			n = *(obj + i*6 + 3);
			tmp = n;
			htons(tmp);
			if((n = write(newsock, &tmp, sizeof(unsigned short))) < 0){
				close(newsock);
				printf("Can`t write to socket!\n");
				return -1;
			}
			n = *(obj + i*6 + 5);
			tmp = n;
			htons(tmp);
			if((n = write(newsock, &tmp, sizeof(unsigned short))) < 0){
				close(newsock);
				printf("Can`t write to socket!\n");
				return -1;
			}
		}
	}
	
	return 0;
}

void CreateKnownMap(int x, int y, int pid, char *mapdata)
{
	int robots[2];
	robots[0] = x;
	robots[1] = y;
	
	int xt,yt,n,N,k1,k2,i,j,dx,dy;
	for(i = 0; i < COLS*ROWS; i++){
		vismap[i] = '?';
	}
	vismap[((ROWS-robots[1])*COLS+robots[0]-1)] = mapdata[((ROWS-robots[1])*COLS+robots[0]-1)];
	for(j = 0; j < 4; j++){
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

			while((n < N)&&(mapdata[((ROWS-yt)*COLS+xt-1)] != '#')){
				i = 0;
				while((i < k1)&&(mapdata[((ROWS-yt)*COLS+xt-1)] != '#')&&(n < N)){
					xt += dx;
					n++;
					i++;
					vismap[((ROWS-yt)*COLS+xt-1)] = mapdata[((ROWS-yt)*COLS+xt-1)];
				}
				i = 0;
				while((i < k2)&&(mapdata[((ROWS-yt)*COLS+xt-1)] != '#')&&(n < N)){
					yt += dy;
					n++;
					i++;
					vismap[((ROWS-yt)*COLS+xt-1)] = mapdata[((ROWS-yt)*COLS+xt-1)];
				}
			}
			
			n = 0;
			xt = robots[0];
			yt = robots[1];
			while((n < N)&&(mapdata[((ROWS-yt)*COLS+xt-1)] != '#')){
				i = 0;
				while((i < k1)&&(mapdata[((ROWS-yt)*COLS+xt-1)] != '#')&&(n < N)){
					yt += dy;
					n++;
					i++;
					vismap[((ROWS-yt)*COLS+xt-1)] = mapdata[((ROWS-yt)*COLS+xt-1)];;
				}
				i = 0;
				while((i < k2)&&(mapdata[((ROWS-yt)*COLS+xt-1)] != '#')&&(n < N)){
					xt += dx;
					n++;
					i++;
					vismap[((ROWS-yt)*COLS+xt-1)] = mapdata[((ROWS-yt)*COLS+xt-1)];
				}
			}
		}while(k1>1);
	}
	xt = robots[0];
	yt = robots[1];
	
	vismap[((ROWS-yt-1)*COLS+xt+1-1)] = mapdata[((ROWS-yt-1)*COLS+xt+1-1)];;
	
	vismap[((ROWS-yt-1)*COLS+xt-1-1)] = mapdata[((ROWS-yt-1)*COLS+xt-1-1)];
	
	vismap[((ROWS-yt+1)*COLS+xt-1-1)] = mapdata[((ROWS-yt+1)*COLS+xt-1-1)];
	
	vismap[((ROWS-yt+1)*COLS+xt+1-1)] = mapdata[((ROWS-yt+1)*COLS+xt+1-1)];
	
	for(i = 0; i < ROWS; i++)
		for(j = 0; j < COLS; j++){
			if(map[i][j] == '@')
				map[i][j] = mapdata[i*COLS+j];
			if((map[i][j] == '?')&&(vismap[i*COLS+j] != '?'))
				map[i][j] = vismap[i*COLS+j];
			if(vismap[i*COLS+j] == '@')
				map[i][j] = vismap[i*COLS+j];
		}
	
	/*printf("GAME PROCESS %d: my known map:\n",pid);
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLS; j++)
			printf("%c",map[i][j]);
		printf("\n");
	}*/
}

void CreateWaypointsList(int x, int y)
{
	int i,j,k;
	struct waypoint *wp,*pwp;
	
	wp = waypoint;
	while(wp != NULL){
		while(wp->next != NULL){
			pwp = wp;
			wp = wp->next;	
		}
		
		free(wp);
		if(wp != waypoint){
			pwp->next = NULL;
		}else{
			waypoint = NULL;
		}
		wp = waypoint;
	}
	
	waypoint = (struct waypoint *)malloc(sizeof(struct waypoint));
	waypoint->next = NULL;
	wp = waypoint;
	for(i = 1; i < ROWS-1; i++){
		for(j = 1; j < COLS-1; j++){
			if(((map[i][j] == ' ')||(map[i][j] == '@'))&&((map[i+1][j] == '?')||(map[i-1][j] == '?')||(map[i][j+1] == '?')||(map[i][j-1] == '?'))){
				wp->y = ROWS - i;
				wp->x = j + 1;
				wp->distance = Volna(x,y,wp->x,wp->y);
				if(wp->distance > 0){
					wp->MaxNewDist = -1000;
					wp->MinNewDist = 1000;
					if(wp != waypoint){
						wp->next = waypoint->next;
						waypoint->next = wp;
					}
					wp = (struct waypoint *)malloc(sizeof(struct waypoint));
				}
			}
		}
	}
	if(waypoint->distance <= 0)
		waypoint = NULL;
	wp = waypoint;
	while(wp != NULL){
		pwp = waypoint;
		j = 0;
		k = 0;
		while(pwp != NULL){
			if(pwp != wp){
				i = Volna(wp->x,wp->y,pwp->x,pwp->y);
				if(i > wp->MaxNewDist)
					wp->MaxNewDist = i;
				if(i < wp->MinNewDist)
					wp->MinNewDist = i;
				j += i;
			}
			pwp = pwp->next;
			k++;
		}
		if(k > 1){
			wp->AvgNewDist = (int)(j/(k-1));
		}else{
			wp->AvgNewDist = 0;
		}
		wp = wp->next;
	}
}

void SetWaypointsStat()
{
	struct waypoint *wp;
	wp = waypoint;
	int i,n = 0;
	waypoints->DistMin = 1000;
	waypoints->MinNewDist = 1000;
	waypoints->DistMax = -1000;
	waypoints->MaxNewDist = -1000;
	waypoints->DistAvg = 0;
	waypoints->AvgNewDist = 0;
		
	while(wp != NULL){
		n++;
		waypoints->DistAvg +=  wp->distance;
		if(wp->distance < waypoints->DistMin)
			waypoints->DistMin = wp->distance;
		if(wp->distance > waypoints->DistMax)
			waypoints->DistMax = wp->distance;
		if(wp->MinNewDist < waypoints->MinNewDist)
			waypoints->MinNewDist = wp->MinNewDist;
		if(wp->MaxNewDist > waypoints->MaxNewDist)
			waypoints->MaxNewDist = wp->MaxNewDist;
		waypoints->AvgNewDist += wp->AvgNewDist;
		wp = wp->next;
	}
	if(n != 0){
		waypoints->DistAvg = (int)(waypoints->DistAvg/n);
		waypoints->AvgNewDist = (int)(waypoints->AvgNewDist/n);
	}
	waypoints->Number = n;
}

void CreateEnemiesList(int number, int mynum, int x, int y, int *obj, struct enemy *enemy)
{
	int i,dir;
	
	dir = *(obj + mynum*6 +3);
	
	for(i = 0; i < number; i++){
		if(i == mynum){
			enemy->probability = -100;
		}else{
			enemy->number = i;
			enemy->x = *(obj + i*6);
			enemy->y = *(obj + i*6 + 1);
			enemy->health = *(obj + i*6 + 2);
			if(vismap[(ROWS-(enemy->y))*COLS + (enemy->x) - 1] == '@'){
				enemy->probability = 100;
				enemy->timesee = 0;
				enemy->distance = Volna(*(obj+mynum*6),*(obj+mynum*6+1),enemy->x,enemy->y);
			}else{
				enemy->timesee++;
				enemy->probability = 49 - (((enemy->x)-x)*((enemy->x)-x) + ((enemy->y)-y)*((enemy->y)-y));
				enemy->distance = 10;
			}
			if(enemy->probability < 0)
				enemy->probability = 0;
			//Переход к относительным координатам
			if(vismap[(ROWS-(enemy->y))*COLS + (enemy->x) - 1] == '@'){
				//printf("### 1 %d %d %d %d %d\n",dir,x,y,enemy->x,enemy->y);
				if(dir == 1){
					enemy->x = enemy->x - x;
					enemy->y = enemy->y - y;
				}else if(dir == 2){
					enemy->x = y - enemy->y;
					enemy->y = enemy->x - x;
				}else if(dir == 3){
					enemy->y = y - enemy->y;
					enemy->x = x - enemy->x;
				}else if(dir == 4){
					enemy->x = enemy->y - y;
					enemy->y = x - enemy->x;
				}
				//printf("### 2 %d %d %d %d %d\n",dir,x,y,enemy->x,enemy->y);
			}else{
				enemy->x = 100;
				enemy->y = 100;
				//printf("### 3 %d %d %d %d %d\n",dir,x,y,enemy->x,enemy->y);
			}
		}
		enemy++;
	}
	for(i = number; i < 8; i++){
		enemy->probability = -200;
		enemy++;
	}
}

void SetEnemiesStat(int number, struct enemy *enemy, struct enemies *enemies)
{
	int i,n = 0,dmin=1000,dmax=-1000,d=0,hmin=1000,hmax=-1000,h=0,tsmin=1000,tsmax=-1000,ts=0,tfmin=1000,tfmax=-1000,tf=0;
	if(number > 1){
		for(i = 0; i < number; i++){
			if(enemy->probability > 0){
				n++;
				h = h + enemy->health;
				d = d + enemy->distance;
				ts = ts + enemy->timesee;
				tf = tf + enemy->timefight;
				if(enemy->health < hmin)
					hmin = enemy->health;
				if(enemy->health > hmax)
					hmax = enemy->health;
				if(enemy->distance < dmin)
					dmin = enemy->distance;
				if(enemy->distance > dmax)
					dmax = enemy->distance;
				if(enemy->timesee < tsmin)
					tsmin = enemy->timesee;
				if(enemy->timesee > tsmax)
					tsmax = enemy->timesee;
				if(enemy->timefight < tfmin)
					tfmin = enemy->timefight;
				if(enemy->timefight > tfmax)
					tfmax = enemy->timefight;
			}
			enemy++;
		}
		enemies->HealthMin = hmin;
		enemies->HealthMax = hmax;
		enemies->DistanceMin = dmin;
		enemies->DistanceMax = dmax;
		enemies->TimeSeeMin = tsmin;
		enemies->TimeSeeMax = tsmax;
		enemies->TimeFightMin = tfmin;
		enemies->TimeFightMax = tfmax;
		if(n != 0){
			enemies->TimeSeeAvg = (int)(ts/n);
			enemies->DistanceAvg = (int)(d/n);
			enemies->HealthAvg = (int)(h/n);
			enemies->TimeFightAvg = (int)(tf/n);
		}
	}
	enemies->Number = n;
}

int Volna(int xst, int yst, int xfin, int yfin)
{
	int i,j,n,k;
	for(i = 0; i < ROWS; i++)
		for(j = 0; j < COLS; j++)
			volna[i][j] = -1;
	volna[ROWS - yst][xst - 1] = 0;
	n = 0;
	k = 1;
	while((volna[ROWS-yfin][xfin-1] == -1)&&(k == 1)){
		k = 0;
		for(i = 1; i < ROWS; i++)
			for(j = 1; j < COLS; j++){
				if(bot.drivemode == 1){
					if(((map[i][j]==' ')||(map[i][j]=='@'))&&(volna[i][j] == -1)){
						if((volna[i+1][j] == n)||(volna[i-1][j] == n)||(volna[i][j+1] == n)||(volna[i][j-1] == n)){
							volna[i][j] = n+1;
							k = 1;
						}
					}
				}else if(bot.drivemode == 2){
					if((map[i][j]==' ')&&(volna[i][j] == -1)&&((map[i+1][j] != '@')||((i+1 == ROWS-bot.y)&&(j == bot.x-1)))&&((map[i-1][j] != '@')||((i-1 == ROWS-bot.y)&&(j == bot.x-1)))&&((map[i][j+1] != '@')||((i == ROWS-bot.y)&&(j+1 == bot.x-1)))&&((map[i][j-1] != '@')||(i == ROWS-bot.y)&&(j-1 == bot.x-1))){
						if((volna[i+1][j] == n)||(volna[i-1][j] == n)||(volna[i][j+1] == n)||(volna[i][j-1] == n)){
							volna[i][j] = n+1;
							k = 1;
						}
					}
				}
			}
		n++;
	}
	if(k == 1)
		return n;
	return -1;
}
