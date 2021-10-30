#include "NumClass.h"
int isPrime(int n) {
    int i = 2;
    for(;i < n;i++){
        if(n%i == 0){
            return 0;
        }
    }
    
    return 1;
}

int isStrong(int n){
    int acc = 0,i =0,tmp=n;
    int fac[9];
    for(;i<10;i++){
        int j;
        fac[i] = 1;
        for(j = 2;j<=i;j++){
            fac[i] *= j;
        }
    }
    while(n > 0){
        int d = n % 10;
        acc += fac[d];
        
        n = n / 10;
    }
    if(acc == tmp)
        return 1;
    return 0;
}