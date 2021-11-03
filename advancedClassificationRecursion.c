#include "NumClass.h"
#include <stdio.h>
#include <math.h>


int getNumLengt(int n){
    return (int)log10(n) +1;
}



int checkArmStorng(int n,int p){
    if(n > 0)
        return (pow(n%10,p) + checkArmStorng(n/10,p));
    else
        return 0;
}

int isPalindromeHelper(int n, int acc){
    if(n == 0)
        return acc;

    acc *= 10;
    acc += n % 10;
    return isPalindromeHelper(n/10,acc);
}

int isArmstrong(int n ){
    if(n == checkArmStorng(n,getNumLengt(n)))
     return 1;
    else
     return 0;
}

int isPalindrome(int n ){
     if(n == isPalindromeHelper(n,0))
         return 1;
    return 0;
}

