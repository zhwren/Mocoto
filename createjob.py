#!/usr/bin/python

import random

status = '/det/flatpanel 0\n/det/tubdetector 0\n'
status += '/det/detector/Number 21\n/det/collimator/Number 21\n\n'
status += '/det/Apron/Copper/thickness 0 mm\n'
status += '/det/Apron/Wolfram/thickness 0 mm\n'
status += '/det/Apron/Aluminum/thickness 0 mm\n\n'
status += '/gen/particle gamma\n/gen/particle/momentumDirection 0 90 0 deg\n'
status += '/gen/particle/deltaThetaPhi 0 0 40 deg\n'
status += '/gen/particle/position -24 0 0 cm\n\n'
status += '/det/target/diameter 20 cm\n'

for i in range(10):
    angle = str(-1*i*0.36)
    personal = status + '/det/target/rotateAngle ' + angle + ' deg\n'
    personal += '/det/target/position 0 0 0 mm\n\n'
    personal += ('/histo/fileName targetRotate_' + str(i) + '.root\n')
    personal += '/run/initialize\n/run/beamOn 5000000'
    filename = 'targetRotate_' + str(i)
    open(filename + '.mac','w').write(personal)
    bashcommand = 'source ~/.bashrc.geant4\n'
    bashcommand += ('Mocoto ' + filename + '.mac $RANDOM > log' + str(i))
    open(filename + '.sh', 'w').write(bashcommand)
