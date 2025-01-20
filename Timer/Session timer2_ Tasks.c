
static volatile u8 flag2 , c;

int main(void)
{
	DIO_init();
	LCD_Init();
	KEYPAD_init();
	ADC_init(VREF_VCC , ADC_SCALER_64);
	//EXI_init();
	
	u8 x= 0 , c2 = 0;
	u32 t1 = 0,t2 = 0 , time = 0;
	
	

	//EXI_TriggerEdge(EX_INT0 , FALLING_EDGE);
	//EXI_TriggerEdge(EX_INT1 , RISING_EDGE);

	//EXI_Enable(EX_INT0);
	//EXI_Enable(EX_INT1);

	//EXI_SetCallBack(EX_INT0 , f1);
	GLOBAL_ENABLE();

	// Enable OV flow interrupt
	//TCNT0 = 6;
	TCCR0 = 2; // lOOK At Data sheet
	SET_BIT(TCCR0 , WGM01);
	SET_BIT(TCCR0 , COM00);
	// Timer is normal mode at 8 Prescaler
	TIMSK = 1; //Enable Interrupt overflow
	SET_BIT(TIMSK , 0);
	SET_BIT(TIMSK , OCIE0);
	
	OCR0 = 10; // Once Timer reach 10 it will send an Interrupt

	TCNT0 = 0;
	c = 0;
	t1= TCNT0;
	x = ADC_ReadVolt(CH_0);  //  216 us
	//_delay_us(300);
	t2 = TCNT0;
	c2 = c;
	time = (t2 - t1) + c*256;
	LCD_SetCursor(2,1);
	LCD_WriteNumber(t2);
	LCD_SetCursor(2,10);
	LCD_WriteNumber(c2);
	LCD_SetCursor(1,1);
	LCD_WriteStr((u8*)"TIMER Test  ");

	while (1)
	{
		// Code here
		LCD_SetCursor(1,13);
		LCD_WriteNumber(x);
		x++;
		if (x == 10)
		{
			x = 0;
		}
		_delay_ms(500);
	}
	return 0;
}


/*ISR(TIMER0_OVF_vect)
{	// Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
	static u16 c = 0; // static local is better because we don't need this variable in main. If it is global, it must be volatile
	TCNT0 = 255;
	
	DIO_TogglePin(PIND0);

}

*/

ISR(TIMER0_OVF_vect)
{	
	c++;
}


// Task 3:
ISR(TIMER0_OC_vect)
{
	DIO_TogglePin(PIND0);
	OCR0 = OCR0 + 9; 
}

