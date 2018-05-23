#!/usr/bin/python3
# -*- coding: utf-8 -*-
from tkinter import *
"""fen=Tk()
fen.focus()
canvas=Canvas(fen, width=700, height=700,bg="brown")"""

def gen_map(chess):
    fen=Tk()
    fen.focus()
    canvas=Canvas(fen, width=700, height=700,bg="brown")
    x = 9
    ratio = 700 / x
    rayon = ratio/2
    maxi = ratio * x
    for i in range(x):
        total = i * ratio
        canvas.create_line(total+rayon,maxi-rayon,total+rayon,0+rayon,fill="gold",width = 2)
        canvas.create_line(maxi-rayon,total+rayon,0+rayon,total+rayon,fill="gold",width = 2) 
    for i in range(8):
        for j in range(8):
            if (i+j)%2:
                canvas.create_rectangle(i*ratio +rayon + 2,j*ratio+rayon + 2,i*ratio+3*rayon - 2,j*ratio+3*rayon - 2,fill="peru",width = 2)
            else:
                canvas.create_rectangle(i*ratio +rayon + 2,j*ratio+rayon + 2,i*ratio+3*rayon - 2,j*ratio+3*rayon - 2,fill="indian red",width = 2)
    for piece in chess:
        j = piece[1]
        i = piece[2]
        color = piece[3]
        text = piece[0]
        canvas.create_oval(i*ratio +rayon + 5 ,j*ratio+rayon + 5,i*ratio+3*rayon - 5,j*ratio+3*rayon - 5,fill=color,width = 3,outline = "bisque2")
        x,y = (i*ratio +rayon + i*ratio+3*rayon)/2,(j*ratio+3*rayon + j*ratio+rayon)/2
        canvas.create_text(x, y,text=text, font="Stencil 30", fill="gold")      
    canvas.pack()
    fen.mainloop()

        
def updated(text):
    chess = primaris()
    act = decompose(text)
    pos = 0
    for i in act:
        act[pos][1],act[pos][2] = act[pos][2],act[pos][1]
        act[pos][3],act[pos][4] = act[pos][4],act[pos][3]
        pos += 1
    for move in act:
        pos = 0
        sto = -1 
        position = 0
        for piece in chess:
            if piece[0:3] == move[0:3]:
                chess[pos][1] = move[3]
                chess[pos][2] = move[4]
                position = [chess[pos][1],chess[pos][2]]
                sto = pos
            pos +=1 
        pos = 0
        if position:
            for piece in chess: 
                if piece[1:3] == position:
                    if sto != pos:

                        chess.pop(pos)

                pos +=1   
    #print ( chess )
    return chess

def decompose(text):
    lst = []
    move = []
    captor = 0
    
    for i in text:
        if i == ' ':
            move = []
            captor = 0
            
        if ord('A') <= ord(i) <= ord('Z'):
            captor = 1
            move.append(i)
        if ord('a') <= ord(i) <= ord('z'):
            if captor == 0:
                captor = 2
                move.append('P')
                move.append(i) 
            elif captor == 1 or captor == 3:
                captor += 1
                move.append(i)
            else:
                move = []
                captor = 0
                
        try:
            if  ord('0') < ord(i) <= ord('9'):
                
                if captor == 2 or captor == 4:
                    move.append(int(i)) 
                    captor += 1
                    if captor == 5:
                        lst.append(move)
                        move = []
                        captor = 0
                else: 
                    move = []
                    captor = 0
        except:
            pass  
    y = 0
    for move in lst:
        x = 0
        for i in move:
            try:
                lst[y][x] = ['a','b','c','d','e','f','g','h'].index(i)
            except:
                pass
            try:
                lst[y][x] = i - 1
            except:
                pass
            x += 1
        y += 1
            
    return lst
        
def primaris():
    blanc = ['R','N','B','Q','K','B','N','R']
    noir = ['R','N','B','K','Q','B','N','R']
    color = 'white'
    table = []
    for i in [0,1,6,7]:
        if i > 2:
            color = 'black'
        for j in range(8):
            if i == 1 or i == 6:
                table.append(['P',i,j,color])
            else:
                if i == 0:
                    table.append([blanc[j],i,j,color])
                else:
                    table.append([noir[i],i,j,color])
    return table

#gen_map(updated('Ra1a4'))  
#canvas.pack()
#fen.mainloop() 
