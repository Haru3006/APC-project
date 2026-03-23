#ifndef MAIN_H
#define MAIN_H
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLACK "\033[1;30m"
#define RESET "\033[0m"
#define BLUE "\033[1;34m"
#define BWHITE   "\033[1;37m"
#define YELLOW  "\033[0;33m"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum
{
    SUCCESS, //0
    FAILURE = -1, //value
} Status;

typedef struct Arguments
{
    char *operator;
    char *operand1;
    char *operand2;
}Arguments;

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
}Dlist;

Status read_and_validate(char *argv[], Arguments *argInfo);
Status validate_operand(char *str);
Status convert_string_to_list(char *str, Dlist **head, Dlist **tail);
Status addition(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2, Dlist **result_head, Dlist **result_tail);
Status subtraction(Dlist **head1, Dlist **head2,Dlist **tail1, Dlist **tail2,Dlist **result_head, Dlist **result_tail);
void arrange_operands(char *op1, char *op2, Arguments *argInfo);
Status multiplication(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2, Dlist **result_head, Dlist **result_tail);
int dl_delete_list(Dlist **head, Dlist **tail);
Status division(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2, Dlist **result_head, Dlist **result_tail);
int compare_lists(Dlist *head1, Dlist *head2);
void print_operation(Dlist *head);
void print_list(Dlist *head);
int operation_perform(char *op1, char *op2, char *operator, Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2);


#endif