#include "NumClass.h"
#include <stdio.h>
#include <math.h>


int checkArmStorng(int n,int p){
    if(n > 0)
        return (pow(n%10,p) + checkArmStorng(n/10,p++));
    else
        return -1;
}

int isPalindromeHelper(){
    return 0;
}

int isArmstrong(int n ){
    if(n == checkArmStorng(n,0))
     return 1;
    else
     return 0;
}

int isPalindrome(int n ){
     return 0;
}

