//From: Eplankton Date: 2021/8/12

const char version[] = "1.0.5";
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
void matrixShow(char *);                      //To detect a matrix.(5)
void matrixExtract(struct matrix *, float *); //To import a matrix from 'matrixstream'.(Invisible to user)
int matrixEmploy(struct matrix *);            //To confirm a matrix and return its name/row/column.(Invisible to user)
void matrixAdd(char *);                       //To add two matrixes together.(6)
void matrixMinus(char *);                     //To minus two matrixes.(7)
void matrixMulti(char *);                     //To multiply two matrixes together at accuracy.(8)
void matrixTran(char *);                      //To transpose a matrix.(9)
void matrixScale(char *);                     //To scalar multiplay a matrix.(10)
void matrixDet(char *);                       //To get the Det(matrix) under 20.(11)
float Det(struct matrix *, float *);          //To get the Det.(Invisible to user)
void matrixInv(char *);                       //To inverse a matrix.(12)
float vectorDot(char *);                      //To calculate the dot-product of two vectors result into a value.(13)
void vectorCross(char *);                     //To calculate the crodd-product of two vectors result into a new vector.(14)
double vectorMag(char *);                     //To calculate the norm of a vector.(15)
double vectorAngle(char *);                   //To calculate the angle of two vector show as arccos(x) into a value.(16)
                                              //To get the identity vector of a vector.(17)
void vectorN0(char *);                        //To get the normal vector of two vectors.(18)
int matrixDelete(char *);                     //To delete a matrix.(19)
int valueDelete(char *);                      //To delete a value.(20)
void fileDelete(char *);                      //To delete a file.(101)

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
    printf("\n[\033[32;1mSuccess\033[0m]\033[36;1m BioMatrix\033[0m (v%s) is running on your environment!\n", version);
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

void fileDelete(char *userInput)
{
    int check = 0;
    char *filename;
    filename = strchr(userInput, '(') + sizeof(char);
    filename[strlen(filename) - 1] = '\0';
    if (filename != "command_list" && filename != "help" && filename != "function.h" && filename != "extension.h" && filename != "main.c")
    {
        check = 1;
    }

    if (check == 1)
    {
        if (remove(filename) == -1)
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m File Not_Found\033[0m \033[33;1m <~ %s\033[0m\n", filename);
        }
        else
        {
            printf("\n[\033[32;1mFILE\033[0m]: \033[33;1m%s\033[0m has been deleted.\n", filename);
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m System file\033[0m \033[33;1m <~ %s\033[0m\n", filename);
    }
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
    if (cnt >= 2)
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
                        printf("\nThe row(\033[32;1m%d\033[0m)column(\033[32;1m%d\033[0m) = ", i + 1, j + 1);

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

void matrixShow(char *userInput)
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

        while (token != NULL && j < 2 && fp != NULL && cnt >= 2)
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

        if (token != 0 && check == 0 && cnt >= 2)
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
                                printf("\033[37;1m %g \033[0m", matrixAns[i][j]);
                            else
                                printf("\033[37;1m[ %g \033[0m", matrixAns[i][j]);
                        }
                        printf("\033[37;1m]\033[0m\n");
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
            printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> matrix.Add(A,B,result)\033[0m\n");
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

        while (token != NULL && j < 2 && cnt >= 2)
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

        if (token != 0 && check == 0 && cnt >= 2)
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
                                printf("\033[37;1m %g \033[0m", matrixAns[i][j]);
                            else
                                printf("\033[37;1m[ %g \033[0m", matrixAns[i][j]);
                        }
                        printf("\033[37;1m]\033[0m\n");
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
            printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> matrix.Minus(A,B,result)\033[0m\n");
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
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m No matrix exists.\033[0m\n");
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

        while (token != NULL && j < 2 && cnt >= 2)
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

                    FILE *fvalue = NULL;
                    fvalue = fopen("value", "a+");

                    while (!feof(fvalue) && check == 0)
                    {
                        fgets(buff, 64, (FILE *)fvalue);
                        len = strlen(bach);
                        if (strncmp(buff, bach, len) == 0 && check == 0) //Whether userInput is a useable matrixName.
                        {
                            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Value_existed\033[0m \033[33;1m<~ %s\033[0m\n", result.name);
                            check = 1;
                        }
                    }
                    fclose(fvalue);
                }

                break;
            }
            j++;
        }

        if (token != 0 && check == 0 && cnt >= 2)
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

                    int c = 0;
                    float acc = 9e-004; //Set the accuracy if you need

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

                    printf("\n[\033[32;1mMatrix\033[0m]: \033[33;1m%s\033[0m <\033[37;1m %d\033[0m,\033[37;1m %d\033[0m > has been saved.\n", result.name, result.row, result.column);

                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            if (j != 0)
                                printf("\033[37;1m %.3g \033[0m", matrixAns[i][j]);
                            else
                                printf("\033[37;1m[ %g \033[0m", matrixAns[i][j]);
                        }
                        printf("\033[37;1m]\033[0m\n");
                    }

                    if (result.row == 1 && result.column == 1) //If result is a 1x1 matrix.
                    {
                        printf("\n[\033[36;1mSystem.Out\033[0m]: \033[33;1m%s\033[0m is an value.\n", result.name);
                        FILE *fvalue = NULL;
                        fvalue = fopen("value", "a+");
                        fprintf(fvalue, "\n%s<%d,%d>\n%g\n#\n", result.name, result.row, result.column, matrixAns[0][0]);
                        fclose(fvalue);
                    }
                    else
                    {
                        fprintf(fp, "\n%s<%d,%d>\n", result.name, result.row, result.column);

                        for (i = 0; i < result.row; i++)
                        {
                            for (j = 0; j < result.column; j++)
                            {
                                if (j == result.column - 1)
                                    fprintf(fp, "%.3g\n", matrixAns[i][j]);
                                else
                                    fprintf(fp, "%.3g ", matrixAns[i][j]);
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
                                fprintf(fstream, "%.3g\n", matrixAns[i][j]);
                            }
                        }
                        fprintf(fstream, "#\n");
                        fclose(fstream);
                    }
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
            printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> matrix.Multi(A,B,result)\033[0m\n");
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

        while (token != NULL && j < 1 && cnt >= 1)
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

    if (token != 0 && check == 0 && cnt >= 1)
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
                        printf("\033[37;1m %g \033[0m", matrixAns[i][j]);
                    else
                        printf("\033[37;1m[ %g \033[0m", matrixAns[i][j]);
                }
                printf("\033[37;1m]\033[0m\n");
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
        printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> matrix.Tran(A,result)\033[0m\n");
    }
    fclose(fp);
}

void matrixScale(char *userInput)
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

        while (token != NULL && j < 2 && fp != NULL && cnt >= 2)
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

        if (token != 0 && check == 0 && cnt >= 2)
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
                            printf("\033[37;1m %g \033[0m", matrixAns[i][j]);
                        else
                            printf("\033[37;1m[ %g \033[0m", matrixAns[i][j]);
                    }
                    printf("\033[37;1m]\033[0m\n");
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
            printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> matrix.Scale(A,scale,result)\033[0m\n");
        }
        fclose(fp);
    }
}

void matrixDet(char *userInput)
{
    struct matrix former;
    char *token;
    int len = 0, check = 0, sure = 0;
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
                printf("\n\033[32;1mDet\033[0m(\033[33;1m%s\033[0m) = \033[37;1m%g\033[0m\n", former.name, result);
                break;
            case 3:
                result = matrixfirst[0][0] * matrixfirst[1][1] * matrixfirst[2][2] + matrixfirst[0][2] * matrixfirst[1][0] * matrixfirst[2][1] + matrixfirst[0][1] * matrixfirst[1][2] * matrixfirst[2][0] -
                         matrixfirst[0][0] * matrixfirst[1][2] * matrixfirst[2][1] - matrixfirst[0][2] * matrixfirst[1][1] * matrixfirst[2][0] - matrixfirst[0][1] * matrixfirst[1][0] * matrixfirst[2][2];
                printf("\n\033[32;1mDet\033[0m(\033[33;1m%s\033[0m) = \033[37;1m%g\033[0m\n", former.name, result);
                break;
            default:
                result = Det(p, arone);
                printf("\n\033[32;1mDet\033[0m(\033[33;1m%s\033[0m) = \033[37;1m%g\033[0m\n", former.name, result);
                break;
            }

            printf("\n[\033[32;1mValue\033[0m]: \033[33;1mDet(%s)\033[0m has been saved.\n", former.name);
            printf("\033[37;1m[ %g ]\033[0m\n", result);
            printf("\n[\033[36;1mSystem.Out\033[0m]: \033[33;1mDet(%s)\033[0m is an value.\n", former.name);
            FILE *fvalue = NULL;
            fvalue = fopen("value", "a+");
            fprintf(fvalue, "\nDet(%s)<1,1>\n%g\n#\n", former.name, result);
            fclose(fvalue);
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

void matrixInv(char *userInput)
{
    struct matrix former;
    struct matrix result;
    struct matrix *p = &former;
    char *token;
    int len = 0, check = 0, k = 0, cnt = 0;

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

        while (token != NULL && j < 1 && cnt >= 1)
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

    if (token != 0 && check == 0 && cnt >= 1)
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
                        float sub[former.row - 1][former.column - 1];
                        float *temp = &sub[0][0];

                        for (m = 0; m < former.row; m++)
                        {
                            for (n = 0; n < former.row; n++)
                            {
                                for (i = 0; i < former.row; i++)
                                {
                                    for (j = 0; j < former.row; j++)
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
                                else
                                {
                                    sh = 1;
                                }

                                struct matrix submatrix;
                                submatrix.row = former.row - 1, submatrix.column = former.column - 1;
                                struct matrix *q = &submatrix;
                                temp = &sub[0][0];
                                matrixAns[n][m] = cof * sh * Det(q, temp);
                            }
                        }
                        break;
                    }

                    default:
                    {
                        int m = 0, n = 0, sh = 1;
                        float cof = 1 / (Det(p, arone));
                        float sub[former.row - 1][former.column - 1];
                        float *temp = &sub[0][0];

                        for (m = 0; m < former.row; m++)
                        {
                            for (n = 0; n < former.row; n++)
                            {
                                for (i = 0; i < former.row; i++)
                                {
                                    for (j = 0; j < former.row; j++)
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
                                else
                                {
                                    sh = 1;
                                }

                                struct matrix submatrix;
                                submatrix.row = former.row - 1, submatrix.column = former.column - 1;
                                struct matrix *q = &submatrix;
                                temp = &sub[0][0];
                                matrixAns[n][m] = cof * sh * Det(q, temp);
                            }
                        }
                        break;
                    }
                    break;
                    }

                    printf("\n\n[\033[32;1mMatrix\033[0m]: \033[33;1m%s\033[0m <\033[37;1m %d\033[0m,\033[37;1m %d\033[0m > has been saved.\n", result.name, former.row, former.column);
                    for (i = 0; i < former.row; i++)
                    {
                        for (j = 0; j < former.column; j++)
                        {
                            if (j != 0)
                                printf(" %.3g\t ", matrixAns[i][j]);
                            else
                                printf("[ %.3g\t ", matrixAns[i][j]);
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
        printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> matrix.Inv(A,A^-1)\033[0m\n");
    }
    fclose(fp);
}

float Det(struct matrix *f, float *array) //Use expansion.h
{
    float answer = 0;
    int i = 0, j = 0;
    float a[f->row][f->column];

    float matrix[20][20];

    for (i = 0; i < f->row; i++)
    {
        for (j = 0; j < f->column; j++)
        {
            matrix[i][j] = *array;
            a[i][j] = *array;
            array++;
        }
    }

    i = 0, j = 0;

    switch (f->row)
    {
    case 2:
    {
        answer = a[0][0] * a[1][1] - a[1][0] * a[0][1];
        break;
    }
    case 3:
    {
        answer = a[0][0] * a[1][1] * a[2][2] + a[0][2] * a[1][0] * a[2][1] + a[0][1] * a[1][2] * a[2][0] -
                 a[0][0] * a[1][2] * a[2][1] - a[0][2] * a[1][1] * a[2][0] - a[0][1] * a[1][0] * a[2][2];

        break;
    }

    default: //20 >dimension > 3
    {
        answer = determinant(matrix, f->row); //This function is taken from https://zhuanlan.zhihu.com/p/305328519
    }
    break;
    }

    return answer;
}

int matrixDelete(char *userInput)
{
    int check = 0;
    FILE *fp = NULL;
    fp = fopen("matrix", "r");

    FILE *ftemp = NULL;
    ftemp = fopen("temp", "a+");

    if (fp != NULL)
    {
        char buff[64];
        char *matrixName;

        matrixName = strchr(userInput, '(') + sizeof(char); //userInput as 'matrixInput(test)', matrixName = "test"
        matrixName[strlen(matrixName) - 1] = '<';

        if (strlen(matrixName) != 0)
        {
            fclose(fp);
            fp = fopen("matrix", "r");

            int len = 0;
            while (!feof(fp))
            {
                fgets(buff, 64, (FILE *)fp);
                len = strlen(matrixName);

                if (strncmp(buff, matrixName, len) == 0 && check == 0)
                {
                    check = 1;
                    while (strchr(buff, '#') == NULL)
                    {
                        fgets(buff, 64, (FILE *)fp);
                    }
                }
                else
                {
                    if (strchr(buff, '#') != NULL)
                    {
                        fputc(buff[0], (FILE *)ftemp);
                        fputc('\n', (FILE *)ftemp);
                    }
                    else
                    {
                        fprintf((FILE *)ftemp, buff);
                    }
                }

                int i = 0;
                for (i = 0; i < 63; i++)
                {
                    buff[i] = '\0';
                }
            }

            fclose(fp);
            fclose(ftemp);

            remove("matrix");
            fp = fopen("matrix", "a+");
            ftemp = fopen("temp", "r");
            int i = 0;
            for (i = 0; i < 63; i++)
            {
                buff[i] = '\0';
            }

            while (!feof(ftemp))
            {
                fgets(buff, 64, (FILE *)ftemp);

                fprintf((FILE *)fp, buff);
                for (i = 0; i < 63; i++)
                {
                    buff[i] = '\0';
                }
            }

            fclose(ftemp);
            fclose(fp);
            remove("temp");

            FILE *fp2 = NULL;
            FILE *ftemp2 = NULL;
            fp2 = fopen("matrixstream", "r");
            ftemp2 = fopen("temp", "a+");

            len = 0;
            check = 0;
            for (i = 0; i < 63; i++)
            {
                buff[i] = '\0';
            }

            while (!feof(fp2))
            {
                fgets(buff, 64, (FILE *)fp2);
                len = strlen(matrixName);

                if (strncmp(buff, matrixName, len) == 0 && check == 0)
                {
                    check = 1;
                    while (strchr(buff, '#') == NULL)
                    {
                        fgets(buff, 64, (FILE *)fp2);
                    }
                }
                else
                {
                    if (strchr(buff, '#') != NULL)
                    {
                        fputc(buff[0], (FILE *)ftemp2);
                        fputc('\n', (FILE *)ftemp2);
                    }
                    else
                    {
                        fprintf((FILE *)ftemp2, buff);
                    }
                }

                int i = 0;

                for (i = 0; i < 63; i++)
                {
                    buff[i] = '\0';
                }
            }

            fclose(fp2);
            fclose(ftemp2);

            remove("matrixstream");
            fp2 = fopen("matrixstream", "a+");
            ftemp2 = fopen("temp", "r");

            while (!feof(ftemp2))
            {
                fgets(buff, 64, (FILE *)ftemp2);

                fprintf((FILE *)fp2, buff);
                for (i = 0; i < 63; i++)
                {
                    buff[i] = '\0';
                }
            }
            fclose(ftemp2);
            fclose(fp2);
            remove("temp");

            matrixName[strlen(matrixName) - 1] = '\0';
            printf("\n[\033[32;1mMatrix\033[0m]: \033[33;1m%s\033[0m has been deleted.\n", matrixName);

            if (check == 0)
            {
                printf("\n[\033[31;1mError\033[0m]:\033[31;1m Matrix Not_Found\033[0m \033[33;1m <~ %s\033[0m\n", matrixName);
            }
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m No matrix exists\033[0m\n");
    }

    return check;
    check = 0;
}

float vectorDot(char *userInput)
{
    float answer = 0;
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

        while (token != NULL && j < 2 && cnt >= 2)
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

                    FILE *fvalue = NULL;
                    fvalue = fopen("value", "a+");

                    while (!feof(fvalue) && check == 0)
                    {
                        fgets(buff, 64, (FILE *)fvalue);
                        len = strlen(bach);
                        if (strncmp(buff, bach, len) == 0 && check == 0) //Whether userInput is a useable matrixName.
                        {
                            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Value_existed\033[0m \033[33;1m<~ %s\033[0m\n", result.name);
                            check = 1;
                        }
                    }
                    fclose(fvalue);
                }

                break;
            }
            j++;
        }

        if (token != 0 && check == 0 && cnt >= 2)
        {
            int i = 0, j = 0;

            int check_former = matrixEmploy(p);
            int check_latter = matrixEmploy(q);

            if (check_former != 0 && check_latter != 0)
            {
                if (((former.row == 1 && former.column != 1) || (former.row != 1 && former.column == 1)) && ((latter.row == 1 && latter.column != 1) || (latter.row != 1 && latter.column == 1)) && ((former.row * former.column) == (latter.row * latter.column)))
                {
                    float matrixfirst[former.row][former.column];
                    float matrixsecond[latter.row][latter.column];
                    float vectorone[(former.row > former.column) ? former.row : former.column];
                    float vectorsec[(latter.row > latter.column) ? latter.row : latter.column];

                    float *arone = &matrixfirst[0][0];
                    float *artwo = &matrixsecond[0][0];

                    matrixExtract(p, arone);
                    matrixExtract(q, artwo);

                    printf("\n[\033[34;1mVector\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", former.name, former.row, former.column);
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
                    printf("\n[\033[34;1mVector\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", latter.name, latter.row, latter.column);
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

                    if (former.row > former.column)
                    {
                        int i = 0;
                        for (i = 0; i < former.row; i++)
                        {
                            vectorone[i] = matrixfirst[i][0];
                        }
                    }
                    else
                    {
                        int i = 0;
                        for (i = 0; i < former.column; i++)
                        {
                            vectorone[i] = matrixfirst[0][i];
                        }
                    }

                    if (latter.row > latter.column)
                    {
                        int i = 0;
                        for (i = 0; i < latter.row; i++)
                        {
                            vectorsec[i] = matrixsecond[i][0];
                        }
                    }
                    else
                    {
                        int i = 0;
                        for (i = 0; i < latter.column; i++)
                        {
                            vectorsec[i] = matrixsecond[0][i];
                        }
                    }

                    for (i = 0; i < ((former.row > former.column) ? former.row : former.column); i++)
                    {
                        answer += vectorone[i] * vectorsec[i];
                    }

                    result.row = 1;
                    result.column = 1;

                    printf("\n[\033[32;1mValue\033[0m]: \033[33;1m%s\033[0m has been saved.\n", result.name);
                    printf("\033[37;1m[ %g ]\033[0m\n", answer);
                    printf("\n[\033[36;1mSystem.Out\033[0m]: \033[33;1m%s\033[0m is an value.\n", result.name);
                    FILE *fvalue = NULL;
                    fvalue = fopen("value", "a+");
                    fprintf(fvalue, "\n%s<%d,%d>\n%g\n#\n", result.name, result.row, result.column, answer);
                    fclose(fvalue);
                }
                else
                {
                    printf("\n[\033[31;1mError\033[0m]:\033[37;1m Not available vector.\033[0m\n");
                }
            }
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
            printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> vector.Dot(a,b,value.name)\033[0m\n");
        }
        fclose(fp);
    }

    return answer;
}

void vectorCross(char *userInput)
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

        while (token != NULL && j < 2 && cnt >= 2)
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

        if (token != 0 && check == 0 && cnt >= 2)
        {
            int i = 0, j = 0;

            int check_former = matrixEmploy(p);
            int check_latter = matrixEmploy(q);

            if (check_former != 0 && check_latter != 0)
            {
                if (((former.row == 3 && former.column == 1) || (former.row == 1 && former.column == 3)) && ((latter.row == 1 && latter.column == 3) || (latter.row == 3 && latter.column == 1)))
                {
                    float matrixfirst[former.row][former.column];
                    float matrixsecond[latter.row][latter.column];
                    float matrixAns[3][1];

                    float vectorone[(former.row > former.column) ? former.row : former.column];
                    float vectorsec[(latter.row > latter.column) ? latter.row : latter.column];

                    float *arone = &matrixfirst[0][0];
                    float *artwo = &matrixsecond[0][0];

                    matrixExtract(p, arone);
                    matrixExtract(q, artwo);

                    printf("\n[\033[34;1mVector\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", former.name, former.row, former.column);
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
                    printf("\n[\033[34;1mVector\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", latter.name, latter.row, latter.column);
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

                    if (former.row > former.column)
                    {
                        int i = 0;
                        for (i = 0; i < former.row; i++)
                        {
                            vectorone[i] = matrixfirst[i][0];
                        }
                    }
                    else
                    {
                        int i = 0;
                        for (i = 0; i < former.column; i++)
                        {
                            vectorone[i] = matrixfirst[0][i];
                        }
                    }

                    if (latter.row > latter.column)
                    {
                        int i = 0;
                        for (i = 0; i < latter.row; i++)
                        {
                            vectorsec[i] = matrixsecond[i][0];
                        }
                    }
                    else
                    {
                        int i = 0;
                        for (i = 0; i < latter.column; i++)
                        {
                            vectorsec[i] = matrixsecond[0][i];
                        }
                    }

                    result.row = 3;
                    result.column = 1;

                    matrixAns[0][0] = vectorone[1] * vectorsec[2] - vectorone[2] * vectorsec[1];
                    matrixAns[1][0] = vectorone[2] * vectorsec[0] - vectorone[0] * vectorsec[2];
                    matrixAns[2][0] = vectorone[0] * vectorsec[1] - vectorone[1] * vectorsec[0];

                    printf("\n[\033[32;1mVector\033[0m]: \033[33;1m%s\033[0m <\033[37;1m %d\033[0m,\033[37;1m %d\033[0m > has been saved.\n", result.name, result.row, result.column);
                    for (i = 0; i < result.row; i++)
                    {
                        for (j = 0; j < result.column; j++)
                        {
                            if (j != 0)
                                printf("\033[37;1m %.3g \033[0m", matrixAns[i][j]);
                            else
                                printf("\033[37;1m[ %g \033[0m", matrixAns[i][j]);
                        }
                        printf("\033[37;1m]\033[0m\n");
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
                    if ((former.row * former.column != 3))
                        printf("\n[\033[31;1mError\033[0m]:\033[37;1m Not available vector\033[0m \033[33;1m<~ %s\033[0m\n", former.name);
                    else
                    {
                        if ((latter.row * latter.column != 3))
                            printf("\n[\033[31;1mError\033[0m]:\033[37;1m Not available vector\033[0m \033[33;1m<~ %s\033[0m\n", latter.name);
                    }
                }
            }
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input \033[0m\n");
            printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> vector.Cross(a,b,vector.name) only in 3D.\033[0m\n");
        }
        fclose(fp);
    }
}

double vectorMag(char *userInput)
{
    struct matrix former;
    char *token;
    int len = 0, check = 0, sure = 0;
    double result = 0, yyds = 0;
    struct matrix *p = &former;

    FILE *fp = NULL;
    fp = fopen("matrix", "r+");
    if (fp == NULL)
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m No vector exists\033[0m\n");
    }
    else
    {
        char buff[64];
        former.name = strchr(userInput, '(') + 1;
        former.name[strlen(former.name) - 1] = '\0';

        if (former.name[0] == '\0')
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Not a vector\033[0m\n");
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

        if (check_former != 0 && (former.row == 1 || former.column == 1) && (former.row * former.column != 1))
        {
            float matrixfirst[former.row][former.column];
            float *arone = &matrixfirst[0][0];

            matrixExtract(p, arone);

            printf("\n[\033[34;1mVector\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", former.name, former.row, former.column);
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

            i = 0, j = 0;

            if (former.row > former.column)
            {
                for (i = 0; i < former.row; i++)
                {
                    yyds += matrixfirst[i][0] * matrixfirst[i][0];
                }
                result = sqrt(yyds);
            }
            else
            {
                for (i = 0; i < former.column; i++)
                {
                    yyds += matrixfirst[0][i] * matrixfirst[0][i];
                }
                result = sqrt(yyds);
            }

            printf("\n[\033[32;1mValue\033[0m]: \033[33;1mMag(%s)\033[0m has been saved.\n", former.name);
            printf("\033[37;1m[ %g ]\033[0m\n", result);
            printf("\n[\033[36;1mSystem.Out\033[0m]: \033[33;1mMag(%s)\033[0m is an value.\n", former.name);
            FILE *fvalue = NULL;
            fvalue = fopen("value", "a+");
            fprintf(fvalue, "\nMag(%s)<1,1>\n%g\n#\n", former.name, result);
            fclose(fvalue);
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Not a vector\033[0m \033[33;1m <~ %s\033[0m\n", former.name);
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m Vector Not_Found\033[0m \033[33;1m <~ %s\033[0m\n", former.name);
    }

    fclose(fp);
    return result;
}

int valueDelete(char *userInput)
{
    int check = 0;
    FILE *fp = NULL;
    fp = fopen("value", "r");

    FILE *ftemp = NULL;
    ftemp = fopen("temp", "a+");

    if (fp != NULL)
    {
        char buff[64];
        char *pre;
        pre = strchr(userInput, '(') + sizeof(char);
        char matrixName[strlen(pre)];
        int i = 0;
        for (i = 0; i < strlen(pre) - 1; i++)
        {
            matrixName[i] = pre[i];
        }
        //userInput as 'matrixInput(test)', matrixName = "test"
        matrixName[strlen(pre) - 1] = '<';

        if (strlen(matrixName) != 0)
        {
            fclose(fp);
            fp = fopen("value", "r");

            int len = 0;
            while (!feof(fp))
            {
                int i = 0;
                for (i = 0; i < 63; i++)
                {
                    buff[i] = '\0';
                }
                fgets(buff, 64, (FILE *)fp);
                len = strlen(pre);
                if (strncmp(buff, matrixName, len) == 0 && check == 0)
                {
                    check = 1;
                    while (strchr(buff, '#') == NULL)
                    {
                        fgets(buff, 64, (FILE *)fp);
                    }
                }
                else
                {
                    if (strchr(buff, '#') != NULL)
                    {
                        fputc(buff[0], (FILE *)ftemp);
                        fputc('\n', (FILE *)ftemp);
                    }
                    else
                    {
                        fprintf((FILE *)ftemp, buff);
                        for (i = 0; i < 63; i++)
                        {
                            buff[i] = '\0';
                        }
                    }
                }
            }

            fclose(fp);
            fclose(ftemp);
            remove("value");
            fp = fopen("value", "a+");
            ftemp = fopen("temp", "r");
            int i = 0;
            for (i = 0; i < 63; i++)
            {
                buff[i] = '\0';
            }
            while (!feof(ftemp))
            {
                fgets(buff, 64, (FILE *)ftemp);

                fprintf((FILE *)fp, buff);
                for (i = 0; i < 63; i++)
                {
                    buff[i] = '\0';
                }
            }
            fclose(ftemp);
            fclose(fp);
            remove("temp");

            matrixName[strlen(pre) - 1] = '\0';

            if (check == 0)
            {
                printf("\n[\033[31;1mError\033[0m]:\033[31;1m Value Not_Found\033[0m \033[33;1m <~ %s\033[0m\n", matrixName);
            }
            else
            {
                printf("\n[\033[32;1mValue\033[0m]: \033[33;1m%s\033[0m has been deleted.\n", matrixName);
            }
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m No value exists\033[0m\n");
    }

    return check;
}

double vectorAngle(char *userInput)
{
    double answer = 0;

    struct matrix former;
    struct matrix latter;
    struct matrix result;

    struct matrix *p = &former;
    struct matrix *q = &latter;

    int len = 0, cnt = 0, k = 0, check = 0;

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
        if (cnt >= 2)
        {
            int j = 0, check = 0;
            const char cut[2] = ",";
            const char cap[2] = "(";
            char *token2;
            char *token3;
            char *token1;

            char buff[64];
            char *temp;

            token1 = strtok(userInput, cut);

            former.name = strchr(token1, '(') + sizeof(char);

            while (token1 != NULL && j < 2 && cnt >= 2)
            {
                switch (j)
                {
                case 0:

                    token2 = strtok(NULL, cut);
                    latter.name = token2;
                    break;

                case 1:
                {
                    token3 = strtok(NULL, cut);
                    if (token3 == 0)
                    {
                        printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name_invalid\033[0m\n");
                        check = 1;
                    }
                    else
                    {
                        int i = 0;
                        result.name = token3;
                        result.name[strlen(token3) - 1] = '\0';

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

                        FILE *fvalue = NULL;
                        fvalue = fopen("value", "a+");

                        while (!feof(fvalue) && check == 0)
                        {
                            fgets(buff, 64, (FILE *)fvalue);
                            len = strlen(bach);
                            if (strncmp(buff, bach, len) == 0 && check == 0) //Whether userInput is a useable matrixName.
                            {
                                printf("\n[\033[31;1mError\033[0m]:\033[31;1m Value_existed\033[0m \033[33;1m<~ %s\033[0m\n", result.name);
                                check = 1;
                            }
                        }
                        fclose(fvalue);
                    }

                    break;
                }
                }

                j++;
            }

            if (check == 0 && matrixEmploy(p) != 0 && matrixEmploy(q) != 0)
            {
                char dothead[64] = "vector.Dot(";
                char tail[2] = ")";

                strcat(dothead, former.name);
                strcat(dothead, cut);
                strcat(dothead, latter.name);
                strcat(dothead, cut);
                strcat(dothead, "TEMP_VAL");
                strcat(dothead, tail);

                char magone[64] = "vector.Mag(";
                strcat(magone, former.name);
                strcat(magone, tail);

                char magsec[64] = "vector.Mag(";
                strcat(magsec, latter.name);
                strcat(magsec, tail);

                answer = acos((vectorDot(dothead)) / (vectorMag(magone) * vectorMag(magsec))); //Reference

                printf("\n[\033[32;1mValue\033[0m]: \033[33;1m%s\033[0m has been saved.\n", result.name);
                printf("\033[37;1m[ %g ]\033[0m\n", answer);
                printf("\n[\033[36;1mSystem.Out\033[0m]: \033[33;1m%s\033[0m is an value.\n", result.name);

                FILE *fvalue = NULL;
                fvalue = fopen("value", "a+");
                fprintf(fvalue, "\n%s<1,1>\n%g\n#\n", result.name, answer);
                fclose(fvalue);

                char delsec[64] = "vector.Del(";
                strcat(delsec, "Mag(");
                strcat(delsec, latter.name);
                strcat(delsec, ")");
                strcat(delsec, tail);

                char delone[64] = "vector.Del(";
                strcat(delone, "Mag(");
                strcat(delone, former.name);
                strcat(delone, ")");
                strcat(delone, tail);

                char deltemp[64] = "value.Del(";
                const char *tep = "TEMP_VAL";
                strcat(deltemp, tep);
                strcat(deltemp, tail);

                valueDelete(delone);
                valueDelete(delsec);
                valueDelete(deltemp);
            }
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
        }
    }

    fclose(fp);
    return answer;
}

void vectorN0(char *userInput)
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
    fp = fopen("matrix", "a+");
    if (fp == NULL)
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m No matrix exists\033[0m\n");
    }
    else
    {
        if (cnt >= 2)
        {
            int j = 0, check = 0;
            const char cut[] = ",";
            const char cap[2] = "(";
            char *token;
            char buff[64];

            token = strtok(userInput, cut);

            former.name = strchr(token, '(') + sizeof(char);

            while (token != NULL && j < 2 && cnt >= 2)
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

            char head[64] = "vector.Cross(";
            const char tail[] = ")";
            strcat(head, former.name);
            strcat(head, cut);
            strcat(head, latter.name);
            strcat(head, cut);
            strcat(head, "TEMP_VCT");
            strcat(head, tail);
            vectorCross(head);

            char imd[64] = "vector.Mag(";
            strcat(imd, "TEMP_VCT");
            strcat(imd, tail);

            double sox = 1.0 / vectorMag(imd);

            char VAL[21];
            sprintf(VAL, "%g", sox);
            char Hal[64] = "matrix.Scale(";
            strcat(Hal, "TEMP_VCT");
            strcat(Hal, cut);
            strcat(Hal, VAL);
            strcat(Hal, cut);
            strcat(Hal, result.name);
            strcat(Hal, tail);
            matrixScale(Hal);

            char delone[64] = "value.Del(";
            strcat(delone, "Mag(TEMP_VCT)");
            strcat(delone, tail);

            char delsec[64] = "vector.Del(";
            strcat(delsec, "TEMP_VCT");
            strcat(delsec, tail);

            fclose(fp);
            valueDelete(delone);
            matrixDelete(delsec);
        }
        else
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input \033[0m\n");
            printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> vector.N0(a,b,result.name)\033[0m\n");
        }
    }
}