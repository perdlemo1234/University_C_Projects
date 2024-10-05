#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

struct matrix
{
    int numrow;
    int numcol;
    int *elements;
};
typedef struct matrix Matrix;

void image2char(int image[], int Height, int Width)
{
    for (int i=0 ; i< Height; i++){
        for (int k=0 ; k < Width; k++){
            if (image[i*Width+k]<=85){
                printf(" ");
            }
            else if(85 < image[i*Width+k] <= 170){
                printf("I");
            }
            else{
                printf("M");
            }
        }
        printf("\n");
    }
}

/*
Read a matrix from file. Don't change it!
filename: the file that contains the matrix.
return: a matrix structure containing the matrix.
*/
Matrix read_matrix(char *filename)
{
    FILE *f = fopen(filename, "rb");
    // read int variables to the file.
    int numrow = getw(f);
    int numcol = getw(f);
    Matrix M = {numrow, numcol, calloc(numrow * numcol, sizeof(int))};

    for (int i = 0; i < M.numrow; i++)
    {
        for (int j = 0; j < M.numcol; j++)
        {
            M.elements[i*numcol + j] = getc(f);
        }
    }

    fclose(f);
    return M;
}

int get_elem(Matrix M, int i, int j)
{
    return M.elements[i*M.numcol + j];
}

void set_elem(Matrix M, int i, int j, int value)
{
    M.elements[i*M.numcol + j] = value;
}

/*
Compute the pairwise squared distance of the i-th row of M1 and the j-th row of M2.
M1: the first matrix.
M2: the second matrix.
return: a matrix D where D_ij is the squared distance between the i-th row of M1 and the j-th row of M2.
*/
void pairwise_dist2(Matrix T, Matrix X, Matrix D)
{
    if ((T.numcol) == (X.numcol) && (D.numrow) == (T.numrow) && (D.numcol) == (X.numrow)){ //checks if the size of matrix for M1, M2 & D are suitable ; if not, exit the line of code...
        for (int i=0 ; i < T.numrow ; i++) {
            for ( int j = 0 ; j < X.numrow ; j++){
                double squared_distance = 0;
                for ( int k=0 ; k<T.numcol ;k++){ //the paramter being changed here is k, which changes for column of M1 & rows for M2
                    squared_distance = squared_distance + (get_elem(T,i,k)-get_elem(X,j,k))*(get_elem(T,i,k)-get_elem(X,j,k));
                }
                D.elements[i*D.numcol + j] = squared_distance;
            }
        }
    }
    else{
        printf("Not Valid!");
        exit(0);
    }
}
/*
Find the index of the minimum element in an array. 
a: the array.
len: the length of the array.
return: the index of the minimum element in the array.
example: [1,2,3,4,5] -> 0
         [5,4,3,2,1] -> 4
*/
int find_min_index(int a[], int len)
{
    int min_value = a[0]; 
    int min_index = 0; 
    for (int i= 0 ; i<len ; i++){
        if (a[i]<min_value){
            min_value = a[i]; 
            min_index = i; 
        }
    }
    return min_index; 
}
/*
Find the indices of 5 minimum elements in an array.
a: the array.
len: the length of the array.
return: an array of 5 integers containing the indices of the 5 minimum elements in a.
example: [1,2,33,4,5,23,6] -> [0,1,3,4,6]
*/
void minimum5(int a[], int len, int indices[])
{
    for (int i=0;i<5;i++){ 
        indices[i] = find_min_index(a,len);
        a[find_min_index(a,len)]=INT_MAX; //assign the minimum value to the maximum possible value so that function loops through and find the (n-1) smallest number
    }
}
        
void main()
{
    // 10% for submitting the correct code.
    Matrix X = read_matrix("./X.matrix");
    printf("N: %d, M: %d\n", X.numrow, (int) sqrt(X.numcol));   

    Matrix T = read_matrix("./T.matrix");
    printf("L: %d\n", T.numrow);

    Matrix Y = read_matrix("./Y.matrix");
    int s = 0;
    for (int i = 0; i < Y.numrow; i++)
    {
        if(Y.elements[i*Y.numcol + 0] == 1)
            s++;
    }
    printf("Number of 1 in the training set: %d\n", s);

    //TODO: construct the matrix D, where D_ij is the squared distance between the i-th row of T and the j-th row of X.
    // 40% of the total score.
    // 15% for the helper functions.
    // 25% for the pairwise_dist2 function.

    int *array = malloc(T.numrow*X.numrow*sizeof(int));
    struct matrix D ={T.numrow,X.numrow,array}; // set an array for matrix D
    pairwise_dist2(T,X,D);

    for(int i=0; i<T.numrow; i++){ 
        printf("The %d-th testing image:\n", i);
        int HEIGHT = sqrt(T.numcol); 
        int WIDTH = sqrt(T.numcol); //since each row of T has ALL the elements of a test image , so square root is the number of columns and rows 
        int b[T.numcol];
        for (int r=0;r<T.numcol;r++){
            b[r] = get_elem(T,i,r);
        }
        image2char(b, HEIGHT, WIDTH);

        //TODO: find the indices of the 5 smallest elements in the i-th row of D.
        // 15% of the total score.
        int indices[5];    //Set the array for length 5
        int a[X.numrow];   //Set array a to length of numcol
        for (int j=0; j<X.numrow; j++){ //Get the elements from row i of D to array a
            a[j] = get_elem(D,i,j);
        }

        int labels[5]; 
        for (int k=0; k<5 ;k++){
            minimum5(a,X.numrow,indices); //calls function to get array indices
            labels[k] = Y.elements[indices[k]]; //finding the value of the element corresponding to its indices(the value) 
            printf("%d\t",indices[k]); 
        }


        int count=0; 
        for (int l=0; l<5 ;l++){
            if (labels[l] == 1){
                count = count +1;
            }
        }
        if (count>=3){//conditions to check if labels has more than or equals to "1" elements 
            printf("The %d-th testing image is classified as %d", i, 1);
        }           
        else{
            printf("The %d-th testing image is classified as not 1", i);
        }

        // 15% of the total score.
        printf("\n");
        printf("----------------------------------------\n");
    
    }
    // did you free the memory that allocated in your program?
    // - 5% for every missing free.
    free(X.elements);
    free(T.elements);
    free(Y.elements);
    free(array); 
}