#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


int main(){

    // Initialize Parameters
    int n=4;
    int maxWeight=50;
    int minWeight=0;
    float probabilityOfInfinity=0.50;
    int n_threads=1;


    int A[n][n];
    int inf= maxWeight*n;

    srand(time(NULL));

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if(i==j){
                A[i][i]=0;
                continue;
            }

            A[i][j] = rand()%(maxWeight-minWeight+1) + minWeight;

            if(rand()%1000 < (probabilityOfInfinity*1000)/1){
                A[i][j]=inf;
            }
        }
    }

    printf("INPUT GRAPH:\n");

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if (A[i][j]!= inf){
                printf("%d\t", A[i][j]);
            }
            else{
                printf("inf\t");
            }
        }
        printf("\n");
    }
    printf("\n");

    
    double start_time= omp_get_wtime();

    for(int k=0; k<n; k++){
        #pragma omp parallel for num_threads(n_threads)
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){

                if(A[i][j]==inf && A[k][j]!=inf && A[i][k]!=inf){
                    A[i][j]= A[i][k]+A[k][j];
                }

                if(A[i][j]>A[i][k]+A[k][j] && A[k][j]!=inf && A[i][k]!=inf){
                    A[i][j] = A[i][k]+A[k][j];
                }
            }
        }
    }
    double end_time= omp_get_wtime();

    printf("IF DIAGONAL ELEMENT IS -VE THEN INPUT GRAPH HAS -VE CYCLE\n");
    printf("(Please increase min weight then or manually input graph)\n\n");

    printf("OUTPUT GRAPH:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if (A[i][j]!= inf){
                printf("%d\t", A[i][j]);
            }
            else{
                printf("inf\t");
            }
        }
        printf("\n");
    }

    printf("Time Taken: %f", end_time-start_time);

    printf("\n");
}
