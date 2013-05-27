#include <string.h>
#define STACK_DEPTH 25

class LogikChecker{
	int ProceedIf(char **string, int *strnum)
	{
		char *p;
		char word[20];
		int result;
		p = *string;
		if(getword(&p,word) == 0)
			return -1;
		if(strcmp(word,"(") != 0){
			return -1;
		}else{
			result = GetResult(&p, strnum);
			if(result == -1){
				return -1;
			}
		}
		*string = p;
		return result;
	}
	
	int GetResult(char **string, int *strnum)
	{
		char *p;
		p = *string;
		int result = 0,rescur;
		char op = 'o';
		int notflag = 0;
		char word[20];
		int num1;
		if(getnum(&p,&num1) == 0){
			if(getword(&p,word) == 0)
				return -1;
		}else{
			strcpy(word,"number");
		}
		
		while(strcmp(word,")") != 0){
			if(strcmp(word,"not") == 0){
				notflag = ~notflag;
				notflag = notflag & 01;
			}else if(strcmp(word,"or") == 0){
				if(op == ' '){
					op = 'o';
				}else{
					return -1;
				}
			}else if(strcmp(word,"and") == 0){
				if(op == ' '){
					op = 'a';
				}else{
					return -1;
				}
			}else if((strcmp(word,"isavailablepoint") == 0)||(strcmp(word,"cangoforward") == 0)||(strcmp(word,"cangoleft") == 0)||(strcmp(word,"cangoright") == 0)||(strcmp(word,"cangoback") == 0)||(strcmp(word,"isdefinedwaypoint") == 0)||(strcmp(word,"waypointexists") == 0)||(strcmp(word,"finishisknown") == 0)||(strcmp(word,"number") == 0)||(strcmp(word,"my") == 0)||(strcmp(word,"waypoint") == 0)||(strcmp(word,"waypoints") == 0)||(strcmp(word,"target") == 0)||(strcmp(word,"enemies") == 0)){
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
			}else if(strcmp(word,"(") == 0){
				if(op == ' ')
					return -1;
				rescur = GetResult(&p,strnum);
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
			}else if(strcmp(word,"\n") == 0){
				(*strnum)++;
			}else{
				return -1;
			}
			if(getnum(&p,&num1) == 0){
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
		*string = p;
		return 1;
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
			}else if((*p == '(')||(*p == ')')||(*p == '{')||(*p == '}')||(*p == '=')||(*p == ',')||(*p == '.')||(*p == '+')||(*p == '-')||(*p == '*')||(*p == '/')||(*p == '\n')){
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
			result = 1;
		}else if(strcmp(word,"cangoleft") == 0){
			result = 1;
		}else if(strcmp(word,"cangoright") == 0){
			result = 1;
		}else if(strcmp(word,"cangoback") == 0){
			result = 1;
		}else if(strcmp(word,"isdefinedwaypoint") == 0){
			result = 1;
		}else if(strcmp(word,"finishisknown") == 0){
			result = 1;
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
		char word[30];
		char mode[30];
		if((getword(&p,word) == 0)||(strcmp(word,"(") != 0))
			return -1;
		if(getword(&p,mode) == 0)
			return -1;
		if((getword(&p,word) == 0)||(strcmp(word,")") != 0))
			return -1;
		if(strcmp(mode,"normal") == 0){
			*string = p;
			return 1;
		}else if(strcmp(mode,"carefull") == 0){
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
			res = 100;
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
			res = 100;
		}else if(strcmp(word,"healthmax") == 0){
			res = 100;
		}else if(strcmp(word,"healthavg") == 0){
			res = 100;
		}else if(strcmp(word,"distancemin") == 0){
			res = 100;
		}else if(strcmp(word,"distancemax") == 0){
			res = 100;
		}else if(strcmp(word,"distanceavg") == 0){
			res = 100;
		}else if(strcmp(word,"timeseemin") == 0){
			res = 100;
		}else if(strcmp(word,"timeseemax") == 0){
			res = 100;
		}else if(strcmp(word,"timeseeavg") == 0){
			res = 100;
		}else if(strcmp(word,"timefightmin") == 0){
			res = 100;
		}else if(strcmp(word,"timefightmax") == 0){
			res = 100;
		}else if(strcmp(word,"timefightavg") == 0){
			res = 100;
		}else if(strcmp(word,"number") == 0){
			res = 100;
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
			res = 100;
		}else if(strcmp(word,"x") == 0){
			res = 100;
		}else if(strcmp(word,"y") == 0){
			res = 100;
		}else if(strcmp(word,"distance") == 0){
			res = 100;
		}else if(strcmp(word,"probability") == 0){
			res = 100;
		}else if(strcmp(word,"timesee") == 0){
			res = 100;
		}else if(strcmp(word,"timefight") == 0){
			res = 100;
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
			res = 100;
		}else if(strcmp(word,"x") == 0){
			res = 100;
		}else if(strcmp(word,"y") == 0){
			res = 100;
		}else if(strcmp(word,"distance") == 0){
			res = 100;
		}else if(strcmp(word,"probability") == 0){
			res = 100;
		}else if(strcmp(word,"timesee") == 0){
			res = 100;
		}else if(strcmp(word,"timefight") == 0){
			res = 100;
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
			res = 100;
		}else if(strcmp(word,"x") == 0){
			res = 100;
		}else if(strcmp(word,"y") == 0){
			res = 100;
		}else if(strcmp(word,"distance") == 0){
			res = 100;
		}else if(strcmp(word,"maxnewdist") == 0){
			res = 100;
		}else if(strcmp(word,"avgnewdist") == 0){
			res = 100;
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
			res = 10;
		}else if(strcmp(word,"maxdist") == 0){
			res = 10;
		}else if(strcmp(word,"avgdist") == 0){
			res = 10;
		}else if(strcmp(word,"minnewdist") == 0){
			res = 10;
		}else if(strcmp(word,"maxnewdist") == 0){
			res = 10;
		}else if(strcmp(word,"avgnewdist") == 0){
			res = 10;
		}else if(strcmp(word,"number") == 0){
			res = 10;
		}else{
			*stat = -1;
		}
		*string = p;
		return res;
	}
	
	int SetWaypointsPriority(char **string)
	{
		char *p;
		p = *string;
		char word[30];
		int stat = 0;
		
		if((getword(&p,word) == 0)||(strcmp(word,"(") != 0))
			return -1;
		
		Calc(&p,&stat);
		if(stat == -1)
			return -1;
		
		*string = p;
		return 0;
	}
	
	int SetEnemiesPriority(char **string)
	{
		char *p;
		p = *string;
		char word[30];
		int stat = 0;
		
		if((getword(&p,word) == 0)||(strcmp(word,"(") != 0))
			return -1;
	
		Calc(&p,&stat);
		if(stat == -1)
			return -1;
		
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
	
	int TestDirections(char **string)
	{
		char *p;
		int num1,num2;
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
		
		*string = p;
		return 0;
	}
	public:
		int check(char *logik, int *strnum, char *response)
		{
			int result,i;
			*strnum = 1;
			int stat;
			char word[30] = "";
			char *p;
			p = logik;
			int EndIf[STACK_DEPTH];
			int ifdepth = 0;
			stat = getword(&p,word);
			EndIf[0] = 1;
			for(i = 1; i < STACK_DEPTH; i++)
				EndIf[i] = 0;
	
			while(stat > 0){
				if(strcmp(word,"if") == 0){
					result = ProceedIf(&p, strnum);
					if(result == -1){
						strcpy(response,"Error in 'if' statement");
						return -1;
					}
					getword(&p,word);
					if(strcmp(word,"{") != 0){
						strcpy(response,"{ expected");
						return -1;
					}
					ifdepth++;
					EndIf[ifdepth] = 0;
				}else if(strcmp(word,"elseif") == 0){
					result = ProceedIf(&p, strnum);
					if(result == -1){
						strcpy(response,"Error in 'elseif' statement");
						return -1;
					}
					getword(&p,word);
					if(strcmp(word,"{") != 0){
						strcpy(response,"{ expected");
						return -1;
					}
					ifdepth++;
				}else if(strcmp(word,"else") == 0){
					getword(&p,word);
					if(strcmp(word,"{") != 0){
						strcpy(response,"{ expected");
						return -1;
					}
					ifdepth++;
					if(EndIf[ifdepth] == 1){
						return -1;
					}else if(EndIf[ifdepth] == 0){
						EndIf[ifdepth] = 1;
					}
				}else if(strcmp(word,"stop") == 0){
				}else if(strcmp(word,"step") == 0){
				}else if(strcmp(word,"stepleft") == 0){
				}else if(strcmp(word,"stepright") == 0){
				}else if(strcmp(word,"stepback") == 0){
				}else if(strcmp(word,"shoot") == 0){
				}else if(strcmp(word,"turnleft") == 0){
				}else if(strcmp(word,"turnright") == 0){
				}else if(strcmp(word,"setwaypointspriority") == 0){
					i = SetWaypointsPriority(&p);
					if(i == -1){
						strcpy(response,"Error in 'SetWaypointsPriority' arifmetic!");
						return -1;
					}
				}else if(strcmp(word,"setenemiespriority") == 0){
					i = SetEnemiesPriority(&p);
					if(i == -1){
						strcpy(response,"Error in 'SetEnemiesPriority' arifmetic!");
						return -1;
					}
				}else if(strcmp(word,"setdrivemode") == 0){
					i = SetDriveMode(&p);
					if(i == -1){
						strcpy(response,"Error in 'SetDriveMode' statement");
						return -1;
					}
				}else if(strcmp(word,"getwaypoint") == 0){
				}else if(strcmp(word,"gettarget") == 0){
				}else if(strcmp(word,"gotowaypoint") == 0){
				}else if(strcmp(word,"gotofinish") == 0){
				}else if(strcmp(word,"}") == 0){
					if(ifdepth > 0){
						ifdepth--;
					}else{
						strcpy(response,"Unexpected }");
						return -1;
					}
				}else if(strcmp(word,"\n") == 0){
					(*strnum)++;
				}else{
					strcpy(response,"Unknown command");
					return -1;
				}
				stat = getword(&p,word);
			}
			if(ifdepth != 0){
				return -2;
			}
			return 0;
		}
};
