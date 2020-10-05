#include<stdio.h>
#include<string.h>
char input[100000],buffer[100000];
char input_letter[]={'+','*',',','(',')'};
char *output_letter[]={"Plus\0","Star\0","Comma\0","LParenthesis\0","RParenthesis\0"};
char *sp_input[]={"BEGIN\0","END\0","FOR\0","IF\0","THEN\0","ELSE\0"};
char *sp_output[]={"Begin\0","End\0","For\0","If\0","Then\0","Else\0"};
int token_equals(char *token1,char *token2)
{
	if(strlen(token1)!=strlen(token2))
		return 0;
	for (int i=0;i<strlen(token1);i++)
	{
		if(token1[i]!=token2[i])
			return 0;
	}
	return 1;
}
int isLetter(char letter)
{
	return ('a'<=letter&&letter<='z')||('A'<=letter&&letter<='Z')||('0'<=letter&&letter<='9');
}
int main(int argc,char *argv[])
{
	FILE *file=fopen(argv[1],"r");
	int num=fread(input,sizeof(char),100000,file);
	for(int i=num;i<100000;i++)
		input[i]='\0';
	for(int i=0;i<num;i++)
	{
		int check=0;
		for(int j=0;j<5;j++)
		{
			if(input[i]==input_letter[j])
			{
				printf("%s\n",output_letter[j]);
				check=1;
				break;
			}
		}
		if(check)
			continue;
		if(input[i]==' '||input[i]=='\n'||(input[i]=='\r'&&input[i+1]=='\n')){continue;}
		else if(input[i]==':')
		{
			if(i+1<strlen(input)&&input[i+1]=='=')
			{
				printf("Assign\n");
				i++;
			}
			else
				printf("Colon\n");
			continue;
		}
		else if('0'<=input[i]&&input[i]<='9')
		{
			int num=input[i]-'0';
			while('0'<=input[i+1]&&input[i+1]<='9')
			{
				i++;
				num*=10;
				num+=input[i]-'0';
			}
			printf("Int(%d)\n",num);
			continue;
		}
		else if(('a'<=input[i]&&input[i]<='z')||('A'<=input[i]&&input[i]<='Z'))
		{
			int top=-1;
			buffer[++top]=input[i];
			while(isLetter(input[i+1]))
			{
				buffer[++top]=input[++i];
				for(int j=0;j<6;j++)
				{
					if(token_equals(buffer,sp_input[j])&&(i+1>=strlen(input)||!isLetter(input[i+1])))
					{
						printf("%s\n",sp_output[j]);
						top=-1;
						break;
					}
				}
			}
			if(top!=-1)
			{
				printf("Ident(%s)\n",buffer);
			}
			for(int i=0;i<=100000;i++)
			{
				buffer[i]=0;
			}
		}
		else
		{
			printf("Unknown\n");
			return 0;
		}
	}
}
