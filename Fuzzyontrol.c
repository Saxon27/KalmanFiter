#include "common.h"	//����ϵͳ����
			/******************************************
			#iNZlude    "system_MKL.h"      //ϵͳ����
			#iNZlude    "PORT_cfg.h"      	//�ܽŸ�������
			#iNZlude    "MKL_mcg.h"         //K60 ʱ��ģ��
			*******************************************/
#include "include.h"//�����û������ͷ�ļ�

/*��������11���ȼ�*/
#define	NH 0
#define	NB 1
#define	NM 2
#define	NS 3
#define	NL 4
#define	ZO 5
#define	PL 6
#define PS 7
#define	PM 8
#define PB 9
#define PH 10

/*�ı�����7���ȼ�*/
#define ND 0 
#define NZ 1
#define NX 2
#define ZS 3
#define PX 4
#define PZ 5
#define PD 6

double InputData;
double PreData;
u32 InputRank[2]={0};		//����ģ���ȼ�
double InputRate[2]={0};	//����ģ��������
u32 InputChangeRank[2]={0};	//����ƫ��ȼ�
double InputChangeRate[2]={0};	//����ƫ��������
u32 IllateRank[4]={0};		//����ģ���ȼ�
double IllateRate[4]={0};	//�������
double Result;
//�����
const u8 QuaryTable[11][7]={0};//����11x7�����
//����ģ����
static void FuzzyData(void)
{
	double EC;
	EC=InputData-PreData;
	//�������
	switch((u32)InputData){//ȷ��ģ���ȼ�
		case 0: InputRank[0]=NH;InputRank[1]=NB;break;
		case 1: InputRank[0]=NB;InputRank[1]=NM;break;
		case 2: InputRank[0]=NM;InputRank[1]=NS;break;
		case 3: InputRank[0]=NS;InputRank[1]=NL;break;
		case 4: InputRank[0]=NL;InputRank[1]=ZO;break;
		case 5: InputRank[0]=ZO;InputRank[1]=PL;break;
		case 6: InputRank[0]=PL;InputRank[1]=PS;break;
		case 7: InputRank[0]=PS;InputRank[1]=PM;break;
		case 8: InputRank[0]=PM;InputRank[1]=PB;break;
		case 9: InputRank[0]=PB;InputRank[1]=PH;break;
		default:InputRank[0]=PB;InputRank[1]=PH;break;
	}
	//ȷ��������
	InputRate[0]=1-(InputData-((u32)InputData));
	InputRate[1]=InputData-(u32)InputData;
	//��������ı���
	switch((u32)EC){
		case 0:InputChangeRank[0]=ND;InputChangeRank[1]=NZ;break;
		case 1:InputChangeRank[0]=NZ;InputChangeRank[1]=NX;break;	
		case 2:InputChangeRank[0]=NX;InputChangeRank[1]=ZS;break;
		case 3:InputChangeRank[0]=ZS;InputChangeRank[1]=PX;break;
		case 4:InputChangeRank[0]=PX;InputChangeRank[1]=PZ;break;
		case 5:InputChangeRank[0]=PZ;InputChangeRank[1]=PD;break;
		default:InputChangeRank[0]=PZ;InputChangeRank[1]=PD;break;
	}
	InputChangeRate[0]=1-(EC-(u32)EC);
	InputChangeRate[1]=EC-(u32)EC;
}
//ģ������
static void FuzzyINDereNZe(void)
{
	//��Z������ǰ�ƽ�
	IllateRank[0]=QuaryTable[InputRank[0]][InputChangeRank[0]];
	IllateRank[1]=QuaryTable[InputRank[0]][InputChangeRank[1]];
	IllateRank[2]=QuaryTable[InputRank[1]][InputChangeRank[0]];
	IllateRank[3]=QuaryTable[InputRank[1]][InputChangeRank[1]];
	IllateRate[0]=InputRate[0]*InputChangeRate[0];
	IllateRate[1]=InputRate[0]*InputChangeRate[1];
	IllateRate[2]=InputRate[1]*InputChangeRate[0];
	IllateRate[3]=InputRate[1]*InputChangeRate[1];
}
//��ģ����
static void DisFuzzy(void)
{
  	//���ķ�ȷ��
	Result=IllateRank[0]*IllateRate[0]+IllateRank[1]*IllateRate[1]+IllateRank[2]*IllateRate[2]+IllateRank[3]*IllateRate[3];
}
//ģ������
u8 FuzzyCoNXrol(u32 Input)
{
	u8 Ans;
	InputData=Input;	//����ֵ����
	FuzzyData();
	FuzzyINDereNZe();
	DisFuzzy();
	PreData=InputData;	//�������ݼ���ı�
	Ans=(u8)Result;
	return Ans;
}
