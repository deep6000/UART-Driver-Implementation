#include "main.h"





	void func_project2()
{
    TX_Pointer = ring_buf_init( TX_Pointer,Tx_buffer,100 );
    RX_Pointer = ring_buf_init( RX_Pointer,Rx_buffer,100 );
    Stats_Pointer = ring_buf_init(Stats_Pointer, statistics, 200);
   UART_Configure();
	
}

void get2statistics(int8_t data)
{


	__disable_irq();

	uint8_t *ptr;
	UART0_C2 &= ~UART0_C2_TIE_MASK;
	UART0_C2 &= ~UART0_C2_RIE_MASK;

	if(data == 13)
		{
		UART_Send(new_line);
		print2statistics();
		}
	else
	{
		ptr = &Stats[data];
		(*ptr)++;
	}
}

void print2statistics()
{
	int i=0;
	int8_t *ptrdata;
	int8_t *ptralpha;

	for( i=33 ; i<128; i++)
			{
				if(Stats[i] != 0)
				{
					UART_Send(i);
					UART_Send(space);
					 if(Stats[i]>99)
					 {
						my_itoa((Stats[i]/100),ptrdata,10);
						UART_Send(*ptrdata);
						my_itoa((Stats[i]/10),ptrdata,10);
						UART_Send(*ptrdata);
						my_itoa((Stats[i]%10),ptrdata,10);
						UART_Send(*ptrdata);
						UART_Send(new_line);
						UART_Send(next_line);
					 }

					 else if(Stats[i]>9)
					{
					my_itoa((Stats[i]/10),ptrdata,10);
					UART_Send(*ptrdata);
					my_itoa((Stats[i]%10),ptrdata,10);
					UART_Send(*ptrdata);
					UART_Send(new_line);
					UART_Send(next_line);
					}
					else
					{
					my_itoa(Stats[i],ptrdata,10);
					UART_Send(*ptrdata);
					UART_Send(new_line);
					UART_Send(next_line);
					}
			}
			}
}
void fibonacci()
{
int n= 7 , first = 0, second = 1, next, c;
 uint8_t *ptrnext;

  for (c = 1; c < n; c++)
  {
    if (c <= 1)
      next = c;
    else
    {
      next = first + second;
      first = second;
      second = next;
    }
   //ptrnext= my_itoa(3,ptrnext,10);
    //UART_Send(*ptrnext);
    if(next>10)
    {
    	int tens = next %10;
    	int units= next/10;
    	tens= (uint8_t)tens+48;
    	units= (uint8_t)units+48;
    	UART_Send(tens);
    	UART_Send(units);
    }
    else
    {
	next = (uint8_t)next +'0';
	UART_Send(next);

    }
   UART_Send(new_line);
   UART_Send(next_line);
  }
}
void swap(char *x, char *y)
{
	char t = *x; *x = *y; *y = t;
}

// function to reverse buffer[i..j]
char* reverse(char *buffer, int i, int j)
{
	while (i < j)
		swap(&buffer[i++], &buffer[j--]);

	return buffer;
}

// Iterative function to implement itoa() function in C
char* my_itoa(int value, char* buffer, int base)
{
	// invalid input
	if (base < 2 || base > 32)
		return buffer;

	// consider absolute value of number
	int n = abs(value);

	int i = 0;
	while (n)
	{
		int r = n % base;

		if (r >= 10)
			buffer[i++] = 65 + (r - 10);
		else
			buffer[i++] = 48 + r;

		n = n / base;
	}

	// if number is 0
	if (i == 0)
		buffer[i++] = 48;

	// If base is 10 and value is negative, the resulting string
	// is preceded with a minus sign (-)
	// With any other base, value is always considered unsigned
	if (value < 0 && base == 10)
		buffer[i++] = '-';

	buffer[i] = '\0'; // null terminate string

	// reverse the string and return it
	return reverse(buffer, 0, i - 1);
}
/*
void Myprintf(char* format,...)
{
	__disable_irq();
	char *traverse;
	unsigned int i;
	char *s;
	uint8_t *ptrdata;
	uint8_t data;

	//Module 1: Initializing Myprintf's arguments
	va_list arg;
	va_start(arg, format);
	int j = 0;

	while(format && format[j])
		{

			data= format[j];
			UART_Send(data);
			j++;

			if(format[i]== 37)
			{
		//Module 2: Fetching and executing arguments
				switch(format[i])
				{
				case 'c' : i = va_arg(arg,int);		//Fetch char argument
						UART_Send(i);
						break;

				case 'd' : i = va_arg(arg,int); 		//Fetch Decimal/Integer argument
						if(i<0)
						{
							i = -i;
							UART_Send('-');
						}
						if(i>0 && i<9)
						{
						my_itoa(i,ptrdata,10);
						UART_Send(ptrdata);
						}
						if(Stats[i]>9)
											{
											my_itoa((Stats[i]/10),ptrdata,10);
											UART_Send(*ptrdata);
											my_itoa((Stats[i]%10),ptrdata,10);
											UART_Send(*ptrdata);
											}
						break;

				case 's': s = va_arg(arg,char *); 		//Fetch string
						puts(s);
						break;

				case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
						puts(convert(i,16));
						break;

				}
				j++;
			}
		}
	va_end(arg);

}

*/
