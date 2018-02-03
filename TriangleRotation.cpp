#include<stdio.h>
#include<graphics.h>
#include<math.h>

// pre-processor directories to calculate co-ordinates for the displaying device
#define fx(x) (getmaxx()/2+x)    
#define fy(y) (getmaxy()/2-y)

// pre-processor directories to calculate the round-off value to the nearest integer
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

void drawQuadrants();   // function prototype to create quadrants

int main(void)
/* (x1,y1), (x2,y2) and (x3,y3) are the co-ordinates of the vertices of a traingle. 
   'a' is the angle(in degree) through which the triangle is supposed to be rotated. 'r' is the radian couterpart of the same.
   All these are initialized from before in this piece of code. To avoid any loss of generality, take user-inputs.
   
   
   After rotaion through angle 'a' once w.r.t. the point (x1,y1), the new co-ordinates of the traigle are:
         (x1,y1),(nx2,ny2) and (nx3,ny3).

   After rotaion through angle 'a' twice w.r.t the point (x1,y1), the new co-ordinates of the traigle are:
         (x1,y1),(mx2,my2) and (mx3,my3).
         
   A pre-defined function 'initwindow()' has been used to create the displaying screen.
   
   A user-defined function 'drawQuadrants()' has been used to draw the co-ordinate axes.
   
*/
{
    int x1=10,y1=10,x2=x1+50,y2=y1-35,x3=x1-25,y3=y1-63,a=60,nx2,ny2,nx3,ny3,mx2,my2,mx3,my3;
    double r;        // declaring and initializing variables
    initwindow(X,Y);     // creating window
    drawQuadrants(); // calling function to draw quadrants
    //drawing a triangle
    setcolor(LWHITE);    // setting a color for the triangle
    line(fx(x1),fy(y1),fx(x2),fy(y2));
    line(fx(x2),fy(y2),fx(x3),fy(y3));
    line(fx(x3),fy(y3),fx(x1),fy(y1));
    
    r=a*(PI/180);    // converting the rotating angle to radian
    
    // rotating once w.r.t (x1,y1)
    // calcluating the new positions of the points (x2,y2) and (x3,y3)
    nx2=R(((x2*(cos(r)))-(y2*(sin(r)))));                   
    ny2=R(((x2*(sin(r)))+(y2*(cos(r)))));                   
    nx3=R(((x3*(cos(r)))-(y3*(sin(r)))));                   
    ny3=R(((x3*(sin(r)))+(y3*(cos(r)))));                   
    
    //drawing the rotated triangle
    setcolor(IMAGENTA);    // setting a color for this triangle
    line(fx(x1),fy(y1),fx(nx2),fy(ny2));
    line(fx(nx2),fy(ny2),fx(nx3),fy(ny3));
    line(fx(nx3),fy(ny3),fx(x1),fy(y1));
    
    // rotating twice w.r.t (x1,y1)
    // calcluating the new positions of the points (nx2,ny2) and (nx3,ny3)
    mx2=R(((nx2*(cos(r)))-(ny2*(sin(r)))));                   
    my2=R(((nx2*(sin(r)))+(ny2*(cos(r)))));                   
    mx3=R(((nx3*(cos(r)))-(ny3*(sin(r)))));                   
    my3=R(((nx3*(sin(r)))+(ny3*(cos(r)))));                   
    
    //drawing the rotated triangle
    setcolor(YELLOW);    // setting a color for this triangle
    line(fx(x1),fy(y1),fx(mx2),fy(my2));
    line(fx(mx2),fy(my2),fx(mx3),fy(my3));
    line(fx(mx3),fy(my3),fx(x1),fy(y1));
     
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
