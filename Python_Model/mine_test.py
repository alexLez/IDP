'''
Created on 10 Nov 2018

@author: alexa
'''
from IDP.gameObjects import mine
import numpy as np
import random

minelist = [mine(1,2,1),mine(1,3,1),mine(1,4,1)]
print ([mine.xpos for mine in minelist])
minelist[1].xpos = 2

print ([mine.xpos for mine in minelist])

