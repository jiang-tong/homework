#ifndef __SCORE_H__
#define __SCORE_H__
#include <stdio.h>
typedef struct student
{
	char number[20];  //ѧ��
	char name[20];    //����
	float dailyScore;   //ƽʱ�ɼ�
	float experimentalScore;    //ʵ��ɼ�
	float finalScore;   //��ĩ�ɼ�
	float generalScore; //�����ɼ�

}SS;


/*---------------��������-------------------*/

//1.��ȡѧ����������
//void readData(SS stu[], int N);
SS* readDataFromFile(int *N);

//2.����N��ѧ�������ܳɼ�
void calcuScore(SS stu[], int N);


//3.���������ɼ�����
void sortScore(SS stu[], int N);


//4.����һ���ĸ�ʽ���N��ѧ����������Ϣ
void printOut(SS stu[], int N);


//5.  ��ѯ������ѧ�ſɲ�ѯĳ��ѧ���ĳɼ���Ϣ��
void searchInformation(SS stu[], int N);

//6. ������ͳ��ȫ��ѧ���ɼ��ľ�ֵ�ͱ�׼������Գɼ��ֲ���Ҫ������
void analysisScore(SS stu[], int N);

#endif
