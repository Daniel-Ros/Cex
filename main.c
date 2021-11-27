#include <stdio.h>
#include "my_mat.h"
int main()
{
    char m;
    do {
        int mat[10][10];
        scanf("%c",&m);
        switch (m) {
            case 'A':
                load_mat(&mat[0]);
                fwa(&mat[0]);
                break;
            case 'B':
                {
                    int a,b;
                    scanf("%d",&a);
                    scanf("%d",&b);
                    if(mat[a][b] == 0){
                        printf("False\n");
                    } else{
                        printf("True\n");
                    }
                }
                break;
            case 'C':
                {
                    int a,b;
                    scanf("%d",&a);
                    scanf("%d",&b);
                    if(mat[a][b]==0){
                        printf("-1\n");
                    }else{
                        printf("%d\n",mat[a][b]);
                    }

                }
                break;
            default:
                break;
        }
    }while(m != 'D');
}
