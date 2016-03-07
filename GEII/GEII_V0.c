/*
	Pierre JOUBERT - K4A
	Programme ballon sonde v0.0

	première étape : faire fonctionner le SPI : Capteur de pression et CTN

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
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "librairie_SPI.c"



int main(int argc, char *argv[])
{

	int retour,var_pression,var_temperature;

	retour = PressionCTN(argc,argv);
	var_temperature = retour/1000;
	var_pression = retour%(var_temperature*1000);
	printf(" Pression : %d\n Temperature : %d\n",var_pression,var_temperature );
}
