from SimpleCV import *
import time
import sys

#opens file with name of "frame_times.txt"
f = open("frame_times.txt","r") 

#first line of file is number of frames
framecount = int(f.readline())

#stream of data that will be converted to avi video file
vs = VideoStream("out.avi")

#incrementer
x = 1

#loop concatenates frames with specific times to generate video file
while x <= framecount:
    Image("../images/image_"+str(x)+".png").save(vs)
    time.sleep(float(f.readline()))
    x+= 1
