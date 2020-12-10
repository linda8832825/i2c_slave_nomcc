#ifndef INIT_H
#define	INIT_H

#include <xc.h> // include processor files - each processor file is guarded.  

void init(void);
void OSCILLATOR_Initialize(void);
void PMD_Initialize(void);
void PIN_MANAGER_Initialize(void);
void slave_init(void);





#endif	/* INIT_H */

