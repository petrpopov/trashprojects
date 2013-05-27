#define STACK_DEPTH 25
#define ROWS 20
#define COLS 20
#define LOGIK_LENGTH 2500

char map[ROWS][COLS];
char vismap[ROWS*COLS];
char tmpmap[ROWS][COLS];
int volna[ROWS][COLS];

struct bot{
	int num;
	char logik[LOGIK_LENGTH];
	int x;
	int y;
	int dir;
	int health;
	int drivemode;
};

struct enemies{
	int DistanceMin;
	int DistanceMax;
	int DistanceAvg;
	int HealthMin;
	int HealthMax;
	int HealthAvg;
	int TimeSeeMin;
	int TimeSeeMax;
	int TimeSeeAvg;
	int TimeFightMin;
	int TimeFightMax;
	int TimeFightAvg;
	int Number;
};

struct enemy{
	int number;
	int x;
	int y;
	int health;
	int timesee;
	int timefight;
	int probability;
	int distance;
	long priority;
};

struct waypoint{
	int x;
	int y;
	int distance;
	int MinNewDist;
	int MaxNewDist;
	int AvgNewDist;
	long priority;
	struct waypoint *next;
};

struct waypoints{
	int DistMin;
	int DistMax;
	int DistAvg;
	int MinNewDist;
	int MaxNewDist;
	int AvgNewDist;
	int Number;
};

struct bot bot;

struct enemy target;

struct enemies enemies;

struct waypoints *waypoints = NULL;

struct enemy enemy[8];
int encalc;

struct waypoint *waypoint = NULL;
struct waypoint *wpcalc;
struct waypoint wpactive;

int Line(int num, int *xlp, int *ylp);
char ObjectAtPointPrivate(int xr, int yr);

int parse(char *response)
{
	int result,i,j;

	strcpy(response,"");

	int stat,time = 1;
	char word[30] = "";
	char *p = bot.logik;
	int EndIf[STACK_DEPTH];
	int ifdepth = 0,oldifdepth,DoIf = 0;
	char ch[7];
	ch[6] = '\0';
	stat = getword(&p,word);
	EndIf[0] = 1;
	for(i = 1; i < STACK_DEPTH; i++)
		EndIf[i] = 0;

	//Пока не кончились слова и единицы действия
	while((stat > 0)&&(time > 0)){
			//Если слово if
		if(strcmp(word,"if") == 0)
		{
			//Переходим к обработчику
			result = ProceedIf(&p);
			//И печатаем результат
			if(result == -1){
				return -1;
			}
			getword(&p,word);
			if(strcmp(word,"{") != 0){
				return -1;
			}
			//Если if был неверный
			if(result == 0){
				//Пока не наткнёмся на блок, который надо выполнить
				while(DoIf == 0){
					//Пропускаем текущий блок
					oldifdepth = ifdepth;
					ifdepth++;
					do{
						if(getword(&p,word) == 0){
							return -1;
						}
						if(strcmp(word,"{") == 0)
							ifdepth++;
						if(strcmp(word,"}") == 0)
							ifdepth--;
					}while(ifdepth > oldifdepth);

					//Берём новое слово
					if(getword(&p,word) == 0){
						return -1; //???
					}
					//Если там else
					if(strcmp(word,"else") == 0){
						getword(&p,word);
						if(strcmp(word,"{") != 0){
							return -1;
						}
						//То его надо выполнять
						DoIf = 1;
						ifdepth++;
						//Причём это конец if`а
						EndIf[ifdepth] = 1;
						//Берём новое слово
						stat = getword(&p,word);
					//Если там elseif
					}else if(strcmp(word,"elseif") == 0){
						//Считаем условие
						result = ProceedIf(&p);
						if(result == -1){
							return -1;
						}
						getword(&p,word);
						if(strcmp(word,"{") != 0){
							return -1;
						}
						//Если оно верно
						if(result == 1){
							//То его надо выполнять
							DoIf = 1;
							ifdepth++;
							//Берём новое слово
							stat = getword(&p,word);
						}else if(result == 0){
						}
					//Если там не if и не elseif, то это конец блока, и надо работать
					}else{
						DoIf = 1;
					}
				}
				//Сбрасываем флаг необходимости обработки
				DoIf = 0;
			//Если if верный - работаем
			}else if(result == 1){
				ifdepth++;
				stat = getword(&p,word);
			}
		}else if(strcmp(word,"stop") == 0){
			return 0;
		}else if(strcmp(word,"step") == 0){
			strcat(response,"st ");
			time--;
		}else if(strcmp(word,"stepleft") == 0){
			strcat(response,"tl st tr ");
			time--;
		}else if(strcmp(word,"stepright") == 0){
			strcat(response,"tr st tl ");
			time--;
		}else if(strcmp(word,"stepback") == 0){
			strcat(response,"tl tl st tr tr ");
			time--;
		}else if(strcmp(word,"shoot") == 0){
			time--;
			i = Shoot();
			if(i != -1){
				strcat(response,"sh ");
				ch[0] = i + '0';
				ch[1] = ' ';
				ch[5] = ' ';
				ch[4] = (target.probability % 10) + '0';
				ch[3] = (int)((double)((target.probability % 100) - (target.probability % 10))/10) + '0';
				if(target.probability == 100){
					ch[2] = 1 + '0';
				}else{
					ch[2] = '0';
				}
				strcat(response,ch);
				
			}
		}else if(strcmp(word,"test") == 0){
			Test();
			stat = getword(&p,word);
		}else if(strcmp(word,"turnleft") == 0){
			TurnLeft();
			strcat(response,"tl ");
			stat = getword(&p,word);
		}else if(strcmp(word,"turnright") == 0){
			TurnRight();
			strcat(response,"tr ");
			stat = getword(&p,word);
		}else if(strcmp(word,"setwaypointspriority") == 0){
			i = SetWaypointsPriority(&p);
			if(i == -1){
				return -1;
			}
			stat = getword(&p,word);
		}else if(strcmp(word,"setenemiespriority") == 0){
			i = SetEnemiesPriority(&p);
			if(i == -1){
				return -1;
			}
			stat = getword(&p,word);
		}else if(strcmp(word,"setdrivemode") == 0){
			i = SetDriveMode(&p);
			if(i == 1){
				strcat(response,"sdmn ");
			}else if(i == 2){
				strcat(response,"sdmc ");
			}else{
				return -1;
			}
			stat = getword(&p,word);
		}else if(strcmp(word,"getwaypoint") == 0){
			i = GetWaypoint();
			if(i == -1){
				return -1;
			}
			stat = getword(&p,word);
		}else if(strcmp(word,"gettarget") == 0){
			i = GetTarget();
			if(i == -1){
				return -1;
			}
			stat = getword(&p,word);
		}else if(strcmp(word,"gotowaypoint") == 0){
			i = GoToWaypoint();
			if(i == -1){
				return -1;
			}else if(i > 0){
				for(j = 1; j < i; j++){
					strcat(response,"tl ");
				}
				strcat(response,"st ");
				time--;
			}
			stat = getword(&p,word);
		}else if(strcmp(word,"gotofinish") == 0){
			i = GoToFinish();
			if(i == -1){
				return -1;
			}else if(i > 0){
				for(j = 1; j < i; j++){
					strcat(response,"tl ");
				}
				strcat(response,"st ");
				time--;
			}
			stat = getword(&p,word);
		//Если закончился некий if,
		}else if(strcmp(word,"}") == 0){
			//И синтаксис верный
			if(ifdepth > 0){
				ifdepth--;
				stat = getword(&p,word);
				if(stat == 0){
					return -1; //???
				}
				//Пока идут блоки, которые надо пропустить
				while((strcmp(word,"else") == 0)||(strcmp(word,"elseif") == 0)){
					//Если это elseif
					if(strcmp(word,"elseif") == 0){
						//Пропускаем условие
						result = ProceedIf(&p);
						if(result == -1){

							return -1;
						}
						getword(&p,word);
						if(strcmp(word,"{") != 0){
							return -1;
						}
						//Попускаем сам блок
						oldifdepth = ifdepth;
						ifdepth++;
						do{
							if(getword(&p,word) == 0){
								return -1;
							}
							if(strcmp(word,"{") == 0)
								ifdepth++;
							if(strcmp(word,"}") == 0)
								ifdepth--;
						}while(ifdepth > oldifdepth);
					//Если это else
					}else{
						getword(&p,word);
						if(strcmp(word,"{") != 0){
							return -1;
						}
						//Пропускаем блок
						oldifdepth = ifdepth;
						ifdepth++;
						//И перед ним был ещё один else, то это ошибка
						if(EndIf[ifdepth] == 1){
							return -1;
						//Если не было
						}else if(EndIf[ifdepth] == 0){
							EndIf[ifdepth] = 1;
						}
						do{
							if(getword(&p,word) == 0){
								return -1;
							}
							if(strcmp(word,"{") == 0)
								ifdepth++;
							if(strcmp(word,"}") == 0)
								ifdepth--;
						}while(ifdepth > oldifdepth);
					}
					//Хватаем новое слово
					stat = getword(&p,word);
					if(stat == 0){
						return -1; //???
					}
				}
				//Сбрасываем флаг окончания if`а
				EndIf[ifdepth+1] = 0;
			}else{
				return -1;
			}
		}else{
			return -1;
		}
	}
	if(ifdepth != 0){
		return 0;
	}
	return 0;
}

int ProceedIf(char **string)
{
	char *p;
	char word[20];
	int result;
	p = *string;
	//Читаем слово
	if(getword(&p,word) == 0)
		return -1;
	//Если это не скобка - ошибка синтаксиса
	if(strcmp(word,"(") != 0){
		return -1;
	}else{
	//Если скобка - вызываем обсчёт
		result = GetResult(&p);
		//Если обсчёт прошёл неудачно - возвращаем ошибку на уровень выше
		if(result == -1){
			return -1;
		}
	}
	//Передвигаем указатель по строке
	*string = p;
	//Возвращаем результат
	return result;
}

int GetResult(char **string)
{
	char *p;
	p = *string;
	int result = 0,rescur;
	char op = 'o';		//код логической операции
	int notflag = 0;	//флаг наличия оператора not
	char word[20];
	int num1;
	if(getnum(&p,&num1) == 0){
		//Читаем слово
		if(getword(&p,word) == 0)
			return -1;
	}else{
		strcpy(word,"number");
	}
	//Пока не нашли конец текущего уровня скобок
	while(strcmp(word,")") != 0){
		//Если слово not - устанавливаем notflag
		if(strcmp(word,"not") == 0){
			notflag = ~notflag;
			notflag = notflag & 01;
		}
		//Есди or или and и операции не заявлено - заявляем операцию
		else if(strcmp(word,"or") == 0){
			if(op == ' '){
				op = 'o';
			}else{
				return -1;
			}
		}
		else if(strcmp(word,"and") == 0){
			if(op == ' '){
				op = 'a';
			}else{
				return -1;
			}
		}
		//Если функция - считаем
		else if((strcmp(word,"isavailablepoint") == 0)||(strcmp(word,"cangoforward") == 0)||(strcmp(word,"cangoleft") == 0)||(strcmp(word,"cangoright") == 0)||(strcmp(word,"cangoback") == 0)||(strcmp(word,"isdefinedwaypoint") == 0)||(strcmp(word,"waypointexists") == 0)||(strcmp(word,"finishisknown") == 0)||(strcmp(word,"number") == 0)||(strcmp(word,"waypoint") == 0)||(strcmp(word,"waypoints") == 0)||(strcmp(word,"my") == 0)||(strcmp(word,"target") == 0)||(strcmp(word,"enemies") == 0)){
			if(op == ' ')
				return -1;
			rescur = ProceedFunction(&p,word,num1);
			if(rescur == -1)
				return -1;
			if(notflag == 1){
				notflag = 0;
				rescur = ~rescur;
				rescur = rescur & 01;
			}
			if(op == 'o')
				result = result | rescur;
			if(op == 'a')
				result = result & rescur;
			op = ' ';
		}
		//Если нашли следующий уровень скобок - рекурсия себя
		else if(strcmp(word,"(") == 0){
			if(op == ' ')
				return -1;
			rescur = GetResult(&p);
			if(rescur == -1)
				return -1;
			if(notflag == 1){
				notflag = 0;
				rescur = ~rescur;
				rescur = rescur & 01;
			}
			if(op == 'o')
				result = result | rescur;
			if(op == 'a')
				result = result & rescur;
			op = ' ';
		}else{
			return -1;
		}
		//Читаем новое слово
		if(getnum(&p,&num1) == 0){
		//Читаем слово
			if(getword(&p,word) == 0)
				return -1;
		}else{
			strcpy(word,"number");
		}
	}
	*string = p;
	return result;
}


int IsAvailablePoint(char **string)
{
	char *p;
	int result;
	int xr,yr;
	char word[10];
	p = *string;
	getword(&p,word);
	if(strcmp(word,"(") != 0)
		return -1;
	if(getnum(&p,&xr) == 0)
		return -1;
	getword(&p,word);
	if(strcmp(word,",") != 0)
		return -1;
	if(getnum(&p,&yr) == 0)
		return -1;
	getword(&p,word);
	if(strcmp(word,")") != 0)
		return -1;
	if(bot.drivemode == 1){
		if(ObjectAtPointPrivate(xr,yr) != '#'){
			result = 1;
		}else{
			result = 0;
		}
	}else{
		if((ObjectAtPointPrivate(xr,yr) != '#')&&(ObjectAtPointPrivate(xr,yr) != '@')){
			if(((ObjectAtPointPrivate(xr+1,yr) == '@')&&((xr+1 != 0)||(yr != 0)))||((ObjectAtPointPrivate(xr-1,yr) == '@')&&((xr-1 != 0)||(yr != 0)))||((ObjectAtPointPrivate(xr,yr+1) == '@')&&((xr != 0)||(yr+1 != 0)))||((ObjectAtPointPrivate(xr,yr-1) == '@')&&((xr != 0)||(yr-1 != 0)))){
				result = 0;
			}else{
				result = 1;
			}
		}else{
			result = 0;
		}
	}
	*string = p;
	return result;
}

int CanGoForward()
{
	int result;
	if(bot.drivemode == 1){
		if(ObjectAtPointPrivate(0,1) != '#'){
			result = 1;
		}else{
			result = 0;
		}
	}else{
		if((ObjectAtPointPrivate(0,1) != '#')&&(ObjectAtPointPrivate(0,1) != '@')){
			if((ObjectAtPointPrivate(1,1) == '@')||(ObjectAtPointPrivate(-1,1) == '@')||(ObjectAtPointPrivate(0,2) == '@')){
				result = 0;
			}else{
				result = 1;
			}
		}else{
			result = 0;
		}
	}
	return result;
}

int CanGoBack()
{
	int result;
	if(bot.drivemode == 1){
		if(ObjectAtPointPrivate(0,-1) != '#'){
			result = 1;
		}else{
			result = 0;
		}
	}else{
		if((ObjectAtPointPrivate(0,-1) != '#')&&(ObjectAtPointPrivate(0,-1) != '@')){
			if((ObjectAtPointPrivate(1,-1) == '@')||(ObjectAtPointPrivate(-1,-1) == '@')||(ObjectAtPointPrivate(0,-2) == '@')){
				result = 0;
			}else{
				result = 1;
			}
		}else{
			result = 0;
		}
	}
	return result;
}

int CanGoLeft()
{
	int result;
	if(bot.drivemode == 1){
		if(ObjectAtPointPrivate(-1,0) != '#'){
			result = 1;
		}else{
			result = 0;
		}
	}else{
		if((ObjectAtPointPrivate(-1,0) != '#')&&(ObjectAtPointPrivate(-1,0) != '@')){
			if((ObjectAtPointPrivate(-1,1) == '@')||(ObjectAtPointPrivate(-1,-1) == '@')||(ObjectAtPointPrivate(-2,0) == '@')){
				result = 0;
			}else{
				result = 1;
			}
		}else{
			result = 0;
		}
	}
	return result;
}

int CanGoRight()
{
	int result;
	if(bot.drivemode == 1){
		if(ObjectAtPointPrivate(1,0) != '#'){
			result = 1;
		}else{
			result = 0;
		}
	}else{
		if((ObjectAtPointPrivate(1,0) != '#')&&(ObjectAtPointPrivate(1,0) != '@')){
			if((ObjectAtPointPrivate(1,1) == '@')||(ObjectAtPointPrivate(1,-1) == '@')||(ObjectAtPointPrivate(2,0) == '@')){
				result = 0;
			}else{
				result = 1;
			}
		}else{
			result = 0;
		}
	}
	return result;
}

int IsDefinedWaypoint()
{
	if(wpactive.priority > 0){
		return 1;
	}else{
		return 0;
	}
}

int FinishIsKnown()
{
	int i,j;
	for(i = 0; i < ROWS; i++)
		for(j = 0; j < COLS; j++)
			if(map[i][j] == '$')
				return 1;
	return 0;
}

int getnum(char **string, int *num)
{
	char *p;
	char state = 'g';
	p = *string;
	int res = 0;
	int flag = 0;
	while(1){
		if(isdigit(*p)){
			if(res > 1000)
				return 0;
			state = 'w';
			res = res * 10;
			res = res + *p - '0';
			p++;
		}else if((!isdigit(*p))&&(state == 'w')){
			if(flag == 1)
				res = -res;
			*num = res;
			*string = p;
			return 1;
		}else if((*p == '-')&&(state != 'w')){
			flag = 1;
			p++;
		}else if((!isdigit(*p))&&(!isspace(*p))){
			return 0;
		}else if(*p == '\0'){
			*num = res;
			*string = p;
			return 0;
		}else{
			p++;
		}
	}
}

int Shoot()
{
	if(GetTarget() != -1){
		return target.number;
	}else{
		return -1;
	}
}

int Test()
{
	printf("TEST PASSED\n");
	return 0;
}

int TurnLeft()
{
	if(bot.dir != 1){
		bot.dir--;
	}else{
		bot.dir = 4;
	}
	return 0;
}

int TurnRight()
{
	if(bot.dir != 4){
		bot.dir++;
	}else{
		bot.dir = 1;
	}
	return 0;
}

int getword(char **string, char *word)
{
	char *p;
	int i = 0;
	char state = 'g';
	p = *string;
	while(1){
		if(isalpha(*p)){
			state = 'w';
			word[i++] = tolower(*p++);
		}else if((!isalpha(*p))&&(state == 'w')){
			word[i] = '\0';
			*string = p;
			return 1;
		}else if(*p == '\0'){
			word[i] = '\0';
			*string = p;
			if(strcmp(word,"") == 0)
				return 0;
			return 1;
		}else if((*p == '(')||(*p == ')')||(*p == '{')||(*p == '}')||(*p == '=')||(*p == ',')||(*p == '.')||(*p == '+')||(*p == '-')||(*p == '*')||(*p == '/')){
			word[i] = *p;
			word[i+1] = '\0';
			*string = ++p;
			return 1;
		}else if((*p == '>')||(*p == '<')){
			word[i] = *p;
			p++;
			if(*p != '='){
				word[i+1] = '\0';
				*string = p;
				return 1;
			}else{
				word[i+1] = *p;
				word[i+2] = '\0';
				*string = ++p;
				return 1;
			}
		}else{
			p++;
		}
	}
}

int UpdateMap(char *action, int *winner, int *obj, char gtype)
{
	char word[3];
	int i,n,chance,res = 0;
	if((bot.health <= 0)&&(bot.x > 0)){
		tmpmap[ROWS - bot.y][bot.x-1] = ' ';
		bot.x = 0;
		return res;
	}
	if((bot.health <= 0)&&(bot.x == 0)){
		return res;
	}
	while(getword(&action,word) != 0){
		if(strcmp(word,"st") == 0){
			if((bot.dir == 1)&&(tmpmap[ROWS-bot.y-1][bot.x-1] != '#')){
				if(tmpmap[ROWS-bot.y-1][bot.x-1] == '$')
					*winner = bot.num;
				if(tmpmap[ROWS-bot.y-1][bot.x-1] != '@'){
					tmpmap[ROWS - bot.y][bot.x-1] = ' ';
					tmpmap[ROWS-bot.y-1][bot.x-1] = '@';
					bot.y++;
				}else{
					bot.health = bot.health - 10;
					i = 0;
					while((*(obj + i*6+1) != bot.y+1)||(*(obj + i*6)!=bot.x))
						i++;
					*(obj + i*6+2) = *(obj + i*6+2) - 10;
					*(obj + i*6+5) = 1;
					res = 1;
					//printf("Boooom!\n");
				}
			}
			if((bot.dir == 2)&&(tmpmap[ROWS-bot.y][bot.x] != '#')){
				if(tmpmap[ROWS-bot.y][bot.x] == '$')
					*winner = bot.num;
				if(tmpmap[ROWS-bot.y][bot.x] != '@'){
					tmpmap[ROWS - bot.y][bot.x-1] = ' ';
					tmpmap[ROWS-bot.y][bot.x] = '@';
					bot.x++;
				}else{
					bot.health = bot.health - 10;
					i = 0;
					while((*(obj + i*6+1) != bot.y)||(*(obj + i*6)!=bot.x+1))
						i++;
					*(obj + i*6+2) = *(obj + i*6+2) - 10;
					*(obj + i*6+5) = 1;
					res = 1;
					//printf("Boooom!\n");
				}
			}
			if((bot.dir == 3)&&(tmpmap[ROWS-bot.y+1][bot.x-1] != '#')){
				if(tmpmap[ROWS-bot.y+1][bot.x-1] == '$')
					*winner = bot.num;
				if(tmpmap[ROWS-bot.y+1][bot.x-1] != '@'){
					tmpmap[ROWS - bot.y][bot.x-1] = ' ';
					tmpmap[ROWS-bot.y+1][bot.x-1] = '@';
					bot.y--;
				}else{
					bot.health = bot.health - 10;
					i = 0;
					while((*(obj + i*6+1) != bot.y-1)||(*(obj + i*6)!=bot.x))
						i++;
					*(obj + i*6+2) = *(obj + i*6+2) - 10;
					*(obj + i*6+5) = 1;
					res = 1;
					//printf("Boooom!\n");
				}
			}
			if((bot.dir == 4)&&(tmpmap[ROWS-bot.y][bot.x-2] != '#')){
				if(tmpmap[ROWS-bot.y][bot.x-2] == '$')
					*winner = bot.num;
				if(tmpmap[ROWS-bot.y][bot.x-2] != '@'){
					tmpmap[ROWS - bot.y][bot.x-1] = ' ';
					tmpmap[ROWS-bot.y][bot.x-2] = '@';
					bot.x--;
				}else{
					bot.health = bot.health - 10;
					i = 0;
					while((*(obj + i*6+1) != bot.y)||(*(obj + i*6)!=bot.x-1))
						i++;
					*(obj + i*6+2) = *(obj + i*6+2) - 10;
					*(obj + i*6+5) = 1;
					res = 1;
					//printf("Boooom!\n");
				}
			}
		}else if(strcmp(word,"tl")==0){
			TurnLeft();
		}else if(strcmp(word,"tr")==0){
			TurnRight();
		}else if(strcmp(word,"sdmn")==0){
			bot.drivemode = 1;
		}else if(strcmp(word,"sh")==0){
			getnum(&action,&n);
			getnum(&action,&chance);
			if(gtype == '2'){
				i = 1 + (int)(100*(float)(rand()-1)/RAND_MAX);
				if(chance > i){
					*(obj + n*6 + 2) -= 25;
					*(obj + i*6+5) = 1;
					res = 1;
				}
			}
			//printf("Shot at bot %d. His health %d\n",n,*(obj+n*6+2));
		}else if(strcmp(word,"sdmc")==0){
			bot.drivemode = 2;
		}
	}
	return res;
}

char ObjectAtPointPrivate(int xr, int yr)
{
	int x,y;
	if(bot.dir == 1){
		x = xr + bot.x;
		y = yr + bot.y;
	}
	if(bot.dir == 2){
		x = bot.x + yr;
		y = bot.y - xr;
	}
	if(bot.dir == 3){
		x = bot.x - xr;
		y = bot.y - yr;
	}
	if(bot.dir == 4){
		x = bot.x - yr;
		y = bot.y + xr;
	}
	return map[ROWS - y][x - 1];
}

int ProceedFunction(char **string,char *word, int num)
{
	char *p;
	int result,stat=0;
	int num1,num2;
	p = *string;
	char op[10];
	char func[30];
	
	if(strcmp(word,"isavailablepoint") == 0){	//Унарные функции
		result = IsAvailablePoint(&p);
	}else if(strcmp(word,"cangoforward") == 0){
		result = CanGoForward();
	}else if(strcmp(word,"cangoleft") == 0){
		result = CanGoLeft();
	}else if(strcmp(word,"cangoright") == 0){
		result = CanGoRight();
	}else if(strcmp(word,"cangoback") == 0){
		result = CanGoBack();
	}else if(strcmp(word,"isdefinedwaypoint") == 0){
		result = IsDefinedWaypoint();
	}else if(strcmp(word,"finishisknown") == 0){
		result = FinishIsKnown();
	}else if(strcmp(word,"waypointexists") == 0){
		result = TestDirections(&p);
	}else{
		if(strcmp(word,"number") == 0){		//Бинарные функции
			num1 = num;
		}else{
			num1 = GetBinFuncRes(&p, word, &stat);
			if(stat == -1)
				return -1;
		}
		if(getword(&p,op) == 0)
			return -1;
		//Читаем новое слово
		if(getnum(&p,&num2) == 0){
		//Читаем слово
			if(getword(&p,func) == 0)
				return -1;
		}else{
			strcpy(func,"number");
		}
		if(strcmp(func,"number") != 0){
			num2 = GetBinFuncRes(&p, func, &stat);
			if(stat == -1)
				return -1;
		}
		if(strcmp(op,"<") == 0){
			result = (num1 < num2);
		}else if(strcmp(op,">") == 0){
			result = (num1 > num2);
		}else if(strcmp(op,"=") == 0){
			result = (num1 == num2);
		}else if(strcmp(op,">=") == 0){
			result = (num1 >= num2);
		}else if(strcmp(op,"<=") == 0){
			result = (num1 <= num2);
		}else{
			result = -1;
		}
	}
	*string = p;
	return result;
}

int GetBinFuncRes(char **string, char *word, int *stat)
{
	char *p;
	p = *string;
	int res = 0;
	if(strcmp(word,"my") == 0){
		res = GetSelfProperty(&p,stat);
	}else if(strcmp(word,"enemies") == 0){
		res = GetEnemiesProperty(&p,stat);
	}else if(strcmp(word,"enemy") == 0){
		res = GetEnemyProperty(&p,stat);
	}else if(strcmp(word,"target") == 0){
		res = GetTargetProperty(&p,stat);
	}else if(strcmp(word,"waypoint") == 0){
		res = GetWaypointProperty(&p,stat);
	}else if(strcmp(word,"waypoints") == 0){
		res = GetWaypointsProperty(&p,stat);
	}else{
		*stat = -1;
	}
	*string = p;
	return res;
}

int SetDriveMode(char **string)
{
	char *p;
	p = *string;
	int i;
	char word[30];
	char mode[30];
	if((getword(&p,word) == 0)||(strcmp(word,"(") != 0))
		return -1;
	if(getword(&p,mode) == 0)
		return -1;
	if((getword(&p,word) == 0)||(strcmp(word,")") != 0))
		return -1;
	if(strcmp(mode,"normal") == 0){
		bot.drivemode = 1;
		*string = p;
		return 1;
	}else if(strcmp(mode,"carefull") == 0){
		bot.drivemode = 2;
		*string = p;
		return 2;
	}else{
		return -1;
	}
}

int GetSelfProperty(char **string, int *stat)
{
	char *p;
	p = *string;
	char word[30];
	int res = 0;
	if((getword(&p,word) == 0)||(strcmp(word,".") != 0))
		*stat = -1;
	if(getword(&p,word) == 0)
		*stat = -1;
	if(strcmp(word,"health") == 0){
		res = bot.health;
	}else{
		*stat = -1;
	}
	*string = p;
	return res;
}

int GetEnemiesProperty(char **string, int *stat)
{
	char *p;
	p = *string;
	char word[30];
	int res = 0;
	if((getword(&p,word) == 0)||(strcmp(word,".") != 0))
		*stat = -1;
	if(getword(&p,word) == 0)
		*stat = -1;
	if(strcmp(word,"healthmin") == 0){
		res = enemies.HealthMin;
	}else if(strcmp(word,"healthmax") == 0){
		res = enemies.HealthMax;
	}else if(strcmp(word,"healthavg") == 0){
		res = enemies.HealthAvg;
	}else if(strcmp(word,"distancemin") == 0){
		res = enemies.DistanceMin;
	}else if(strcmp(word,"distancemax") == 0){
		res = enemies.DistanceMax;
	}else if(strcmp(word,"distanceavg") == 0){
		res = enemies.DistanceAvg;
	}else if(strcmp(word,"timeseemin") == 0){
		res = enemies.TimeSeeMin;
	}else if(strcmp(word,"timeseemax") == 0){
		res = enemies.TimeSeeMax;
	}else if(strcmp(word,"timeseeavg") == 0){
		res = enemies.TimeSeeAvg;
	}else if(strcmp(word,"timefightmin") == 0){
		res = enemies.TimeFightMin;
	}else if(strcmp(word,"timefightmax") == 0){
		res = enemies.TimeFightMax;
	}else if(strcmp(word,"timefightavg") == 0){
		res = enemies.TimeFightAvg;
	}else if(strcmp(word,"number") == 0){
		res = enemies.Number;
	}else{
		*stat = -1;
	}
	*string = p;
	return res;
}

int GetEnemyProperty(char **string, int *stat)
{
	char *p;
	p = *string;
	char word[30];
	int res = 0;
	if((getword(&p,word) == 0)||(strcmp(word,".") != 0))
		*stat = -1;
	if(getword(&p,word) == 0)
		*stat = -1;
	if(strcmp(word,"health") == 0){
		res = enemy[encalc].health;
	}else if(strcmp(word,"x") == 0){
		res = enemy[encalc].x;
	}else if(strcmp(word,"y") == 0){
		res = enemy[encalc].y;
	}else if(strcmp(word,"distance") == 0){
		res = enemy[encalc].distance;
	}else if(strcmp(word,"probability") == 0){
		res = enemy[encalc].probability;
	}else if(strcmp(word,"timesee") == 0){
		res = enemy[encalc].timesee;
	}else if(strcmp(word,"timefight") == 0){
		res = enemy[encalc].timefight;
	}else{
		*stat = -1;
	}
	*string = p;
	return res;
}

int GetTargetProperty(char **string, int *stat)
{
	char *p;
	p = *string;
	char word[30];
	int res = 0;
	if((getword(&p,word) == 0)||(strcmp(word,".") != 0))
		*stat = -1;
	if(getword(&p,word) == 0)
		*stat = -1;
	if(strcmp(word,"health") == 0){
		res = target.health;
	}else if(strcmp(word,"x") == 0){
		res = target.x;
	}else if(strcmp(word,"y") == 0){
		res = target.y;
	}else if(strcmp(word,"distance") == 0){
		res = target.distance;
	}else if(strcmp(word,"probability") == 0){
		res = target.probability;
	}else if(strcmp(word,"timesee") == 0){
		res = target.timesee;
	}else if(strcmp(word,"timefight") == 0){
		res = target.timefight;
	}else{
		*stat = -1;
	}
	*string = p;
	return res;
}

int GetWaypointProperty(char **string, int *stat)
{
	char *p;
	p = *string;
	char word[30];
	int res = 0;
	if((getword(&p,word) == 0)||(strcmp(word,".") != 0))
		*stat = -1;
	if(getword(&p,word) == 0)
		*stat = -1;
	if(strcmp(word,"minnewdist") == 0){
		res = wpcalc->MinNewDist;
	}else if(strcmp(word,"distance") == 0){
		res = wpcalc->distance;
	}else if(strcmp(word,"maxnewdist") == 0){
		res = wpcalc->MaxNewDist;
	}else if(strcmp(word,"avgnewdist") == 0){
		res = wpcalc->AvgNewDist;
	}else{
		*stat = -1;
	}
	*string = p;
	return res;
}

int GetWaypointsProperty(char **string, int *stat)
{
	char *p;
	p = *string;
	char word[30];
	int res = 0;
	if((getword(&p,word) == 0)||(strcmp(word,".") != 0))
		*stat = -1;
	if(getword(&p,word) == 0)
		*stat = -1;
	if(strcmp(word,"mindist") == 0){
		res = waypoints->DistMin;
	}else if(strcmp(word,"maxdist") == 0){
		res = waypoints->DistMax;
	}else if(strcmp(word,"avgdist") == 0){
		res = waypoints->DistAvg;
	}else if(strcmp(word,"minnewdist") == 0){
		res = waypoints->MinNewDist;
	}else if(strcmp(word,"maxnewdist") == 0){
		res = waypoints->MaxNewDist;
	}else if(strcmp(word,"avgnewdist") == 0){
		res = waypoints->AvgNewDist;
	}else if(strcmp(word,"number") == 0){
		res = waypoints->Number;
	}else{
		*stat = -1;
	}
	*string = p;
	return res;
}

int SetWaypointsPriority(char **string)
{
	char *p,*tmp;
	p = *string;
	char word[30];
	int stat = 0;
	struct waypoint *wp;
	
	if((getword(&p,word) == 0)||(strcmp(word,"(") != 0))
		return -1;
	
	tmp = p;
	wp = waypoint;
	while(wp != NULL){
		p = tmp;
		wpcalc = wp;
		wp->priority = Calc(&p,&stat);
		if(stat == -1)
			return -1;
		wp = wp->next;
	}
	
	*string = p;
	return 0;
}

int SetEnemiesPriority(char **string)
{
	char *p,*tmp;
	p = *string;
	char word[30];
	int stat = 0;
	int i;
	
	if((getword(&p,word) == 0)||(strcmp(word,"(") != 0))
		return -1;
	tmp = p;
	for(i = 0; i < 8; i++){
		enemy[i].priority = -1000;
		if((enemy[i].probability > 0)&&(enemy[i].health > 0)){
			p = tmp;
			encalc = i;
			enemy[i].priority = Calc(&p,&stat);
			if(stat == -1)
				return -1;
		}
	}
	
	*string = p;
	return 0;
}

int Calc(char **string, int *stat)
{
	char *p;
	p = *string;
	char func[30];
	char op1[30];
	char op2[30];
	int num1,num2,num3;
	num1 = 0;
	strcpy(op1,"+");
	
	if(getnum(&p,&num2) == 0){
		if(getword(&p,func) == 0){
			*stat = -1;
			return -1;
		}
	}else{
		strcpy(func,"number");
	}
	
	if(strcmp(func,"(") == 0){
		num2 = Calc(&p,stat);
	}else if(strcmp(func,"number") == 0){
		
	}else{
		num2 = GetBinFuncRes(&p,func,stat);
	}
	if(*stat == -1)
		return -1;
	
	if(getword(&p,op2) == 0){
		*stat = -1;
		return -1;
	}
	
	while(strcmp(op2,")") != 0){
		
		if(getnum(&p,&num3) == 0){
			if(getword(&p,func) == 0){
				*stat = -1;
				return -1;
			}
		}else{
			strcpy(func,"number");
		}
		
		if(strcmp(func,"(") == 0){
			num3 = Calc(&p,stat);
		}else if(strcmp(func,"number") == 0){
			
		}else{
			num3 = GetBinFuncRes(&p,func,stat);
		}
		
		if(*stat == -1)
			return -1;
			
		if(((strcmp(op2,"*") == 0)||(strcmp(op2,"/") == 0))&&((strcmp(op1,"+") == 0)||(strcmp(op1,"-") == 0))){
			if(strcmp(op2,"*") == 0){
				num2 = num2*num3;
			}else if(strcmp(op2,"/") == 0){
				if(num3 == 0){
					*stat = -1;
					return -1;
				}
				num2 = (int)((double)num2/(double)num3);
			}else{
				*stat = -1;
				return -1;
			}
		}else{
			if(strcmp(op1,"*") == 0){
				num1 = num1*num2;
			}else if(strcmp(op1,"/") == 0){
				if(num2 == 0){
					*stat = -1;
					return -1;
				}
				num1 = (int)((double)num1/(double)num2);
			}else if(strcmp(op1,"+") == 0){
				num1 = num1 + num2;
			}else if(strcmp(op1,"-") == 0){
				num1 = num1 - num2;
			}else{
				*stat = -1;
				return -1;
			}
			strcpy(op1,op2);
			num2 = num3;
		}
		
		if(getword(&p,op2) == 0){
			*stat = -1;
			return -1;
		}
	}
	
	if(strcmp(op1,"*") == 0){
		num1 = num1*num2;
	}else if(strcmp(op1,"/") == 0){
		if(num2 == 0){
			*stat = -1;
			return -1;
		}
		num1 = (int)((double)num1/(double)num2);
	}else if(strcmp(op1,"+") == 0){
		num1 = num1 + num2;
	}else if(strcmp(op1,"-") == 0){
		num1 = num1 - num2;
	}else{
		*stat = -1;
		return -1;
	}
	
	*string = p;
	return num1;
}

int GetWaypoint()
{
	struct waypoint *wp;
	wp = waypoint;
	wpactive.priority = -1000;
	if(wp == NULL)
		return -1;
	while(wp != NULL){
		if(wp->priority > wpactive.priority){
			wpactive.priority = wp->priority;
			wpactive.x = wp->x;
			wpactive.y = wp->y;
		}
		wp = wp->next;
	}
	return 0;
}

int GetTarget()
{
	int i,res = -1;
	target.priority = -1000;
	
	for(i = 0; i < 8; i++)
		if(enemy[i].probability > 0)
			if(enemy[i].priority > target.priority){
				target = enemy[i];
				res = 0;	
			}
	
	return res;
}

int GoToWaypoint()
{
	int i;
	if(wpactive.priority < 0)
		return -1;
	
	if((bot.x == wpactive.x)&&(bot.y == wpactive.y)){
		wpactive.priority = -1000;
		return 0;
	}
	
	i = FollowWave(bot.x, bot.y, wpactive.x, wpactive.y);
	
	if(i == 1){
		if(bot.dir == 1){
			return 1;
		}else if(bot.dir == 2){
			return 2;
		}else if(bot.dir == 3){
			return 3;
		}else if(bot.dir == 4){
			return 4;
		}
	}else if(i == 2){
		if(bot.dir == 1){
			return 4;
		}else if(bot.dir == 2){
			return 1;
		}else if(bot.dir == 3){
			return 2;
		}else if(bot.dir == 4){
			return 3;
		}
	}else if(i == 3){
		if(bot.dir == 1){
			return 3;
		}else if(bot.dir == 2){
			return 4;
		}else if(bot.dir == 3){
			return 1;
		}else if(bot.dir == 4){
			return 2;
		}
	}else if(i == 4){
		if(bot.dir == 1){
			return 2;
		}else if(bot.dir == 2){
			return 3;
		}else if(bot.dir == 3){
			return 4;
		}else if(bot.dir == 4){
			return 1;
		}
	}else{
		return -1;
	}
}

int GoToFinish()
{
	int i,j,k = 0;
	
	if(wpactive.priority < 0)
		return -1;
	
	for(i = 0; i < ROWS; i++)
		for(j = 0; j < COLS; j++)
			if(map[i][j] == '$'){
				wpactive.y = ROWS - i;
				wpactive.x = j + 1;
				k = 1;
			}
	if(k == 0)
		return -1;
	
	if((bot.x == wpactive.x)&&(bot.y == wpactive.y)){
		wpactive.priority = -1000;
		return 0;
	}
	
	i = FollowWave(bot.x, bot.y, wpactive.x, wpactive.y);
	
	if(i == 1){
		if(bot.dir == 1){
			return 1;
		}else if(bot.dir == 2){
			return 2;
		}else if(bot.dir == 3){
			return 3;
		}else if(bot.dir == 4){
			return 4;
		}
	}else if(i == 2){
		if(bot.dir == 1){
			return 4;
		}else if(bot.dir == 2){
			return 1;
		}else if(bot.dir == 3){
			return 2;
		}else if(bot.dir == 4){
			return 3;
		}
	}else if(i == 3){
		if(bot.dir == 1){
			return 3;
		}else if(bot.dir == 2){
			return 4;
		}else if(bot.dir == 3){
			return 1;
		}else if(bot.dir == 4){
			return 2;
		}
	}else if(i == 4){
		if(bot.dir == 1){
			return 2;
		}else if(bot.dir == 2){
			return 3;
		}else if(bot.dir == 3){
			return 4;
		}else if(bot.dir == 4){
			return 1;
		}
	}else{
		return -1;
	}
}


int FollowWave(int xst, int yst, int xfin, int yfin)
{
	int i,j,n,k=1;
	for(i = 0; i < ROWS; i++)
		for(j = 0; j < COLS; j++)
			volna[i][j] = -1;
	volna[ROWS - yst][xst - 1] = 0;
	n = 0;
	while((volna[ROWS-yfin][xfin-1] == -1)&&(k == 1)){
		k = 0;
		for(i = 1; i < ROWS; i++){
			for(j = 1; j < COLS; j++){
				if(bot.drivemode == 1){
					if(((map[i][j]==' ')||(map[i][j]=='@')||(map[i][j]=='$'))&&(volna[i][j] == -1)){
						if((volna[i+1][j] == n)||(volna[i-1][j] == n)||(volna[i][j+1] == n)||(volna[i][j-1] == n)){
							volna[i][j] = n+1;
							k = 1;
						}
					}
				}else if(bot.drivemode == 2){
					if(((map[i][j]==' ')||(map[i][j]=='$'))&&(volna[i][j] == -1)&&((map[i+1][j] != '@')||((i+1 == ROWS-bot.y)&&(j == bot.x-1)))&&((map[i-1][j] != '@')||((i-1 == ROWS-bot.y)&&(j == bot.x-1)))&&((map[i][j+1] != '@')||((i == ROWS-bot.y)&&(j+1 == bot.x-1)))&&((map[i][j-1] != '@')||(i == ROWS-bot.y)&&(j-1 == bot.x-1))){
						if((volna[i+1][j] == n)||(volna[i-1][j] == n)||(volna[i][j+1] == n)||(volna[i][j-1] == n)){
							volna[i][j] = n+1;
							k = 1;
						}
					}
				}
			}
		}
		n++;
	}
	
	while(n > 1){
		if(volna[ROWS-yfin-1][xfin-1] == n-1){
			yfin++;
		}else if(volna[ROWS-yfin][xfin+1-1] == n-1){
			xfin++;
		}else if(volna[ROWS-yfin+1][xfin-1] == n-1){
			yfin--;
		}else if(volna[ROWS-yfin][xfin-1-1] == n-1){
			xfin--;
		}else{
			return -1;
		}
		n--;
	}
	if((yfin > yst)&&(xfin == xst)){
		return 1;
	}else if((xfin > xst)&&(yfin == yst)){
		return 2;
	}else if((yfin < yst)&&(xfin == xst)){
		return 3;
	}else if((xfin < xst)&&(yfin == yst)){
		return 4;
	}else{
		return -1;
	}
	return -1;
}

int Line(int num, int *xlp, int *ylp)
{
	int areal,dx,dy,deltax,deltay,turn,N = 6,n,i,xt,yt,xr,yr;
	if((num >= 1)&&(num <= 9)){
		areal = bot.dir;
		dx = 1;
		dy = 1;
	}else if((num >= 10)&&(num <= 18)){
		areal = bot.dir +1;
		dx = 1;
		dy = -1;
		num -= 9;
	}else if((num >= 19)&&(num <= 27)){
		areal = bot.dir +2;
		dx = -1;
		dy = -1;
		num -= 18;
	}else if((num >= 28)&&(num <= 36)){
		areal = bot.dir +3;
		dx = -1;
		dy = 1;
		num -= 27;
	}else{
		return -1;
	}
	
	if(areal > 4)
		areal -= 4;
	
	if(num == 1){
		deltax = 1;
		deltay = 5;
		turn = 1;
	}else if(num == 2){
		deltax = 1;
		deltay = 4;
		turn = 1;
	}else if(num == 3){
		deltax = 1;
		deltay = 3;
		turn = 1;
	}else if(num == 4){
		deltax = 1;
		deltay = 2;
		turn = 1;
	}else if(num == 5){
		deltax = 1;
		deltay = 1;
		turn = 1;
		N = 7;
	}else if(num == 6){
		deltax = 1;
		deltay = 1;
		turn = 2;
		N = 7;
	}else if(num == 7){
		deltax = 2;
		deltay = 1;
		turn = 2;
	}else if(num == 8){
		deltax = 3;
		deltay = 1;
		turn = 2;
	}else if(num == 9){
		deltax = 4;
		deltay = 1;
		turn = 2;
	}
	
	if(areal == 2){
		n = deltax;
		deltax = deltay;
		deltay = n;
		dx = dy;
		dy = -dx;
		if(turn == 1){
			turn = 2;
		}else{
			turn = 1;
		}
	}else if(areal == 3){
		dx = -dx;
		dy = -dy;
	}else if(areal == 4){
		n = deltax;
		deltax = deltay;
		deltay = n;
		dx = -dy;
		dy = dx;
		if(turn == 1){
			turn = 2;
		}else{
			turn = 1;
		}
	}
	
	xt = bot.x;
	yt = bot.y;
	xr = xt;
	yr = yt;
	n = 0;
	if(turn == 2){
		while((n < N)&&(map[ROWS-yt][xt-1] != '#')&&(map[ROWS-yt][xt-1] != '?')){
			i = 0;
			while((i < deltax)&&(map[ROWS-yt][xt-1] != '#')&&(map[ROWS-yt][xt-1] != '?')&&(n < N)){
				xr = xt;
				yr = yt;
				xt += dx;
				n++;
				i++;
			}
			i = 0;
			while((i < deltay)&&(map[ROWS-yt][xt-1] != '#')&&(map[ROWS-yt][xt-1] != '?')&&(n < N)){
				yr = yt;
				xr = xt;
				yt += dy;
				n++;
				i++;
			}
		}
	}else{
		while((n < N)&&(map[ROWS-yt][xt-1] != '#')&&(map[ROWS-yt][xt-1] != '?')){
			i = 0;
			while((i < deltay)&&(map[ROWS-yt][xt-1] != '#')&&(map[ROWS-yt][xt-1] != '?')&&(n < N)){
				yr = yt;
				xr = xt;
				yt += dy;
				n++;
				i++;
			}
			i = 0;
			while((i < deltax)&&(map[ROWS-yt][xt-1] != '#')&&(map[ROWS-yt][xt-1] != '?')&&(n < N)){
				xr = xt;
				yr = yt;
				xt += dx;
				n++;
				i++;
			}
		}
	}
	*xlp = xr;
	*ylp = yr;
	return 0;
}

int IsWaypoint(int x, int y)
{
	if((map[ROWS-y-1][x-1] == '?')||(map[ROWS-y+1][x-1] == '?')||(map[ROWS-y][x-2] == '?')||(map[ROWS-y][x] == '?'))
		return 1;
	return 0;
}

int TestDirections(char **string)
{
	char *p;
	int x,y,res,result = 0;
	int num1,num2,i;
	char word[10];
	p = *string;
	getword(&p,word);
	if(strcmp(word,"(") != 0)
		return -1;
	if(getnum(&p,&num1) == 0)
		return -1;
	getword(&p,word);
	if(strcmp(word,",") != 0)
		return -1;
	if(getnum(&p,&num2) == 0)
		return -1;
	getword(&p,word);
	if(strcmp(word,")") != 0)
		return -1;
	if(num1 < 1)
		return -1;
	if(num2 < num1)
		return -1;
	if(num2 > 36)
		return -1;
	
	for(i = num1; i <= num2; i++){
		res = Line(i,&x,&y);
		if(res == -1)
			return -1;
		res = IsWaypoint(x,y);
		if(res == 1){
			*string = p;
			return 1;
		}
	}
	*string = p;
	return 0;
}
