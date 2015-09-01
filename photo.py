#!/usr/bin/env python
import os
import time
import subprocess
import RPi.GPIO as GPIO
#On définie le port 18 comme port d'activation de la prise des photos / Mesures
GPIO.setup(18, GPIO.IN)
from os import chdir
#On sélectionne le dossier
chdir("/home/pi/")
#On crée le nom du dossier de sauvegarde avec le jour
nomDossier = time.strftime('%d/%m/%y',time.localtime())
os.mkdir(nomDossier, mode=0777)
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
if GPIO.input(18)
        if (front=0)
        #Debut de la capture
        try:
            print "Debut de la capture"
            photo_counter = photo_counter + 1
            #titre de la photo
            filename = 'photo_' + photo_counter + '_' + '.jpg'
            cmd = 'raspistill -o ' + filename + ' -awb off' + ' -w ' + str(photo_width) +' -h ' + str(photo_height)
            pid = subprocess.call(cmd, shell=True)
            print "Fin de la capture"
            front = 1;
                
        except KeyboardInterrupt:
            print "\n Fin du programme"
    else
        front=0;
