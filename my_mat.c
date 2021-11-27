#include "my_mat.h"
#include <stdio.h>
void load_mat(int mat[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int d;
            scanf("%d", &d);
            mat[i][j] = d;
        }
    }
}

int min(int a,int b){
    if(a == 0){
        return b;
    }else if(b == 0){
        return a;
    } else if(a > b){
        return b;
    } else{
        return a;
    }

}

void fwa(int mat[][N]) {
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if(i==j){
                    mat[i][j] = 0;
                }else if (mat[i][k] != 0 && mat[k][j] != 0 && mat[i][j] > mat[i][k] + mat[k][j] ) {
                    mat[i][j] = mat[i][k] + mat[k][j];
                }else if(mat[i][k] != 0 && mat[k][j] != 0 && mat[i][j] ==0){
                    mat[i][j] = mat[i][k] + mat[k][j];
                }
            }
        }
    }
}