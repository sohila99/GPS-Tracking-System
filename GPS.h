
void GPS_Init(void)
{
	SYSCTL_RCGCUART_R |= 0x04;
	SYSCTL_RCGCGPIO_R |= 0x04;

	UART1_CTL_R &= ~0x00000001;
	UART1_IBRD_R = 104;
	UART1_FBRD_R = 11;
	UART1_LCRH_R = 0x70;
	UART1_CTL_R = 0x301;

	GPIO_PORTC_AFSEL_R |= 0x30;
	GPIO_PORTC_PCTL_R &= ~0xFF00FFFF;
	GPIO_PORTC_PCTL_R |= 0x00220000;
	GPIO_PORTC_DEN_R |= 0x30;
}

unsigned char GPS_Data_Available(void)
{
	return ((UART1_FR_R & 0x00000010) == 0x00000010) ? 0 : 1; // check if there is data to read at the Receiver
}

char GPS_Data(void) // collects data from the Receiver and puts it in a string
{
	int i=0; // index of array data
	int count=0; // counts number of NMEA sentences
	int end = 1; // ends the loop for all NMEA sentences for one data
	char* str[500];
	while (end) // takes the data of all NMEA sentences for one data
	{
		while ( str[i] != 0x0A) // until line return, takes the data for one NMEA sentence
		{
			while (GPS_Data_Available() != 1);
			str[i] = ( UART1_DR_R & 0xFF );
			i++;
			count++;
		}
		char* ID = strtok(str,",");
		if ( strcmp(ID, "$GPGLL")==0 )
		{
			end = 0;
		}
		i = 0;
	}
	return (str);
}

double Receive_GPS_Data(char* str)
{
	char* ID = strtok(str,",");
 	char* Current_Lat = strtok(NULL,",");
 	char* N_S = strtok(NULL,",");
 	char* Current_Lon = strtok(NULL,",");
	char* E_W = strtok(NULL,",");
	char* Checksum = strtok(NULL,",");

	if ( strcmp(ID, "$GPGLL")==0 )
	{
		Latitude = atof(Current_Lat);
		Longitude = atof(Current_Lon);
		int x = floor(Latitude/100);
		double y = (Latitude - x*100)/60;
		Latitude = x+ y;
		if (strcmp(N_S, "S")==0){
		Latitude =-1*Latitude;}
		y = floor(Longitude/100);
		y = (Longitude - x*100)/60;
		Longitude = x+ y;
		if (strcmp(E_W, "W")==0){
		Longitude =-1*Longitude;}
		double lat_lon = {Latitude, Longitude};
		end = 0;
	}
	}
	return(lat_lon);
}
