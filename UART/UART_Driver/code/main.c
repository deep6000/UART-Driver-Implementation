#include"main.h"


int main()
{

	func_project2();
//	Myprintf("UART");
	fibonacci();


	while(1);

#ifdef Polling
	 UART_Receive_bytes();
#endif

}
