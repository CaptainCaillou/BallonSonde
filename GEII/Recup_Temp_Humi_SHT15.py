#!/usr/bin/env python
import os
import time
import subprocess
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
#On definie le port 18 comme port d'activation de la prise des photos / Mesures

from os import chdir
from sht1x.Sht1x import Sht1x as SHT1x
dataPin = 3
clkPin = 5
sht1x = SHT1x(dataPin, clkPin, SHT1x.GPIO_BOARD)
#On selectionne le dossier
chdir("/home/pi/GEII/")
#On cree le nom du dossier de sauvegarde avec le jour
nomDossier = "/home/pi/GEII/"+time.strftime('%d_%m_%y',time.localtime())
if os.path.exists(nomDossier):
	print "Remplissage du dossier existant !"
else :
	os.mkdir(nomDossier,0777)
chdir(nomDossier)
#Liste des modes d'expositions disponibles : 
#list_ex =
#['off','auto','night','nightpreview','backlight',
#            'spotlight','sports','snow','beach','verylong', 'fixedfps','antishake','fireworks'] 
#Liste des modes de balance des blancs disponibles :
#list_awb = ['off','auto','sun','cloud','shade','tungsten',
#            'fluorescent','incandescent','flash','horizon']
# Dimensions de la photo
photo_width = 1920
photo_height = 1080

photo_counter=0
front=0
while 1:
	temperature = sht1x.read_temperature_C()
	humidity = sht1x.read_humidity()

	print("Temperature: {} Humidite: {} ".format(temperature, humidity))


	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(13, GPIO.IN)
	if GPIO.input(13):
	        if (front==0):
	        #Debut de la capture
	        	try:
					chdir(nomDossier)
					print "Debut de la capture"
					photo_counter = photo_counter + 1
		            #titre de la photo
					filename = 'photo_'+time.strftime('%d_%m_%y_%H_%M_%S',time.localtime())+'_'+str(photo_counter) + '_' + '.jpg'
					cmd = 'raspistill -t 500 -o ' + filename + ' -w ' + str(photo_width) +' -h ' + str(photo_height) 
					pid = subprocess.call(cmd, shell=True)
					print "Fin de la capture"
					chdir("/home/pi/GEII/")
					fichier = open("SHT15_Temp", "w")
					fichier.write("{}                                                                                         ".format(temperature))
					fichier.close()

					fichier = open("SHT15_Humi", "w")
					fichier.write("{}                                                                                         ".format(humidity))
					fichier.close()

					front = 1
		        except KeyboardInterrupt:
		            print "\n Fin du programme"
	else:
	    front=0;
        
