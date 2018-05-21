#!/usr/bin/python3
# -*- coding: utf-8 -*-
from tkinter import *
fen=Tk()
fen.focus()
canvas=Canvas(fen, width=700, height=700,bg="white")

def gen_map():
    
    x = 9
    ratio = 700 / x
    rayon = ratio/2
    maxi = ratio * x
    for i in range(x):
        total = i * ratio
        canvas.create_line(total+rayon,maxi-rayon,total+rayon,0+rayon,fill="black",width = 2)
        canvas.create_line(maxi-rayon,total+rayon,0+rayon,total+rayon,fill="black",width = 2) 
    for i in range(8):
        for j in range(8):
            if (i+j)%2:
                canvas.create_rectangle(i*ratio +rayon,j*ratio+rayon,i*ratio+3*rayon,j*ratio+3*rayon,fill="black",width = 2)

gen_map()  
canvas.pack()
fen.mainloop() 
