//see test.cpp to understand how it works
#include <string.h>
#include <ctype.h>

double Calc(char **string, int *stat);
int getnum(char **string, double *num);
int getword(char **string, char *word);
int GetBinFuncRes(char **string, char *word, int *stat);

double Calc(char **string, int *stat)
{
	char *p;
	char func[30];
	char op1[30];
	char op2[30];
	double num1,num2,num3;
	p = *string;
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
	
	while((strcmp(op2,"=") != 0)&&(strcmp(op2,")") != 0)){
		
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
				num2 = num2/num3;
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
				num1 = num1/num2;
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
		num1 = num1/num2;
	}else if(strcmp(op1,"+") == 0){
		num1 = num1 + num2;
	}else if(strcmp(op1,"-") == 0){
		num1 = num1 - num2;
	}else{
		*stat = -1;
		return -1;
	}
	
	*string = p;
	*stat = 0;
	return num1;
};


int getnum(char **string, double *num)
{
	char *p;
	char state = 'g';
	p = *string;
	double res = 0;
	int flag = 0;
	int dot = 0;
	double order = 1;
	while(1){
		if(isdigit(*p)){
			state = 'w';
			if(dot == 0){
				res = res * 10;
				res = res + *p - '0';
			}else{
				order = order/10;
				res = res + (*p - '0')*order;
			}
			p++;
		}else if((*p == '-')&&(state != 'w')){
			flag = 1;
			p++;
		}else if(*p == '.'){
			if(dot == 0){
				dot = 1;
				p++;
			}else{
				return 0;
			}
		}else if((!isdigit(*p))&&(state == 'w')){
			if(flag == 1)
				res = -res;
			*num = res;
			*string = p;
			return 1;
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
};


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
};


int GetBinFuncRes(char **string, char *word, int *stat)
{
	char *p;
	p = *string;
	int res = 0;

	*stat = -1;

	*string = p;
	return res;
};
