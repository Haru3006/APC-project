#include <stdio.h>
#include "main.h"
#include <string.h>
#include <ctype.h>

Status read_and_validate(char *argv[], Arguments *argInfo)
{
    if(argv[1] == NULL)
    {
        printf(BWHITE"--------------------------------------------------------------"RESET"\n");
        printf(RED "\nNot passed Operand 1" RESET"\n");
        printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        return FAILURE;
    }
    else if(validate_operand(argv[1]) == FAILURE)
    {
        printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        printf(RED "\nInvalid Operand1" RESET"\n");
        printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        return FAILURE;
    }
    else
    //printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
    printf(BLUE"\nOperand 1 Validation done" RESET"\n");
    printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
    if(argv[2] == NULL)
    {
        printf(RED "Operator not passed" RESET"\n");
        printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        return FAILURE;
    }
    if(strcmp(argv[2],"*")!=0 && strcmp(argv[2],"+")!=0 && strcmp(argv[2],"-")!=0 && strcmp(argv[2],"/")!=0 )
    {
        printf(RED "Invalid Operator" RESET"\n");
        printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        return FAILURE;
    }
    argInfo->operator = argv[2];

    if(argv[3] == NULL)
    {
        printf(RED "Not passed Operand2" RESET"\n");
        printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        return FAILURE;
    }
    else if(validate_operand(argv[3]) == FAILURE)
    {
        printf(RED "Invalid Operand2" RESET"\n");
        printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        return FAILURE;
    }
    else
    {
        printf(BLUE"Operand 2 Validation done" RESET"\n");
        printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        if(strcmp(argv[2], "-") == 0) //|| strcmp(argv[2], "/") == 0)
        {
            printf(BLACK "Checking operands for subtraction" RESET"\n");
            printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
            arrange_operands(argv[1], argv[3], argInfo);
        }
        else
        {
            argInfo->operand1 = argv[1];
            argInfo->operand2 = argv[3];
        }
    }
    return SUCCESS;
}

Status validate_operand(char *str)
{
    int i = 0;

    if (str[0] == '+' || str[0] == '-')
    {
        i = 1;
    }
    if (str[i] == '\0')
        return FAILURE;

    for (i; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}

Status convert_string_to_list(char *str, Dlist **head, Dlist **tail)
{
    int i=0;
    if(str[0] == '+' || str[0] == '-')
    {
        i=1;
    }
    for(i; str[i] != '\0'; i++)
    {
        Dlist *new = malloc(sizeof(Dlist));
        new->data = str[i] - '0';
        new->next = NULL;
        new->prev = NULL;

        if(*head == NULL)
        {
            *head = new;
            *tail = new;
        }
        else
        {
            (*tail)->next = new;
            new->prev = *tail;
            *tail = new;
        }
    }
    return SUCCESS;
}

void print_list(Dlist *head)
{
   while(head)
   {
       printf(YELLOW"%d", head->data);
       head = head->next;
   }
    printf("\n");
}

Status addition(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2, Dlist **result_head, Dlist **result_tail)
{
    *result_head = *result_tail = NULL;
    int carry=0, value, val1, val2;
    Dlist *tail1_temp = *tail1;
    Dlist *tail2_temp = *tail2;
    while(tail1_temp != NULL || tail2_temp != NULL)
    {
            if(tail1_temp==NULL) 
                val1 = 0;
            else
                val1 = tail1_temp->data;
            if(tail2_temp==NULL)
                val2 = 0;
            else
                val2 = tail2_temp->data;

            value = val1 + val2 + carry;
            carry = value/10;
            Dlist *new_result = malloc(sizeof(Dlist));
            new_result->prev = NULL;
            new_result->next = NULL;
            new_result->data = value % 10;
            if(*result_head == NULL)
            {
                *result_head = new_result;
                *result_tail = new_result;
            }
            else
            {
                (*result_head)->prev = new_result;
                new_result->next = *result_head;
                (*result_head) = new_result;
            }
            if(tail1_temp!=NULL)
            tail1_temp = tail1_temp->prev;
            if(tail2_temp!=NULL)
            tail2_temp = tail2_temp->prev;
    }
    if(carry > 0)
    {
        Dlist *new_result = malloc(sizeof(Dlist));
        new_result->data = carry;
        new_result->prev = NULL;
        new_result->next = NULL;
        (*result_head)->prev = new_result;
        new_result->next = *result_head;
        *result_head = new_result;
    }
    return SUCCESS;
}
        
void print_operation(Dlist *head)
{
    printf(GREEN"Head ->");
    while(head)
    {
        printf(GREEN"%d <-", head->data);
        head = head->next;
        if(head)
        printf(GREEN"> ");
    }
    printf(GREEN"Tail" RESET"\n");
}

Status subtraction(Dlist **head1, Dlist **head2,Dlist **tail1, Dlist **tail2,Dlist **result_head, Dlist **result_tail)
{
    int borrow = 0, val1, val2, value;
    Dlist *tail1_temp = *tail1;
    Dlist *tail2_temp = *tail2;
    *result_head = *result_tail = NULL;

    while(tail1_temp != NULL)
    {
        val1 = tail1_temp->data;

        if(tail2_temp != NULL)
            val2 = tail2_temp->data;
        else
            val2 = 0;
        val1 = val1 - borrow;

        if(val1 < val2)
        {
            val1 = val1 + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        value = val1 - val2;

        Dlist *new_result = malloc(sizeof(Dlist));
        new_result->data = value;
        new_result->prev = NULL;
        new_result->next = NULL;

        if(*result_head == NULL)
        {
            *result_head = new_result;
            *result_tail = new_result;
        }
        else
        {
            (*result_head)->prev = new_result;
            new_result->next = *result_head;
            *result_head = new_result;
        }

        tail1_temp = tail1_temp->prev;

        if(tail2_temp != NULL)
            tail2_temp = tail2_temp->prev;
    }
    while(*result_head && (*result_head)->data == 0 && (*result_head)->next != NULL)
    {
        Dlist *temp = *result_head;
        *result_head = (*result_head)->next;
        (*result_head)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}

void arrange_operands(char *op1, char *op2, Arguments *argInfo)
{
    int len1 = strlen(op1);
    int len2 = strlen(op2);

    if(len1 > len2)
    {
        argInfo->operand1 = op1;
        argInfo->operand2 = op2;
        //printf("Op1 > Op2\n");
    }
    else if(len2 > len1)
    {
        argInfo->operand1 = op2;
        argInfo->operand2 = op1;
        //printf("Op1 < Op2\n");
    }
    else
    {
        // if lengths equal compare digit by digit
        int i;
        for(i = 0; op1[i] != '\0'; i++)
        {
            if(op1[i] > op2[i])
            {
                argInfo->operand1 = op1;
                argInfo->operand2 = op2;
                //printf("op1 and op2 are of equal length and op1 > op2\n");
                return;
            }
            else if(op1[i] < op2[i])
            {
                argInfo->operand1 = op2;
                argInfo->operand2 = op1;
                //printf("op1 and op2 are of equal length and op1 < op2\n");
                return;
            }
        }

        // if both numbers equal
        argInfo->operand1 = op1;
        argInfo->operand2 = op2;
    }
}

int dl_delete_list(Dlist **head, Dlist **tail)
{
    if(*head == NULL)
    {
        return FAILURE;
    }
    else
    {
        while((*head)->next != NULL)
        {
            (*head) = (*head)->next;
            free((*head)->prev);
            (*head)->prev = NULL;
        }
        free(*head);
        *head = *tail = NULL;
    }
}

int operation_perform(char *op1, char *op2, char *operator, Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2)
{
    int compare = compare_lists(*head1, *head2);
    if((op1[0]=='+' || op1[0]>='0' && op1[0]<='9')&&(op2[0]=='-'))//op1 +ve and op2 -ve
    {
        if(operator[0] == '+')
        {
            operator[0] = '-';
            if(compare == 1)
                return -1;
            else
                return 1;
        }
        else if(operator[0] == '-')
        {
            operator[0] = '+';
            return 1;
        }
        else if(operator[0] == '*')
            return -1;
        else
            return -1;
    }
    if((op1[0]=='+' || op1[0]>='0' && op1[0]<='9')&&(op2[0]=='+' || op2[0]>='0' && op2[0]<='9')) //both r positive
    {
        if(operator[0] == '+')
            return 1;
        else if(operator[0] == '-')
        {
            operator[0] = '-';
            if(compare == 1)
                return -1;
            else
                return 1;
        }
        else if(operator[0] == '*')
            return 1;
        else
            return 1;
    }
    if((op1[0]=='-')&&(op2[0]=='+' || op2[0]>='0' && op2[0]<='9'))  //op1 -ve and op2 +ve
    {
        if(operator[0] == '+')
        {
            operator[0] = '-';
            if(compare == 1)
                return 1;
            else
                return -1;   
        }
        else if(operator[0] == '-')
        {
            operator[0] = '+';
            return -1;
        }
        else if(operator[0] == '*')
            return -1;
        else
            return -1;
    }
    if((op1[0]=='-')&&(op2[0]=='-')) // both -ve
    {
        if(operator[0] == '+')
        {
            return -1;   
        }
        else if(operator[0] == '-')
        {
            if(compare==1)
                return 1;
            else
                return -1;
        }
        else if(operator[0] == '*')
            return 1;
        else
            return 1;
    }
}

Status multiplication(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2, Dlist **result_head, Dlist **result_tail)
{
    Dlist *tail2_temp = *tail2;
    Dlist *temp1_head = NULL, *temp1_tail = NULL;
    Dlist *temp2_head = NULL, *temp2_tail = NULL;
    int count = 0;

    while (tail2_temp != NULL)
    {
        temp1_head = NULL;
        temp1_tail = NULL;

        int carry = 0;
        int val2 = tail2_temp->data;

        Dlist *tail1_temp = *tail1;

        // Multiply one full number
        while (tail1_temp != NULL)
        {
            int val1 = tail1_temp->data;
            int value = val1 * val2 + carry;
            carry = value / 10;

            Dlist *new = malloc(sizeof(Dlist));
            new->data = value % 10;
            new->prev = NULL;
            new->next = NULL;

            if (temp1_head == NULL)
            {
                temp1_head = new;
                temp1_tail = new;
            }
            else
            {
                temp1_head->prev = new;
                new->next = temp1_head;
                temp1_head = new;
            }

            tail1_temp = tail1_temp->prev;
        }

        // If carry remains
        if (carry > 0)
        {
            Dlist *new = malloc(sizeof(Dlist));
            new->data = carry;
            new->prev = NULL;
            new->next = temp1_head;
            temp1_head->prev = new;
            temp1_head = new;
        }

        // Add shift zeros at END
        for (int i = 0; i < count; i++)
        {
            Dlist *new = malloc(sizeof(Dlist));
            new->data = 0;
            new->next = NULL;
            new->prev = temp1_tail;
            temp1_tail->next = new;
            temp1_tail = new;
        }

        // First partial result
        if (*result_head == NULL)
        {
            *result_head = temp1_head;
            *result_tail = temp1_tail;
        }
        else
        {
            temp2_head = NULL;
            temp2_tail = NULL;

            addition(result_head, &temp1_head, result_tail, &temp1_tail, &temp2_head, &temp2_tail);

            dl_delete_list(&temp1_head, &temp1_tail);

            *result_head = temp2_head;
            *result_tail = temp2_tail;
        }

        tail2_temp = tail2_temp->prev;
        count++;
    }

    return SUCCESS;
}

int compare_lists(Dlist *head1, Dlist *head2)
{
    Dlist *temp1 = head1;
    Dlist *temp2 = head2;
    int len1 = 0, len2 = 0;

    while(temp1)
    { 
        len1++; 
        temp1 = temp1->next; 
    }
    while(temp2)
    { 
        len2++; 
        temp2 = temp2->next; 
    }

    if(len1 < len2) 
        return 1; //operand1 smaller
    if(len1 > len2) 
        return 2; //operand1 larger

    temp1 = head1;
    temp2 = head2;

    while(temp1 && temp2)
    {
        if(temp1->data < temp2->data) 
            return 1; //smaller
        if(temp1->data > temp2->data) 
            return 2;  //larger
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0; // equal
}

Status division(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2,Dlist **result_head, Dlist **result_tail)
{
    Dlist *temp1_head = NULL,*temp1_tail = NULL;
    Dlist *new = malloc(sizeof(Dlist));
    new->data = 0;
    new->prev = NULL;
    new->next = NULL;
    temp1_head = new;
    temp1_tail = new;

    Dlist *temp2_head = NULL,*temp2_tail = NULL;
    Dlist *new1 = malloc(sizeof(Dlist));
    new1->data = 1;
    new1->prev = NULL;
    new1->next = NULL;
    temp2_head = new1;
    temp2_tail = new1;

    Dlist *temp3_head = NULL,*temp3_tail = NULL;
    while(compare_lists(*head1, *head2) != 1)
    {
        Dlist *new_head = NULL, *new_tail = NULL;

        addition(&temp1_head, &temp2_head, &temp1_tail, &temp2_tail, &new_head, &new_tail);

        dl_delete_list(&temp1_head, &temp1_tail);

        temp1_head = new_head;
        temp1_tail = new_tail;

        subtraction(head1, head2, tail1, tail2, &temp3_head, &temp3_tail);

        dl_delete_list(head1, tail1);

        *head1 = temp3_head;
        *tail1 = temp3_tail;

        temp3_head = NULL;
        temp3_tail = NULL;
    }
    *result_head = temp1_head; 
    *result_tail = temp1_tail;
    return SUCCESS;
}
