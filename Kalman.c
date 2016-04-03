#include "common.h"	//����ϵͳ����
			/******************************************
			#include    "system_MKL.h"      //ϵͳ����
			#include    "PORT_cfg.h"      	//�ܽŸ�������
			#include    "MKL_mcg.h"         //K60 ʱ��ģ��
			*******************************************/
#include "include.h"//�����û������ͷ�ļ�


volatile u32 AdjustVar1=0;//����ֵ
volatile u32 AdjustVar2=0;
volatile u32 AdjustVar3=0;
/*�������˲���Ҫ����4��ֵ����������Զ�����*/
u8 KalmanFitterAD1(u8 MeasVar)
{
    static double PreOptimalVar=1;                       //��ǰ����ֵ
    double CurMeasVar=0,CurEstimateVar=0;        //��ǰ����ֵ����ǰԤ��ֵ
    double CurOptimalVar=0;                      //��ǰ����ֵ
    #define SysNoiseCoVar         (2.7182818-6)
    #define MeasNoiseCoVar        (2.7182818-1)           //ϵͳ����Э�����������Э����
    static double CurSysCoVar=0,PreSysCoVar=30;         //��ǰϵͳЭ�����ǰϵͳЭ����
    double KalmanGain=0;                         //����������
    CurMeasVar=MeasVar;                         //��ǰϵͳ����ֵ
    //��ǰϵͳ����ֵ����ǰϵͳЭ������Ҫ���÷����ʼֵ��������
    
    
    
    /*��ǰ����ֵ=��ǰ����ֵ+����ֵ*/
    CurEstimateVar=PreOptimalVar+AdjustVar1;
    AdjustVar1=0;                                //�趨����ֵ��ԭ���Ǽӿ����
    
    
    
    /*��ǰϵͳЭ����=��ǰϵͳЭ����+ϵͳ����Э����*/
    CurSysCoVar=PreSysCoVar+SysNoiseCoVar;
    
    
    
    /*����������=��ǰϵͳЭ����/(��ǰϵͳЭ����+��������Э����)*/
    KalmanGain=CurSysCoVar/(CurSysCoVar+MeasNoiseCoVar);
    
    
    
    
    /*��ǰϵͳ����ֵ=��ǰϵͳ����ֵ+����������*������ֵ-��ǰϵͳ����ֵ��*/
    CurOptimalVar=CurEstimateVar+KalmanGain*(CurMeasVar-CurEstimateVar);
    
    
    
    /*��ǰϵͳ����Э����=��1-���������棩x��ǰϵͳЭ����*/
    PreSysCoVar =(1-KalmanGain)*CurSysCoVar;
    PreOptimalVar=CurOptimalVar;
    
    /*��������*/
    return (u8)CurOptimalVar;
    
}
u8 KalmanFitterAD2(u8 MeasVar)
{
    static double PreOptimalVar=1;                       //��ǰ����ֵ
    double CurMeasVar=0,CurEstimateVar=0;        //��ǰ����ֵ����ǰԤ��ֵ
    double CurOptimalVar=0;                      //��ǰ����ֵ
    #define SysNoiseCoVar         (2.7182818-6)
    #define MeasNoiseCoVar        (2.7182818-1)           //ϵͳ����Э�����������Э����
    static double CurSysCoVar=0,PreSysCoVar=30;         //��ǰϵͳЭ�����ǰϵͳЭ����
    double KalmanGain=0;                         //����������
    CurMeasVar=MeasVar;                         //��ǰϵͳ����ֵ
    //��ǰϵͳ����ֵ����ǰϵͳЭ������Ҫ���÷����ʼֵ��������
    
    
    
    /*��ǰ����ֵ=��ǰ����ֵ+����ֵ*/
    CurEstimateVar=PreOptimalVar+AdjustVar2;
    AdjustVar2=0;                                //�趨����ֵ��ԭ���Ǽӿ����
    
    
    
    /*��ǰϵͳЭ����=��ǰϵͳЭ����+ϵͳ����Э����*/
    CurSysCoVar=PreSysCoVar+SysNoiseCoVar;
    
    
    
    /*����������=��ǰϵͳЭ����/(��ǰϵͳЭ����+��������Э����)*/
    KalmanGain=CurSysCoVar/(CurSysCoVar+MeasNoiseCoVar);
    
    
    
    
    /*��ǰϵͳ����ֵ=��ǰϵͳ����ֵ+����������*������ֵ-��ǰϵͳ����ֵ��*/
    CurOptimalVar=CurEstimateVar+KalmanGain*(CurMeasVar-CurEstimateVar);
    
    
    
    /*��ǰϵͳ����Э����=��1-���������棩x��ǰϵͳЭ����*/
    PreSysCoVar =(1-KalmanGain)*CurSysCoVar;
    
    /*�����ݹ������*/
    PreOptimalVar=CurOptimalVar;
    
    /*��������*/
    return (u8)CurOptimalVar;
}
u8 KalmanFitterAD3(u8 MeasVar)
{
    static double PreOptimalVar=1;                       //��ǰ����ֵ
    double CurMeasVar=0,CurEstimateVar=0;        //��ǰ����ֵ����ǰԤ��ֵ
    double CurOptimalVar=0;                      //��ǰ����ֵ
    #define SysNoiseCoVar         (2.7182818-6)
    #define MeasNoiseCoVar        (2.7182818-1)           //ϵͳ����Э�����������Э����
    static double CurSysCoVar=0,PreSysCoVar=30;         //��ǰϵͳЭ�����ǰϵͳЭ����
    double KalmanGain=0;                         //����������
    CurMeasVar=MeasVar;                         //��ǰϵͳ����ֵ
    //��ǰϵͳ����ֵ����ǰϵͳЭ������Ҫ���÷����ʼֵ��������
    
    
    
    /*��ǰ����ֵ=��ǰ����ֵ+����ֵ*/
    CurEstimateVar=PreOptimalVar+AdjustVar3;
    AdjustVar3=0;                                //�趨����ֵ��ԭ���Ǽӿ����
    
    
    
    /*��ǰϵͳЭ����=��ǰϵͳЭ����+ϵͳ����Э����*/
    CurSysCoVar=PreSysCoVar+SysNoiseCoVar;
    
    
    
    /*����������=��ǰϵͳЭ����/(��ǰϵͳЭ����+��������Э����)*/
    KalmanGain=CurSysCoVar/(CurSysCoVar+MeasNoiseCoVar);
    
    
    
    
    /*��ǰϵͳ����ֵ=��ǰϵͳ����ֵ+����������*������ֵ-��ǰϵͳ����ֵ��*/
    CurOptimalVar=CurEstimateVar+KalmanGain*(CurMeasVar-CurEstimateVar);
    
    
    
    /*��ǰϵͳ����Э����=��1-���������棩x��ǰϵͳЭ����*/
    PreSysCoVar =(1-KalmanGain)*CurSysCoVar;
    PreOptimalVar=CurOptimalVar;
    
    /*��������*/
    return (u8)CurOptimalVar;
}

//��������������ݼ���ƫ�����

u8 Distance(u8 L,u8 M,u8 R)
{
	double Result=0;
    
	return (u8)Result;
}