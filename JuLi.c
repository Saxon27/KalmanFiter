#include "common.h"	//����ϵͳ����
			/******************************************
			#include    "system_MKL.h"      //ϵͳ����
			#include    "PORT_cfg.h"      	//�ܽŸ�������
			#include    "MKL_mcg.h"         //K60 ʱ��ģ��
			*******************************************/
#include "include.h"//�����û������ͷ�ļ�
/*
*����˵����
1�����ȼ����й��ɵ�3����
2��Ȼ�������Ϊ����
3�����������
4�������������ͽ������Ϊϵ������
*/



//�����������������
int ComputMatrix(unsigned char X1,unsigned char X2,unsigned char X3)
{
#define Y1	-110
#define Y2	0
#define Y3	110
  double Sum=0;
  double C1,C2,C3;		//�������Ľ��
  double Matrix[3][3];		//3X3�洢�������
  //��������ʽa1��b2��c3+b1��c2��a3+c1��a2��b3-a3��b2��c1-b3��c2��a1-c3��a2��b1
  Sum= X2*X3*X3+X1*X2*X2+X1*X3*X3-X2*X1*X1-X3*X2*X2-X1*X1*X3;	//�������׾��������ʽ
  //���㣨��У����룩��ɵ������
  //1,X,X*X
  Matrix[0][0]=(double)(X2*X3*X3-X3*X2*X2)/Sum;
  Matrix[1][0]=(double)(X1*X3*X3-X3*X2*X2)/Sum;
  Matrix[2][0]=(double)(X1*X2*X2-X1*X2*X2)/Sum;
  Matrix[0][1]=(double)(X3*X3-X2*X2)/Sum;
  Matrix[1][1]=(double)(X3*X3-X1*X1)/Sum;
  Matrix[2][1]=(double)(X2*X2-X1*X1)/Sum;
  Matrix[0][2]=(double)(X3-X2)/Sum;
  Matrix[1][2]=(double)(X3-X1)/Sum;
  Matrix[2][2]=(double)(X3-X2)/Sum;
  
  
  //����ϵ������
  C1=Matrix[0][0]*Y1+Matrix[0][1]*Y2+Matrix[0][1]*Y3;
  C2=Matrix[1][0]*Y1+Matrix[1][1]*Y2+Matrix[1][2]*Y3;
  C3=Matrix[2][0]*Y1+Matrix[2][1]*Y2+Matrix[2][2]*Y3;
  
  return ((int)(-C2/2/C3));//��������ߵ��м�ֵ
  
  
}
