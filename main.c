#include "common.h"	//����ϵͳ����
			/******************************************
			#include    "system_MKL.h"      //ϵͳ����
			#include    "PORT_cfg.h"      	//�ܽŸ�������
			#include    "MKL_mcg.h"         //K60 ʱ��ģ��
			*******************************************/
#include "include.h"//�����û������ͷ�ļ�
u8 adv1,adv2,adv3;
void AD_AVR(void)
{
        u8 AD1[10],AD2[10],AD3[10];
        u8 i,max,min;
        u32 sum;
        for(i=0;i<=9;i++){
          AD1[i]=(u8)(126*adc_once(ADC0_SE8,  ADC_8bit)/160);
          AD2[i]=(u8)(126*adc_once(ADC0_SE9, ADC_8bit)/198);
          AD3[i]=(u8)(126*adc_once(ADC0_SE13, ADC_8bit)/192);
        }
        max=0;min=255;
        for(i=0;i<=9;i++){
          sum+= AD1[i];
            if(max<AD1[i])
              max=AD1[i];
            if(min>AD1[i])
              min=AD1[i];
        }
        adv1=(sum-max-min)/8; 
        max=0;min=255;
        for(i=0;i<=9;i++){
          sum+= AD2[i];
            if(max<AD2[i])
              max=AD2[i];
            if(min>AD2[i])
              min=AD2[i];
        }
        adv2=(sum-max-min)/8;
        max=0;min=255;
        for(i=0;i<=9;i++){
          sum+= AD3[i];
            if(max<AD3[i])
              max=AD3[i];
            if(min>AD3[i])
              min=AD3[i];
        }
        adv3=(sum-max-min)/8;
}
void main()
{
        
        DisableInterrupts; //�ر��ж�ʹ��
	KEY_INIT(); 
	LED_INIT();
	uart_init(UART0,115200);     //��ʼ������(���� printf ���� ���õĶ˿ھ��� UART0���Ѿ���ʼ���ˣ���˴˴�����Ҫ�ٳ�ʼ��)
	DELAY_MS(100);//�ϵ���ʱ
	adc_init(ADC0_DP0);//ADC��ʼ��
	while(1)
	{
            AD_AVR();
          //��������ʾ����
            printf("������е�����:%d,%d,%d",adv1,adv2,adv3);
            printf("�����֮��:%d",adv1+adv3);
            printf("�����ֻ��:%d",abs(adv1-adv3));
            //printf("\n\nADCת�������%d\r\n",ADC_data);
            printf("\r\n");
           DELAY_MS(500);
            //dianya = ADC_data*3.3/65535;
            //printf("\r\n");
	   
	}
	
}




/******************************************************************************/










/***************************   ADCѧϰ   ***************************************
extern void     adc_init    (ADCn_Ch_e);                //ADC��ʼ��
extern uint16   adc_once    (ADCn_Ch_e, ADC_nbit);      //�ɼ�һ��һ·ģ������ADֵ
	ADCn_Ch_e//ADCͨ��
	ADC_nbit//n = 8,12,16

extern void     adc_stop    (ADCn_e);                   //ֹͣADCת��

*******************************************************************************/

















/******************************��ʱ����*************************************/
/***************************************************************************
VCAN_MK60_conf.h
#if  0
#include "MKL_lptmr.h"//��ʱ����ʱ
#define     DELAY()         lptmr_delay_ms(500)
#define     DELAY_MS(ms)    lptmr_delay_ms(ms)
#define     DELAY_US(us)    lptmr_delay_us(us)
#elif   0
#include "MKL_pit.h"
#define DELAY()         pit_delay_ms(PIT1,500)
#define DELAY_MS(ms)    pit_delay_ms(PIT1,ms)
#define DELAY_US(us)    pit_delay_us(PIT1,us)
#else
#include "MKL_SysTick.h"//ϵͳʱ��
#define DELAY()         systick_delay_ms(500)
#define DELAY_MS(ms)    systick_delay_ms(ms)
#define DELAY_US(us)    systick_delay_us(us)

Ҳ����˵Ҫ�������ʱ��ֱ��ȥ VCAN_MK60_conf.h����һ��ѡ��������
DELAY()       //500ms��ʱ 
DELAY_MS(ms)  //ms����ʱ
DELAY_US(us)  //us����ʱ
****************************************************************************/



