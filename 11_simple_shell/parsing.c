#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS   100

char** parser_string(char* inputString);

int main(void){
    size_t n = 0,readchars = 0;
    char* inputMsg = NULL;
    char** resultStrings = NULL;

    printf("enter the input string: ");
    readchars = getline(&inputMsg,&n,stdin);

    resultStrings = parser_string(inputMsg);
    int i = 0;
    while(resultStrings[i] != NULL){
        printf("parsedstring[%d]: %s\n",i,resultStrings[i]);
        i++;
    }


}

char** parser_string(char* inputString){
    int i,j,k;
    int start,length;
    
    char** parsed_array = (char**)malloc(sizeof(char*) * MAX_WORDS);
    if(parsed_array == NULL){
        puts("malloc()");
        exit(EXIT_FAILURE);
    }
    
    i = j = k = 0;
    
    while(inputString[i] != '\0'){
        while(isspace(inputString[i]))
            i++;
        
        if(inputString[i] == '\0')
            break;
            
        start = i;
        while(inputString[i] != '\0' && !isspace(inputString[i]))
            i++;

        length = i - start;

        parsed_array[j] = (char*)malloc(length + 1);

        for(k = 0;k < length; k++)
            parsed_array[j][k] = inputString[start + k];
        
        parsed_array[j][k] = '\0';

        j++;
    }

    parsed_array[j] = NULL;
    return parsed_array;

}