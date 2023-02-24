#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
	FILE *fp = fopen("./calData.txt","r");
	char buf[1024];
	int bufLen = 1024;
	int a;
	int b;
	char sign;
	while((fgets(buf,sizeof(buf),fp)) != NULL)
	{
		sscanf(buf,"%d%c%d",&a,&sign,&b);
		switch(sign)
		{
			case '+':
				printf("%d + %d = %d\n",a,b,a + b);
				break;
			case '-':
				printf("%d - %d = %d\n",a,b,a - b);
				break;
			case '*':
				printf("%d * %d = %d\n",a,b,a*b);
				break;
			case '/':
				if(b != 0)
				{
					printf("%d / %d = %d\n",a / b);
					break;
				}
				else
				{
					printf("除数不能是0\n");
					break;
				}

		}
	}


	return 0;
}

