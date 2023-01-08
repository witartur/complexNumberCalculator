#include<stdio.h>
#include<stdlib.h>

struct complexNb
{
    float real;
    float imaginary;
};

struct element             // stack element -> number and pointer for previous number
{
    struct complexNb Nb;           
    struct element *previousEl_ptr;
};

struct element *currentEl_ptr = NULL;

void first(struct complexNb number);       // memory allocation for first element on stack
void push(struct complexNb number);                    // memory allocation for next element on stack
struct complexNb pop(void);                       // memory allocation for previous element on stack
void printStack(void);   
void clearStack(struct element *currentEl_ptr);                     
          

int main(void)
{
    int stackNb = 0;         //number of complexNb on my stack
    struct complexNb number;
    char tempArray [25];  // temp array for storing data for sscanf
    int sRes = 0;
    char sign;               //user input other than numbers
    
    while(1)
    {
        
        printf("\n********** COMPLEX NUMBER CALCULATOR **********\n");
        printf("\nPut the number, make calcualtion (+ - * /), C clear the stack or E exit the programm \n"); 
        // printStack();
        gets(tempArray);
        
        sRes = sscanf(tempArray, "%f", "%f", &number.real, &number.imaginary);
        
        if (stackNb == 0 && sRes == 1 && sRes == 2) 
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
            
        }
        else if (stackNb >= 1 && sRes == 2) 
        {
            push(number);
            stackNb ++;
            
        }
        else if (stackNb >= 1 && sRes == 1 )
        {
            number.imaginary = 0;
            push(number);  
            stackNb ++;
        }
        else
        {
            sscanf(tempArray, "%c", &sign);
            if(sign =='E')
            {   
                clearStack(currentEl_ptr);
                exit(0);
            }
            else if(sign =='C')
            {   
                clearStack(currentEl_ptr);
                stackNb = 0;
            }
            else if(stackNb == 0)
            {
            printf("Enter first number");
            }        

            else if(stackNb == 1)
            {
            printf("Enter second number");
            }
            else if (sign =='+')
            {
                
            }
            else if (sign =='-')
            {
                
            }
            else if (sign =='*')
            {
                
            }
            else if (sign =='/')
            {
                
            }
            
            else
            {
            printf("Read the instruction");
            }

        }



        system("cls");
    }
    
    return 0;

}

void first(struct complexNb number)
{
    struct element firstEl;

    currentEl_ptr = malloc(sizeof(struct element));
    
    firstEl.Nb = number;
    firstEl.previousEl_ptr = NULL;

    currentEl_ptr = &firstEl;

}

void push(struct complexNb number)
{
    struct element nextEl;
    
    nextEl.Nb = number;
    nextEl.previousEl_ptr = currentEl_ptr;
    currentEl_ptr = malloc(sizeof(struct element));
    currentEl_ptr = &nextEl;

}

struct complexNb pop(void)
{
    struct element previousEl;
   
    previousEl = *currentEl_ptr;
    free(currentEl_ptr);
    currentEl_ptr = previousEl.previousEl_ptr;
   
    return previousEl.Nb;
}

void printStack(void) 
{
    struct element *tempEl_ptr = malloc(sizeof(struct element));
    *tempEl_ptr = *currentEl_ptr;

    while(1)
    {
    
        printf("%f j%f\n", (*tempEl_ptr).Nb.real, (*tempEl_ptr).Nb.imaginary);
        if ((*tempEl_ptr).previousEl_ptr == NULL)
        {
            break;
        }

        *tempEl_ptr = *tempEl_ptr->previousEl_ptr;

        
    }
}

void clearStack(struct element *currentEl_ptr)
{
    struct element previousEl;
   
    while (currentEl_ptr->previousEl_ptr != NULL)
    { 
        previousEl = *currentEl_ptr;
        free(currentEl_ptr);
        currentEl_ptr = previousEl.previousEl_ptr;
    }

}