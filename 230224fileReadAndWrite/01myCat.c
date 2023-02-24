#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char** argv)
{
	if(argv[1] == NULL || argc < 2)
	{
		printf("usage:inputsource file\n");
	}
	else
	{
		FILE *fp = fopen(argv[1],"r");
		char* buf = NULL;
		const int bufLen = 4096;
		int nRead = 0;
		buf = (char*)malloc(bufLen * sizeof(char));
		while((fgets(buf,bufLen,fp)) != NULL)
		{
			printf("%s",buf);
		}
		free(buf);
		buf = NULL;
		fclose(fp);
	}
	return 0;
}
