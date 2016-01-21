#include <Arduino.h>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

const char neigbhoringCells[4][2]={
    {-1,0},{0,1},{1,0},{0,-1}
};
const byte neigbhoringWalls[4][2]={
    {0,0},{0,1},{1,0},{0,0}
};


template <byte ROWS,byte COLUMNS>
class NanoMouseMaze
{
private:
    // vertical walls array
    boolean verticalWalls[ROWS][COLUMNS+1];

    // horizontal walls array
    boolean horizontalWalls[ROWS+1][COLUMNS];

public:
    // value array
    byte values[ROWS][COLUMNS];
    
    byte mouseRow;
    byte mouseColumn;
    byte mouseHeading;
    
    byte targetRow;
    byte targetColumn;

    
    //Constructor method (called when the maze is created)
    NanoMouseMaze()
    {
        //initialize verticalWalls (add exterior walls)
        for(byte i = 0;i < ROWS;i++)
        {
            for(byte j = 0;j<COLUMNS+1;j++)
            {
                if(j==0 || j == COLUMNS)
                {
                    verticalWalls[i][j] = true;
                }
            }
        }

        //initialize horizontalWalls (add exterior walls)
        for(byte i = 0;i < ROWS + 1;i++)
        {
            for(byte j=0;j<COLUMNS;j++)
            {
                if(i==0 || i==ROWS)
                {
                    horizontalWalls[i][j]=true;
                }
            }
        }
    }

    void setTargetCell(byte x, byte y)
    {
       values[x][y]=0;
       targetRow=x;
       targetColumn=y;
    }

    void turnTowardBestNeighbor()
    {
        //Remember to replace this funtion since it is for debugging only 
        //you need to implement a functional flow of control
       
       byte desiredHeading = findBestNeighbor();
       byte headingDifference = mouseHeading - desiredHeading;

       switch(headingDifference)
       {
        //move Right
        case -1:{}
        case  3:{}
        break;

        //move Left
        case  1:{}
        case -3:{}
        break;

        //turn 180
        case  2:{}
        case -2:{}
        break; 
        } 

        mouseHeading=desiredHeading;
    }

    void solve(){


        for(byte i=0;i<ROWS;i++){
            for(byte j=0;j<COLUMNS;j++)
            {
                values[i][j]=255;
            }
        }
         setTargetCell(targetRow,targetColumn);

        bool solvingFlag= true;
        while(solvingFlag)
        {   solvingFlag= false;
            for(byte i=0;i<ROWS;i++)
            {
            for(byte j=0;j<COLUMNS;j++)
                {
                    if(values[i][j]<255)
                    {
                        for(byte k=0;k<4;k++)
                        {
                            char neigbhoringCellRow= i + neigbhoringCells[k][0];
                            char neigbhoringCellColumn= j + neigbhoringCells[k][1];

                            byte neigbhoringWallRow= i + neigbhoringWalls[k][0];
                            byte neigbhoringWallColumn= j + neigbhoringWalls[k][1];
                          
                            bool wallExists= false;

                            if(k==NORTH||k==SOUTH)
                                wallExists = horizontalWalls[neigbhoringWallRow][neigbhoringWallColumn];
                            else //Must be east or west since they are equal
                                wallExists = verticalWalls[neigbhoringWallRow][neigbhoringWallColumn];
                            if((values[neigbhoringCellRow][neigbhoringCellColumn]==255) && !(wallExists))
                            {   
                                values[neigbhoringCellRow][neigbhoringCellColumn]=values[i][j]+1;
                                solvingFlag=true;
                            }
                        }
                    }
                }
             }
        }
    
    }

    void scanWalls()
    {
        if(1/*Check front Sensor*/)
        addWall(mouseHeading);
        if(1/*Check left  Sensor*/)
        addWall((mouseHeading+3) % 4);
        if(1/*Check right Sensor*/)
        addWall((mouseHeading+1) % 4);
  //    if(1/*Check back  Sensor*/)
    }
    void setMouseLocation(byte row, byte column,byte c_Heading=255)
    {
        mouseRow=row;
        mouseColumn=column;
        if(c_Heading!=255)
        mouseHeading=c_Heading;
    }

    //Function to add wall using a specific location
    void addWallByLocation(byte row, byte column,byte c_Direction)
    {
        /*
        *Have to remember the how to find the specific location using the array above
        *The function will take a byte arguments
        *THe function has to have a third argument to specify wheater the wall is vertical or horizintal
        */
        switch(c_Direction)
        {
            case NORTH:
                horizontalWalls[row][column] = true;
                break;
            case EAST:
                verticalWalls[row][column+1] = true;
                break;
            case SOUTH:
                horizontalWalls[row+1][column] = true;
                break;
            case WEST:
                verticalWalls[row][column] = true;
                break;
        }

    }
    void addWall(byte cardinialDirection)
    {
        switch(cardinialDirection)
        {
            case NORTH:
                horizontalWalls[mouseRow][mouseColumn] = true;
                break;
            case EAST:
                verticalWalls[mouseRow][mouseColumn+1] = true;
                break;
            case SOUTH:
                horizontalWalls[mouseRow+1][mouseColumn] = true;
                break;
            case WEST:
                verticalWalls[mouseRow][mouseColumn] = true;
                break;
        }

    }
    byte findBestNeighbor()
    {
        byte valueBestNeighbor = 255;
        byte desiredHeading = NORTH;
        for(byte k=0;k<4;k++)
        {
            char neigbhoringCellRow= mouseRow + neigbhoringCells[k][0];
            char neigbhoringCellColumn= mouseColumn + neigbhoringCells[k][1];

            byte neigbhoringWallRow= mouseRow + neigbhoringWalls[k][0];
            byte neigbhoringWallColumn= mouseColumn + neigbhoringWalls[k][1];
          
            bool wallExists= false;

            if(k==NORTH||k==SOUTH)
                wallExists = horizontalWalls[neigbhoringWallRow][neigbhoringWallColumn];
            else //Must be east or west since they are equal
                wallExists = verticalWalls[neigbhoringWallRow][neigbhoringWallColumn];
            if((values[neigbhoringCellRow][neigbhoringCellColumn]<=valueBestNeighbor) && !(wallExists))
            {   

                if(values[neigbhoringCellRow][neigbhoringCellColumn]==valueBestNeighbor&&mouseHeading!=k)
                    continue;
                valueBestNeighbor=values[neigbhoringCellRow][neigbhoringCellColumn];
                desiredHeading=k;
            }
        }
        return desiredHeading;
    }

    /*PRINT FUNCTION
    Do not change or add code below this line*/
    
    void print()
    {
        for(byte i = 0;i < 2*ROWS+1;i++)
        {
            for(byte j = 0;j < 2*COLUMNS+1;j++)
            {
                //Add Horizontal Walls
                if(i%2 == 0 && j%2 == 1)
                {
                    if(horizontalWalls[i/2][j/2] == true)
                    {
                        Serial.print(" ---");
                    }
                    else
                    {
                        Serial.print("    ");
                    }
                }

                //Add Vertical Walls
                if(i%2 == 1 && j%2 == 0)
                {
                    if(verticalWalls[i/2][j/2] == true)
                    {
                        Serial.print("|");
                    }
                    else
                    {
                        Serial.print(" ");
                    }
                }

                //Add Flood Fill Values
                if(i%2 == 1 && j%2== 1)
                {
                    if((i-1)/2 == mouseRow && (j-1)/2 == mouseColumn)
                    {
                        if(mouseHeading == NORTH)
                        {
                            Serial.print(" ↑ ");
                        }
                        else if(mouseHeading == EAST)
                        {
                            Serial.print(" → ");
                        }
                        else if(mouseHeading == SOUTH)
                        {
                            Serial.print(" ↓ ");
                        }
                        else if(mouseHeading == WEST)
                        {
                            Serial.print(" ← ");
                        }
                    }
                    else
                    {
                        byte value = values[(i-1)/2][(j-1)/2];
                        if(value >= 100)
                        {
                            Serial.print(value);
                        }
                        else
                        {
                            Serial.print(" ");
                            Serial.print(value);
                        }
                        if(value < 10)
                        {
                            Serial.print(" ");
                        }
                    }
                }
            }
            Serial.print("\n");
        }
        Serial.print("\n");
    }
};
