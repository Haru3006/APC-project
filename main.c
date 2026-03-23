#include "main.h"
#include <stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
    Arguments argInfo;

    int ret = read_and_validate(argv, &argInfo);
    if(ret == FAILURE)
    {
        printf(RED"Invalid Arguments" RESET"\n");
        printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        return 0;
    }
    printf(GREEN"Argument validated" RESET"\n");

    Dlist *head1=NULL, *tail1=NULL;
    Dlist *head2=NULL, *tail2=NULL;
    Dlist *result_head=NULL, *result_tail=NULL;
    
    ret = convert_string_to_list(argInfo.operand1, &head1, &tail1);
    ret = convert_string_to_list(argInfo.operand2, &head2, &tail2);

    printf(BLUE"Operand1 List: " RESET);
    print_operation(head1);

    printf(BLUE"Operand2 List: " RESET);
    print_operation(head2);
    printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
    int return_sign = operation_perform(argInfo.operand1, argInfo.operand2, argInfo.operator, &head1, &head2, &tail1, &tail2);
  
    switch(argInfo.operator[0])
    {
        case '+':
        ret = addition(&head1,&head2,&tail1,&tail2,&result_head, &result_tail);
        if(ret == FAILURE)
        {
            printf(RED"Addition not performed" RESET"\n");
            printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        }
        else if(ret == SUCCESS)
        {
            //printf("Addition done successfully\n");
            if(return_sign == -1)
            {
                result_head->data = result_head->data * -1;
            }
            printf(GREEN"The value is: ");
            print_list(result_head);
            printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");

        }
        break;
        case '-':
        ret = subtraction(&head1,&head2,&tail1,&tail2,&result_head, &result_tail);
        if(ret == FAILURE)
        {
            printf(RED"Subtraction not performed" RESET"\n");
            printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        }
        else if(ret == SUCCESS)
        {
            //printf("Subtraction done successfully\n");
            if(return_sign == -1)
            {
                result_head->data = result_head->data * -1;
            }
            printf(GREEN"The value is: ");
            print_list(result_head);
            printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        }
        break;
        case '*':
        ret = multiplication(&head1,&head2,&tail1,&tail2,&result_head, &result_tail);
        if(ret == FAILURE)
        {
            printf(RED"Multiplication not performed" RESET"\n");
            printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        }
        else if(ret == SUCCESS)
        {
            //printf("Multiplication done successfully\n");
            if(return_sign == -1)
            {
                result_head->data = result_head->data * -1;
            }
            printf(GREEN"The value is: ");
            print_list(result_head);
            printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
        }
        break;
        case '/':
        if(compare_lists(head1, head2)<0)
        {
            Dlist *new = malloc(sizeof(Dlist));
            new->data = 0;
            new->prev = NULL;
            new->next = NULL;
            result_head = new;
            print_list(result_head);
        }
        else if(strcmp(argv[1],argv[3]) == 0)
        {
            Dlist *new = malloc(sizeof(Dlist));
            new->data = 1;
            new->prev = NULL;
            new->next = NULL;
            result_head = new;
            print_list(result_head);
        }
        else
        {
            ret = division(&head1,&head2,&tail1,&tail2,&result_head, &result_tail);
            if(ret == FAILURE)
            {
                printf(RED"Division not performed" RESET"\n");
                printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
            }  
            else if(ret == SUCCESS)
            {
               // printf("Division done successfully\n");
                if(return_sign == -1)
            {
                result_head->data = result_head->data * -1;
            }
                printf(GREEN"The value is: ");
                print_list(result_head);
                printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");
            }
        }
        break;
        default:
        printf(RED"Kindly pass appropriate opeator to perform" RESET"\n");
        printf(BWHITE"--------------------------------------------------------------------------"RESET"\n");

    }
    dl_delete_list(&head1, &tail1);
    dl_delete_list(&head2, &tail2);
    dl_delete_list(&result_head, &result_tail);

    return 0;
}
