#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int ALLOC_SIZE_INIT = 50;
int fail = 0;

typedef struct dynamicString{
    char* string;
    unsigned int stringLenght;
    unsigned int allocSize;
} dynamicString;

int initString(dynamicString *s){ 
    if (! (s->string = malloc (ALLOC_SIZE_INIT * sizeof(char)))){
        return 1;
    }

    s->allocSize = ALLOC_SIZE_INIT;

    return 0;
}

int addSizeString(dynamicString *s){
    int newSize = s->allocSize + ALLOC_SIZE_INIT;

    if (!(s->string = realloc(s->string, (newSize * sizeof(char))))){
        return 2;
    }

    s->allocSize = newSize;
}

int addCharToString(dynamicString *s, char c){
    if (s->stringLenght + 1 >= s->allocSize){
        fail = addSizeString(&s);
    }

    s->string[s->stringLenght] = c;
    s->stringLenght++;
    s->string[s->stringLenght] = '\0';

    return fail;
}


int main(){

    FILE *sourceCode;
    sourceCode = fopen("test.txt", "r");
    char c;
    dynamicString* s;
    initString(s);
     while(c != ' ')
    {
        c = (char)(getc(sourceCode));
        addCharToString(s, c);
    }

    printf("%s\n", s);

}