#include "NanoMouseMaze.h"
NanoMouseMaze<7,7> maze;

unsigned long start = micros();

void forwardWhiskers()
{
switch(maze.mouseHeading)
{
  case NORTH:
  case SOUTH:{ maze.mouseRow += neigbhoringCells[maze.mouseHeading][0];}
  break;

  case WEST:
  case EAST:{maze.mouseColumn += neigbhoringCells[maze.mouseHeading][1];}

}
}

void setup() {
 
 


Serial.begin(9600); 
maze.setTargetCell(0,6);
maze.setMouseLocation(6,0,NORTH);

  for(int k=0;k<21;k++)
  { 
  randomSeed(95*k);

  maze.addWallByLocation((random(3414) *random(412))    %8,(random(31)    *random(4123)) %8,random(10)%4);
  maze.addWallByLocation((random(333)  *random(43214))  %8,(random(32812) *random(434))  %8,random(9)%4);
  maze.addWallByLocation((random(46214)*random(341))    %8,(random(617561)*random(3434)) %8,random(99)%4);
  maze.addWallByLocation((random(414)  *random(123231)) %8,(random(31223) *random(17321))%8,random(15)%4);
  }

 maze.print();

/*
maze.solve();
forwardWhiskers();  
maze.print();

maze.setMouseLocation(5,1,SOUTH);
maze.solve();
forwardWhiskers();
maze.print();

maze.setMouseLocation(5,1,WEST);
maze.solve();
forwardWhiskers();
maze.print();


maze.setMouseLocation(5,1,EAST);
maze.solve();
forwardWhiskers();
maze.print(); */
 /*
  maze.addWall(NORTH);
 for(byte i=0;i<7;i++)
 {
  if(i==1)continue;
  maze.addWallByLocation(6,i,NORTH);
  maze.addWallByLocation(i,2,NORTH);
  maze.addWallByLocation(i,2,EAST);
 }
*/
  //maze.scanWalls();  
 // maze.print();
 // Serial.println(maze.findBestNeighbor());
 
}
byte counter=0;
void loop(){
maze.solve();
maze.turnTowardBestNeighbor();
forwardWhiskers();
maze.print();

//delay(2500);

counter++;

Serial.print(counter);
if(maze.values[maze.mouseRow][maze.mouseColumn]==0)
{
  maze.setTargetCell(6,0);
}
if(maze.mouseRow==6 && maze.mouseColumn==0)
{stop();}//maze.scanWalls();
}
void stop(){

unsigned long end = micros();
unsigned long delta = end - start;
Serial.println(delta);
while(true){}
}

