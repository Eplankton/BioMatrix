//From: Eplankton Date: 2021/8/12
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "function.h"

int main()
{
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);

    printf("\n\033[32;1mBioMatrix\033[0m v0.0.1 %sType 'help()' for manual information.\n", asctime(info)); //System.time & version

    int key = 0, i = 0;
    char userInput[64];

    while (key >= 0)
    {
        for (i = 0; i < 63; i++)
        {
            userInput[i] = '\0';
        }
        i = 0;

        printf("\n\033[33;1m>> \033[0m");
        scanf("%s", userInput);
        key = search(userInput);

        switch (key)
        {
        case 1:
            test();
            key = 0;
            break;
        case 2:
            help();
            key = 0;
            break;
        case 3:
            clear();
            key = 0;
            break;
        case 4:
            matrixInput(userInput);
            key = 0;
            break;
        case 5:
            matrixDetect(userInput);
            key = 0;
            break;
        case 6:
            matrixAdd(userInput);
            key = 0;
            break;
        case 7:
            matrixMinus(userInput);
            key = 0;
            break;
        case 8:
            matrixMulti(userInput);
            key = 0;
            break;
        case 9:
            matrixTran(userInput);
            key = 0;
            break;
        case 10:
            matrixScal(userInput);
            key = 0;
            break;
        case 11:
            matrixDet(userInput);
            key = 0;
            break;
        case 12:
            matrixInverse(userInput);
            key = 0;
            //Add cases here.

        case 0: //Confirm the order {search()}
            while (getchar() != '\n')
                ;
            break;

        case -1: //Exit the process(-1) {exit() & quit()}
            break;
        }
    }

    return 0;
}
