#include<stdio.h>
#include<graphics.h>

// pre-processor directories to calculate co-ordinates for the displaying window in the form of Cartesian co-ordinates
#define fx(x) (getmaxx()/2+x)    
#define fy(y) (getmaxy()/2-y)

// required constants
#define X 640
#define Y 480
// colors
#define LRED 4
#define LCYAN 3
#define YELLOW 14

void drawQuadrants(int);   // function prototype to create quadrants
void lineBresenham(int,int,int,int,int);  // function prototype to draw a straight line using Bresenham's algorithm
void markEndPoints(int,int,int,int,int);  // function prototype to mark the two end points with circles

int main(void)
/* 
   Variable Description:-
             x1- abcissa of the starting point
             y1- ordinate of the starting point
             x2- abcissa of the terminating point
             y2- ordinate of the terminating point
             
             
   Functions Description:-
             Predefined:
                  initwindow()- to create the displaying window
                  putpixel()- to draw a particular pixel with a particular color
                  getch()- to hold the console till a button is pressed
             User-defined:
                  drawQuadrants()- to draw quadrants
                  lineBresenham()- to draw a straight line using Bresenham's algorithm
*/ 
{
    int x1=100,y1=20,x2=50,y2=200;  // declaring and initializing variables
    initwindow(X,Y);     // creating window
    drawQuadrants(LCYAN); // calling function to draw quadrants
    lineBresenham(x1,y1,x2,y2,LRED);  // function call to draw a straight line using Bresenham's algorithm
    getch();
    return 0;
}  // end of main

// function definition to create quadrants
void drawQuadrants(int color)
/* Functions Description:-
             Predefined:
                  setcolor()- to draw a particular segment of the program with a particular color passed as an argument
                  line()- to draw a line
*/
{
    setcolor(color);   // setting a color for the co-ordinate axes
    line(0,fy(0),X,fy(0));   // drawing the X-axis; fy(0)=480/2=240;
    line(fx(0),0,fx(0),Y);   // drawing the Y-axis; fx(0)=640/2=320;
}  // end of function definition

// function call to draw a straight line using Bresenham's algorithm
void lineBresenham(int x1,int y1,int x2,int y2,int color)
/*  Variable Description:-
             x1- abcissa of the starting point
             y1- ordinate of the starting point
             x2- abcissa of the terminating point
             y2- ordinate of the terminating point
             color- the color with which the line is to be drawn
             dx- difference from x2 to x1
             dy- difference from y2 to y1
             (x,y) - pixel to plot
             absDX- absolute values of dx
             absDY- absolute values of dy
             
     Functions Description:-
             Predefined:
                  putpixel()- to draw a particular pixel with a particular color
                  delay()- to hold the present scenario for some time passed as an argument
             User-defined:
                  markEndPoints()- to mark the two end points with circles
                  
     Algorithm:-
             We assume that slope is gentle (increment x, find y).
             If dx<0 we assume it to be positive for calculation of decision varaible.
               x= x+1 or x-1 according as dx>0 <left ro right) or dx<0 (right to left) respectively. 
               Initial decision parameter, d=2*dy-dx;
                       Now d=d+2(dy-dx), if d>0, NE pixel to plot, y=y+1
                            =d+2dx, if d<=0, E pixel to plot, y=y;
             
             If slope is sharp/ steep, just interchange the roles of x and y and proceed same as above.              
*/
{
    // declaring variables
    int dx,dy,x,y,d,k,absDX,absDY;
    double slope;
    // calculating x and y differences
    absDX=dx=x2-x1;  
    absDY=dy=y2-y1;
    // initializing starting point to plot
    x=x1;
    y=y1;
    // absolute values are needed for the calculation of decision parameters in this algorithm
    if(dx<0)    
       absDX=-dx;
    if(dy<0)
       absDY=-dy;
    if(dx==0 && dy==0)    // if both points are same
    {
         markEndPoints(x1,y1,x2,y2,YELLOW);    // function call to mark the two end points with circles
         putpixel(fx(x),fy(y),color);   // plot the pixel with color 'color'
    }
    else if(dx==0 && dy!=0) // line is vertical
    {
         markEndPoints(x1,y1,x2,y2,YELLOW);    // function call to mark the two end points with circles
         if(y1<y2)  // top to bottom
           while(y2!=y++)    // continue untill initial ordinate reaches final
                 putpixel(fx(x),fy(y),color);   // plot the pixel (x,y) with color 'color'
         else   // bottom to top
           while(y2!=y--)    // continue untill initial ordinate reaches final
                 putpixel(fx(x),fy(y),color);   // plot the pixel (x,y) with color 'color'
    }  
    else if(dx!=0 && dy==0) // line is horizontal
    {
         markEndPoints(x1,y1,x2,y2,YELLOW);    // function call to mark the two end points with circles
         if(x1<x2)  // left to right
           while(x2!=x++)   // continue untill initial abcissa reaches final
                 putpixel(fx(x),fy(y),color);   // plot the pixel (x,y) with color 'color'
         else  // right to left
           while(x2!=x--)   // continue untill initial abcissa reaches final
                 putpixel(fx(x),fy(y),color);   // plot the pixel (x,y) with color 'color'
    } 
    else 
    {
         if(absDY<absDX)    // if slope is gentle
         {
              d=2*absDY-absDX;  // calculating initial decision parameter
              markEndPoints(x1,y1,x2,y2,YELLOW);    // function call to mark the two end points with circles
              putpixel(fx(x),fy(y),color);    // plot (x,y) pixel with color 'color'
              if(dx>0)   // left to right
                 while(x2!=x++)  /// continue untill initial abcissa reaches final
                 {
                    if(d>0)  // move to NE pixel
                    {
                          // find corresponding 'y'
                          if(dy>0)
                             y=y+1;
                          else
                             y=y-1;
                          d=d+2*(absDY-absDX);   // calculate the decision variable parameter accordingly
                    }
                    else   // move to E pixel 
                       d=d+2*absDY;  // calculate the decision variable parameter accordingly
                    putpixel(fx(x),fy(y),color);  // plot (x,y) pixel with color 'color'
                    delay(50);    // holding the present state for 50 milliseconds
                 }  
              else   //  right to left
                 while(x2!=x--)  /// continue untill initial abcissa reaches final
                 {
                         if(d>0)  // NW pixel to plot
                         {
                                // find corresponding 'y'
                                if(dy>0)
                                   y=y+1;
                                else
                                   y=y-1;
                                d=d+2*(absDY-absDX);   // calculate the decision variable parameter accordingly
                         }
                         else   // W pixel to plot
                                d=d+2*absDY;  // calculate the decision variable parameter accordingly
                         putpixel(fx(x),fy(y),color);  // plot (x,y) pixel with color 'color'
                         delay(50);    // holding the present state for 50 milliseconds
                   }        
           }   // if slope was gentle
           
           else    // if slope is gentle
           {
              d=2*absDX-absDY;  // calculating initial decision parameter
              markEndPoints(x1,y1,x2,y2,YELLOW);    // function call to mark the two end points with circles
              putpixel(fx(x),fy(y),color);    // plot (x,y) pixel with color 'color'
              if(dy>0)   // bottom to top
                 while(y2!=y++)  /// continue untill initial abcissa reaches final
                 {
                    if(d>0)  // move to NE pixel
                    {
                          // find corresponding 'y'
                          if(dx>0)
                              x=x+1;
                          else
                              x=x-1;
                          d=d+2*(absDX-absDY);   // calculate the decision variable parameter accordingly
                    }
                    else   // E pixel to plot
                       d=d+2*absDX;  // calculate the decision variable parameter accordingly
                    putpixel(fx(x),fy(y),color);  // plot (x,y) pixel with color 'color'
                    delay(50);    // holding the present state for 50 milliseconds
                 }  
              else   //  top to bottim
                 while(y2!=y--)  /// continue untill initial abcissa reaches final
                 {
                         if(d>0)  // move to NW pixel 
                         {
                                // find corresponding 'y'
                                if(dx>0)
                                   x=x+1;
                                else
                                   x=x-1;
                                d=d+2*(absDX-absDY);   // calculate the decision variable parameter accordingly
                         }
                         else   // move to W pixel
                                d=d+2*absDX;  // calculate the decision variable parameter accordingly
                         putpixel(fx(x),fy(y),color);  // plot (x,y) pixel with color 'color'
                         delay(50);    // holding the present state for 50 milliseconds
                   }        
           }   // if slope was gentle
          
    }
}  // end of function definition

// function call to mark the two end points with circles
void markEndPoints(int x1,int y1,int x2,int y2,int color)
/* Functions Description:-
             Predefined:
                setcolor()- to draw a particular segment of the program with a particular color passed as an argument
                delay()- to hold the present scenario for some time passed as an argument
                circle()- to draw a circle
*/                        
{
    setcolor(color);   // setting a color for the circle around the starting and terminating points of the line
    circle(fx(x1),fy(y1),3);   // function call to draw a circle with (x1,y1) as center and radius 3 units 
    delay(500);     // holding the present state for 50 milliseconds
    circle(fx(x2),fy(y2),3); // function call to draw a circle with (x2,y2) as center and radius 3 units 
}     // end of function definition                  




    
    
    
    
