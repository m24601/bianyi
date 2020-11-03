#include<stdio.h>
char token[5]={'+','*','(',')','i'};
int priority[6][6]={
    {1,-1,-1,1,-1},
    {1,1,-1,1,-1},
    {-1,-1,-1,0,-1},
    {1,1,-2,1,-2},
    {1,1,-2,1,-2},
};
char stack1[1005],input[1005];
int m,tops1=-1,tops2=-1;
int GetIndex(char c)
{
    for(int i=0;i<5;i++)
    {
        if(token[i]==c)
            return i;
    }
    return -1;
}
int merge()
{
	if(stack1[tops1]=='i'){
		stack1[tops1--]='\0';
		tops2++;
		return 1;
	}else if((stack1[tops1]=='*'||stack1[tops1]=='+')&&tops2>0){
		stack1[tops1--]='\0';
		tops2--;
		return 1;
	}else if(tops1>0&&(stack1[tops1]==')'||stack1[tops1-1]=='(')&&tops2>=0){
		stack1[tops1--]='\0';
		stack1[tops1--]='\0';
		return 1;
	}
	return 0;
}
int main(int argc,char*argv[])
{
    FILE *file=fopen(argv[1],"r");
    int num=fread(input,sizeof(char),1000,file);
    if(input[num-1]=='\n')num--;
    if(input[num-1]=='\r')num--;
    for(int i=0;i<num;i++)
    {
    	m=GetIndex(input[i]);
    	if(m==-1){
    		printf("E\n");
    		return 0;
		}else if(tops1==-1){
			stack1[++tops1]=input[i];
			printf("I%c\n",input[i]);
		}else if(priority[GetIndex(stack1[tops1])][m]==-2){
			printf("E\n");
    		return 0;
		}else if(priority[GetIndex(stack1[tops1])][m]<=0){
			stack1[++tops1]=input[i];
			printf("I%c\n",input[i]);
		}else if(priority[GetIndex(stack1[tops1])][m]==1){
			while(tops1!=-1&&priority[GetIndex(stack1[tops1])][m]==1){
				if(!merge()){
					printf("RE\n");
					return 0;
				}
				printf("R\n");
			}
			stack1[++tops1]=input[i];
			printf("I%c\n",input[i]);
		}
	}
	while(tops1!=-1){
		if(!merge()){
			printf("RE\n");
			return 0;
		}
		if(tops2>=0)
			printf("R\n");
		else{
			printf("RE\n");
			return 0;
		}
	}
	if(tops2!=0)
		printf("RE\n");
}
