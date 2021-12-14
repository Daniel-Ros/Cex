#include "mystring.h"

#include "stdio.h"

#define TXT 1024
#define WORD 30

int main() {
    char word[WORD];
    char *wrdptr = word;
    char text[TXT];
    char *txtptr =text;
    char ch;

    while (ch != ' ' && ch != '\t' && ch !='\n')
    {
        ch = getchar();
        if(ch == ' ' || ch == '\t' || ch =='\n') continue;
        *wrdptr = ch;
        wrdptr++;
    }
    *wrdptr = '\0';

    while (ch != '~')
    {
        ch = getchar();
        *txtptr = ch;
        txtptr++;
    }
    *txtptr = '\0';

    printf("Gematria Sequences: ");
    gematriaSeq(text,word);
    printf("\nAtbash Sequences: ");
    atbashSeq(text,word);
    printf("\nAnagram Sequences: ");
    anagramSeq(text,word);

    return 0;
}
