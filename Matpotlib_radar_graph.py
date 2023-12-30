from matplotlib import pyplot as plt 
import matplotlib
import numpy as np 
import time 
import serial 
import keyboard


matplotlib.use('TkAgg')

ser = serial.Serial('COM5', baudrate=9600, bytesize=8, 
                    parity='N', stopbits=1, timeout=2)

fig = plt.figure(facecolor='k')
fig.canvas.toolbar.pack_forget()
fig.canvas.manager.set_window_title('ultrasonic sonar')
ax = fig.add_subplot(1,1,1, polar=True)
ax.set_facecolor("black")
ax.grid(color='white', linestyle='-', linewidth=0.5)
ax.set_thetamin(10)
ax.set_thetamax(170)
ax.set_ylim(0, 80)

angles = np.arange(0,181,1)
theta = angles * (np.pi/180)

pols, = ax.plot([], linestyle='', marker='o', markerfacecolor='r', markeredgecolor='w',
                markeredgewidth=1.0, markersize=2.0,
                alpha=0.5)

line1, = ax.plot([], color='w', linewidth=3.0,)

fig.canvas.draw()
dists = np.ones((len(angles),))
fig.show()
fig.canvas.blit(ax.bbox)
fig.canvas.flush_events()
axbackground = fig.canvas.copy_from_bbox(ax.bbox)

while True:

    try:
        data = ser.readline()
        decoded = data.decode()
        data = (decoded.replace('\r','')).replace('\n','')
        if data != '':
            vals = [float(ii) for ii in data.split(',')]
            if len(vals) < 2:
                continue
            angle, dist = vals 
            dists[int(angle)] = dist
            pols.set_data(theta, dists)
            fig.canvas.restore_region(axbackground)
            ax.draw_artist(pols)
            line1.set_data(np.repeat((angle * (np.pi/180)), 2), np.linspace(0.0, 100, 2))
            ax.draw_artist(line1)
            fig.canvas.blit(ax.bbox)
            fig.canvas.flush_events()

        if keyboard.is_pressed('q'):
            print("user quit")
            break 

    except KeyboardInterrupt:
        plt.close('all')
        print('keyboard')
        break 
exit 

