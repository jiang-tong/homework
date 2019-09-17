#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "SCORE.h"
#define  _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "SCORE.h"
int main()
{

	printf("******************************\n");
	printf("       学生成绩管理分析系统        \n");
	printf("       JiangTong           \n");
	printf("******************************\n\n");

	/*-1.变量初始化-*/
	int N = 0;            //学生总数
	SS  *pstu = NULL;    //学生数组-结构体数组指针实现

	//2.读取学生信息
	pstu = readDataFromFile(&N);

	/*-3.计算学生总成绩（总成绩 = 0.2*平时成绩 + 0.2* 实验成绩 + 0.6*期末成绩)--*/
	calcuScore(pstu, N);

	/*-4.根据学生成绩排名-*/
	sortScore(pstu, N);

	/*-5.按照排名输出学生信息-*/
	printOut(pstu, N);

    //*6.  查询：输入学号可查询某个学生的成绩信息。
	searchInformation(pstu, N);


	//*7. 分析：统计全班学生成绩的均值和标准方差，并对成绩分布简要分析
    analysisScore(pstu, N);

    //*-8.释放动态内存空间-*//
	free(pstu);

	system("pause");
	return 0;
}
//1.1手动输入学生基本数据
void readData(SS stu[], int N)
{

	printf("请按照如下格式输入学生信息:学号,姓名,平时成绩,实验成绩，期末成绩\n");

	for (int i = 0; i < N; i++)
	{
		printf("第%d个学生:", i + 1);
		scanf("%s %s %f %f %f", &stu[i].number, &stu[i].name, &stu[i].dailyScore,&stu[i].experimentalScore, &stu[i].finalScore);
		printf("\n");
	}

	printf("------成绩录入完毕!--------\n");

}

//1.2从文件里读取学生基本数据
SS* readDataFromFile(int *N)
{

	printf("\n------第一步: 从文件读取学生的成绩信息--------\n");

	SS *stu;// 开辟新空间,存取文件中的每个学生信息

	FILE *fp = NULL;
	int count = 0;
	int index = 0;

	fp = fopen("data.txt", "r");

	//1.获取学生数目
	if (fp != NULL)
	{
		fscanf(fp, "%d", &count);
		*N = count;
	}
	else
	{
		printf("failed to open the info file\n");
		getchar();
	}

	printf("学生数目为:%d\n", count);


	//2.给所有学生分配存储空间
	stu = (SS*)malloc(count * sizeof(SS));


	//3.读取每条学生的信息
	while ((!feof(fp)))
	{

		//读入文件数据到内存
		fscanf(fp, "%s %s %f %f %f\n", (stu[index].number), (stu[index].name), &stu[index].dailyScore, &stu[index].experimentalScore, &stu[index].finalScore);

		//输出排序后的学生信息
		printf("* 学号:%s	姓名:%s		平时成绩：%4.2f分	实验成绩：%4.2f分	期末成绩:%4.2f分\n", (stu[index].number), (stu[index].name), stu[index].dailyScore, stu[index].experimentalScore, stu[index].finalScore);

		index++;
	}

	getchar();

	fclose(fp);

	return stu;
}

//2.计算N个学生各自的总评成绩
void calcuScore(SS stu[], int N)
{


	printf("\n------第二步: 计算每个学生的总评成绩--------\n");

	for (int i = 0; i < N; i++)
	{

		stu[i].generalScore = 0.2*stu[i].dailyScore + 0.2 * stu[i].experimentalScore + 0.6*stu[i].finalScore;
		printf("* 学号：%s	姓名:%s		总成绩:%4.2f分\n", (stu[i].number), (stu[i].name), stu[i].generalScore);

	}

	getchar();
}


//3.根据总评成绩排名
int cmpBigtoSmall(const void *a, const void *b)
{

	SS *aa = (SS *)(a);
	SS *bb = (SS *)(b);



	if ((*aa).generalScore < (*bb).generalScore)  return 1;

	else if ((*aa).generalScore > (*bb).generalScore)  return -1;

	else
		return 0;

}

void sortScore(SS stu[], int N)
{

	qsort(&(stu[0]), N, sizeof(stu[0]), cmpBigtoSmall);

}

//4.按照一定的格式输出N个学生的信息
void printOut(SS stu[], int N)
{

	printf("\n------第三步: 根据总成绩输出学生排名信息!------\n");

	for (int i = 0; i < N; i++)
	{

		printf("第%d名信息 学号：%s	姓名:%s		总成绩:%4.2f分\n", i + 1, &(stu[i].number[0]), &(stu[i].name[0]), stu[i].generalScore);
	}

	getchar();

}
//5. 查询：输入学号可查询某个学生的成绩信息
void searchInformation(SS stu[], int N)
{
    printf("\n------第四步: 输入学号查询某个学生的成绩信息--------\n");
    int i,k=-1;
    int index=0;
    char c[10];
    printf("输入你要查询的学号信息:");
    scanf("%s",c);
    for(int i=0; i<N; i++)
    {
        if(strcmp(stu[i].number, c)==0)
        {
            printf("该学生的信息为：%s %s %4.2f分 %4.2f分 %4.2f分\n",(stu[i].number), (stu[i].name), stu[i].dailyScore, stu[i].experimentalScore, stu[i].finalScore);
        }
    }
}
//6. 分析：统计全班学生成绩的均值和标准方差，并对成绩分布简要分析
void analysisScore(SS stu[], int N)
{
    printf("\n------第五步: 统计全班学生成绩的均值和标准方差，并对成绩分布简要分析--------\n");
    float mean;
    float variance;
    for (int i = 0; i < N; i++)
    {
		mean += stu[i].generalScore;
	}
	mean = 1.0 * mean / N;
	for (int i = 0; i < N; i++)
    {
		variance += (stu[i].generalScore - mean) * (stu[i].generalScore - mean);
	}
	variance = 1.0 * variance / N;
	if (mean >= 80)
		printf("全班同学的均值为:%4.4f，  整体水平优秀！\n", mean);
	else if (mean >= 60)
		printf("全班同学的均值为:%4.4f，  整体水平比较差！\n", mean);
	else
		printf("全班同学的均值为:%4.4f，  整体水平非常差！\n", mean);

	if (variance <= 10)
		printf("全班同学的方差为:%4.4f， 成绩波动较小。\n", variance);
	else if (variance <= 20)
		printf("全班同学的方差为:%4.4f， 成绩波动有点大。\n", variance);
	else
		printf("全班同学的方差为:%4.4f， 成绩波动非常大。\n", variance);
		printf("全班同学的均值为:%4.4f\n方差为:%4.4f\n", mean, variance);
	getchar();
}
