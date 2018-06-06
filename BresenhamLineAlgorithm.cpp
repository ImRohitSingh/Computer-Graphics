#include<stdio.h>
#include<graphics.h>
#include<math.h>
 
// required constants 
#define X 640
#define Y 480
 
 void lineBresenham(int,int,int,int,int);   // function prototype to draw a straight line using Bresenham's algorithm
 
 int main(void)
 /* 
   Variable Description:-
             x1- abscissa of the starting point
             y1- ordinate of the starting point
             x2- abscissa of the terminating point
             y2- ordinate of the terminating point
             
             
   Functions Description:-
             Predefined:
                  initwindow()- to create the displaying window
                  circle()- to mark the end points
                  getch()- to hold the console till a button is pressed
             User-defined:
                  lineBresenham()- to draw a straight line using Bresenham's algorithm
*/ 
 {
     int x1,y1,x2,y2;  // declaring variables
     // accept user inputs
     printf("Enter the points: ");
     scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
     initwindow(X,Y);  // creating window
     
     // marking the two-end points with circles
     circle(x1,y1,5);   
     circle(x2,y2,5);
    
     lineBresenham(x1,y1,x2,y2,12);  // function call to draw a straight line using Bresenham's algorithm
     
     getch();
     return 0;
}  // end of main

// function definition to draw a straight line using Bresenham's algorithm
void lineBresenham(int x1,int y1,int x2,int y2,int color)
/*  Variable Description:-
             x1- abscissa of the starting point
             y1- ordinate of the starting point
             x2- abscissa of the terminating point
             y2- ordinate of the terminating point
             color- the color with which the line is to be drawn
             dx- difference between x2 and x1
             dy- difference between y2 and y1
             (x,y) - pixel to plot
             absDX- absolute values of dx
             absDY- absolute values of dy
             xInc- constant value that adds up to x after each iteration
             yInc- constant value that adds up to y after each iteration
             
     Functions Description:-
             Predefined:
                  putpixel()- to draw a particular pixel with a particular color
                  delay()- to hold the present scenario for some time passed as an argument
                  
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
     int x,y,xInc,yInc,d,dx,dy,absDx,absDy;  // declaring variables
     // initializing variables and calculating some constants
     x=x1;
     y=y1;
     dx=x2-x1;
     dy=y2-y1;
     absDx=abs(dx);
     absDy=abs(dy);
     
     if(x1==x2 && y1==y2)  //same point
               putpixel(x1,y1,color);  // plot the pixel with color 'color'
     else if(y1==y2)  // horizontal line
     {
          // calculate xInc, y remains constant
          if(x1<x2)
             xInc=1;
          else
             xInc=-1;
          
          while(x!=x2)
          {
             putpixel(x,y,color); // plot the pixel with color 'color'
             x+=xInc;   // change x
             delay(1);  // holding the present state for 1 milliseconds
          } 
          putpixel(x,y,color); // plot the pixel with color 'color'
     } 
     else if(x1==x2)  // vertical
     {
          // calculate yInc, x remains constant
          if(y1<y2)
             yInc=1;
          else
             yInc=-1;
          while(y!=y2)
          {
             putpixel(x,y,color);  // plot the pixel with color 'color'
             y=y+yInc;   // change y
             delay(1);  // holding the present state for 1 milliseconds
          } 
          putpixel(x,y,color);
     } 
     else if(absDy<absDx) // gentle slope
     {
          // calculate xInc
          if(x1<x2)
            xInc=1;
          else
            xInc=-1;
          // calculate yInc
          if(y1<y2)
            yInc=1;
          else
            yInc=-1;
          
          d=2*absDy-absDx;  // initial decision parameter
          while(x!=x2)
          {
              if(d>0) // move to NE, y changes
              {
                  d=d+2*absDy-2*absDx;
                  y+=yInc;
              }
              else   // move to E pixel
                  d=d+2*absDy;
              x+=xInc;
              putpixel(x,y,color);  // plot the pixel with color 'color'
              delay(1); // holding the present state for 1 milliseconds
          }   
     }
     else  // sharp
     {
          // calculate xInc
         if(x1<x2)
            xInc=1;
          else
            xInc=-1;
           // calculate yInc
          if(y1<y2)
            yInc=1;
          else
            yInc=-1;
            
          d=2*absDx-absDy;   // initial decision parameter
          
          while(y!=y2)
          {
             if(d>0)  // x changes
             {
                d=d+2*absDx-2*absDy;
                x+=xInc;
             }
             else   // x remains same
                 d=d+2*absDx;
             y+=yInc;
             delay(1);    // holding the present state for 1 milliseconds
             putpixel(x,y,color);   // plot the pixel with color 'color'
          }       
     }
}  // end of function

