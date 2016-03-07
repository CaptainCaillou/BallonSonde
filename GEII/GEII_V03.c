/*
	Pierre JOUBERT - K4A
	Programme ballon sonde v0.2

	Le SPI : Capteur de pression et CTN fonctionne, les données sont interprétées pour être converties en grandeur physique
	Le DS18B20 fonctionne : les données de température du ballon sont récupérées
	
	troisème étape : récupérer du GPS qui se trouvent dans le fichier /dev/ttyAMA0

*/

/* DROITS D'AUTEUR CONCERNANT LE SPI
 * 
 * SPI testing utility (using spidev driver)
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <wiringPi.h>

#include "librairie_SPI.c"
#include "librairie_capteur_analog.c"
#include "librairie_DS18B20.c"
 

int main(int argc, char *argv[])
{

	int retour,var_pression,var_temperature;
	float temp,pres,tempDS18B20;
	char heure[6],minute[2],seconde[2],latitude[2],latitude_seconde_char[7],longitude[3],longitude_seconde_char[7],indicateur_latitude[2],indicateur_longitude[2],altitude[6];
	char positionGPGGA,latitude_degre,latitude_seconde;
	char buff[2048];
	char trammeGPGGA[100];

	float calc_coord;

	char * Position [30]={0};
	char *result;
	char test;
	char front=1;

	wiringPiSetup () ;

	while (1)
	{

		if (digitalRead(2))
		{
			if(front)
			{
				front=0;
				//on intéroge le CAN pour récupérer les informations de la CTN et du capteur de pression
				retour = PressionCTN(argc,argv);

				//on converti l'entier reçu de la fonction de réception (C'était mieux que de passer par un pointeur, je trouve !)
				
				var_temperature = retour/1000;
				var_pression = retour%(var_temperature*1000);
				//printf(" Pression : %d\n Temperature : %d\n",var_pression,var_temperature );

				//on converti les valeurs de pression et de température en grandeurs physiques
				temp=conversionCTN(var_temperature);
				pres=conversionMPX(var_pression);

				//Affichage des valeurs de pression et de température
				printf("\n Pression : %f kPa \n Temperature de la CTN: %.2f °C\n",pres,temp );

				//Récupération des données du DS18B20
				tempDS18B20=temperature_DS18B20();

				//Affichage des données du DS18B20
				printf(" \n Temperature du DS18B20: %.2f °C\n",tempDS18B20 );



				//Récupération des données du GPS
			 	
				char * pEnd;

				FILE* fd = NULL;
			    char gps[2048];
			    memset(gps,0,sizeof(gps));

			    fd = fopen("/dev/ttyAMA0","r");

			    if(NULL == fd)
			    {
			        printf("\n fopen() Error!!!\n");
			        return 1;
			    }

			    if(SIZE*NUMELEM != fread(gps,8,NUMELEM,fd))
			    {
			        printf("\n fread() failed\n");
			        return 1;
			    }

			    fclose(fd);

			    strcpy(buff,gps);
			    
			    result = strstr(buff,"$GPGGA,");
				int position = result - buff;


			    memcpy( trammeGPGGA, &buff[position], 71 );
				trammeGPGGA[71] = '\0';

				//printf("Tramme gardée : %s\n",trammeGPGGA );

			    memcpy( heure, &trammeGPGGA[7], 2 );
				heure[2] = '\0';
				memcpy( minute, &trammeGPGGA[9], 2 );
				minute[2] = '\0';
				memcpy( seconde, &trammeGPGGA[11], 2 );
				seconde[2] = '\0';
				
				printf("\n Heure : %s h %s m %s s\n",heure,minute,seconde );

				memcpy( latitude, &trammeGPGGA[18], 2 );
				latitude[2] = '\0';

				memcpy( latitude_seconde_char, &trammeGPGGA[20], 7 );
				latitude_seconde_char[7] = '\0';

				memcpy( indicateur_latitude, &trammeGPGGA[28], 7 );
				indicateur_latitude[1]= '\0';
				

				for (int i = 2; i < 7; i++)
				{
					latitude_seconde_char[i]=latitude_seconde_char[i+1];
				}

				printf(" Latitude  : %s,%s° %s\n",latitude,latitude_seconde_char,indicateur_latitude );



				memcpy( longitude, &trammeGPGGA[30], 3 );
				longitude[3] = '\0';

				memcpy( longitude_seconde_char, &trammeGPGGA[33], 7 );
				longitude_seconde_char[7] = '\0';


				memcpy( indicateur_longitude, &trammeGPGGA[41], 7 );
				indicateur_longitude[1]= '\0';

				for (int i = 2; i < 7; i++)
				{
					longitude_seconde_char[i]=longitude_seconde_char[i+1];
				}

				printf(" Longitude : %s,%s° %s\n",longitude,longitude_seconde_char,indicateur_longitude );
			
				memcpy( altitude, &trammeGPGGA[52], 5 );
				altitude[5] = '\0';

				printf(" Altitude : %s m\n",altitude );
			

			}
		}
		else
		{
			front=1;
		}
	}
    return 0;
}