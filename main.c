#include <stdlib.h>
#include <stdio.h>

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

int recupDATASHT15(void)
{
	int dataSHT;


	return dataSHT;
}

int recupGPS(void) // Serie 
{
	int coordGPS;

	return coordGPS
}



int main(int argc, char *argv[])
{
	char totalMesures[30];
	int tempBallon, DataCAN, coordGPS;
	FILE* fichier = NULL;
	fichier = fopen("mesures.csv","a");

	fprintf(totalMesures, "%f, %f, %f,  \n",TBallon );
	fputs(totalMesures,fichier);
	fclose(fichier);
	return 0;
}
