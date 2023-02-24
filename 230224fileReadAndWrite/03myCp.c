#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copyFile(char* src,char* dst)
{
	if(strcmp(src,dst) == 0)
	{
		printf("path is same, try again.\n");
		exit(1);
	}
	FILE *fSrc = fopen(src,"rb");
	FILE *fDst = fopen(dst,"wb");
	int bufLen = 1024;
	char* buf = (char*)malloc(bufLen * sizeof(char));
	int nRead = 0;
	while((nRead = fread(buf,1,bufLen,fSrc)) > 0)
	{
		fwrite(buf,nRead,1,fDst);
	}
	free(buf);
	buf = NULL;
	fclose(fSrc);
	fSrc = NULL;
	fclose(fDst);
	fDst = NULL;
}

int main(int argc,char** argv)
{
	if(argv[1] == NULL || argv[2] == NULL)
	{
		printf("usage:input source file\n");
	}
	else
	{
		copyFile(argv[1],argv[2]);
	}
	return 0;
}
