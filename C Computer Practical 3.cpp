#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class matrix //brought matrix class over 
{
    int num_rows;
    int num_cols;
    int *elements;

public:
    int get_elem(int i, int j)
    {
        if (i >= 0 && i < num_rows && j >= 0 && j < num_cols)
        {
            return elements[i * num_cols + j];
        }
        else
        {
            printf("Invalid Indices!\n");
        }
    }

    matrix(int nrow, int ncol , int *elem){
        num_rows = nrow;
        num_cols = ncol; 
        elements = elem; 
    }
};

class Problem
{ 
public:
    Problem(){//initialising the constructor
        int nrow = 5 ;
        int ncol = 5 ;
        int nodes[] = {0,1,1,0,0 , 1,0,0,0,0 , 0,0,0,1,1 , 1,1,1,0,1 , 1,0,1,0,0};
        matrix A(nrow,ncol,nodes); // brought matrix class over within the Problem Constructor
    }

    double link(int numpage , double *pagerank)
    {
        int nrow = 5 ;
        int ncol = 5 ;
        int nodes[] = {0,1,1,0,0 , 1,0,0,0,0 , 0,0,0,1,1 , 1,1,1,0,1 , 1,0,1,0,0};
        matrix A(nrow,ncol,nodes);
        //I repeated the same exact code from the Problem constructor as I needed to use get_elem function to extract the "1"s and the "0s" from the nodes array

        double pvalue = 0; 
        for ( int i=0 ; i<5; i++){
            pvalue += ((pagerank[i]) * (A.get_elem(i,numpage))); //counting the p-value at each iteration - (pagerank at each iteration is multiplied with it's respective node)
        }
        return pvalue; 
    } 

    double normalise(int numpage , double *qvalues)
    {
        double sum = 0;
        for (int i=0; i < 5 ; i++) {
            sum += qvalues[i]; //for loop to sum all of the q values
        }
        return ((qvalues[numpage]) / (sum)); //code to normalise the q value 
    }
    
    void solve()
    {
        double oldpagerank[] = {0.2 , 0.2 , 0.2 , 0.2 , 0.2};
        double oldpagerankcompare[5];
        double newpagerank[] = {0.2 , 0.2 , 0.2 , 0.2 ,0.2};
        double newpagerankcompare[] ={0.2,0.2,0.2,0.2,0.2}; 
        double qvalues[5];
        // created "newpagerankcompare" & "oldpagerankcompare" as filler arrays

        for (int k=0 ; k<5 ;k++){
            while(fabs(newpagerankcompare[k] - oldpagerankcompare[k]) > 1e-5){ //setting cutoff-point at each iteration
                for (int k=0 ;k<5 ; k++){
                    oldpagerank[k] = newpagerank[k];
                }

                for (int i=0 ; i<5 ; i++){
                    qvalues[i] = link(i,newpagerank); //qvalues being calculated from the updated pagerank
                }

                for (int j=0 ; j<5 ;j++){
                    newpagerank[j] = normalise(j,qvalues); //qvalues are being normalised and send to newpagerank
                }

                for (int l=0 ; l<5 ;l++){
                    newpagerankcompare[l] = newpagerank[l]; //filler-arrays so that they are updated
                    oldpagerankcompare[l] = oldpagerank[l]; //filler-arrays so that they are updated
                }
            }
        }

        for (int p=0 ; p<5 ; p++){
            printf("The popularity of website %d is %.2f \n", p+1 , newpagerank[p]); 
        }
    }
}; 

int main()
{
    Problem cw3;
    cw3.solve();
}
//output (example):
//0.10 0.10 0.20 0.40 0.20
