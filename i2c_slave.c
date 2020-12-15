#include <xc.h>
#include "pic16f18854.h"
#include "init.h"
#include <stdbool.h>

uint8_t z,y;
void __interrupt() I2C_Slave_Read(){
    if(PIR3bits.SSP1IF == 1){//傳輸已完成
        SSP1CON1bits.CKP = 0;//clock拉伸，確保資料的讀取

        if ((SSP1CON1bits.SSPOV) || (SSP1CON1bits.WCOL)){//接收溢出或發生衝突
            z = SSP1BUF; // 清空SSP1BUF
            SSP1CON1bits.SSPOV = 0; // 清除溢位標籤
            SSP1CON1bits.WCOL = 0;  // 清除衝突標籤
            SSP1CON1bits.CKP = 1;
        }

    if(!SSP1STATbits.D_nA && !SSP1STATbits.R_nW){//接收master寫入的資料
        while(!SSP1STATbits.BF); //當SSP1SUF滿時
        z = SSP1BUF;//接收slave的id
        SSP1CON1bits.CKP = 1;//在一進中斷的時候設為0，拉伸clk，現在接收完slave的id後恢復scl的動作
        while(!SSP1STATbits.BF); //當SSP1SUF滿時
        y=SSP1BUF; //接收master傳給slave的data
        if(y==0xDB) RA0=1;//data接收正確
        if(y==0x74) RA1=1;
        if(z==0xDB) RA2=1;
        if(z==0x74) RA3=1;//slave接收正確
        SSP1CON1bits.CKP = 1; //恢復SCL的動作
    }
    //    else if(!SSP1STATbits.D_nA && SSP1STATbits.R_nW)//傳送slave的資料給master讀
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
