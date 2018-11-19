'''
Created on 7 Nov 2018

@author: alexa
'''

from IDP.gameObjects import car, arena, mine
import arcade
import random
import matplotlib.path as mpltPath
import numpy as np

carsprite_scaling = 1/6.5
redmine_scaling = 1/19
yellowmine_scaling = 1/16

class MineSweep(arcade.Window):
    
    def __init__(self): 
        super().__init__(new_arena.width, new_arena.height) #sets up window with inputed height and width in pixel measurements
        self.newcarsprite = None
        
    def setup(self): #runs on setup, adds car, arena and mine objects
             
        self.newcar = car(new_arena.safe_zone_offset, new_arena.safe_zone_offset, tilt_angle=70, vel=8, width=150, height=200, color=arcade.color.GRAY, arena = new_arena) #creates car/robot object
        self.newcarsprite = arcade.Sprite("carsprite.png", carsprite_scaling)
        self.newcarsprite.center_x = self.newcar.xpos
        self.newcarsprite.center_y = self.newcar.ypos
        self.newcarsprite.angle = -self.newcar.tilt_angle + 90
        
        self.minelist = []
                
        total_mines = 6
        red_mines = total_mines//3
        yellow_mines = total_mines - red_mines
        min_mine_dist = 100
                
        positions = [[random.randrange(200, 900), random.randrange(300, 900)]] #initial placement #200, 900 ,, 300,900
        
        while len(positions) < total_mines: #adds mines at random places to arena but makes sure no mines are placed too close together
            newpos = [random.randrange(200,900 ), random.randrange(300, 900)] #initial placement #200, 900 ,, 300,900
            test = []
            for position in positions: 
                test.append(np.linalg.norm([a - b for a,b in zip(position, newpos)]) < min_mine_dist)     
            if np.any(test):
                pass
            else:
                positions.append(newpos)
        
        self.minespritelist = arcade.SpriteList()   
            
        for i in range (total_mines): #adds number of yellow mine and (total-yellow) red mines
            if i<yellow_mines:
                self.minelist.append(mine(positions[i][0],positions[i][1], 25))
                minesprite = arcade.Sprite("yellowminesprite.png", yellowmine_scaling)
                minesprite.center_x = positions[i][0]
                minesprite.center_y = positions[i][1]
                self.minespritelist.append(minesprite)
            else:
                self.minelist.append(mine(positions[i][0],positions[i][1], 25, dangerous=True))
                minesprite = arcade.Sprite("redminesprite.png", redmine_scaling)
                minesprite.center_x = positions[i][0]
                minesprite.center_y = positions[i][1]
                self.minespritelist.append(minesprite)
        
        
        
        self.minemove = False
        self.brake = False
        self.detect = False
        self.vismine = None
        self.clearedmines = []
        self.movingmines = []
        self.ind = None

    def update(self, dt): #loops through every frame, contains all movement logic, can update spirtes if i get around to it
        
        self.newcarsprite.center_x = self.newcar.xpos
        self.newcarsprite.center_y = self.newcar.ypos
        self.newcarsprite.angle = self.newcar.tilt_angle - 90
        
        self.newcar.drive()       
        
        
        poly = self.newcar.sensor_poly()
        path = mpltPath.Path(poly)
        
        if self.minemove == False or True: #normal skip this if mine is being pushed ie when after detect has happened
            for mine in self.minelist:
                if arcade.geometry.are_polygons_intersecting(mine.hitbox(mine.xpos, mine.ypos), poly):
                    
                    if mine in self.movingmines or mine in self.clearedmines: #prevents being triggers on mine/s being moved
                        pass
                    
                    
                    elif self.newcar.perpdist([self.newcar.xpos,self.newcar.ypos], [mine.xpos,mine.ypos]) > self.newcar.height/2 + mine.radius + 5: #controls speed to mine then stops 5 pixels away
                        if self.brake ==False:
                            self.vismine = mine
                        self.brake = True
                        break
                    
                    else:
                        self.detect = True #car is close enough so detect and mine push occur
                        self.brake = False
                        self.newcar.vel = 0
                        self.newcar.drive()

                        
        
        #     
        if self.brake: #controls velocity to proportional to perpendicular distance to the mine in range that it is approaching
            self.newcar.vel = self.newcar.control_vel(self.newcar.perpdist([self.newcar.xpos,self.newcar.ypos], [self.vismine.xpos,self.vismine.ypos]), self.vismine.radius) # dist to go/ startingdist (sensor height +mine radius)


        if self.detect: #checks if mine is dangerous
            arcade.pause(1)
            print ("Dangerous!" if self.vismine.dangerous else "Safe!") #prints dangerous or safe
            arcade.pause(1)
            self.newcar.vel = self.newcar.startvel
            if not self.vismine.dangerous:
                print ("The coordinates are : " + str(self.vismine.xpos) + "," + str(self.vismine.ypos))
                self.minemove = True  #starts pushing mine if it safe
                self.movingmines.append(self.vismine)
            else:
                print ("The coordinates are : " + str(self.vismine.xpos) + "," + str(self.vismine.ypos))
                angle = self.newcar.turn(90, Rand=True)                 #turns away if mine is red
                for mine in self.movingmines:
                    mine.turn([self.newcar.xpos,self.newcar.ypos], angle)
            self.detect = False
            
        if self.minemove:
            
            minescleared = []
            
            for vismine in self.movingmines: 
            
                if not vismine.dangerous:
                    vismine.beingmoved = True
                
                i = self.minelist.index(vismine) #checks which mine is being moved from the list
                vismine.move(self.newcar.vel, self.newcar.tilt_angle) #updates position then updates the minelist with the new position
                self.minelist[i].xpos = vismine.xpos
                self.minelist[i].ypos = vismine.ypos
                self.minespritelist[i].center_x = vismine.xpos #updates the minesprite
                self.minespritelist[i].center_y = vismine.ypos
                    
                minescleared.append(arcade.geometry.are_polygons_intersecting(vismine.hitbox(vismine.xpos, vismine.ypos), new_arena.safe_outline()))
                    
            if not np.any(minescleared): #if the mine if no longer in the safe zone it is left on the edge
                self.minemove = False             
                self.clearedmines += self.movingmines
                self.movingmines = []
                self.newcar.turn(90, Rand=True)
                print (self.clearedmines)

            "if mine.hitbox not intersecting with safe zone, then stop and leave mine. and turn away and continue as normal"

            
            #  then car velocity back to normal and
            # mine.move until car reaches end
                  # """
                
                #self.newcar.turn(90, Rand=True)
                
                
        if np.any((path.contains_points(new_arena.edge_outline()))):
        #    WALL = True
            self.newcar.turn(90, Rand=True)

        
        
    def on_draw(self): #renders objects
                
        arcade.start_render()
        self.newcarsprite.draw()
        self.minespritelist.draw()
        #self.newcar.draw()
        #for mine in self.minelist:
        #    mine.draw()
        new_arena.draw_safezone()
        new_arena.draw_starting_area(self.newcar.height, self.newcar.width)
            


            
        
new_arena = arena(1100, 1100, 100) #probably can put in setup #1100 each initial size 100 offset

def main():
    window = MineSweep() 
    window.setup()
    arcade.run()
    
if __name__ == "__main__":
    main()
