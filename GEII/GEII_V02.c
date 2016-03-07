/*
	Pierre JOUBERT - K4A
	Programme ballon sonde v0.2

	Le SPI : Capteur de pression et CTN fonctionne, les données sont interprétées pour être converties en grandeur physique

	troisème étape : récupérer les données du DS18B20 qui se trouvent dans le dossier /sys/bus/w1/devices/28-041591dd2cff/ dans le fichier w1_slave

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
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "librairie_SPI.c"
#include "librairie_capteur_analog.c"
#include "librairie_DS18B20.c"


int main(int argc, char *argv[])
{

	int retour,var_pression,var_temperature;
	float temp,pres,tempDS18B20;

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
	printf(" \n Temperature du DS18B20: %.2f °C\n",tempDS18B20 );


}