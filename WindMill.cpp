#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>

// pre-processor directories to calculate co-ordinates for the displaying device
#define fx(x) (getmaxx()/2+x)    
#define fy(y) (getmaxy()/2-y)

// pre-processor directory to calculate the round-off value to the nearest integer
#define R(x) ((int)(x+0.5))

// required constants
#define PI 3.14
#define X 640
#define Y 480
// colors
#define LWHITE 7
#define LCYAN 3
#define IMAGENTA 13
#define YELLOW 14

void drawMillStand(int,int);   // function prototype to draw the trunk of the mill
void drawBlade(int,int,int,int,int,int,int); // function prototype to draw a blade of the mill
void calRotate(int,int,int,int,int,int,int);   // function prototype to draw a blade by calculating the new co-ordinates after a rotation
void createWindMill();    // function prototype to create a windmill
void createStill(int,int,int,int,int,int,int);  // function prototype to create a stationary image of a windmill

int main(void)
/* 
   Variable Description:-
            (x1,y1), (x2,y2) and (x3,y3) are the co-ordinates of the vertices of the blades of a triangle. 
            'a' is the angle(in degree) through which a blade is rotated. 
            'r' is the radian couterpart for the same.
            'increment' is a variable used to make the appearance of the blades at different positions after each iteration,
                                              and incremented by a constant factor each time to affect the rotation viewing.
            'speed' is basically the time(in milliseconds) for which a complete picture of the windmill 
                                     is made to stay in the window at each iteration.
   
         Note: All these variables are initialized from before in this piece of code. To avoid any loss of generality, take user-inputs.
   
   Functions used:-
          Pre-defined functions:   
             initwindow() - to create the displaying screen.
             setcolor()- to color everything drawn after that that segment till the same function has been invoked with a different color.
             line() - to draw a line.
             kbhit() - to stop the program by pressing any key. If a key has been pressed then it returns a non-zero value, otherwise a zero.
             cleardevice() - to delete evrything from the window at a particular instant
          User-defined functions:
             drawBlade() - to draw a blade of the mill.
             calRotate() - to calculate new co-ordinates and after a rotation and draw the rotated triangle accordingly.
             createWindMill()- to create a windmill.
             
   Logic Description:-        
         The trunk of the mill is drawn on which it is standing. A blade is drawn rotated through angle 'increment' w.r.t. the point (x1,y1) and the corresponding blade is drawn accordingly.
         Two other blades are drawn w.r.t. the point (x1,y1) rotated through angles 'increment+a' and 'increment-a'. At this point it 
         is a stationary windmill. 'increment' is incremented by a constant factor so that the bladed rotate in the same direction.
         A delay is applied. The whole diagram is deleted. And the entire process is repeated to draw the whole windmill with the updated
         'increment' angle. This makes the blade appear in a different position. As the process is repeated this makes every picture look
         like a moving image rotated keeping a particular point (x1,y1) fixed.
   
*/
{     
    initwindow(X,Y);     // creating window
    
    createWindMill();  // function call to create windmill
    
    getch();
    return 0;
}  // end of main

// function definition to create trunk of the mill
void drawMillStand(int x,int y)
{
    setcolor(LCYAN);   // setting a color for the co-ordinate axes
    line(fx(x),fy(y),fx(x),Y);   // drawing the stand
} // end of function

// function definition to create quadrants
void drawBlade(int x1,int y1,int x2,int y2,int x3,int y3,int color)
{
     setcolor(color);    // setting a color for the triangle
     // drawing the respective lines
     line(fx(x1),fy(y1),fx(x2),fy(y2));
     line(fx(x2),fy(y2),fx(x3),fy(y3));
     line(fx(x3),fy(y3),fx(x1),fy(y1));
}   // end of function

// function definition to draw a blade and the trunk of the mill together
void calRotate(int x1,int y1,int x2,int y2,int x3,int y3,int a)  
{
     // declaring and initializing variables
     int nx2,ny2,nx3,ny3;
     double r;
     
     r=(a*PI)/180;    // converting the rotating angle 'a' to radian
     
     // calcluating the new positions of the points (x2,y2) and (x3,y3) after a rotation
     nx2=R(((x2*(cos(r)))-(y2*(sin(r)))));                   
     ny2=R(((x2*(sin(r)))+(y2*(cos(r)))));                   
     nx3=R(((x3*(cos(r)))-(y3*(sin(r)))));                   
     ny3=R(((x3*(sin(r)))+(y3*(cos(r))))); 
      
     //drawing a blade for the mill
    drawBlade(x1,y1,nx2,ny2,nx3,ny3,YELLOW);
}   // end of function


//   function definition to create windmill
void createWindMill()
{
      // declaring and initializing variables
     int x1=10,y1=10,x2=x1+50,y2=y1-35,x3=x1-25,y3=y1-63,a=240,speed=10,increment=10;
     while(!(kbhit()))    
     {
         delay(speed);
         cleardevice(); // clear the window
         // each itertion of these steps draws a stationary windmill
         drawMillStand(x1,y1); // calling function to draw the trunk of the mill
         // functions calls to calculate new co-ordinates and after a rotation and draw the rotated triangle accordingly 
         calRotate(x1,y1,x2,y2,x3,y3,increment); 
         calRotate(x1,y1,x2,y2,x3,y3,increment+a);
         calRotate(x1,y1,x2,y2,x3,y3,increment-a);
         // change by a constant factor
         increment+=5;
     }     
}


