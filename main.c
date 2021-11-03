#include <stdio.h>
#include "NumClass.h"


int main()
{
    int n1,n2,i=0;
    scanf("%d",&n1);
    scanf("%d",&n2);
    printf("The Armstrong numbers are:");
    for(i=n1;i<=n2;i++){
        if(isArmstrong(i)){
            printf(" %d",i);
        }
    }
    printf("\n");
    printf("The Palindromes are:");
    for(i=n1;i<=n2;i++){
        if(isPalindrome(i)){
            printf(" %d",i);
        }
    }
    printf("\n");
    printf("The Prime numbers are:");
    for(i=n1;i<=n2;i++){
        if(isPrime(i)){
            printf(" %d",i);
        }
    }
    printf("\n");
    printf("The Strong numbers are:");
    for(i=n1;i<=n2;i++){
        if(isStrong(i)){
            printf(" %d",i);
        }
    }
    return 0;
}
