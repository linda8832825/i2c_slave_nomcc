#include <pic16f18854.h>
#include "init.h"
void init(void)
{
    PMD_Initialize();
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    slave_init();
}

void OSCILLATOR_Initialize(void)
{
    // NOSC HFINTOSC; NDIV 1; 
    OSCCON1 = 0x60;
    // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCCON3 = 0x00;
    // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCEN = 0x00;
    // HFFRQ 4_MHz; 
    OSCFRQ = 0x02;
    // HFTUN 0; 
    OSCTUNE = 0x00;
}

void PMD_Initialize(void)
{
    // CLKRMD CLKR enabled; SYSCMD SYSCLK enabled; SCANMD SCANNER enabled; FVRMD FVR enabled; IOCMD IOC enabled; CRCMD CRC enabled; NVMMD NVM enabled; 
    PMD0 = 0x00;
    // TMR0MD TMR0 enabled; TMR1MD TMR1 enabled; TMR4MD TMR4 enabled; TMR5MD TMR5 enabled; TMR2MD TMR2 enabled; TMR3MD TMR3 enabled; NCOMD DDS(NCO) enabled; TMR6MD TMR6 enabled; 
    PMD1 = 0x00;
    // ZCDMD ZCD enabled; DACMD DAC enabled; CMP1MD CMP1 enabled; ADCMD ADC enabled; CMP2MD CMP2 enabled; 
    PMD2 = 0x00;
    // CCP2MD CCP2 enabled; CCP1MD CCP1 enabled; CCP4MD CCP4 enabled; CCP3MD CCP3 enabled; CCP5MD CCP5 enabled; PWM6MD PWM6 enabled; PWM7MD PWM7 enabled; 
    PMD3 = 0x00;
    // CWG3MD CWG3 enabled; CWG2MD CWG2 enabled; CWG1MD CWG1 enabled; MSSP1MD MSSP1 enabled; UART1MD EUSART enabled; MSSP2MD MSSP2 enabled; 
    PMD4 = 0x00;
    // DSMMD DSM enabled; CLC3MD CLC3 enabled; CLC4MD CLC4 enabled; SMT1MD SMT1 enabled; SMT2MD SMT2 enabled; CLC1MD CLC1 enabled; CLC2MD CLC2 enabled; 
    PMD5 = 0x00;
}

void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISA = 0x00;
    TRISB = 0xFF;
    TRISC = 0xFF;

    /**
    ANSELx registers
    */
    ANSELC = 0xE7;
    ANSELB = 0xFF;
    ANSELA = 0xFD;

    /**
    WPUx registers
    */
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    ODx registers
    */
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLE = 0x08;

//    SSP1CLKPPS = 0x13;   //RC3->MSSP1:SCL1;    
//    RC3PPS = 0x14;   //RC3->MSSP1:SCL1;    
//    RC4PPS = 0x15;   //RC4->MSSP1:SDA1;    
//    SSP1DATPPS = 0x14;   //RC4->MSSP1:SDA1;    
}

void slave_init(void){
    SSP1STAT = 0xC0;//智能輸入邏輯
    SSP1ADD = (uint8_t)(0x50<<1);
    SSP1MSK = 0xFF;
    SSP1CON1 = 0x3E;
    SSP1CON2 = 0x21;
    SSP1CON3 = 0xFF;
    
    GIE = 1;//中斷智能
    PEIE = 1;//中斷智能
    PIR3bits.SSP1IF = 0;//等待傳輸
    PIR3bits.BCL1IF = 0;//未檢測到衝突
    PIE3bits.SSP1IE = 1;//允許中斷
    PIE3bits.BCL1IE = 1;//衝突允許中斷
    
}

/**
 End of File
*/
