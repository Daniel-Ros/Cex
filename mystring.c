#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <malloc.h>
#include "mystring.h"

void gematriaSeq(char * str,char *wrd)
{
    char *tmp = (char*)malloc((strlen(str) + 10));
    char *currStr = tmp;
    char *lastChecked = str;
    int currGeo = 0;
    int cmp;
    int first = 0;

    cmp = toGematria(wrd);
    while(*str != '~')
    {
        int g = *str;
        if(97 <= g && g <= 122)
            g -= 96;
        else if(65 <= g && g <= 90)
            g -= 64;
        else
            g = 0;

        currGeo += g;
        if(currGeo == 0 && g == 0){
            lastChecked++;
            while (isSpecialCh(*lastChecked) != 0) lastChecked++;
            str = lastChecked;
            continue;
        }

        if(currGeo < cmp)
        {
            *currStr = *str;
            currStr++;
            str++;
        }
        else if(currGeo == cmp)
        {
            *currStr = *str;
            currStr++;
            *currStr = '\0';
            if(first ==0)
            {
                printf("%s",tmp);
                first++;
            }
            else
            {
                printf("~%s",tmp);
            }
            currStr = tmp;
            currGeo = 0;
            lastChecked++;
            while (isSpecialCh(*lastChecked) != 0) lastChecked++;
            str = lastChecked;
        }
        else
        {
            currGeo = 0;
            currStr = tmp;
            lastChecked++;
            while (isSpecialCh(*lastChecked) != 0) lastChecked++;
            str = lastChecked;
        }
    }

    free(tmp);
}

int toGematria(char *str)
{
    int ret = 0;
    while(*str != '\0')
    {
        int g = *str;
        if(97 <= g && g <= 122)
            g -= 96;
        else if(65 <= g && g <= 90)
            g -= 64;
        else
            g = 0;

        ret += g;
        str++;
    }
    return ret;
}


void atbashSeq(char * str,char* cmp)
{
    char *cmp_original = malloc(30);
    char *cmp_reverse= malloc(30);

    char *tmp = (char*)malloc((strlen(str)));
    char *currTmp = tmp;
    char * lastChecked = str;

    int first = 0;
    memcpy(cmp_original,cmp,30);
    memcpy(cmp_reverse,cmp,30);
    toAtbash(cmp,'\0');
    toReverse(cmp_reverse,'\0');
    toAtbash(cmp_reverse,'\0');
    while(*str != '~')
    {
        currTmp = tmp;
        int i = 0;
        for(;i< strlen(cmp) && *str != '~';)
        {
            char c = *str;
            if(isSpecialCh(c) == 0)
            {
                *currTmp = c;
                currTmp++;
                i++;
                str++;
            }
            else{
                str++;
            }
        }
        if(i <= strlen(cmp) -1)
            continue;

        if(strcmp(cmp,tmp) == 0)
        {
            if(first ==0)
            {
                printf("%s",tmp);
                first++;
            }
            else
            {
                printf("~%s",tmp);
            }
        }

        if(strcmp(cmp_reverse,tmp) == 0)
        {
            if(first ==0)
            {
                printf("%s",tmp);
                first++;
            }
            else
            {
                printf("~%s",tmp);
            }
        }

        *currTmp = 0;
        lastChecked++;
        while (isSpecialCh(*lastChecked) != 0) lastChecked++;
        str = lastChecked;
    }

    memcpy(cmp,cmp_original,30);
    free(cmp_original);
    free(cmp_reverse);
    free(tmp);
}


void toAtbash(char* str,char nullTer)
{
    while (*str != nullTer)
    {
        if(97 <= *str && *str <= 122)
        {
            *str = (122 - *str) + 97;
        }
        else if(65 <= *str && *str<= 90)
        {
            *str = (90 - *str) + 65;
        }
        str++;
    }
}

void toReverse(char* str,char nullTer)
{
    char *ret = (char *) malloc(30);
    char *curr = ret;
    int len = strlen(str);

    for (int i = len - 1; i >= 0 ; --i) {
        *curr = *(str+i);
        curr++;
    }

    for (int i = 0; i<len ; ++i) {
        str[i]= ret[i];
    }
    free(ret);
}

void anagramSeq(char *str, char *cmp)
{
    int numbers[129] = {0};
    int cmpnumbers[129];

    getNumOfLetters(cmp,'\0',numbers);
    cpyarr(numbers,cmpnumbers,129);

    char *tmp = (char*)malloc((strlen(str) + 10));
    char *currStr = tmp;

    char *lastChecked = str;

    int first = 0;

    while(*str != '~')
    {
        int g = *str;

        cmpnumbers[g]--;
        if(g != ' ')
            cmpnumbers[26]--;

        if(cmpnumbers[g] == -1 && g != ' '){
            cpyarr(numbers,cmpnumbers,129);
            currStr = tmp;
            lastChecked++;
            while (isSpecialCh(*lastChecked) != 0) lastChecked++;
            str = lastChecked;
        }
        else if(cmpnumbers[26] == 0 && g != ' ')
        {
            *currStr = *str;
            currStr++;
            *currStr = '\0';
            if(first ==0)
            {
                printf("%s",tmp);
                first++;
            }
            else
            {
                printf("~%s",tmp);
            }
            cpyarr(numbers,cmpnumbers,129);
            currStr = tmp;
            lastChecked++;
            while (isSpecialCh(*lastChecked) != 0) lastChecked++;
            str = lastChecked;
        }
        else
        {
            *currStr = *str;
            currStr++;
            str++;
        }
    }
    free(tmp);
}


void getNumOfLetters(char *str,char nullTer,int * ret)
{
    while(*str != nullTer)
    {
        int g = *str;
        ret[g]++;
        ret[26]++;
        str++;
    }
    ret[27] = -2;
}

void cpyarr(int *src,int* dest,int size)
{
    for(int i = 0; i < size;i++){
        dest[i] = src[i];
    }
}

int isSpecialCh(char ch)
{
    if(97 <= ch && ch <= 122)
        return 0;
    else if(65 <= ch && ch <= 90)
        return 0;
    else if(ch =='~')
        return 0;
    else
        return 1;
}