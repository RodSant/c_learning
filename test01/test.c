#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char text_sample[] = "This is a test to change {var1} and {var1} with another value, and {var2} with another one";


int bitescmp(const char *text1, const char *text2, int len)
{
    for(int i=0; i < len; i++)
    {
        if(text1[i] != text2[i]) return -1;
    }
    return 1;
}

char *testFunc(const char *source, const char *find, const char *replace)
{
    int sourceLen = (int)strlen(source);
    int findLen = (int)strlen(find);
    int replaceLen = (int)strlen(replace);
    int occurances = 0;

    for(int i=0; i < sourceLen; i++)
    {
        if(bitescmp(&source[i],find, findLen) > 0){
            printf("Found at: %i\n", i);
            i+=findLen-1;
            occurances +=1;
        }
    }

    int newSize = (int)(sizeof(char)*sourceLen + (replaceLen-findLen)*occurances);

    printf("replaceLen: %i\nfindLen: %i\nsourceLen: %i\nnew size: %i\n\n", replaceLen, findLen, sourceLen, newSize);

    char *output = (char*) malloc(sizeof(char)*sourceLen + (replaceLen-findLen)*occurances);

    int countReplaced = 0;

    for(int i=0; i < sourceLen; i++)
    {
        if(bitescmp(&source[i],find, findLen) > 0){
            printf("Replacing at: %i\n",i);
            memcpy(&output[i+(countReplaced*(replaceLen-findLen))],replace,replaceLen);
            i+=findLen-1;
            countReplaced+=1;
        }else{
            output[i+(countReplaced*(replaceLen-findLen))] = source[i];
        }
    }

    return output;
}

int main(){

    char find[] = "{var1}";
    char replace[] = "XXXX123";

    char *output;
    char *output2;

    output = testFunc(text_sample, "{var1}", "XXX123XXXX");
    printf("%s\n", output);
    output2 = testFunc(output, "{var2}", "YY12X");
    printf("%s\n", output2);
    
    return 0;
}