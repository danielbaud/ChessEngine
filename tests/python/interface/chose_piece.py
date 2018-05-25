#!/usr/bin/python3
# -*- coding: utf-8 -*-
from tkinter import *
import time

play = ""
def gen_piece():
    global ratio,rayon,fen,play_1
    play_1 = 0
    fen=Tk()
    canvas=Canvas(fen, width=700, height=400,bg="brown")
    x = 5
    ratio = 700 / x
    rayon = ratio/2
    maxi = ratio * x
    canvas=Canvas(fen, width=700, height=ratio*2,bg="brown")
    for i in range(x-1):
        canvas.create_rectangle(i*ratio +rayon + 2,rayon + 2,i*ratio+3*rayon - 2,3*rayon - 2,fill="indian red",width = 2)
        x,y = (i*ratio +rayon + i*ratio+3*rayon)/2,(3*rayon + rayon)/2
        canvas.create_text(x, y,text=['Q','N','R','B'][i], font="Stencil 30", fill="gold")
    canvas.bind("<Button-1>", reset_1)
    play_1 = loop_1()
    if play_1 == 0:
      canvas.pack()
      fen.mainloop()    
    return play_1

def loop_1():
    global play_1
    if play_1 == 0:
        fen.after(10,loop_1)
    else:
        fen.destroy()
    return play_1    


def reset_1(event):
    global play_1
    X = int((event.x - rayon)/ratio)
    play_1 = ['Q','N','R','B'][X]
    

