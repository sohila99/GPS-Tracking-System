
void GPS_INIT(void)
{
SYSCTL_RCGCUART_R |= 0x04;
SYSCTL_RCGCGPIO_R |= 0x04;
GPIO_PORTC_AFSEL_R |= 0x30;
GPIO_PORTC_PCTL_R &= 0xFF00FFFF;
GPIO_PORTC_PCTL_R |= 0x00220000;
}
