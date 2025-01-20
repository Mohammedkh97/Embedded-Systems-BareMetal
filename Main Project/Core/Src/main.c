
#include "MainApp.h"
//#include "Al-Ahram.h"

int main(void)
{
//	Al_Ahram_setup();
	SysInit();
	while (1)
	{
//		Al_Ahram_Runnable();
		System_Runnable();
	}
}

