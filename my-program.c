#include<stdio.h>
#include<string.h>
char buffer[100000];
int intbuffer;
FILE *file;
int check(char buf[],int num,char keyword[])
{
	if(strlen(keyword)!=num+1)
		return 0;
	for(int i=0;i<=num;i++)
	{
		if(buf[i]!=keyword[i])
			return 0;
	}
	return 1;
}
int isLetter(char letter)
{
	if('a'<=letter&&letter<='z'||'A'<=letter&&letter<='Z'||'0'<=letter&&letter<='9')
		return 1;
	return 0;
}
int main(int argc,char * argv[])
{
	file=fopen(argv[1],"r");
	char input[100000];
	fgets(input,100000,file);
	input[strlen(input)-1]='\0';
	for(int i=0;i<strlen(input);i++)
	{
		if(input[i]=='+')
			printf("Plus\r\n");
		else if(input[i]=='*')
			printf("Star\r\n");
		else if(input[i]==',')
			printf("Comma\r\n");
		else if(input[i]=='(')
			printf("LParenthesis\r\n");
		else if(input[i]==')')
			printf("RParenthesis\r\n");
		else if(input[i]==':')
		{
			if(i+1<strlen(input)&&input[i+1]=='=')
			{
				i++;
				printf("Assign\r\n");
			}
			else
			{
				printf("Colon\r\n");
			}
		}
		else if('0'<=input[i]&&input[i]<='9')
		{
			int j;
			intbuffer=input[i]-'0';
			for(j=i+1;j<strlen(input);j++)
			{
				if('0'<=input[j]&&input[j]<='9')
				{
					intbuffer*=10;
					intbuffer+=input[j]-'0';
				}
				else
					break;
			}
			i=j-1;
			printf("Int(%d)\r\n",intbuffer);
		}
		else if('a'<=input[i]&&input[i]<='z'||'A'<=input[i]&&input[i]<='Z')
		{
			int top=0,j;
			buffer[top]=input[i];
			for(j=i+1;j<strlen(input);j++)
			{
				if(isLetter(input[j]))
				{
					buffer[++top]=input[j];
					if(check(buffer,top,"BEGIN\0")&&(j+1>=strlen(input)||!isLetter(input[j+1])))
					{
						printf("Begin\r\n");
						top=-1;
						break;
					}
					if(check(buffer,top,"END\0")&&(j+1>=strlen(input)||!isLetter(input[j+1])))
					{
						printf("End\r\n");
						top=-1;
						break;
					}
					if(check(buffer,top,"FOR\0")&&(j+1>=strlen(input)||!isLetter(input[j+1])))
					{
						printf("For\r\n");
						top=-1;
						break;
					}
					if(check(buffer,top,"IF\0")&&(j+1>=strlen(input)||!isLetter(input[j+1])))
					{
						printf("If\r\n");
						top=-1;
						break;
					}
					if(check(buffer,top,"THEN\0")&&(j+1>=strlen(input)||!isLetter(input[j+1])))
					{
						printf("Then\r\n");
						top=-1;
						break;
					}
					if(check(buffer,top,"ELSE\0")&&(j+1>=strlen(input)||!isLetter(input[j+1])))
					{
						printf("Else\r\n");
						top=-1;
						break;
					}
				}
				else
				{
					buffer[top+1]='\0';
					break;
				}
			}
			if(top!=-1)
			{
				printf("Ident(%s)\r\n",buffer);
				i=j-1;
			}
			else
				i=j;
		}
		else
		{
			printf("Unknown\r\n");
			return 0;
		}
	}
}
