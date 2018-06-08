// Cubic Bezier Curve
#include<stdio.h>
#include<graphics.h>
#include<math.h>

#define I(x) ((int)(x+0.5))   /*macro used for scan conversion of point, 
                            addressing a pixel by its centre point*/
// defining constants
#define error 0.0000000000001   // error term
#define X 640   // displaying window's width
#define Y 480  // displaying window's height

typedef struct point
{
       int x[4];  // storing absciccas'
       int y[4];  // storing ordinates'
} S;     // declaring a structure to hold the four control points 

void bezier(S,int,int);   // function prototype to draw the Bezier curve
void boundary(S,int);   // function prototype to draw the boundary formed by the four control points

int main(void)
/* 
   Variable Description:-
             inp- storing the control points (x[i],y[i]), for i=0(1)3
             i- loop initializer
             
   Functions Description:-
             Predefined:
                  initwindow()- to create the displaying window
                  getch()- to hold the console till a button is pressed
             User-defined:
                  boundary()- to draw the boundary formed by the four control points
                  bezier()-  to draw the Bezier curve
*/ 
{
    // declaring necessary variables
    S inp;
    int i;
    // accept user inputs
    printf("Enter 4 points:\n");
    for(i=0;i<4;++i)
    {
       printf("Enter (x%d,y%d): ",i,i);
       scanf("%d %d",&inp.x[i],&inp.y[i]);
    }
    
    initwindow(X,Y); // creating window 
    
    boundary(inp,6);  // function call to draw the Bezier curve
    bezier(inp,5,WHITE);  // function call to draw the boundary formed by the four control points
    getch();
    return 0;
}  // end of main

// function definition to draw the boundary formed by the four control points
void boundary(S inp,int color)
/*  
    Variable Description:-
             inp- storing the control points (x[i],y[i]), for i=0(1)3
                     
    Functions Description:-
             Predefined:
                  setlinestyle()- to increase the thickness of the lines, drawn as the boundary
                  setcolor() - to set a particular color for the objects to be drawn
                  line()- to draw the boundaries
*/ 
{
     setlinestyle(0,0,4);  // specify the thickness  
     setcolor(color);  // color the next objects with 'color'
     // plot the lines
     line(inp.x[0],inp.y[0],inp.x[1],inp.y[1]);
     line(inp.x[1],inp.y[1],inp.x[2],inp.y[2]);
     line(inp.x[2],inp.y[2],inp.x[3],inp.y[3]);
}  // end of function

// function definition to draw the Bezier curve
void bezier(S inp,int pointCol,int curveCol)
/* 
   Variable Description:-
             inp- storing the control points (x[i],y[i]) [represented generally by Bi/Pi] , for i=0(1)3
             
   Function Description:-
             t- parameter belonging to the interval [0,1] to ensure finiteness
             xt- the new abscissa of the curve
             yt- the new ordinate of the curve
             xold- abscissa of the previous point on the curve
             yold- ordinate of the previous point on the curve
                   [ draw a line from (xold,yold) to (xt,yt) (or vice-versa) after each iteration... ]
                       [ putpixel() will be less efficient and the choice of the error term 'error' will increase 
                                the number of iterations and thus has to be manipulated... ]
             i- loop initializer
             
   Functions Description:-
             Predefined:
                  setlinestyle()- to reassign the thickness of the lines to be drawn
                  setcolor() - to set a particular color for the objects to be drawn
                  delay()- to hold the present scenario for some time passed as an argument
                  line()- to draw the curve
                  circle()- to distinguish the control points

*/ 
{
    // declaring variables 
    int i;
    double t,xt,yt,xold,yold;
    setcolor(pointCol);  // color the next objects with 'pointCol' (mainly to distinguish the control points)
    for(i=0;i<4;++i)
    {
      circle(inp.x[i],inp.y[i],3);  // marking the control points with circles
    }
    t=0.0;  // initialize parameter
    setlinestyle(0,0,0);  // reassign the thickness of the lines to be drawn
    setcolor(curveCol); // color the next objects with 'curveCol' (to draw the curve)
    while(1)  // run inifinitely
    {
        // calculate points using basis function (Bezier function) of Bezier curves
        xt=pow(1-t,3)*inp.x[0]+3*t*inp.x[1]*(pow(1-t,2))+3*pow(t,2)*inp.x[2]*(1-t)+pow(t,3)*inp.x[3];
        yt=pow(1-t,3)*inp.y[0]+3*t*inp.y[1]*(pow(1-t,2))+3*pow(t,2)*inp.y[2]*(1-t)+pow(t,3)*inp.y[3];

        if(t==0.0) // for the initial point 
        {
          // initialize the previous coordinates
          xold=xt; 
          yold=yt;  
        }
        
        t+=0.005;  // increment the parameter
        line(I(xt),I(yt),I(xold),I(yold)); // draw the line that adds up to draw the curve
        if(t>(1+error))  // exit condition
               break;
        // store the previous coordinates
        xold=xt; 
        yold=yt;
        delay(1);  // to hold the present scenario for 1 milliseconds
    }
} // end of function
      
     
