#include<stdio.h>
#include<graphics.h>
#include<conio.h>
// pre-processor directories to calculate co-ordinates for the displaying device
#define fx(x) (getmaxx()/2+x)    
#define fy(y) (getmaxy()/2-y)

/* macro used for scan conversion of point, addressing a pixel by its centre point*/
#define R(x) ((int)(x+0.5))

// required constants
#define X 640
#define Y 480

// colors
#define LWHITE 7
#define LCYAN 3
#define IMAGENTA 13    
#define YELLOW 14      
#define GRAY 8

void drawQuadrants();   // function prototype to create quadrants
void ellipseMidPointApp(int,int,int,int); // function prototype to draw a ellipse through Mid-Point Approach
void paint(int,int,int,int);   // function prototype to plot 4 different points of an ellipse at once
void boundaryFill(int,int,int,int); // function prototype to color the ellipse applying 'boundary fill' technique

int main(void)
/* 
   Variable Description:-
            (x1,y1) is the co-ordinate of the center of the ellipse. 
            'a' is the length of the semi-major axis. 
            'b' is the length of the semi-minor axis.
            'x' is the abcissa of the starting point from where plotting is to begin.
            'y' is the ordinate of the starting point from where plotting is to begin.
            'd' is a decision parameter
            'speed' is basically the time(in milliseconds) for which a delay will be applied
   
            Note: Variables 'x1','y1','a','b' and 'speed' are initialized from before in this piece of code. To avoid any loss of generality, take user-inputs.
   
   Functions used:-
          Pre-defined functions:   
             initwindow() - to create the displaying screen.
             setcolor()- to color everything drawn after that that segment till the same function has been invoked with a different color.
             delay() - to hold the current state for a particular time
             putpixel()- to color the pixel (x,y) with a given color, say C (passed as an integer).
          User-defined functions:
             drawQuadrants() -  to draw four quadrants of the window.
             ellipseMidPointApp() - to draw an ellipse through Mid-Point Approach.
             paint() - plot 4 different points of an ellipse at once.
             boundaryFill()- to color the ellipse applying 'boundary fill' technique
             
   Logic Description:- 
           For the first quadrant start form (0,b), increments 'x' by '1' and find corresponding 'y' and plot the (x,y) pixel. 
           Repeat the process untill a closed figure is obtained. For each quadrant find the reflecting points of the 4 quadrants and plot them too.
           
          Algorithm:
              
          
          Initially: 
                         
*/
{
    // declaring and initializing variables
    int x1=60,y1=60,a=80,b=60;
    initwindow(X,Y);     // creating window
    drawQuadrants(); // calling function to draw quadrants 
    ellipseMidPointApp(x1,y1,a,b);   // function call to draw a circle through Mid-Point Approach
    boundaryFill(x1,y1,YELLOW,GRAY);    // function call to color the ellipse using Boundary-Fill Technique
    getch();
    return 0;
}  // end of main

// function definition to create quadrants
void drawQuadrants()
{
    setcolor(LCYAN);   // setting a color for the co-ordinate axes
    line(0,fy(0),X,fy(0));   // drawing the X-axis; fy(0)=480/2=240;
    line(fx(0),0,fx(0),Y);   // drawing the Y-axis; fx(0)=640/2=320;
}

// function definition to draw a circle through Mid-Point Approach
void ellipseMidPointApp(int x1,int y1,int a,int b)
{
     // declaring and initializing variables
     int x=0,y,speed=20,d;
     y=b;
     d=R((b*b)-(a*a*b)+(0.25*a*a));     
     // applying Mid-point algorithm
     while(R(((a*a)*(y-0.5)))>((b*b)*(x+1)))
     {          
              paint(x1,y1,x,y);    // function call to plot 4 different points of an ellipse at once
              if(d<0)  // if decision variable is negative, E corner
                  d=d+(b*b)*((2*x)+3);
              else   // if decision variable is non-negative, SE corner
              {
                  d=d+((b*b)*(2*x+3))+((a*a)*((-2*y)+3));
                  y=y-1;
              }
              x=x+1;
              delay(speed);    // holding the present state for 'speed' milliseconds
     }
     d=R(((b*b)*((x+0.5)*(x+0.5)))+((a*a)*((y-1)*(y-1)))-((a*a)*(b*b)));
     while(y>0)
     {
               paint(x1,y1,x,y);    // function call to plot 4 different points of an ellipse at once
               if(d<0)
               {
                   d=d+((b*b)*(2*x+2))+((a*a)*(((-2)*y)+3));
                   x=x+1;
               }
               else
                   d=d+((a*a)*(((-2)*y)+3));
               y=y-1;
               delay(speed);    // holding the present state for 'speed' milliseconds
     }      
     paint(x1,y1,x,y);    // function call to plot 4 different points of an ellipse at once; this call plots the points (x1+a,y1) and (x1-a,y1).
}

// function definition to plot 4 different points of an ellipse at once
void paint(int x1,int y1,int x,int y)
{
     // first quadrant
     putpixel(fx(x1+x),fy(y1-y),YELLOW);  // starting from (0,b) and drawing left to right
     // second quadrant
     putpixel(fx(x1-x),fy(y1-y),YELLOW);  // starting from (0,b) and drawing right to left
     // third quadrant
     putpixel(fx(x1-x),fy(y1+y),YELLOW); // starting from (0,-b) and drawing right to left
     // fourth quadrant
     putpixel(fx(x1+x),fy(y1+y),YELLOW); // starting from (0,-b) and drawing left to right
}

// function prototype to color the ellipse applying 'boundary fill' technique
void boundaryFill(int x,int y,int boundCol,int fillCol)
{
     int color;   // declaring variable
     color=getpixel(fx(x),fy(y));      // get the color of the current pixel
     if(color!=boundCol && color!=fillCol)
     {
                   putpixel(fx(x),fy(y),fillCol);
                   // right semi-ellipse
                   boundaryFill(x,y+1,boundCol,fillCol); 
                   boundaryFill(x,y-1,boundCol,fillCol);  
                   // left semi-ellipse
                   boundaryFill(x+1,y,boundCol,fillCol);  
                   boundaryFill(x-1,y,boundCol,fillCol);    
     }     
}

