#include "common.h"	//����ϵͳ����
			/******************************************
			#include    "system_MKL.h"      //ϵͳ����
			#include    "PORT_cfg.h"      	//�ܽŸ�������
			#include    "MKL_mcg.h"         //K60 ʱ��ģ��
			*******************************************/
#include "include.h"//�����û������ͷ�ļ�
u8 adv1,adv2,adv3;
u8 var[8];
#define CMD_WARE     3	//����ʾ����
u8 FinishOfRx=0;        //���ڽ����������
u32 RxData;
u8 FinishOfRead=0;
/*�������˲�ʹ�ñ���*/
//extern volatile u32 AdjustVar1=0;//����ֵ
//extern volatile u32 AdjustVar2=0;
///extern volatile u32 AdjustVar3=0;
u8 KalmanFitterAD1(u8 MeasVar);
u8 KalmanFitterAD2(u8 MeasVar);
u8 KalmanFitterAD3(u8 MeasVar);
/*********************************************/
//����������ʾ����
void VIEW_send(uint8 *buff, uint32 size)//��λ��	
{
    uint8 cmdf[2] = {CMD_WARE, ~CMD_WARE};      //���ڵ��� ʹ�õ�ǰ����
    uint8 cmdr[2] = {~CMD_WARE, CMD_WARE};      //���ڵ��� ʹ�õĺ�����
    uart_putbuff(UART0,cmdf, sizeof(cmdf));    //�ȷ���ǰ����
    uart_putbuff(UART0,buff, size);             //��������
    uart_putbuff(UART0,cmdr, sizeof(cmdr));    //���ͺ�����
}

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
        sum=0;max=0;min=255;
        for(i=0;i<=9;i++){
          sum+= AD1[i];
            if(max<AD1[i])
              max=AD1[i];
            if(min>AD1[i])
              min=AD1[i];
        }
        adv1=(sum-max-min)/8; 
        
        
        sum=0;max=0;min=255;
        for(i=0;i<=9;i++){
          sum+= AD2[i];
            if(max<AD2[i])
              max=AD2[i];
            if(min>AD2[i])
              min=AD2[i];
        }
        adv2=(sum-max-min)/8;
        
        
        sum=0;max=0;min=255;
        for(i=0;i<=9;i++){
          sum+= AD3[i];
            if(max<AD3[i])
              max=AD3[i];
            if(min>AD3[i])
              min=AD3[i];
        }
        adv3=(sum-max-min)/8;
}





void uart0_handler(void)
{
    char ch;

    if(uart_query(UART0) == 1)   //�������ݼĴ�����
    {
        //�û���Ҫ�����������
        uart_getchar   (UART0, &ch);                    //���޵ȴ�����1���ֽ�
        uart_putchar   (UART0 , ch);                    //�����ַ���
        if(ch!=' '){
          FinishOfRx=0;         //����û�����
          if(FinishOfRead==1){     //��ȡ���
            RxData=RxData*10;
            RxData+=ch-'0';
            }
        }else{
            FinishOfRx = 1; //�������
            printf("�������������%d\r\n",RxData);
        }
        
    }
}

void main()
{
        unsigned char A1,A2,A3;
	unsigned char K1,K2,K3;
        DisableInterrupts; //�ر��ж�ʹ��
	KEY_INIT(); 
	LED_INIT();
	uart_init(UART0,115200);     //��ʼ������(���� printf ���� ���õĶ˿ھ��� UART0���Ѿ���ʼ���ˣ���˴˴�����Ҫ�ٳ�ʼ��)
	adc_init(ADC0_DP0);//ADC��ʼ��
        set_vector_handler(UART0_VECTORn,uart0_handler);   // �����жϷ��������ж���������  uart0_handler ������ӵ��ж�����������Ҫ�����ֶ�����
        uart_rx_irq_en(UART0);
        //printf("������ϵͳ����\r\n");
        
	while(1)
	{
            AD_AVR();
            A1=(u8)(126*adc_once(ADC0_SE8,  ADC_8bit)/160);
            A2=(u8)(126*adc_once(ADC0_SE9, ADC_8bit)/198);
            A3=(u8)(126*adc_once(ADC0_SE13, ADC_8bit)/192);
            K1=KalmanFitterAD1(A1);
            K2=KalmanFitterAD2(A2);
            K3=KalmanFitterAD3(A3);
            //printf("\r\n������е�ƽ������:      %d %d %d",adv1,adv2,adv3);
           // printf("\r\n������е�����ֵ:        %d %d %d",A1,A2,A3);
            //printf("\r\n�м��еĿ���������:       %d ",KalmanFitterAD1(adv2));
          //��������ʾ����
            //printf("\n\nADCת�������%d\r\n",ADC_data);
           // printf("\r\n");
          DELAY_MS(10);
           var[0]=K1;                   
           var[1]=K2;
           var[2]=K3;  
           var[3]=A1;	
           var[4]=A2;
           var[5]=A3;          
           var[6]=adv1;
           var[7]=adv2;
           VIEW_send((uint8 *)var,sizeof(var)); //��λ��

	   
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



