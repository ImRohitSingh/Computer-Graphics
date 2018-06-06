#include<stdio.h>
#include<graphics.h>
#include<math.h>
 
#define R(x) ((int)(x+0.5)) /*macro used for scan conversion of point, 
                            addressing a pixel by its centre point*/
// required constants 
#define X 640
#define Y 480

void lineDDA(int,int,int,int,int);  // function prototype to draw a straight line using DDA algorithm

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
                  getch()- to hold the console till a button is pressed
                  circle()- to mark the end points
             User-defined:
                  lineDDA()- to draw a straight line using DDA algorithm
*/ 
{
    int x1,y1,x2,y2; // declaring variables
     // accept user inputs
    printf("Enter the points: "); 
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
    
    initwindow(X,Y);// creating window 
     // marking the two-end points with circles
    circle(x1,y1,5); 
    circle(x2,y2,5);
    
    lineDDA(x1,y1,x2,y2,12);  // function call to draw a straight line using DDA algorithm
    
    getch();
    return 0;
}  // end of main

// function definition to draw a straight line using DDA algorithm
void lineDDA(int x1,int y1,int x2,int y2,int color)
/*  Variable Description:-
             x1- abscissa of the starting point
             y1- ordinate of the starting point
             x2- abscissa of the terminating point
             y2- ordinate of the terminating point
             color- the color with which the line is to be drawn
             (x,y) - pixel to plot
             xInc- constant value that adds up to x after each iteration
             yInc- constant value that adds up to y after each iteration
             
     Functions Description:-
             Predefined:
                  putpixel()- to draw a particular pixel with a particular color
                  delay()- to hold the present scenario for some time passed as an argument
                  
     Algorithm:-
             Assuming that slope is gentle:-
             Strategy: change x, find y
                  x = x + xInc;
                  y = y + yInc, where yInc = xInc * m and xInc is unit change in x direction
             
             If slope is sharp/ steep:- 
             Strategy: change y, find x
                  y = y + yInc;
                  x = x + xInc, where xInc = yInc * 1/m and yInc is unit change in y direction            
*/
{
     double m,x,y,xInc,yInc; // declaring variables
     // initializing variables
     x=x1;
     y=y1;
     if(x1==x2 && y1==y2)  // same point
               putpixel(R(x1),R(y1),color);  // plot the pixel with color 'color'
     else if(y1==y2)  // horizontal line
     {
          // calculate xInc, y remains constant
          if(x1<x2)  
             xInc=1;  // left to right
          else
             xInc=-1;  // right to left
          while(x!=x2)   // continue till the initial point reaches the final point
          {
             putpixel(R(x),R(y),color);    // plot the pixel with color 'color'
             x+=xInc;  // increment x
             delay(1);  // holding the present state for 1 milliseconds
          } 
          putpixel(R(x),R(y),color); // plot the pixel with color 'color'
     }  
     else if(x1==x2)  // vertical line
     {
          // calculate yInc, x remains constant
          if(y1<y2)  // bottom to top
             yInc=1;
          else
             yInc=-1;  // top to bottom
          while(y!=y2)  // continue till the initial point reaches the final point
          {
             putpixel(R(x),R(y),color);   // plot the pixel with color 'color'
             y=y+yInc; // increment y
             delay(1); // holding the present state for 1 milliseconds
          } 
          putpixel(R(x),R(y),color);
     } 
     else if(abs(y2-y1)<abs(x2-x1))  // |m|<=1, i.e., gentle slope
     {
          m=(y2-y1)/((double)(x2-x1));  // calculate slope
          if(x1<x2)  // left to right
          {
             xInc=1;
             yInc=m;
          }
          else  // right to left
          {
             xInc=-1;
             yInc=-m;
          }
          
          while(x!=x2)  // continue till the initial point reaches the final point
          {
             putpixel(R(x),R(y),color);  // plot the pixel with color 'color'
             x+=xInc;  // increment x
             y=y+yInc; // increment y
             delay(1);  // holding the present state for 1 milliseconds
          } 
          putpixel(R(x),R(y),color);  // plot the pixel with color 'color'
     }
     else  // |m|>1 i.e. sharp slope.
     {
         m=(x2-x1)/((double)(y2-y1));  // calculate inverse of slope
         if(y1<y2)  // bottom to top 
         {
            yInc=1;
            xInc=m;
         }
         else  // top to bottom 
         {
             yInc=-1;
             xInc=-m;
         }
         while(y!=y2)  // continue till the initial point reaches the final point
         {
            putpixel(R(x),R(y),color);  // plot the pixel with color 'color'
            x+=xInc; // increment x
            y+=yInc; // increment y
            delay(1); // holding the present state for 1 milliseconds
         }
         putpixel(R(x),R(y),color);  // plot the pixel with color 'color'
     }
}  // end of function
         
