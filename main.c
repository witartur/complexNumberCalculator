#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct complexNb
{
    float real;
    float imaginary;
};

struct element                                  // stack element -> number and pointer for previous number
{
    struct complexNb Nb;           
    struct element *previousEl_ptr;
};

struct element *currentEl_ptr = NULL;
bool warning = false;                           // flag for printing the warning

void first(struct complexNb number);            // memory allocation for first element on stack
void push(struct complexNb number);             // memory allocation for next element on stack
void pop(void);                                 // memory allocation for previous element on stack
void printStack(int stackNb, bool warning);     // printing whole stack
void clearStack(void);                          // clearing whole stack   
void addition(void);
void subtraction(void);
void multiplication(void);
void division(void);
          

int main(void)
{
    int stackNb = 0;                // number of elements on the stack
    struct complexNb number;        // user input number
    char tempArray [25];            // temp array for storing data for sscanf
    int sRes = 0;                   // auxilary variable for sscanf function result
    char sign;                      // user input other than numbers
    
    while(1)
    {
        system("cls");
        // fputs("\x1b[H\x1b[2J\x1b[3J", stdout); fflush(stdout);
        printf("\n********** COMPLEX NUMBER CALCULATOR **********\r\n");
        printf("\nPut the number, make calcualtion (+ - * /), press C for clear the stack, E for exit the programm or P for deleting previous number \r\n"); 
        printStack(stackNb, warning); 
        gets(tempArray);
        
        sRes = sscanf(tempArray, "%f" "%f", &number.real, &number.imaginary);
        
        if (stackNb == 0 && (sRes == 1 || sRes == 2)) 
        {  
            if (sRes == 2)
            {
                first(number);
                stackNb ++;
            }
            else if (sRes == 1)
            {
                number.imaginary = 0;
                first(number);
                stackNb ++;
            }
            warning = false;
        }
        else if (stackNb >= 1 && sRes == 2) 
        {
            push(number);
            stackNb ++;
            warning = false;
        }
        else if (stackNb >= 1 && sRes == 1 )
        {
            number.imaginary = 0;
            push(number);  
            stackNb ++;
            warning = false;
        }
        else
        {
            sscanf(tempArray, "%c", &sign);
            if(sign =='E' || sign =='e')
            {   
                clearStack();
                exit(0);
                warning = false;
            }
            else if(sign =='C'|| sign =='c')
            {   
                clearStack();
                stackNb = 0;
                warning = false;
            }
            else if(sign =='P'|| sign =='p')
            {   
                pop();
                stackNb--;
                warning = false;
            }
            
            else if (sign =='+')
            {
                addition();
                stackNb--;
                warning = false;
            }
            else if (sign =='-')
            {
                subtraction();
                stackNb--;
                warning = false;
            }
            else if (sign =='*')
            {
                multiplication();
                stackNb--;
                warning = false;
            }
            else if (sign =='/')
            {
                division();
                stackNb--;
                warning = false;
            } 
            else
            {
            warning = true;
            }
        }

    }
    
    free(currentEl_ptr);

    return 0;

}

void first(struct complexNb number)
{
    currentEl_ptr = malloc(sizeof(struct element));
    
    (*currentEl_ptr).Nb = number;
    (*currentEl_ptr).previousEl_ptr = NULL;
}

void push(struct complexNb number)
{
    struct element *nextEl_ptr;
    nextEl_ptr = malloc(sizeof(struct element));
    
    (*nextEl_ptr).Nb = number;
    (*nextEl_ptr).previousEl_ptr = currentEl_ptr;
    
    currentEl_ptr = nextEl_ptr;
}

void pop(void)
{
    struct element *tempEl_ptr;         // temporary element
   
    tempEl_ptr = currentEl_ptr;
    currentEl_ptr = tempEl_ptr->previousEl_ptr;
}

void printStack(int stackNb, bool warning) 
{
    struct element *tempEl_ptr = NULL;
    struct complexNb tempArray[stackNb];
 
    tempEl_ptr = currentEl_ptr;
    int i = 0;

    while(1)
    {
        if (tempEl_ptr == NULL)
        {
            break;
        }

        tempArray[i] = (*tempEl_ptr).Nb;
        tempEl_ptr = tempEl_ptr->previousEl_ptr;
        i++;
    }

    for(i=1; i<=stackNb ;i++ )
    {  
        printf("%f %fi\n", tempArray[stackNb-i].real, tempArray[stackNb-i].imaginary);
    }

    printf("\r\n\n");

    if (warning == true)
    {
        printf("***READ THE INSTRUCTION AGAIN***\r\n");
    }
    
    
}

void clearStack()
{
    struct element previousEl;
   
    while (currentEl_ptr->previousEl_ptr != NULL)
    { 
        previousEl = *currentEl_ptr;
        free(currentEl_ptr);
        currentEl_ptr = previousEl.previousEl_ptr;
    }

}

void addition()
{
    struct complexNb nb1;
    struct complexNb nb2;
    struct complexNb result;

    nb1 = currentEl_ptr->Nb;
    pop();
    nb2 = currentEl_ptr->Nb;
    pop();

    result.real = nb1.real + nb2.real;
    result.imaginary = nb1.imaginary + nb2.imaginary;

    push(result);

}

void subtraction()
{
    struct complexNb nb1;
    struct complexNb nb2;
    struct complexNb result;

    nb1 = currentEl_ptr->Nb;
    pop();
    nb2 = currentEl_ptr->Nb;
    pop();

    result.real = nb1.real - nb2.real;
    result.imaginary = nb1.imaginary - nb2.imaginary;

    push(result);

}

void multiplication()
{
    struct complexNb nb1;
    struct complexNb nb2;
    struct complexNb result;

    nb1 = currentEl_ptr->Nb;
    pop();
    nb2 = currentEl_ptr->Nb;
    pop();

    result.real = nb1.real * nb2.real;
    result.imaginary = nb1.imaginary * nb2.imaginary;

    push(result);

}

void division()
{
    struct complexNb nb1;
    struct complexNb nb2;
    struct complexNb result;

    nb1 = currentEl_ptr->Nb;
    pop();
    nb2 = currentEl_ptr->Nb;
    pop();

    result.real = nb1.real / nb2.real;
    result.imaginary = nb1.imaginary / nb2.imaginary;

    push(result);

}