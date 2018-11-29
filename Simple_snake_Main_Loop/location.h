int direction_facing = 1; //1 for facing forwards and -1 for facing the other way in the SNAKE

const int trigPinx = 10;
const int trigPiny = 9;
const int echoPinx = 12;
const int echoPiny = 11;
int coordinate[2]={0,0};
void find_coordinate();
void xydistance();
float xdistance;
float ydistance;
int current_position; // used to remember position when depositing yellow mines
//initilise the x and y coordinates to 0 for when starting
int xcoordinate=0;
int ycoordinate=0;
