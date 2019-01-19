
#include "main.h"

/*************************************************************
Global Variables
**************************************************************/


/*************************************************************/
UART_Status UART_Configure()
{
	SystemInit();
	__disable_irq();
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;		//Clock gate enable for PORTA
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;		//Clock gate enable for UART0

	// Select Clock source
 	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL(0);
    SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);  	//MCGFLLCLK as UART0

    // set TX pin and RX pin
	PORTA_PCR1 |= PORT_PCR_MUX(2); 			//ALT2 mode for UART0_Rx
	PORTA_PCR2 |= PORT_PCR_MUX(2);			//ALT2 mode for UART0_Tx

	//disable transmitter before configure
	UART0_C2 &= ~(UART0_C2_TE_MASK|UART0_C2_RE_MASK);

    UART0_BDH |= UART_BDH_SBNS(0);			// 1 STOP bit
	UART0_C1  |= UART_C1_M(0);				// 8 BIT mode
	UART0_C1  |= UART_C1_PE(0);				// NO PARITY

	UART0_BDH &= 0x00;
	UART0_BDL |= 0x17; 

/*

	// Set Baud Rate
    uint16_t baud_value = (System_clock/((OSR+1)*Baud_rate));

	UART0_C4=UART0_C4_OSR(0x0F);
	UART0_BDH= ((baud_value>>8)& UART0_BDH_SBR_MASK);
	UART0_BDL=(baud_value & UART0_BDL_SBR_MASK);
*/

	//enable transmitter and receiver
	UART0_C2 |= UART0_C2_TE_MASK ;
	UART0_C2 |= UART0_C2_RE_MASK ;
	#ifdef IRQ
	UART0_C2 |= UART0_C2_RIE_MASK;	//Peripheral interrupt enable (RX)
	__enable_irq();
	NVIC_EnableIRQ(UART0_IRQn); 			//Enable at NVIC

  //  UART0_C2 |= UART)_C2_TIE_MASK;

#endif


}

UART_Status UART_Send(uint8_t data)
{
    UART_Status status;
    if(data != NULL)
    {
		while(!(UART0_S1 & UART0_S1_TDRE_MASK));
        UART0_D = data;
        status = Success;
    }
    else if (data == NULL)
    {
        status = Null_pointer;
    }
    else
    {
        status = Unknown_error;
    }
    return status;
}

UART_Status UART_Send_bytes(uint8_t* data, uint8_t length)
{
    UART_Status status;
    if(data != NULL)
    {
        for(uint8_t i=0;i< length; i++)
        {
            while(!(UART0_S1 & UART0_S1_TDRE_MASK));
            UART0_D = *(data+i);
            ring_buf_remove(TX_Pointer, &data );

        }
        status= Success;
    }
    else if(data = NULL)
        status= Null_pointer;

    else if (length == 0)
        status = Invalid_length;

    else
        status = Unknown_error;
	return status;
}

char UART_Receive (uint8_t  data)
{

	uint8_t  val = UART0_D;
    return val;
}


UART_Status UART_Receive_bytes()
{
	int size;
	uint8_t data;
	int j=0;
   UART_Status status;


    		while(!(UART0_S1 & UART0_S1_RDRF_MASK));

    		data=UART0_D;
    		UART_Send(data);
    		if (data == 13)
    		   {

    			size=ring_buf_entries(Stats_Pointer);
    		    	for(int i= 0; i<size;i++)
    		    	 {

    		    		TDATA = ring_buf_remove(Stats_Pointer,&TD_ptr);
    		    		 get2statistics(TDATA);
    		    	 }
    		    	UART_Send(new_line);
    		    	UART_Send(next_line);
    		    	print2statistics();

    		   }

    		else if(!(ring_buf_full(Stats_Pointer)))
    		{

    			ring_buf_insert( Stats_Pointer , &data);
    		}

    		else if((ring_buf_full(Stats_Pointer)))
    		{
    		size=ring_buf_capacity(Stats_Pointer);
    		ring_buf_reinit( Stats_Pointer ,statistics, (size+1));
    		ring_buf_insert( Stats_Pointer , data);
    		}



}


#ifdef IRQ
void UART0_IRQHandler(void)
{
	__disable_irq();

if ((UART0_C2 & UART0_C2_TIE_MASK) == UART0_C2_TIE_MASK)
    {
		TDATA = ring_buf_remove(RX_Pointer,&TD_ptr);
		//UART_Send(TDATA);
		get2statistics(RDATA);
		UART0_C2 &= ~ UART0_C2_TIE_MASK;
		UART0_C2 |= UART0_C2_RIE_MASK;
    }
 else if((UART0_C2 & UART0_C2_RIE_MASK) == UART0_C2_RIE_MASK)
    {
    	if(!(ring_buf_full(RX_Pointer)))
    	{
    		RDATA= UART0_D;
    		if(RDATA != 0)
    		{
    		UART_Send(RDATA);
    		}
    		ring_buf_insert(RX_Pointer, &RDATA);
    		//ring_buf_insert(TX_Pointer, &TDATA);
    		UART0_C2 &=~ UART0_C2_RIE_MASK;
    		UART0_C2 |= UART0_C2_TIE_MASK;
    	}

    }
	__enable_irq();
}
#endif
