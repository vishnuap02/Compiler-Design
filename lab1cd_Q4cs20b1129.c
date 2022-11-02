// Vishnu Abhay Parvatikar
// cs20b1129

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20
char infix[20], s[20], pref[20], q[20];
int top = -1;
struct list
{
    char data;
    struct list *next;
} *stack = NULL, *prefix = NULL, *prefix1 = NULL;
void push(int);
char pop();
void infix_to_prefix();
int precedence(char);
void push_frm_ptos(int);
char oper(char);
void dis(struct list *p)
{
    while (p != NULL)
    {
        printf("%c\t", p->data);
        p = p->next;
    }
    printf("\n");
}
int is_digit(char k)
{
    int n;
    char l[1];
    l[0] = k;
    n = atoi(l);
    return n;
}
void pushprefix()
{
    struct list *node = NULL;
    node = (struct list *)malloc(sizeof(struct list));
    node->data = pop();
    if (prefix == NULL)
    {
        node->next = NULL;
    }
    else
    {
        node->next = prefix;
    }
    prefix = node;
}
void push_prefix_from_infix(int i)
{
    struct list *node = NULL;
    node = (struct list *)malloc(sizeof(struct list));
    node->data = infix[i];
    if (prefix == NULL)
    {
        node->next = NULL;
    }
    else
    {
        node->next = prefix;
    }
    prefix = node;
}
int main()
{
    struct list *head = NULL;
    head = (struct list *)malloc(sizeof(struct list));
    printf("\nINPUT THE INFIX EXPRESSION : ");
    scanf("%s", infix);
    infix_to_prefix();
    dis(prefix);
    int k, i, x, j;
    k = 0;
    head = prefix;
    while (head != NULL)
    {
        q[k] = head->data;
        head = head->next;
        k++;
    }
    strrev(q);
    int vis;
    printf(":.........is EQUIVALENT PREFIX NOTATION \n ");
    return 0;
}
void push(int pos) // method that pushes the elements onto the character stack
{
    if (top == MAX - 1)
    {
        printf("\nSTACK OVERFLOW\n");
    }
    else
    {
        struct list *node = NULL;
        node = (struct list *)malloc(sizeof(struct list));
        node->data = infix[pos];
        if (stack == NULL)
        {
            node->next = NULL;
        }
        else
        {
            node->next = stack;
        }
        stack = node;
    }
}
char pop() // method that removes character from stack and returns them
{
    char ch;
    ch = stack->data;
    stack = stack->next;
    return (ch);
}
void infix_to_prefix()
{
    int i = 0, j = 0;
    strrev(infix); // Reverse the infix expression
    while (infix[i] != '\0')
    {
        // if an alphabet is found then copy it to the output string
        if (is_digit(infix[i]))
        {
            push_prefix_from_infix(i);
            i++;
        }
        else if (infix[i] == ')') // In the reversed string, closing bracket will be found first so put it in the stack
        {
            push(i);
            i++;
        }
        else if (infix[i] == '(')
        {
            while (stack->data != ')') // pop till opening bracket is found //
            {
                pushprefix();
            }
            pop();
            i++;
        }
        else
        {
            // if the stack if empty, then we simply put the operator in stack
            if (stack == NULL)
            {
                push(i);
                i++;
            }
            // if the precedence of operator is less than the stack top then
            else if (precedence(infix[i]) < precedence(stack->data))
            {
                pushprefix();
                while (precedence(stack->data) > precedence(infix[i]))
                {
                    pushprefix();
                    if (stack == NULL)
                    {
                        break;
                    }
                }
                push(i);
                i++;
            }
            // if the precedence of operator is greater than or equal to the stack top
            else if (precedence(infix[i]) >= precedence(stack->data))
            {
                push(i); // Push it onto the stack
                i++;
            }
        }
    }
    // At the end remove all the operators from the stack
    while (stack != NULL)
    {
        pushprefix();
    }
}
/* Function to return precedence of operators */
int precedence(char alpha)
{
    if (alpha == '+' || alpha == '-')
    {
        return (1);
    }
    if (alpha == '*' || alpha == '/')
    {
        return (2);
    }
    return 0;
}
void push_frm_ptos(int i)
{
    struct list *node = NULL;
    node = (struct list *)malloc(sizeof(struct list));
    node->data = q[i];
    if (stack == NULL)
    {
        node->next = NULL;
    }
    else
    {
        node->next = stack;
    }
    stack = node;
}
