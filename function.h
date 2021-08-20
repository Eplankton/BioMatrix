//From: Eplankton Date: 2021/8/12
struct matrix
{
    char *name;
    int row;
    int column;
};

int search(char *);                           //Compare userInput with the list of command.(0)
void test();                                  //A test process.(1)
void help();                                  //Help manual.(2)
void clear();                                 //Clear the screen.(3)
void matrixInput(char *);                     //To input a matrix.(4)
void matrixDetect(char *);                    //To detect a matrix.(5)
void matrixExtract(struct matrix *, float *); //To import a matrix from 'matrixstream'.
int matrixEmploy(struct matrix *);            //To confirm a matrix and return its name/row/column.
void matrixAdd(char *);                       //To add two matrixes together.(6)
void matrixMinus(char *);                     //To minus two matrixes.(7)
void matrixMulti(char *);                     //To multiply two matrixes together.(8)
void matrixTran(char *);                      //To transpose a matrix.(9)
void matrixScal(char *);                      //To scalar multiplay a matrix.(10)
void matrixDet(char *);                       //To get the Det(matrix) under 3x3.(11)
float Det(struct matrix *, float *);          //To get the Det(matrix) under 3x3.
void matrixInverse(char *);

int search(char *userInput)
{
    int i = 0, note = 0, len = 0, check = 0;
    FILE *fp = NULL;
    char buff[64];
    char copy[64];
    char temp[64];
    for (i = 0; i < 63; i++)
    {
        temp[i] = '\0';
        copy[i] = '\0';
        buff[i] = '\0';
    }
    i = 0;

    fp = fopen("command_list", "r");

    if (strchr(userInput, ')') == NULL || strchr(userInput, '(') == NULL)
    {
        printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m LOST_()?\033[0m\n");
    }
    else
    {
        if (userInput[0] != '\0')
        {
            while (userInput[i] != '(')
            {
                temp[i] = userInput[i];
                i++;
            }
            const char t[2] = "(";
            strcat(temp, t);
            len = strlen(temp);

            while (strcmp(buff, "END") != 0 && check == 0)
            {
                fgets(buff, 64, (FILE *)fp);

                if (strncmp(buff, temp, len) == 0) //Whether userInput is a command or not.
                {
                    check = 1;
                    for (i = 0; i < 63; i++)
                    {
                        copy[i] = buff[i];
                    }
                }
            }
        }
    }

    if (check == 0)
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m Command_NotFound\033[0m\n");
    }
    else
    {
        char *token;
        token = strchr(copy, '#') + sizeof(char);
        note = atoi(token);
    }
    for (i = 0; i < 63; i++)
    {
        temp[i] = '\0';
        copy[i] = '\0';
        buff[i] = '\0';
    }
    fclose(fp);
    return note;
}

void test()
{
    printf("\n[\033[32;1mSuccess\033[0m]\033[36;1m BioMatrix\033[0m (v0.0.1) is running on your environment !\n");
}

void help()
{
    int i = 0;
    FILE *fp = NULL;
    char buff[128];
    fp = fopen("help", "r");

    while (strcmp(buff, "END") != 0)
    {
        fgets(buff, 128, (FILE *)fp);
        printf("\n\033[37m  %s\033\n", buff);
    }
}

void clear()
{
    printf("\33[2J");
    printf("\33[100A");
}

void matrixInput(char *userInput)
{
    FILE *fp = NULL;
    fp = fopen("matrix", "a+");
    int i = 0, j = 0, row = 0, column = 0, cnt = 0, len = 0;
    const char cut[2] = ",";
    const char cap[2] = "(";
    char *token;
    char *matrixName;
    char buff[64];
    for (i = 0; i < 63; i++)
    {
        if (userInput[i] == ',')
        {
            cnt++;
        }
    }
    i = 0;
    if (cnt == 2)
    {
        token = strtok(userInput, cut);
        matrixName = strchr(token, '(') + sizeof(char);

        while (token != NULL && j < 2)
        {
            switch (j)
            {
            case 0:

                token = strtok(NULL, cut);
                row = atoi(token);

                break;
            case 1:

                token = strtok(NULL, cut);
                column = atoi(token);

                break;
            }
            j++;
        }

        int check = 0;

        if (row != 0 && column != 0 && matrixName[0] != ')')
        {

            char bach[strlen(matrixName) + 2];

            for (i = 0; i <= strlen(matrixName) + 1; i++)
            {
                bach[i] = '\0';
            }

            for (i = 0; i < strlen(matrixName) + 1; i++)
            {
                bach[i] = matrixName[i];
            }

            bach[strlen(matrixName)] = '<';
            bach[strlen(matrixName) + 1] = '\0';

            while (!feof(fp) && check == 0)
            {
                fgets(buff, 64, (FILE *)fp);
                len = strlen(bach);
                if (strncmp(buff, bach, len) == 0 && check == 0) //Whether userInput is a useable matrixName.
                {
                    printf("\n[\033[31;1mError\033[0m]:\033[31;1m Matrix Existed\033[0m \033[33;1m<~ %s\033[0m\n", strtok(matrixName, ")"));
                    check = 1;
                }
            }

            float save[row][column];
            float *r = &save[0][0];
            int m = 0, n = 0, i = 0;

            if (check != 0)
            {
                fclose(fp);
                fp = fopen("matrix", "r");

                while (!feof(fp) && check != 0)
                {
                    fgets(buff, 64, (FILE *)fp);
                    len = strlen(bach);
                    if (strncmp(buff, bach, len) == 0 && check == 0)
                    {
                        printf("\n\033[31;1mHere:\033[0m\n\n");
                        check = 0;
                        while (strchr(buff, '#') == NULL)
                        {
                            printf("\033[37;1m%s\033[0m", buff);
                            fgets(buff, 64, (FILE *)fp);
                        }
                    }
                }
            }
            else
            {
                printf("\n[\033[32;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n\n", matrixName, row, column);
                for (i = 0; i < row; i++)
                {
                    for (j = 0; j < column; j++)
                    {
                        save[i][j] = 0;
                    }
                }

                for (m = 0; m < row; m++)
                {
                    for (n = 0; n < column; n++)
                    {
                        printf(" %g ", save[m][n]);
                    }
                    printf("\n");
                }

                for (i = 0; i < row; i++)
                {
                    for (j = 0; j < column; j++)
                    {
                        printf("\nThe row(%d)column(%d) = ", i + 1, j + 1);

                        scanf("%g", &save[i][j]);

                        *r++ = save[i][j]; //Output the matrix

                        printf("\n");

                        for (m = 0; m < row; m++)
                        {
                            for (n = 0; n < column; n++)
                            {
                                if (m == i && n == j)
                                {
                                    printf("\033[33;1m %g \033[0m", save[m][n]);
                                }
                                else
                                {
                                    printf(" %g ", save[m][n]);
                                }
                            }
                            printf("\n");
                        }
                    }
                    printf("\n");
                }

                printf("\n[\033[32;1mMatrix\033[0m]: \033[33;1m%s\033[0m <\033[37;1m %d\033[0m,\033[37;1m %d\033[0m > has been saved.\n\n", matrixName, row, column);

                for (i = 0; i < row; i++)
                {
                    for (j = 0; j < column; j++)
                    {
                        if (j != 0)
                            printf("\033[37;1m %g \033[0m", save[i][j]);
                        else
                            printf("\033[37;1m[ %g \033[0m", save[i][j]);
                    }
                    printf("\033[37;1m]\033[0m\n");
                }

                fprintf(fp, "\n%s<%d,%d>\n", matrixName, row, column);
                for (i = 0; i < row; i++)
                {
                    for (j = 0; j < column; j++)
                    {
                        if (j == column - 1)
                            fprintf(fp, "%g\n", save[i][j]);
                        else
                            fprintf(fp, "%g ", save[i][j]);
                    }
                }
                fprintf(fp, "#\n");

                FILE *fstream = NULL;
                fstream = fopen("matrixstream", "a+");
                fprintf(fstream, "\n%s<%d,%d>\n", matrixName, row, column);
                for (i = 0; i < row; i++)
                {
                    for (j = 0; j < column; j++)
                    {
                        fprintf(fstream, "%g\n", save[i][j]);
                    }
                }
                fprintf(fstream, "#\n");
                fclose(fstream);
            }
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
    }
    fclose(fp);
}

void matrixDetect(char *userInput)
{
    FILE *fp = NULL;
    fp = fopen("matrix", "r");
    if (fp != NULL)
    {
        char buff[64];
        char *prov;
        char *matrixName;
        int check = 0;
        matrixName = strchr(userInput, '(') + sizeof(char); //userInput as 'matrixInput(test)', matrixName = "test"
        matrixName[strlen(matrixName) - 1] = '<';

        if (strlen(matrixName) != 0)
        {
            fclose(fp);
            fp = fopen("matrix", "r");

            int len = 0;
            while (!feof(fp) && check == 0)
            {
                fgets(buff, 64, (FILE *)fp);
                len = strlen(matrixName);
                if (strncmp(buff, matrixName, len) == 0 && check == 0)
                {
                    printf("\n\033[34;1mHere:\033[0m\n");
                    check = 1;
                    while (strchr(buff, '#') == NULL)
                    {
                        printf("\033[37;1m%s\033[0m", buff);
                        fgets(buff, 64, (FILE *)fp);
                    }
                }
            }
            if (check == 0)
            {
                matrixName[strlen(matrixName) - 1] = '\0';
                printf("\n[\033[31;1mError\033[0m]:\033[31;1m Matrix Not_Found\033[0m \033[33;1m <~ %s\033[0m\n", matrixName);
            }
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
        }

        fclose(fp);
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m No matrix exists\033[0m\n");
    }
}

void matrixExtract(struct matrix *f, float *array)
{
    FILE *fstream = NULL;
    fstream = fopen("matrixstream", "r");
    char buff[64];
    int k = 0;
    for (k = 0; k < 63; k++)
    {
        buff[k] = '\0';
    }
    char *matrixName;
    int check = 0, number = 0;
    matrixName = f->name;

    if (matrixName[0] != '\0')
    {
        fclose(fstream);
        fstream = fopen("matrixstream", "r");

        int len = 0;
        len = strlen(matrixName);

        while (!feof(fstream) && check == 0)
        {
            fgets(buff, 32, (FILE *)fstream);
            if (strncmp(buff, matrixName, len) == 0 && check == 0)
            {
                check = 1;
                while (strchr(buff, '#') == NULL && number != (f->row) * (f->column))
                {
                    int i = 0, j = 0;

                    if (number != (f->row) * (f->column))
                    {
                        for (i = 0; i < f->row; i++)
                        {
                            for (j = 0; j < f->column; j++)
                            {
                                fscanf(fstream, "%g", array);
                                for (k = 0; k < 31; k++)
                                {
                                    buff[k] = '\0';
                                }
                                k = 0;
                                fgets(buff, 32, (FILE *)fstream);
                                array++;
                                number++;
                            }
                        }
                    }
                }
            }
            for (k = 0; k < 31; k++)
            {
                buff[k] = '\0';
            }
        }
        if (check == 0)
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Matrix Not_Found\033[0m \033[33;1m <~ %s\033[0m\n", matrixName);
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
    }

    fclose(fstream);
}

int matrixEmploy(struct matrix *f)
{
    FILE *fp = NULL;
    fp = fopen("matrix", "r");
    char buff[32];
    int k = 0;
    for (k = 0; k < 31; k++)
    {
        buff[k] = '\0';
    }
    char *matrixName;
    char *token;
    char *temp;
    int check = 0, i = 0, j = 0;
    matrixName = f->name;
    char prov[strlen(matrixName) + 2];

    for (i = 0; i <= strlen(matrixName) + 1; i++)
    {
        prov[i] = '0';
    }

    for (i = 0; i < strlen(matrixName) + 1; i++)
    {
        prov[i] = matrixName[i];
    }

    prov[strlen(matrixName)] = '<';
    prov[strlen(matrixName) + 1] = '\0'; //A new way to detect matrixName without using strtok()

    if (matrixName != 0)
    {
        fclose(fp);
        fp = fopen("matrix", "r");

        while (!feof(fp) && check == 0)
        {
            fgets(buff, 32, (FILE *)fp);
            int len = strlen(prov);
            if (strncmp(buff, prov, len) == 0 && check == 0)
            {
                check = 1;
                token = strtok(buff, ",");
                temp = strchr(token, '<') + 1;
                token = strtok(NULL, ",");
                f->row = atoi(temp);
                f->column = atoi(token);
            }
        }
        if (check == 0)
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Matrix Not_Found\033[0m \033[33;1m <~ %s\033[0m\n", matrixName);
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
    }

    fclose(fp);
    return check;
}

void matrixAdd(char *userInput)
{
    struct matrix former;
    struct matrix latter;
    struct matrix result;

    struct matrix *p = &former;
    struct matrix *q = &latter;

    int cnt = 0, k = 0;
    for (k = 0; k < 63; k++)
    {
        if (userInput[k] == ',')
        {
            cnt++;
        }
    }
    k = 0;

    FILE *fp = NULL;
    fp = fopen("matrix", "r+");
    if (fp == NULL)
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m No matrix exists\033[0m\n");
    }
    else
    {
        int len = 0, j = 0, check = 0;
        const char cut[2] = ",";
        const char cap[2] = "(";
        char *token;
        char buff[64];

        token = strtok(userInput, cut);

        former.name = strchr(token, '(') + sizeof(char);

        while (token != NULL && j < 2 && fp != NULL && cnt == 2)
        {
            switch (j)
            {
            case 0:
                token = strtok(NULL, cut);
                latter.name = token;
                break;
            case 1:
                token = strtok(NULL, cut);
                if (strlen(token) == 0)
                {
                    printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name_invalid\033[0m\n");
                }
                else
                {
                    int i = 0;
                    result.name = token;
                    result.name[strlen(token) - 1] = '\0';

                    char bach[strlen(result.name) + 2];

                    for (i = 0; i <= strlen(result.name) + 1; i++)
                    {
                        bach[i] = '0';
                    }

                    for (i = 0; i < strlen(result.name) + 1; i++)
                    {
                        bach[i] = result.name[i];
                    }

                    bach[strlen(result.name)] = '<';
                    bach[strlen(result.name) + 1] = '\0';

                    while (!feof(fp) && check == 0)
                    {
                        fgets(buff, 64, (FILE *)fp);
                        len = strlen(bach);
                        if (strncmp(buff, bach, len) == 0 && check == 0) //Whether userInput is a useable matrixName.
                        {
                            printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name existed\033[0m \033[33;1m<~ %s\033[0m\n", result.name);
                            check = 1;
                        }
                    }
                }

                break;
            }
            j++;
        }

        if (token != 0 && check == 0 && cnt == 2)
        {
            int i = 0, j = 0;

            int check_former = matrixEmploy(p);
            int check_latter = matrixEmploy(q);

            if (check_former != 0 && check_latter != 0)
            {
                if (former.row == latter.row && former.column == latter.column)
                {
                    float matrixfirst[former.row][former.column];
                    float matrixsecond[latter.row][latter.column];
                    float *arone = &matrixfirst[0][0];
                    float *artwo = &matrixsecond[0][0];

                    matrixExtract(p, arone);
                    matrixExtract(q, artwo);

                    printf("\n[\033[34;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", former.name, former.row, former.column);
                    for (i = 0; i < former.row; i++)
                    {
                        for (j = 0; j < former.column; j++)
                        {
                            if (j != 0)
                                printf(" %g ", matrixfirst[i][j]);
                            else
                                printf("[ %g ", matrixfirst[i][j]);
                        }
                        printf("]\n");
                    }
                    printf("\n[\033[34;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", latter.name, latter.row, latter.column);
                    for (i = 0; i < latter.row; i++)
                    {
                        for (j = 0; j < latter.column; j++)
                        {
                            if (j != 0)
                                printf(" %g ", matrixsecond[i][j]);
                            else
                                printf("[ %g ", matrixsecond[i][j]);
                        }
                        printf("]\n");
                    }

                    result.row = former.row;
                    result.column = former.column;
                    float matrixAns[former.row][latter.column];

                    printf("\n[\033[32;1mMatrix\033[0m]: \033[33;1m%s\033[0m <\033[37;1m %d\033[0m,\033[37;1m %d\033[0m > has been saved.\n", result.name, result.row, result.column);

                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            matrixAns[i][j] = matrixfirst[i][j] + matrixsecond[i][j];
                        }
                    }

                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            if (j != 0)
                                printf(" %g ", matrixAns[i][j]);
                            else
                                printf("[ %g ", matrixAns[i][j]);
                        }
                        printf("]\n");
                    }

                    fprintf(fp, "\n%s<%d,%d>\n", result.name, result.row, result.column);

                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            if (j == result.column - 1)
                                fprintf(fp, "%g\n", matrixAns[i][j]);
                            else
                                fprintf(fp, "%g ", matrixAns[i][j]);
                        }
                    }
                    fprintf(fp, "#\n");

                    FILE *fstream = NULL;
                    fstream = fopen("matrixstream", "a+");
                    fprintf(fstream, "\n%s<%d,%d>\n", result.name, result.row, result.column);
                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            fprintf(fstream, "%g\n", matrixAns[i][j]);
                        }
                    }
                    fprintf(fstream, "#\n");
                    fclose(fstream);
                }
                else
                {
                    printf("\n[\033[31;1mError\033[0m]:\033[31;1m row/column not equal\033[0m\n");
                }
            }
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
            printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> matrixAdd(A,B,result)\033[0m\n");
        }
        fclose(fp);
    }
}

void matrixMinus(char *userInput)
{
    struct matrix former;
    struct matrix latter;
    struct matrix result;

    struct matrix *p = &former;
    struct matrix *q = &latter;

    int len = 0, cnt = 0, k = 0;
    for (k = 0; k < 63; k++)
    {
        if (userInput[k] == ',')
        {
            cnt++;
        }
    }
    k = 0;

    FILE *fp = NULL;
    fp = fopen("matrix", "r+");
    if (fp == NULL)
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m No matrix exists\033[0m\n");
    }
    else
    {
        int j = 0, check = 0;
        const char cut[2] = ",";
        const char cap[2] = "(";
        char *token;
        char buff[64];

        token = strtok(userInput, cut);

        former.name = strchr(token, '(') + sizeof(char);

        while (token != NULL && j < 2 && cnt == 2)
        {
            switch (j)
            {
            case 0:
                token = strtok(NULL, cut);
                latter.name = token;
                break;
            case 1:
                token = strtok(NULL, cut);
                if (token == 0)
                {
                    printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name_invalid\033[0m\n");
                }
                else
                {
                    int i = 0;
                    result.name = token;
                    result.name[strlen(token) - 1] = '\0';

                    char bach[strlen(result.name) + 2];

                    for (i = 0; i <= strlen(result.name) + 1; i++)
                    {
                        bach[i] = '0';
                    }

                    for (i = 0; i < strlen(result.name) + 1; i++)
                    {
                        bach[i] = result.name[i];
                    }

                    bach[strlen(result.name)] = '<';
                    bach[strlen(result.name) + 1] = '\0';

                    while (!feof(fp) && check == 0)
                    {
                        fgets(buff, 64, (FILE *)fp);
                        len = strlen(bach);
                        if (strncmp(buff, bach, len) == 0 && check == 0) //Whether userInput is a useable matrixName.
                        {
                            printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name existed\033[0m \033[33;1m<~ %s\033[0m\n", result.name);
                            check = 1;
                        }
                    }
                }

                break;
            }
            j++;
        }

        if (token != 0 && check == 0 && cnt == 2)
        {
            int i = 0, j = 0;

            int check_former = matrixEmploy(p);
            int check_latter = matrixEmploy(q);

            if (check_former != 0 && check_latter != 0)
            {
                if (former.row == latter.row && former.column == latter.column)
                {
                    float matrixfirst[former.row][former.column];
                    float matrixsecond[latter.row][latter.column];
                    float *arone = &matrixfirst[0][0];
                    float *artwo = &matrixsecond[0][0];

                    matrixExtract(p, arone);
                    matrixExtract(q, artwo);

                    printf("\n[\033[34;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", former.name, former.row, former.column);
                    for (i = 0; i < former.row; i++)
                    {
                        for (j = 0; j < former.column; j++)
                        {
                            if (j != 0)
                                printf(" %g ", matrixfirst[i][j]);
                            else
                                printf("[ %g ", matrixfirst[i][j]);
                        }
                        printf("]\n");
                    }
                    printf("\n[\033[34;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", latter.name, latter.row, latter.column);
                    for (i = 0; i < latter.row; i++)
                    {
                        for (j = 0; j < latter.column; j++)
                        {
                            if (j != 0)
                                printf(" %g ", matrixsecond[i][j]);
                            else
                                printf("[ %g ", matrixsecond[i][j]);
                        }
                        printf("]\n");
                    }

                    result.row = former.row;
                    result.column = former.column;
                    float matrixAns[former.row][latter.column];

                    printf("\n[\033[32;1mMatrix\033[0m]: \033[33;1m%s\033[0m <\033[37;1m %d\033[0m,\033[37;1m %d\033[0m > has been saved.\n", result.name, result.row, result.column);

                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            matrixAns[i][j] = matrixfirst[i][j] - matrixsecond[i][j];
                        }
                    }

                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            if (j != 0)
                                printf(" %g ", matrixAns[i][j]);
                            else
                                printf("[ %g ", matrixAns[i][j]);
                        }
                        printf("]\n");
                    }

                    fprintf(fp, "\n%s<%d,%d>\n", result.name, result.row, result.column);

                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            if (j == result.column - 1)
                                fprintf(fp, "%g\n", matrixAns[i][j]);
                            else
                                fprintf(fp, "%g ", matrixAns[i][j]);
                        }
                    }
                    fprintf(fp, "#\n");

                    FILE *fstream = NULL;
                    fstream = fopen("matrixstream", "a+");
                    fprintf(fstream, "\n%s<%d,%d>\n", result.name, result.row, result.column);
                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            fprintf(fstream, "%g\n", matrixAns[i][j]);
                        }
                    }
                    fprintf(fstream, "#\n");
                    fclose(fstream);
                }
                else
                {
                    printf("\n[\033[31;1mError\033[0m]:\033[31;1m row/column not equal\033[0m\n");
                }
            }
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
            printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> matrixMinus(A,B,result)\033[0m\n");
        }
        fclose(fp);
    }
}

void matrixMulti(char *userInput)
{
    struct matrix former;
    struct matrix latter;
    struct matrix result;

    struct matrix *p = &former;
    struct matrix *q = &latter;

    int len = 0, cnt = 0, k = 0;
    for (k = 0; k < 63; k++)
    {
        if (userInput[k] == ',')
        {
            cnt++;
        }
    }
    k = 0;

    FILE *fp = NULL;
    fp = fopen("matrix", "r+");
    if (fp == NULL)
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m No matrix exists\033[0m\n");
    }
    else
    {
        int j = 0, check = 0;
        const char cut[2] = ",";
        const char cap[2] = "(";
        char *token;
        char buff[64];

        token = strtok(userInput, cut);

        former.name = strchr(token, '(') + sizeof(char);

        while (token != NULL && j < 2 && cnt == 2)
        {
            switch (j)
            {
            case 0:
                token = strtok(NULL, cut);
                latter.name = token;
                break;
            case 1:
                token = strtok(NULL, cut);
                if (token == 0)
                {
                    printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name_invalid\033[0m\n");
                }
                else
                {
                    int i = 0;
                    result.name = token;
                    result.name[strlen(token) - 1] = '\0';

                    char bach[strlen(result.name) + 2];

                    for (i = 0; i <= strlen(result.name) + 1; i++)
                    {
                        bach[i] = '0';
                    }

                    for (i = 0; i < strlen(result.name) + 1; i++)
                    {
                        bach[i] = result.name[i];
                    }

                    bach[strlen(result.name)] = '<';
                    bach[strlen(result.name) + 1] = '\0';

                    while (!feof(fp) && check == 0)
                    {
                        fgets(buff, 64, (FILE *)fp);
                        len = strlen(bach);
                        if (strncmp(buff, bach, len) == 0 && check == 0) //Whether userInput is a useable matrixName.
                        {
                            printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name existed\033[0m \033[33;1m<~ %s\033[0m\n", result.name);
                            check = 1;
                        }
                    }
                }

                break;
            }
            j++;
        }

        if (token != 0 && check == 0 && cnt == 2)
        {
            int i = 0, j = 0;

            int check_former = matrixEmploy(p);
            int check_latter = matrixEmploy(q);

            if (check_former != 0 && check_latter != 0)
            {
                if (former.column == latter.row)
                {
                    float matrixfirst[former.row][former.column];
                    float matrixsecond[latter.row][latter.column];
                    float *arone = &matrixfirst[0][0];
                    float *artwo = &matrixsecond[0][0];

                    matrixExtract(p, arone);
                    matrixExtract(q, artwo);

                    printf("\n[\033[34;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", former.name, former.row, former.column);
                    for (i = 0; i < former.row; i++)
                    {
                        for (j = 0; j < former.column; j++)
                        {
                            if (j != 0)
                                printf(" %g ", matrixfirst[i][j]);
                            else
                                printf("[ %g ", matrixfirst[i][j]);
                        }
                        printf("]\n");
                    }
                    printf("\n[\033[34;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", latter.name, latter.row, latter.column);
                    for (i = 0; i < latter.row; i++)
                    {
                        for (j = 0; j < latter.column; j++)
                        {
                            if (j != 0)
                                printf(" %g ", matrixsecond[i][j]);
                            else
                                printf("[ %g ", matrixsecond[i][j]);
                        }
                        printf("]\n");
                    }

                    result.row = former.row;
                    result.column = latter.column;
                    float matrixAns[former.row][latter.column];
                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            matrixAns[i][j] = 0;
                        }
                    }

                    printf("\n[\033[32;1mMatrix\033[0m]: \033[33;1m%s\033[0m <\033[37;1m %d\033[0m,\033[37;1m %d\033[0m > has been saved.\n", result.name, result.row, result.column);

                    int c = 0;

                    for (i = 0; i < former.row; i++)
                    {
                        for (j = 0; j < latter.column; j++)
                        {
                            for (c = 0; c < former.column; c++)
                            {
                                matrixAns[i][j] += (matrixfirst[i][c] * matrixsecond[c][j]);
                            }
                        }
                    }

                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            if (j != 0)
                                printf(" %g ", matrixAns[i][j]);
                            else
                                printf("[ %g ", matrixAns[i][j]);
                        }
                        printf("]\n");
                    }

                    fprintf(fp, "\n%s<%d,%d>\n", result.name, result.row, result.column);

                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            if (j == result.column - 1)
                                fprintf(fp, "%g\n", matrixAns[i][j]);
                            else
                                fprintf(fp, "%g ", matrixAns[i][j]);
                        }
                    }
                    fprintf(fp, "#\n");

                    FILE *fstream = NULL;
                    fstream = fopen("matrixstream", "a+");
                    fprintf(fstream, "\n%s<%d,%d>\n", result.name, result.row, result.column);
                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            fprintf(fstream, "%g\n", matrixAns[i][j]);
                        }
                    }
                    fprintf(fstream, "#\n");
                    fclose(fstream);
                }
                else
                {
                    printf("\n[\033[31;1mError\033[0m]:\033[37;1m A<i,n> x B<n,j> = C<i,j>\033[0m\n");
                }
            }
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
            printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> matrixMulti(A,B,result)\033[0m\n");
        }
        fclose(fp);
    }
}

void matrixTran(char *userInput)
{
    struct matrix former;
    struct matrix result;
    char *token;
    int len = 0, check = 0, k = 0, cnt = 0;
    struct matrix *p = &former;
    for (k = 0; k < 63; k++)
    {
        if (userInput[k] == ',')
        {
            cnt++;
        }
    }
    k = 0;

    FILE *fp = NULL;
    fp = fopen("matrix", "r+");
    if (fp == NULL)
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m No matrix exists\033[0m\n");
    }
    else
    {
        int j = 0;
        const char cut[2] = ",";
        const char cap[2] = "(";

        char buff[64];

        token = strtok(userInput, cut);

        former.name = strchr(token, '(') + sizeof(char);

        while (token != NULL && j < 1 && cnt == 1)
        {

            token = strtok(NULL, cut);
            if (token == 0)
            {
                printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name_invalid\033[0m\n");
            }
            else
            {
                int i = 0;
                result.name = token;
                result.name[strlen(token) - 1] = '\0';

                char bach[strlen(result.name) + 2];

                for (i = 0; i <= strlen(result.name) + 1; i++)
                {
                    bach[i] = '0';
                }

                for (i = 0; i < strlen(result.name) + 1; i++)
                {
                    bach[i] = result.name[i];
                }

                bach[strlen(result.name)] = '<';
                bach[strlen(result.name) + 1] = '\0';

                while (!feof(fp) && check == 0)
                {
                    fgets(buff, 64, (FILE *)fp);
                    len = strlen(bach);
                    if (strncmp(buff, bach, len) == 0 && check == 0) //Whether userInput is a useable matrixName.
                    {
                        printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name existed\033[0m \033[33;1m<~ %s\033[0m\n", result.name);
                        check = 1;
                    }
                }
            }

            break;
        }
        j++;
    }

    if (token != 0 && check == 0 && cnt == 1)
    {
        int i = 0, j = 0;

        int check_former = matrixEmploy(p);

        if (check_former != 0)
        {
            float matrixfirst[former.row][former.column];
            float *arone = &matrixfirst[0][0];

            matrixExtract(p, arone);

            printf("\n[\033[34;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", former.name, former.row, former.column);
            for (i = 0; i < former.row; i++)
            {
                for (j = 0; j < former.column; j++)
                {
                    if (j != 0)
                        printf(" %g ", matrixfirst[i][j]);
                    else
                        printf("[ %g ", matrixfirst[i][j]);
                }
                printf("]\n");
            }

            result.row = former.column;
            result.column = former.row;
            float matrixAns[result.row][result.column];

            printf("\n[\033[32;1mMatrix\033[0m]: \033[33;1m%s\033[0m <\033[37;1m %d\033[0m,\033[37;1m %d\033[0m > has been saved.\n", result.name, result.row, result.column);

            int c = 0;

            for (i = 0; i < result.row; i++)
            {
                for (j = 0; j < result.column; j++)
                {
                    matrixAns[i][j] = matrixfirst[j][i];
                }
            }

            for (i = 0; i < result.row; i++)
            {
                for (j = 0; j < result.column; j++)
                {
                    if (j != 0)
                        printf(" %g ", matrixAns[i][j]);
                    else
                        printf("[ %g ", matrixAns[i][j]);
                }
                printf("]\n");
            }

            fprintf(fp, "\n%s<%d,%d>\n", result.name, result.row, result.column);

            for (i = 0; i < result.row; i++)
            {
                for (j = 0; j < result.column; j++)
                {
                    if (j == result.column - 1)
                        fprintf(fp, "%g\n", matrixAns[i][j]);
                    else
                        fprintf(fp, "%g ", matrixAns[i][j]);
                }
            }
            fprintf(fp, "#\n");

            FILE *fstream = NULL;
            fstream = fopen("matrixstream", "a+");
            fprintf(fstream, "\n%s<%d,%d>\n", result.name, result.row, result.column);
            for (i = 0; i < result.row; i++)
            {
                for (j = 0; j < result.column; j++)
                {
                    fprintf(fstream, "%g\n", matrixAns[i][j]);
                }
            }
            fprintf(fstream, "#\n");
            fclose(fstream);
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Matrix Not_Found\033[0m \033[33;1m <~ %s\033[0m\n", former.name);
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
        printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> matrixTran(A,result)\033[0m\n");
    }
    fclose(fp);
}

void matrixScal(char *userInput)
{
    struct matrix former;
    struct matrix result;

    struct matrix *p = &former;

    int cnt = 0, k = 0;
    float scale = 0;
    for (k = 0; k < 63; k++)
    {
        if (userInput[k] == ',')
        {
            cnt++;
        }
    }
    k = 0;

    FILE *fp = NULL;
    fp = fopen("matrix", "r+");
    if (fp == NULL)
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m No matrix exists\033[0m\n");
    }
    else
    {
        int len = 0, j = 0, check = 0;
        const char cut[2] = ",";
        const char cap[2] = "(";
        char *token;
        char buff[64];

        token = strtok(userInput, cut);

        former.name = strchr(token, '(') + sizeof(char);

        while (token != NULL && j < 2 && fp != NULL && cnt == 2)
        {
            switch (j)
            {
            case 0:
                token = strtok(NULL, cut);
                scale = atof(token);
                break;
            case 1:
                token = strtok(NULL, cut);
                if (token == 0)
                {
                    printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name_invalid\033[0m\n");
                }
                else
                {
                    int i = 0;
                    result.name = token;
                    result.name[strlen(token) - 1] = '\0';

                    char bach[strlen(result.name) + 2];

                    for (i = 0; i <= strlen(result.name) + 1; i++)
                    {
                        bach[i] = '0';
                    }

                    for (i = 0; i < strlen(result.name) + 1; i++)
                    {
                        bach[i] = result.name[i];
                    }

                    bach[strlen(result.name)] = '<';
                    bach[strlen(result.name) + 1] = '\0';

                    while (!feof(fp) && check == 0)
                    {
                        fgets(buff, 64, (FILE *)fp);
                        len = strlen(bach);
                        if (strncmp(buff, bach, len) == 0 && check == 0) //Whether userInput is a useable matrixName.
                        {
                            printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name existed\033[0m \033[33;1m<~ %s\033[0m\n", result.name);
                            check = 1;
                        }
                    }
                }

                break;
            }
            j++;
        }

        if (token != 0 && check == 0 && cnt == 2)
        {
            int i = 0, j = 0;

            int check_former = matrixEmploy(p);

            if (check_former != 0)
            {

                float matrixfirst[former.row][former.column];
                float *arone = &matrixfirst[0][0];

                matrixExtract(p, arone);
                printf("\n[\033[34;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", former.name, former.row, former.column);
                for (i = 0; i < former.row; i++)
                {
                    for (j = 0; j < former.column; j++)
                    {
                        if (j != 0)
                            printf(" %g ", matrixfirst[i][j]);
                        else
                            printf("[ %g ", matrixfirst[i][j]);
                    }
                    printf("]\n");
                }

                result.row = former.row;
                result.column = former.column;
                float matrixAns[result.row][result.column];

                printf("\n[\033[32;1mMatrix\033[0m]: \033[33;1m%s\033[0m <\033[37;1m %d\033[0m,\033[37;1m %d\033[0m > has been saved.\n", result.name, result.row, result.column);

                for (i = 0; i < result.row; i++)
                {
                    for (j = 0; j < result.column; j++)
                    {
                        matrixAns[i][j] = scale * matrixfirst[i][j];
                    }
                }

                for (i = 0; i < result.row; i++)
                {
                    for (j = 0; j < result.column; j++)
                    {
                        if (j != 0)
                            printf(" %g ", matrixAns[i][j]);
                        else
                            printf("[ %g ", matrixAns[i][j]);
                    }
                    printf("]\n");
                }

                fprintf(fp, "\n%s<%d,%d>\n", result.name, result.row, result.column);

                for (i = 0; i < result.row; i++)
                {
                    for (j = 0; j < result.column; j++)
                    {
                        if (j == result.column - 1)
                            fprintf(fp, "%g\n", matrixAns[i][j]);
                        else
                            fprintf(fp, "%g ", matrixAns[i][j]);
                    }
                }
                fprintf(fp, "#\n");

                FILE *fstream = NULL;
                fstream = fopen("matrixstream", "a+");
                fprintf(fstream, "\n%s<%d,%d>\n", result.name, result.row, result.column);
                for (i = 0; i < result.row; i++)
                {
                    for (j = 0; j < result.column; j++)
                    {
                        fprintf(fstream, "%g\n", matrixAns[i][j]);
                    }
                }
                fprintf(fstream, "#\n");
                fclose(fstream);
            }
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
            printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> matrixScal(A,scale,result)\033[0m\n");
        }
        fclose(fp);
    }
}

void matrixDet(char *userInput)
{
    struct matrix former;
    char *token;
    int len = 0, check = 0;
    struct matrix *p = &former;

    FILE *fp = NULL;
    fp = fopen("matrix", "r+");
    if (fp == NULL)
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m No matrix exists\033[0m\n");
    }
    else
    {
        char buff[64];
        former.name = strchr(userInput, '(') + 1;
        former.name[strlen(former.name) - 1] = '\0';

        if (former.name[0] == '\0')
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
        }
        else
        {
            int i = 0;
            char bach[strlen(former.name) + 2];

            for (i = 0; i <= strlen(former.name) + 1; i++)
            {
                bach[i] = '\0';
            }

            for (i = 0; i < strlen(former.name) + 1; i++)
            {
                bach[i] = former.name[i];
            }

            bach[strlen(former.name)] = '<';
            bach[strlen(former.name) + 1] = '\0';

            while (!feof(fp) && check == 0)
            {
                fgets(buff, 64, (FILE *)fp);
                len = strlen(bach);
                if (strncmp(buff, bach, len) == 0 && check == 0) //Whether userInput is a existed matrixName.
                {
                    check = 1;
                }
            }
        }
    }

    if (check == 1)
    {
        int i = 0, j = 0;

        int check_former = matrixEmploy(p);

        if (check_former != 0 && (former.row == former.column))
        {
            float matrixfirst[former.row][former.column];
            float *arone = &matrixfirst[0][0];

            matrixExtract(p, arone);

            printf("\n[\033[34;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", former.name, former.row, former.column);
            for (i = 0; i < former.row; i++)
            {
                for (j = 0; j < former.column; j++)
                {
                    if (j != 0)
                        printf(" %g ", matrixfirst[i][j]);
                    else
                        printf("[ %g ", matrixfirst[i][j]);
                }
                printf("]\n");
            }

            float result = 0;

            switch (former.row)
            {
            case 2:
                result = matrixfirst[0][0] * matrixfirst[1][1] - matrixfirst[1][0] * matrixfirst[0][1];
                printf("\n\033[32;1mDet\033[0m(\033[33;1m%s\033[0m) = %g\n", former.name, result);
                break;
            case 3:
                result = matrixfirst[0][0] * matrixfirst[1][1] * matrixfirst[2][2] + matrixfirst[0][2] * matrixfirst[1][0] * matrixfirst[2][1] + matrixfirst[0][1] * matrixfirst[1][2] * matrixfirst[2][0] -
                         matrixfirst[0][0] * matrixfirst[1][2] * matrixfirst[2][1] - matrixfirst[0][2] * matrixfirst[1][1] * matrixfirst[2][0] - matrixfirst[0][1] * matrixfirst[1][0] * matrixfirst[2][2];
                printf("\n\033[32;1mDet\033[0m(\033[33;1m%s\033[0m) = %g\n", former.name, result);
                break;
            default:
                printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
                break;
            }
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m row != column\033[0m\n");
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m Matrix Not_Found\033[0m \033[33;1m <~ %s\033[0m\n", former.name);
    }

    fclose(fp);
}

void matrixInverse(char *userInput)
{
    struct matrix former;
    struct matrix result;
    char *token;
    int len = 0, check = 0, k = 0, cnt = 0;
    struct matrix *p = &former;
    for (k = 0; k < 63; k++)
    {
        if (userInput[k] == ',')
        {
            cnt++;
        }
    }
    k = 0;

    FILE *fp = NULL;
    fp = fopen("matrix", "r+");
    if (fp == NULL)
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m No matrix exists\033[0m\n");
    }
    else
    {
        int j = 0;
        const char cut[2] = ",";
        const char cap[2] = "(";

        char buff[64];

        token = strtok(userInput, cut);

        former.name = strchr(token, '(') + sizeof(char);

        while (token != NULL && j < 1 && cnt == 1)
        {

            token = strtok(NULL, cut);
            if (token == 0)
            {
                printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name_invalid\033[0m\n");
            }
            else
            {
                int i = 0;
                result.name = token;
                result.name[strlen(token) - 1] = '\0';

                char bach[strlen(result.name) + 2];

                for (i = 0; i <= strlen(result.name) + 1; i++)
                {
                    bach[i] = '0';
                }

                for (i = 0; i < strlen(result.name) + 1; i++)
                {
                    bach[i] = result.name[i];
                }

                bach[strlen(result.name)] = '<';
                bach[strlen(result.name) + 1] = '\0';

                while (!feof(fp) && check == 0)
                {
                    fgets(buff, 64, (FILE *)fp);
                    len = strlen(bach);
                    if (strncmp(buff, bach, len) == 0 && check == 0) //Whether userInput is a useable matrixName.
                    {
                        printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name existed\033[0m \033[33;1m<~ %s\033[0m\n", result.name);
                        check = 1;
                    }
                }
            }

            break;
        }
        j++;
    }

    if (token != 0 && check == 0 && cnt == 1)
    {
        int i = 0, j = 0;

        int check_former = matrixEmploy(p);

        if (check_former != 0)
        {
            if (former.row == former.column)
            {
                float matrixfirst[former.row][former.column];
                float matrixAns[former.row][former.column];
                float *arone = &matrixfirst[0][0];

                matrixExtract(p, arone);

                printf("\n[\033[34;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", former.name, former.row, former.column);
                for (i = 0; i < former.row; i++)
                {
                    for (j = 0; j < former.column; j++)
                    {
                        if (j != 0)
                            printf(" %g ", matrixfirst[i][j]);
                        else
                            printf("[ %g ", matrixfirst[i][j]);
                    }
                    printf("]\n");
                }

                if (Det(p, arone) != 0)
                {
                    switch (former.row)
                    {
                    case 2:
                    {
                        float cof = 1 / (Det(p, arone));
                        matrixAns[0][0] = cof * matrixfirst[1][1];
                        matrixAns[0][1] = (-1) * cof * matrixfirst[0][1];
                        matrixAns[1][0] = (-1) * cof * matrixfirst[1][0];
                        matrixAns[1][1] = cof * matrixfirst[0][0];
                        break;
                    }

                    case 3:
                    {
                        int m = 0, n = 0, sh = 1;
                        float cof = 1 / (Det(p, arone));
                        float sub[2][2];
                        float *temp = &sub[0][0];

                        for (m = 0; m < 3; m++)
                        {
                            for (n = 0; n < 3; n++)
                            {
                                for (i = 0; i < 3; i++)
                                {
                                    for (j = 0; j < 3; j++)
                                    {
                                        if (i != m && j != n)
                                        {
                                            *temp++ = matrixfirst[i][j];
                                        }
                                    }
                                }
                                if ((m + n) % (2) != 0)
                                {
                                    sh = -1;
                                }
                                matrixAns[n][m] = cof * sh * (sub[0][0] * sub[1][1] - sub[1][0] * sub[0][1]);
                                temp = &sub[0][0];
                                i = 0, j = 0, sh = 1;
                            }
                        }
                        break;
                    }

                    default:
                        break;
                    }

                    printf("\n[\033[32;1mMatrix\033[0m]: \033[33;1m%s\033[0m <\033[37;1m %d\033[0m,\033[37;1m %d\033[0m > has been saved.\n", result.name, former.row, former.column);
                    for (i = 0; i < former.row; i++)
                    {
                        for (j = 0; j < former.column; j++)
                        {
                            if (j != 0)
                                printf(" %g ", matrixAns[i][j]);
                            else
                                printf("[ %g ", matrixAns[i][j]);
                        }
                        printf("]\n");
                    }

                    fprintf(fp, "\n%s<%d,%d>\n", result.name, former.row, former.column);

                    for (i = 0; i < former.row; i++)
                    {
                        for (j = 0; j < former.column; j++)
                        {
                            if (j == former.column - 1)
                                fprintf(fp, "%g\n", matrixAns[i][j]);
                            else
                                fprintf(fp, "%g ", matrixAns[i][j]);
                        }
                    }
                    fprintf(fp, "#\n");

                    FILE *fstream = NULL;
                    fstream = fopen("matrixstream", "a+");
                    fprintf(fstream, "\n%s<%d,%d>\n", result.name, former.row, former.column);
                    for (i = 0; i < former.row; i++)
                    {
                        for (j = 0; j < former.column; j++)
                        {
                            fprintf(fstream, "%g\n", matrixAns[i][j]);
                        }
                    }
                    fprintf(fstream, "#\n");
                    fclose(fstream);
                }
                else
                {
                    printf("\n[\033[31;1mError\033[0m]:\033[31;1m Matrix Linearly_Dependent\033[0m \033[33;1m <~ %s\033[0m\n", former.name);
                }
            }
            else
            {
                printf("\n[\033[31;1mError\033[0m]:\033[31;1m row != column\033[0m\n");
            }
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Matrix Not_Found\033[0m \033[33;1m <~ %s\033[0m\n", former.name);
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
        printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> matrixInverse(A,A^-1)\033[0m\n");
    }
    fclose(fp);
}

float Det(struct matrix *f, float *array)
{
    float result = 0;
    int i = 0, j = 0;
    switch (f->row)
    {
    case 2:
    {
        float a[f->row][f->column];
        for (i = 0; i < f->row; i++)
        {
            for (j = 0; j < f->column; j++)
            {
                a[i][j] = *array;
                array++;
            }
        }
        result = a[0][0] * a[1][1] - a[1][0] * a[0][1];
        break;
    }
    case 3:
    {
        float a[f->row][f->column];
        for (i = 0; i < f->row; i++)
        {
            for (j = 0; j < f->column; j++)
            {
                a[i][j] = *array;
                array++;
            }
        }
        result = a[0][0] * a[1][1] * a[2][2] + a[0][2] * a[1][0] * a[2][1] + a[0][1] * a[1][2] * a[2][0] -
                 a[0][0] * a[1][2] * a[2][1] - a[0][2] * a[1][1] * a[2][0] - a[0][1] * a[1][0] * a[2][2];

        break;
    }

    default:
        break;
    }

    return result;
}