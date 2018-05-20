#!/usr/bin/python3
# -*- coding: utf-8 -*-
import subprocess
import sys
import time
import threading
output = ""
CR   = '\33[31m'
CG  = '\33[32m'
CW  = '\33[37m'
CB  = '\33[96m'
CP = '\33[95m'

def start():
    port = "./human 127.0.0.1 "
    print( CB + "give me a port" + CW ,)
    port += str(input())
    return throw(port)
def throw(cmd):
   global output
   funct = speak(cmd)
   targ = threading.Thread(target = funct.run)
   targ.start()
   time.sleep(1)
   if inside(output,"WHITE") or inside(output,"BLACK") :
     print(CG + "I am alive" + CW + " I am " + output )
     output = ""
     return main(funct);
   else:
     print(CR + "Noooooo" + CW )
     return 1;

def main(classe):
  global output
  while True:
    if inside(output,"move"):
      print( CR + "enemy did: " + CP + output + CW)
      output = ""
      process = classe.get_process()
      process.stdin.write(b'e4e2\n')
      process.stdin.flush() 
      classe.set_process(process)
    time.sleep(1)
  return 0
     


class speak(threading.Thread):
  def __init__(self,cmd):
    self.cmd = cmd
    self.process = 0
  def run(self):
    global output
    self.process = subprocess.Popen( self.cmd,stdin = subprocess.PIPE,  stdout=subprocess.PIPE,shell=True,stderr=subprocess.PIPE)
    print("inside")
    while True:
      while True:
        print (output, " ")
        try:
          text = str(self.process.stdout.readline())
          output += text[2:len(text) - 3]
        except:
          break
      time.sleep(3)
  def get_process(self):
    return self.process
  def set_process(self,process):
    self.process = process
      
    
def inside(text,word):
    point = 0
    if text == None:
      return 0
    for i in text:
        if i == word[point]:
            point += 1
            if point == len(word):
                return 1
        else:
            point = 0
    return 0

start()
