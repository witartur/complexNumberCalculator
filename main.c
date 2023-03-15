#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    float real;
    float imaginary;
} complexNb;

struct element                                  // stack element -> number and pointer for previous number
{
    complexNb Nb;
    struct element *previousEl_ptr;
};

struct element *currentEl_ptr = NULL;

void First(complexNb number);            // memory allocation for first element on stack
void Push(complexNb number);             // memory allocation for next element on stack
void Pop(void);                          // memory allocation for previous element on stack
void PrintStack(int stackNb);            // printing whole stack
void ClearStack(void);                   // clearing whole stack
void Addition(void);
void Subtraction(void);
void Multiplication(void);
void Division(void);
void PrintMenu(int stackNb);
void HandleElement(int stackNb, int sRes, complexNb number);
void HandleSign(char sign, int *stackNb);


int main(void)
{
    int stackNb = 0;                // number of elements on the stack
    complexNb number;               // user input number
    char tempArray [25];            // temp array for storing data for sscanf
    int sRes = 0;                   // auxilary variable for sscanf function result
    char sign;                      // user input other than numbers

    while(1)
    {
        PrintMenu(stackNb);

        gets(tempArray);
        sRes = sscanf(tempArray, "%f" "%f", &number.real, &number.imaginary);

        if (sRes == 1 || sRes == 2)
        {
            HandleElement(stackNb, sRes, number);
            stackNb++;
        }
        else
        {
            sscanf(tempArray, "%c", &sign);
            HandleSign(sign, &stackNb);
        }
    }

    free(currentEl_ptr);
    return 0;
}


void PrintMenu(int stackNb)
{
    system("cls");
    // fputs("\x1b[H\x1b[2J\x1b[3J", stdout); fflush(stdout);
    printf("\n********** COMPLEX NUMBER CALCULATOR **********\r\n");
    printf("\nPut the number, make calcualtion (+ - * /), press C for clear the stack, E for exit the programm or P for deleting previous number \r\n");
    PrintStack(stackNb);
}

void HandleElement(int stackNb, int sRes, complexNb number) {
    if (sRes == 2)
    {
        (stackNb > 0) ? Push(number) : First(number);
    }
    else
    {
        number.imaginary = 0;
        (stackNb > 0) ? Push(number) : First(number);
    }
}

void HandleSign(char sign, int *stackNb)
{
    if(*stackNb < 2)
    {
        printf("***NEED AT LEAST 2 NUMBERS FOR CALCULATIONS***\r\n");
        system("pause");
        return;
    }

    (*stackNb)--;

    if(sign =='E' || sign =='e')
    {
        ClearStack();
        exit(0);
    }
    else if(sign =='C'|| sign =='c')
    {
        ClearStack();
        *stackNb = 0;
    }
    else if(sign =='P'|| sign =='p')
    {
        Pop();
    }
    else if (sign =='+')
    {
        Addition();
    }
    else if (sign =='-')
    {
        Subtraction();
    }
    else if (sign =='*')
    {
        Multiplication();
    }
    else if (sign =='/')
    {
        Division();
    }
    else
    {
        (*stackNb)++;
        printf("***READ THE INSTRUCTION AGAIN***\r\n");
        system("pause");
    }
}

void First(complexNb number)
{
    currentEl_ptr = malloc(sizeof(struct element));

    (*currentEl_ptr).Nb = number;
    (*currentEl_ptr).previousEl_ptr = NULL;
}

void Push(complexNb number)
{
    struct element *nextEl_ptr;
    nextEl_ptr = malloc(sizeof(struct element));

    (*nextEl_ptr).Nb = number;
    (*nextEl_ptr).previousEl_ptr = currentEl_ptr;

    currentEl_ptr = nextEl_ptr;
}

void Pop(void)
{
    struct element *tempEl_ptr;         // temporary element

    tempEl_ptr = currentEl_ptr;
    currentEl_ptr = tempEl_ptr->previousEl_ptr;
}

void PrintStack(int stackNb)
{
    struct element *tempEl_ptr = NULL;
    complexNb tempArray[stackNb];

    tempEl_ptr = currentEl_ptr;
    int i = 0;

    while(1)
    {
        if (tempEl_ptr == NULL)
            break;

        tempArray[i] = (*tempEl_ptr).Nb;
        tempEl_ptr = tempEl_ptr->previousEl_ptr;
        i++;
    }

    for(i = 1; i <= stackNb; i++)
    {
        printf("%f %fi\n", tempArray[stackNb-i].real, tempArray[stackNb-i].imaginary);
    }
    printf("\r\n\n");
}

void ClearStack()
{
    struct element previousEl;

    while (currentEl_ptr->previousEl_ptr != NULL)
    {
        previousEl = *currentEl_ptr;
        free(currentEl_ptr);
        currentEl_ptr = previousEl.previousEl_ptr;
    }
}

void Addition()
{
    complexNb nb1;
    complexNb nb2;
    complexNb result;

    nb1 = currentEl_ptr->Nb;
    Pop();
    nb2 = currentEl_ptr->Nb;
    Pop();

    result.real = nb1.real + nb2.real;
    result.imaginary = nb1.imaginary + nb2.imaginary;

    Push(result);
}

void Subtraction()
{
    complexNb nb1;
    complexNb nb2;
    complexNb result;

    nb1 = currentEl_ptr->Nb;
    Pop();
    nb2 = currentEl_ptr->Nb;
    Pop();

    result.real = nb1.real - nb2.real;
    result.imaginary = nb1.imaginary - nb2.imaginary;

    Push(result);
}

void Multiplication()
{
    complexNb nb1;
    complexNb nb2;
    complexNb result;

    nb1 = currentEl_ptr->Nb;
    Pop();
    nb2 = currentEl_ptr->Nb;
    Pop();

    result.real = nb1.real * nb2.real;
    result.imaginary = nb1.imaginary * nb2.imaginary;

    Push(result);
}

void Division()
{
    complexNb nb1;
    complexNb nb2;
    complexNb result;

    nb1 = currentEl_ptr->Nb;
    Pop();
    nb2 = currentEl_ptr->Nb;
    Pop();

    result.real = nb1.real / nb2.real;
    result.imaginary = nb1.imaginary / nb2.imaginary;

    Push(result);
}
