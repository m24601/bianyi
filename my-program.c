#include<stdio.h>
char token[5]={'+','*','(',')','i'};
int priority[6][6]={
    {1,-1,-1,1,-1},
    {1,1,-1,1,-1},
    {-1,-1,-1,0,-1},
    {1,1,-2,1,-2},
    {1,1,-2,1,-2},
};
char stack[1005],input[1005];
int m,tops=-1;
int GetIndex(char c)
{
    for(int i=0;i<5;i++)
    {
        if(token[i]==c)
            return i;
    }
    return -1;
}
int GetFirstTokenIndex()
{
	for(int i=tops;i>=0;i--)
	{
		if(GetIndex(stack[i])!=-1)
			return GetIndex(stack[i]);
	}
	return -1;
}
int merge()
{
	for(int i=tops;i>=0;i--)
	{
		if(stack[i]=='i'){
			stack[i]='N';
			return 1;
		}else if(i>=2&&stack[i]=='N'&&stack[i-1]=='+'&&stack[i-2]=='N'){
			for(int j=i-1;j+2<=tops;j++){
				stack[j]=stack[j+2];
			}
			tops-=2;
			return 1;
		}else if(i>=2&&stack[i]=='N'&&stack[i-1]=='*'&&stack[i-2]=='N'){
			for(int j=i-1;j+2<=tops;j++){
				stack[j]=stack[j+2];
			}
			tops-=2;
			return 1;
		}else if(i>=2&&stack[i]==')'&&stack[i-1]=='N'&&stack[i-2]=='('){
			for(int j=i-1;j+2<=tops;j++){
				stack[j]=stack[j+2];
			}
			tops-=2;
			stack[i]='N';
			return 1;
		}
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
		}else if(GetFirstTokenIndex()==-1){
			stack[++tops]=input[i];
			printf("I%c\n",input[i]);
		}else if(priority[GetFirstTokenIndex()][m]==-2){
			printf("E\n");
    		return 0;
		}else if(priority[GetFirstTokenIndex()][m]<=0){
			stack[++tops]=input[i];
			printf("I%c\n",input[i]);
		}else if(priority[GetFirstTokenIndex()][m]==1){
			while(GetFirstTokenIndex()!=-1&&priority[GetFirstTokenIndex()][m]==1){
				if(!merge()){
					printf("RE\n");
					return 0;
				}
				printf("R\n");
			}
			stack[++tops]=input[i];
			printf("I%c\n",input[i]);
		}
	}
	while(GetFirstTokenIndex()!=-1){
		if(!merge()){
			printf("RE\n");
			return 0;
		}
		printf("R\n");
	}
	if(tops!=0)
		printf("RE\n");
}
