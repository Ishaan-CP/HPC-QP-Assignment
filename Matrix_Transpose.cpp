#include <iostream>
#include <omp.h>
using namespace std;

int main(int argc, char** argv){
    int matrix_size = atoi(argv[1]);
    int** matrix = (int**)malloc(sizeof(int*) * matrix_size);
    for(int i = 0; i < matrix_size; i++){
        matrix[i] = (int*)malloc(sizeof(int) * matrix_size);
    }
    for(int i = 0; i < matrix_size; i++){
        for(int j = 0; j < matrix_size; j++){
            matrix[i][j] = rand() % 10;
        }
    }

    cout<<"Original Matrix: "<<endl;
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    #pragma omp parallel for collapse(2) num_threads(matrix_size*matrix_size/2)
    for (int i = 0; i < matrix_size; i++)
    {
        for(int j = i+1; j<matrix_size; j++){
            matrix[i][j] = matrix[i][j]+matrix[j][i];
            matrix[j][i] = matrix[i][j]-matrix[j][i];
            matrix[i][j] = matrix[i][j]-matrix[j][i];
        }
    }
    
    cout<<"Transpose Matrix: "<<endl;
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}