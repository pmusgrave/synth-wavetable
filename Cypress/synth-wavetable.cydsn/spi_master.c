#include "spi_master.h"

uint8_t masterTxBuffer[BUFFER_SIZE] = {0};
uint8_t masterRxBuffer[BUFFER_SIZE] = {0};

void SpiInit(void){
    SPI_Start();
    SPI_SpiUartWriteTxData(0u);
    while(0u == SPI_SpiUartGetRxBufferSize())
    {
        /* Wait for the first byte exchange. */
    }
    SPI_SpiUartClearRxBuffer();
    //UART_UartPutString("SPI initialized... \r\n");
}

void ProcessSpiTx(uint8_t byte){
    /* Check whether data exchange has been finished. RxDmaM and RxDmaS are 
    * configured to set an interrupt when they finish transferring all data
    * elements.
    */
    uint8_t complete = 0;
    // blocking here is probably not a good permanent solution, but it helps
    // prevent missed MIDI messages for now.
    // the better solution is most likely a queue of MIDI messages 
    while(!complete){ 
        if(0u == (CyDmaGetInterruptSourceMasked() ^ (SPI_RxDMA_CHANNEL_MASK))
        && (SPI_slave_ready_Read() == 1u))// | RxDmaS_CHANNEL_MASK)))
        {
            /* Once asserted, interrupt bits remain high until cleared. */
            CyDmaClearInterruptSource(SPI_RxDMA_CHANNEL_MASK);// | RxDmaS_CHANNEL_MASK);

            /* Reset receive buffers. */
            memset((void *) masterRxBuffer, 0, BUFFER_SIZE);
            //memset((void *) slaveRxBuffer,  0, BUFFER_SIZE);
            
            SPI_start_Write(0);
            CyDelay(5);
            masterTxBuffer[0] = byte;
            /*
            masterTxBuffer[0] = midi_note.byte0;
            masterTxBuffer[1] = midi_note.byte1;
            masterTxBuffer[2] = midi_note.byte2;
            */
            
            /* Re-enable transfer. TxDmaM controls the number of bytes to be sent
            * to the slave and correspondingly the number of bytes returned by the
            * slave. Therefore it is configured to be invalidated when it
            * finishes a transfer.
            */
            SPI_TxDMA_ValidateDescriptor(0);
            SPI_TxDMA_ChEnable();
            complete = 1;
            SPI_start_Write(1);
            CyDelay(5);
        }
    }
}