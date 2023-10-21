#ifndef MONTY_H
#define MONTY_H

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern stack_t *head;
typedef void (*op_func)(stack_t **, unsigned int);

/*file operations*/
void M_open_file_Y(char *file_name);
int M_parse_line_Y(char *buffer, int line_number, int format);
void M_read_file_Y(FILE *);
int M_len_charsY(FILE *);
void M_find_func_Y(char *, char *, int, int);

/*Stack operations*/
stack_t *create_node(int n);
void M_free_nodes_Y(void);
void M_print_stack_Y(stack_t **, unsigned int);
void M_padd_to_stack_Y(stack_t **, unsigned int);
void M_add_to_queue_Y(stack_t **, unsigned int);

void M_acall_fun_Y(op_func, char *, char *, int, int);

void M_print_top_Y(stack_t **, unsigned int);
void M_pop_top_Y(stack_t **, unsigned int);
void M_nop_Y(stack_t **, unsigned int);
void M_swap_nodes_Y(stack_t **, unsigned int);

/*Math operations with nodes*/
void M_add_nodes_Y(stack_t **, unsigned int);
void M_sub_nodes_Y(stack_t **, unsigned int);
void M_div_nodes_Y(stack_t **, unsigned int);
void M_mul_nodes_Y(stack_t **, unsigned int);
void M_mod_nodes_Y(stack_t **, unsigned int);

/*String operations*/
void M_print_char_Y(stack_t **, unsigned int);
void M_print_str_Y(stack_t **, unsigned int);
void M_rotl_Y(stack_t **, unsigned int);

/*Error hanlding*/
void M_err_Y(int error_code, ...);
void M_more_err_Y(int error_code, ...);
void M_more_err_Y(int error_code, ...);
void M_rotr_Y(stack_t **, unsigned int);

#endif
