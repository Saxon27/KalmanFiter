#include "common.h"	//����ϵͳ����
			/******************************************
			#include    "system_MKL.h"      //ϵͳ����
			#include    "PORT_cfg.h"      	//�ܽŸ�������
			#include    "MKL_mcg.h"         //K60 ʱ��ģ��
			*******************************************/
#include "include.h"//�����û������ͷ�ļ�
u32 InputClass[2]={0};	//����
u32 InputRatio[2]={0};
u32 InputChangeClass[2]={0};//����ƫ��
u32 InputChangeRatio[2]={0};
u32 IllateClass[4]={0};	//����ģ���ȼ�
u32 IllateRatio[4]={0};	//�������

//����ģ����
static void FuzzyData(u8 value)
{
	 
}
//ģ������
static void FuzzyInference(void)
{
  
}
//��ģ����
static void DisFuzzy(void)
{

}
//ģ������
u8 FuzzyControl(u32 Input)
{
  return 0;
}
