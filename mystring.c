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

    char * beg = cmp;
    char * currBeg = beg;
    char * end = cmp + strlen(cmp) - 1;
    char * currEnd = cmp + strlen(cmp) - 1;

    char *tmpBeg = (char*)malloc((strlen(str)));
    char *currentTmpBeg = tmpBeg;

    char *tmpEnd = (char*)malloc((strlen(str)));
    char *currentTmpEnd = tmpEnd;

    int first = 0;
    memcpy(cmp_original,cmp,30);
    toAtbash(cmp,'\0');

    while(*str != '~')
    {
        if(*str == ' ' && currBeg != beg)
        {
            *currentTmpBeg = *str;
            currentTmpBeg++;
        }
        else if (*currBeg == *str){
            *currentTmpBeg = *str;
            currentTmpBeg++;
            currBeg++;
        }
        else
        {
            currBeg = beg;
            currentTmpBeg = tmpBeg;
        }

        if(currBeg == end + 1)
        {
            currBeg = beg;
            if(first ==0)
            {
                printf("%s",tmpBeg);
                first++;
            }
            else
            {
                printf("~%s",tmpBeg);
            }
        }
        //inverted
        if(*str == ' ' && currEnd != end)
        {
            *currentTmpEnd = *str;
            currentTmpEnd++;
        }
        else if (*currEnd == *str){
            *currentTmpEnd = *str;
            currentTmpEnd++;
            currEnd--;
        }
        else
        {
            currEnd = end;
            currentTmpEnd = tmpEnd;
        }

        if(currEnd == beg - 1)
        {
            currEnd = end;
            if(first ==0)
            {
                printf("%s",tmpEnd);
                first++;
            }
            else
            {
                printf("~%s",tmpEnd);
            }
        }


        str++;
    }

    memcpy(cmp,cmp_original,30);
    free(cmp_original);
    free(tmpBeg);
    free(tmpEnd);

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