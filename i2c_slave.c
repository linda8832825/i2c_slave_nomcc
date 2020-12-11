#include <xc.h>
#include "pic16f18854.h"

uint8_t z;
void __interrupt() I2C_Slave_Read()
{
    
  if(PIR3bits.SSP1IF == 1)
  {
    SSP1CON1bits.CKP = 0;

    if ((SSP1CON1bits.SSPOV) || (SSP1CON1bits.WCOL)){
    
      z = SSP1BUF; // Read the previous value to clear the buffer
      SSP1CON1bits.SSPOV = 0; // Clear the overflow flag
      SSP1CON1bits.WCOL = 0;  // Clear the collision bit
      SSP1CON1bits.CKP = 1;
    }

    if(!SSP1STATbits.D_nA && !SSP1STATbits.R_nW){//¼g
      while(!SSP1STATbits.BF);  
      RA1=SSP1BUF;
      SSP1CON1bits.CKP = 1;
    }
    else if(!SSP1STATbits.D_nA && SSP1STATbits.R_nW)//Åª
    {
      z = SSP1BUF;
      SSP1STATbits.BF = 0;
      SSP1BUF = PORTA ;
      SSP1CON1bits.CKP = 1;
      while(SSP1STATbits.BF);
    }

    PIR3bits.SSP1IF = 0;
  }
}
