import serial                                 
import math
import numpy 
import matplotlib.pyplot as plt 
from matplotlib.animation import FuncAnimation 
from drawnow import * 
import time


AngleF = [] 
DistanceF = []

arduinoData = serial.Serial('com3', 9600)

fig = plt.figure()
ax = fig.add_subplot(projection='polar')
ax.set_facecolor("black")
ax.grid(color='green', linestyle='-', linewidth=1)
ax.set_thetamin(20)
ax.set_thetamax(160 )

def makeFig():
    ax.scatter(AngleF, DistanceF, color='red')

def getData():
    preData = arduinoData.readline()
    arduinoString = preData.decode('ascii')
    dataArray = arduinoString.split(' , ')
    return dataArray



while True:
    while (arduinoData.inWaiting()==0):
        pass
    angle = float(getData()[0])
    distance = float(getData()[1])
    AngleF.append(math.radians(angle))
    DistanceF.append(distance)
    makeFig()
    plt.pause(0)




