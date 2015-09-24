#include <stdlib.h>
#include <stdio.h>

#include "RPi_SHT1x.c"

#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>
#include <wiringPiSPI.h>

int recupTempBallon(void) //1wire
{
	int tempBallon;

	//protocole 1wire

	return tempBallon
}

int recupDataCAN(void) //pression et température en I2C
{
	int DataCAN;
	int I2CCorrect = wiringPiI2CSetup();
	if(I2CCorrect!=-1)
	{
		//l'I2C est bien ouvert
		DataCAN=wiringPiI2CRead(); // on lit les données I2C
	}else
	{
		return -200;
	}


	return DataCAN
}

float recupTempHumiCarteSHT(void)
{
	char dataSHTc[12];
	const float C1=-4.0;              		// for 12 Bit
	const float C2=+0.0405;           		// for 12 Bit
	const float C3=-0.0000028;        		// for 12 Bit
	const float T1=+0.01;             		// for 14 Bit @ 5V
	const float T2=+0.00008;           		// for 14 Bit @ 5V	

	float rh_lin;                     		// rh_lin:  Humidity linear
	float rh_true;                    		// rh_true: Temperature compensated humidity
	float t_C;                        		// t_C   :  Temperature [C]

	int temp;
	float temperature;
		SHT1x_Measure_Start( SHT1xMeat ); //On demande la température  :                        SHT1xMeaT	= SHT1x_MEAS_T,		// Temperature
		temp = SHT1x_Get_Measure_Value();
		float t = (float)temp;

	int humi;
	float humidite;
		SHT1x_Measure_Start( SHT1xMeaRh ); //On demande l'humidité  :                        SHT1xMeaRh	= SHT1x_MEAS_H,		// Humidity
		humi = SHT1x_Get_Measure_Value();
		float rh = (float)humi;

	t_C = t*0.01 - 40;                  	// calc. temperature from ticks to [C]
	rh_lin = C3*rh*rh + C2*rh + C1;     	// calc. humidity from ticks to [%RH]
	rh_true = (t_C-25)*(T1+T2*rh)+rh_lin;   // calc. temperature compensated humidity [%RH]

	if(rh_true>100)	rh_true=100;       		// cut if the value is outside of
	if(rh_true<0.1)	rh_true=0.1;       		// the physical possible range

	sprintf(dataSHTc,"%.2f%.2f",t_C,rh_true);
	dataSHT=atoi(dataSHTc);
	return dataSHT;
}



int recupGPS(void) // Serie 
{
	int coordGPS;

	return coordGPS
}



int main(int argc, char *argv[])
{
	SHT1x_InitPins(); //fonction d'initialisation du SHT15
	SHT1x_Reset(); //on soft-reboot le SHT15

	char totalMesures[30];
	int tempBallon, DataCAN, coordGPS;
	FILE* fichier = NULL;
	fichier = fopen("mesures.csv","a");

	fprintf(totalMesures, "%f, %f, %f,  \n",TBallon );
	fputs(totalMesures,fichier);
	fclose(fichier);
	return 0;
}
