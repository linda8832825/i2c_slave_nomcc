#include <xc.h>
#include "pic16f18854.h"
#include "init.h"
#include <stdbool.h>

uint8_t z,y;
void __interrupt() I2C_Slave_Read(){
//z = SSP1BUF;
    if(PIR3bits.SSP1IF == 1){
        SSP1CON1bits.CKP = 0;//clock拉伸，確保資料的讀取

        if ((SSP1CON1bits.SSPOV) || (SSP1CON1bits.WCOL)){
            z = SSP1BUF; // Read the previous value to clear the buffer
            SSP1CON1bits.SSPOV = 0; // Clear the overflow flag
            SSP1CON1bits.WCOL = 0;  // Clear the collision bit
            SSP1CON1bits.CKP = 1;
        }

    if(!SSP1STATbits.D_nA && !SSP1STATbits.R_nW){//接收master寫入的資料
        while(!SSP1STATbits.BF); 
        z = SSP1BUF;
        SSP1CON1bits.CKP = 1;
            while(!SSP1STATbits.BF); 
            y=SSP1BUF;
            if(y==0xDB) RA0=1;
            if(y==0x74) RA1=1;
            if(z==0xDB) RA2=1;
            if(z==0x74) RA3=1;
            SSP1CON1bits.CKP = 1;
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
