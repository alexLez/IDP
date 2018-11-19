'''
Created on 6 Nov 2018

@author: alexa
'''

import numpy as np
import arcade
import random

class arena:
    
    "creates arena object with info of the zone driven in"
   
    def __init__(self, height, width, safe_zone_offset):
        
        self.height = height
        self.width = width
        self.safe_zone_offset = safe_zone_offset
        
    def edge_outline(self):
        """ returns list of points around edge of arena, useful for detecting edge collision
        right now only works properly if arena is square
        """
        hnum = int (self.height/4)
        a=np.zeros(hnum+1)
        b=np.linspace(0, self.height, hnum+1)
        d = np.ones(hnum+1) * self.height
        pointsa = list(zip(a,b)) #x=0 y 0-height
        pointsb = list(zip(b,d)) #x0-width y=height
        pointsc = list(zip(d,b)) #x=width y0-height
        pointsd = list(zip(b,a)) #x0width y=0
        return pointsa + pointsb + pointsc + pointsd
    
    def safe_outline(self):
        "returns list of points that make up the outline of the safe zone, useful for depositing swept mines"
        """hnum = int (self.height/4)
        a=np.ones(hnum+1)* self.safe_zone_offset
        b=np.linspace(self.safe_zone_offset, self.height-self.safe_zone_offset, hnum+1)
        d = np.ones(hnum+1) * (self.height-self.safe_zone_offset)
        pointsa = list(zip(a,b)) #x=0 y 0-height
        pointsb = list(zip(b,d)) #x0-width y=height
        pointsc = list(zip(d,b)) #x=width y0-height
        pointsd = list(zip(b,a)) #x0width y=0
        return pointsa + pointsb + pointsc + pointsd"""
        return [[self.safe_zone_offset,self.safe_zone_offset],[self.width-self.safe_zone_offset, self.safe_zone_offset],[self.width-self.safe_zone_offset, self.height-self.safe_zone_offset], [self.safe_zone_offset, self.height-self.safe_zone_offset]]

    def draw_safezone(self):
        arcade.draw_rectangle_outline(self.width/2, self.height/2, self.width-2*self.safe_zone_offset, self.height-2*self.safe_zone_offset, color=arcade.color.WHITE, border_width=3, tilt_angle=0)
        
    def draw_starting_area(self, carheight, carwidth):
        arcade.draw_rectangle_outline(self.safe_zone_offset, self.safe_zone_offset, carheight, carwidth, color=arcade.color.WHITE, border_width=1)
    
class mine(arena):
    
    "creates mine object"
    
    def __init__(self, xpos, ypos, radius, dangerous=False):
        
        self.xpos = xpos
        self.ypos = ypos
        self.dangerous = dangerous
        self.radius = radius
        self.arena = arena
        self.beingmoved = False
        
    def hitbox(self, x, y):
                
        N=30
        point_list = []
        r = self.radius
        for n in range (N):
            point_list.append([r * np.cos(2*np.pi*n/N) + x , r * np.sin(2*np.pi*n/N) + y])
            
        return point_list
        
    def draw(self):
        
        pospoints = mine.hitbox(self, x=self.xpos, y=self.ypos)
        
        if self.dangerous:
            arcade.draw_polygon_filled(pospoints, arcade.color.ALIZARIN_CRIMSON)
            
        else:
            arcade.draw_polygon_filled(pospoints, arcade.color.BANANA_YELLOW)
     
    def move(self, vel, angle):
        self.xpos -= np.sin(angle*np.pi/180) *vel
        self.ypos += np.cos(angle*np.pi/180) *vel
        
    def turn(self, origin, angle):
        ox, oy = origin #newcar.x ,y
        angle = -angle *np.pi/180
        qx = ox + np.cos(angle) * (self.xpos - ox) - np.sin(angle) * (self.ypos - oy)
        qy = oy + np.sin(angle) * (self.xpos - ox) + np.cos(angle) * (self.ypos - oy)
        self.xpos = qx
        self.ypos = qy
        

class car:
    
    "creates robot"
    
    def __init__(self, xpos, ypos, tilt_angle, vel, width, height, color, arena):
        
        self.xpos = xpos
        self.ypos = ypos
        self.tilt_angle = tilt_angle *-1 #to make angle clockwise from vertical 
        self.vel = vel #need to work out pixels per second
        self.width = width
        self.height = height
        self.color = color
        self.arena = arena
        self.startvel = vel
        self.sensor_size = height/6
        
    def draw(self): #draws rectangle to model as car
        arcade.draw_rectangle_filled(self.xpos, self.ypos, self.width, self.height, self.color, self.tilt_angle)
        
    def drive(self): #moves the position with reference to the direction it is facing and its given velocity
        self.xpos -= np.sin(self.tilt_angle*np.pi/180) *self.vel
        self.ypos += np.cos(self.tilt_angle*np.pi/180) *self.vel
        
    def turn(self, angle, Rand=False): #turns the car through a given angle, clockwise

        if Rand: #turns through a random angle, probably more useful for the actual task
            
            ang = random.randint(90,270)
            for i in range(ang): #tries to avoid not turning far enough away from the mine, could be altered
                self.tilt_angle -= 1
            return ang
        
        else:
            for i in range(angle):
                self.tilt_angle -= 1
            return angle

        
    def sensor_poly(self):
        """create rectangle at position of certain size in the direction vehicle is facing
        iterates through all mines outline points as well as wall/safezone position points and returns if any point is in sensor
        might be and edge case if both mine and wall are in sensor but probably unlikely"""
        
        psi = np.arctan(self.width/self.height)
        phi = self.tilt_angle*np.pi/180 - psi
        phi2= np.pi/2 - self.tilt_angle*np.pi/180 - psi
        L = np.sqrt((self.width/2)**2 +(self.height/2)**2)
        x1=self.xpos-L*np.sin(phi)
        y1=self.ypos+L*np.cos(phi)
        x2=self.xpos - L*np.cos(phi2)
        y2=self.ypos +L*np.sin(phi2)
        poly = [[x1, y1],
                [x1-self.sensor_size*np.sin(self.tilt_angle*np.pi/180),y1+self.sensor_size*np.cos(self.tilt_angle*np.pi/180)],
                [x2-self.sensor_size*np.sin(self.tilt_angle*np.pi/180),y2+self.sensor_size*np.cos(self.tilt_angle*np.pi/180)],
                [x2, y2]]
        
        return poly       

    def control_vel(self, current_dist, rad):
        
        vel = self.startvel * (current_dist - self.height/2 - rad)/self.sensor_size
        return vel
    
    def perpdist(self, a, b):
        c = np.array(a)
        d = np.array(b)
        car_mine_vect = d-c
        car_tilt_vect = np.array([-np.sin(self.tilt_angle*np.pi/180), np.cos(self.tilt_angle*np.pi/180)])
        cosang = np.dot(car_mine_vect, car_tilt_vect)
        sinang = np.linalg.norm(np.cross(car_mine_vect, car_tilt_vect))
        ang = np.arctan2(sinang, cosang)
        return np.linalg.norm(car_mine_vect) * np.cos(ang)

    
    
        
