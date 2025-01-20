// Task 1:

ISR(TIMER0_OVF_vect)
{                     // Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
    static u16 c = 0; // static local is better because we don't need this variable in main. If it is global, it must be volatile
    static u16 c2 = 0;
    static u16 c3 = 0;
    TCNT0 = 6;
    c++;
    c2++;
    c3++;

    if (c == 20)
    {
        DIO_TogglePin(PIND0);
        c = 0;
    }

    if (c2 == 40)
    {
        DIO_TogglePin(PIND1);
        c2 = 0;
    }

    if (c3 == 100)
    {
        DIO_TogglePin(PIND4);
        c3 = 0;
    }
}

ISR(TIMER0_OVF_vect)
{                     // Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
    static u16 c = 0; // static local is better because we don't need this variable in main. If it is global, it must be volatile
    TCNT0 = 6;
    c++;

    if (c % 20 == 0)
    {
        DIO_TogglePin(PIND0);
    }

    if (c % 40 == 0)
    {
        DIO_TogglePin(PIND1);
    }

    if (c % 100 == 0)
    {
        DIO_TogglePin(PIND4);
    }

    if (c == 200)
    {
        c = 0;
    }
}

// Task 2:
ISR(TIMER0_OVF_vect)
{                     // Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
    static u16 c = 0; // static local is better because we don't need this variable in main. If it is global, it must be volatile
    TCNT0 = 6;
    c++;
    // c%1
    DIO_TogglePin(PIND0);

    if (c % 2 == 0)
    {
        DIO_TogglePin(PIND1);
    }

    if (c % 5 == 0)
    {
        DIO_TogglePin(PIND4);
    }

    if (c == 10)
    {
        c = 0;
    }
}

// Task 3:

ISR(TIMER0_OVF_vect)
{                     // Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
    static u16 c = 0; // static local is better because we don't need this variable in main. If it is global, it must be volatile
    TCNT0 = 156;
    TCNT0 = 246;

    // Not applicable due to exeution time of Ton < tick time 
    TCNT0 = 255;

    DIO_TogglePin(PIND0);
}
