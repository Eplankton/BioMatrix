//From: Eplankton Date: 2021/8/12(Start date)
const char version[] = "1.0.7";
const char *user_sign = ">>";

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "extension.h"
#include "function.h"

int main()
{
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);

    printf("\n\033[32;1mBiomatrix\033[0m %s \n%sType 'help()' for Manual.\n", version, asctime(info)); //System.time & version

    int key = 0, i;
    char userInput[64];

    while (key >= 0)
    {
        memset(userInput, '\0', 64 * sizeof(char));
        i = 0;
        key = 0;

        printf("\n\033[33;1m%s \033[0m", user_sign);
        scanf("%s", userInput);
        key = search(userInput);

        switch (key)
        {
        case 1:
            test();
            break;
        case 2:
            help();
            break;
        case 3:
            clear();
            break;
        case 4:
            matrixInput(userInput);
            break;
        case 5:
            matrixShow(userInput);
            break;
        case 6:
            matrixAdd(userInput);
            break;
        case 7:
            matrixMinus(userInput);
            break;
        case 8:
            matrixMulti(userInput);
            break;
        case 9:
            matrixTran(userInput);
            break;
        case 10:
            matrixScale(userInput);
            break;
        case 11:
            matrixDet(userInput);
            break;
        case 12:
            matrixInv(userInput);
            break;
        case 13:
            vectorDot(userInput);
            break;
        case 14:
            vectorCross(userInput);
            break;
        case 15:
            vectorMag(userInput);
            break;
        case 16:
            vectorAngle(userInput);
            break;
        case 17:
            vectorI0(userInput);
            break;
        case 18:
            vectorN0(userInput);
            break;
        case 19:
            matrixDelete(userInput);
            break;
        case 20:
            valueDelete(userInput);
            break;
        case 21:
            matrixApproximate(userInput);
            break;
        case 22:
            matrixRank(userInput);
            break;
        case 23:
            matrixEchelon(userInput);
            break;
            //Add cases here.
        case 0: //Confirm the order.
            while (getchar() != '\n')
                ;
            break;
        case -1: //Exit the process(-1) {exit() & quit()}
            break;
        case 101:
            fileDelete(userInput);
            break;
        }
    }

    return 0;
}