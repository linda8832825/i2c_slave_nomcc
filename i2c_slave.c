#include <xc.h>
#include "pic16f18854.h"
#include "init.h"
#include <stdbool.h>

uint8_t z,y;
void __interrupt() I2C_Slave_Read(){
    if(PIR3bits.SSP1IF == 1){//�ǿ�w����
        SSP1CON1bits.CKP = 0;//clock�Ԧ��A�T�O��ƪ�Ū��

        if ((SSP1CON1bits.SSPOV) || (SSP1CON1bits.WCOL)){//�������X�εo�ͽĬ�
            z = SSP1BUF; // �M��SSP1BUF
            SSP1CON1bits.SSPOV = 0; // �M���������
            SSP1CON1bits.WCOL = 0;  // �M���Ĭ����
            SSP1CON1bits.CKP = 1;
        }

    if(!SSP1STATbits.D_nA && !SSP1STATbits.R_nW){//����master�g�J�����
        while(!SSP1STATbits.BF); //��SSP1SUF����
        z = SSP1BUF;//����slave��id
        SSP1CON1bits.CKP = 1;//�b�@�i���_���ɭԳ]��0�A�Ԧ�clk�A�{�b������slave��id���_scl���ʧ@
        while(!SSP1STATbits.BF); //��SSP1SUF����
        y=SSP1BUF; //����master�ǵ�slave��data
        if(y==0xDB) RA0=1;//data�������T
        if(y==0x74) RA1=1;
        if(z==0xDB) RA2=1;
        if(z==0x74) RA3=1;//slave�������T
        SSP1CON1bits.CKP = 1; //��_SCL���ʧ@
    }
    //    else if(!SSP1STATbits.D_nA && SSP1STATbits.R_nW)//�ǰeslave����Ƶ�masterŪ
    //    {
    //      z = SSP1BUF;
    //      SSP1STATbits.BF = 0;
    //      SSP1BUF = PORTA ;
    //      SSP1CON1bits.CKP = 1;
    //      while(SSP1STATbits.BF);
    //    }

    PIR3bits.SSP1IF = 0;
    }
}
