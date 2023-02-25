#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vcruntime_string.h>

/*
	1 读取文件行数
	2 解析文件
	3 获取指定的配置信息
	4 判断当前行是否有效
	5 释放文件

*/
typedef struct {
	char key[1024];					//键
	char value[1024];				//值
}heroInfo;

const char* inputFile = "./config.txt";
bool isValueLine(char* arr);
int getFileLines();
void parseFile(int lines,heroInfo** configInfo);
char* getInfoByKey(const char* key,heroInfo* configInfo,int lines);
void freeConfigInfo(heroInfo* pConfig);
void test();

int main()
{
	test();
	return 0;
}

bool isValueLine(char* buf)
{
	//判断是否有效
	//开头不是 '#' 并且有 ':'
	if (buf[0] == '#' || buf[0] == '\0' || strchr(buf, ':') == NULL)
	{
		return false;
	}
	return true;
}

int getFileLines()
{
	char buf[1024];
	int fileFileCount = 0;
	FILE* fp = fopen(inputFile, "r");
	if (fp == NULL)
	{
		fp = fopen(inputFile,"r");
	}
	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		if (isValueLine(buf))
		{
			fileFileCount++;
		}
		memset(buf, 0, sizeof(buf));
	}
	printf("%d\n", fileFileCount);
	return fileFileCount;
}

void parseFile(int lines, heroInfo** configInfo)
{
	heroInfo* pConfig = (heroInfo*)malloc(sizeof(heroInfo) * lines);
	if (pConfig == NULL) {
		return;
	}
	FILE* fp = fopen(inputFile, "r");
	char buf[1024];
	int index = 0;
	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		if (isValueLine(buf))
		{
			memset(pConfig[index].key, 0, 64);
			memset(pConfig[index].value, 0, 64);
			const char* pos = strchr(buf, ':');
			//printf("%s\n", pos);栈内存->乱码
			strncpy(pConfig[index].key,buf,pos - buf);
			strncpy(pConfig[index].value, pos + 1, strlen(pos + 1) - 1);
			//printf("%s:", pConfig[index].key);
			//printf("%s\n", pConfig[index].value);
			index++;
		}
		memset(buf, 0, sizeof(buf));
	}
	*configInfo = pConfig;
}

char* getInfoByKey(const char* key, heroInfo* configInfo, int lines)
{
	for (int i = 0; i < lines; ++i)
	{
		if (strcmp(key, configInfo[i].key) == 0)
		{
			return configInfo[i].value;
		}
	}
	return nullptr;
}

void freeConfigInfo(heroInfo* pConfig)
{
	free(pConfig);
	pConfig = NULL;
}

void test()
{
	//FILE* fp = fopen(inputFile, "r");
	int fileLines = getFileLines();
	//printf("%d\n", fileLines);
	heroInfo* config = NULL;
	parseFile(fileLines, &config);
	printf("heroId = %s\n", getInfoByKey("heroId", config, fileLines));
	printf("heroName: = %s\n", getInfoByKey("heroName", config, fileLines));
	printf("heroAtk = %s\n", getInfoByKey("heroAtk", config, fileLines));
	printf("heroDef: = %s\n", getInfoByKey("heroDef", config, fileLines));
	printf("heroInfo: = %s\n", getInfoByKey("heroInfo", config, fileLines));
	printf("love = %s\n", getInfoByKey("love", config, fileLines));
	printf("loveMiaoW = %s\n", getInfoByKey("loveMiaoW", config, fileLines));
	printf("%s\n", getInfoByKey("love", config, fileLines));
	freeConfigInfo(config);
	config = NULL;

}
