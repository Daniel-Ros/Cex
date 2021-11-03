#include "NumClass.h"
#include <stdio.h>
#include <math.h>

int getNumLengt(int n){
    return (int)log10(n) +1;
}

int isArmstrong(int n ){
    int acc =0;
    int tmp = n,nth = 0;
    //calculate how many digits we have
    int length = getNumLengt(n);
    while(n > 0)
    {
        nth++;
        n = n/10;
    }

    n=tmp;
    while(n > 0)
    {
        int d = n % 10;
        acc += pow(d, length);
        n = n/10;
    }
     if(tmp == acc)return 1;
    return 0;
}

int isPalindrome(int n ){
     int arr[10]; // the largest integer in C is 2147483647 which is 10 digit long, So this is enought sapce;
     int i =0,j;
    while(n > 0)
    {
        int d = n % 10;
        arr[i++] = d;
        n = n/10;
    }
    for(j=0;j<i;j++){
            if(arr[j] != arr[i-j-1]) return 0;
    }
    return 1;
}
