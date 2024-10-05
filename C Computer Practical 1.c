#include <stdio.h>
#include <math.h>

const double PI = 3.141592653; // declare PI and initialize it with 3.1415926... 

// write plot function below. 
// two inputs, a and b.
// no output. 
int plot(double a, double b){
    printf("Function graph for sin(%2.fx+%2.f)\n\n",a,b);
    for (double i = 1.0; i >= -1.0; i=i-0.2){// this will go through the number i from (1 to -1)
        for (double j = 0.0; j <= 6.2; j=j+0.1){// this will go through the number j from 0 to 6.2 , at which it will exit the loop )
            // this tests if condition is <=0.1. If it is, then it will print * , or else it will leave a blank space. For each iteration of i, once j reaches 6.2 , it will change line and exit the loop.
            if (i>=-0.1 & i<=0.1){//produces - at line 6 for all values of j 
                if (fabs(j-1.6)<=0.05 || fabs(j-0)<=0.05 || fabs(j-3.2)<=0.05 || fabs(j-4.8)<=0.05 ){ //get approximite absolute value of where X value is
                    printf("X");
                }
                else{
                    printf("-");
                }
            }
            else if (j>-0.1 & j<0.1){//prints | at the first instance of j 
                printf("|");
            }
            else if (fabs(sin(a*j+b)-i) <= 0.1){
                printf("*");
            }
            else{
                printf(" ");
            }

            //
    }
    printf("\n"); // change line
}
}
void main(){
    plot(2,1.57);
    // test your plot functions with different a and b. 
    // plot(2, PI/2);
}