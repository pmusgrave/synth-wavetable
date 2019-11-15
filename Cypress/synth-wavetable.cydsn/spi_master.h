#ifndef SPI_MASTER_H
#define SPI_MASTER_H
#include <project.h>
#include "globals.h"
    
void SpiInit(void);
void ProcessSpiTx(uint8_t);
    
#endif