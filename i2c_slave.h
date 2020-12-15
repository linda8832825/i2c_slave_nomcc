#ifndef i2c_slave
#define	i2c_slave

#include <xc.h> 
uint8_t z,y;
void  __interrupt() I2C_Slave_Read();
#endif	/* i2c_slave */

