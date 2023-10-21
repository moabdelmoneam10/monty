#include "monty.h"

/**
 * M_open_file_Y - opens a file
 * @file_name: the file namepath
 * Return: void
 */

void M_open_file_Y(char *file_name)
{
	FILE *fd = fopen(file_name, "r");

	if (file_name == NULL || fd == NULL)
		M_err_Y(2, file_name);

	M_read_file_Y(fd);
	fclose(fd);
}


/**
 * M_read_file_Y - reads a file
 * @fd: pointer to file descriptor
 * Return: void
 */

void M_read_file_Y(FILE *fd)
{
	int line_number, format = 0;
	char *buffer = NULL;
	size_t len = 0;

	for (line_number = 1; getline(&buffer, &len, fd) != -1; line_number++)
	{
		format = M_parse_line_Y(buffer, line_number, format);
	}
	free(buffer);
}


/**
 * M_parse_line_Y - Separates each line into tokens to determine
 * which function to call
 * @buffer: line from the file
 * @line_number: line number
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */

int M_parse_line_Y(char *buffer, int line_number, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		M_err_Y(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	M_find_func_Y(opcode, value, line_number, format);
	return (format);
}

/**
 * M_find_func_Y - find the appropriate function for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * @ln: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void M_find_func_Y(char *opcode, char *value, int ln, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", M_padd_to_stack_Y},
		{"pall", M_print_stack_Y},
		{"pint", M_print_top_Y},
		{"pop", M_pop_top_Y},
		{"M_nop_Y", M_nop_Y},
		{"swap", M_swap_nodes_Y},
		{"add", M_add_nodes_Y},
		{"sub", M_sub_nodes_Y},
		{"div", M_div_nodes_Y},
		{"mul", M_mul_nodes_Y},
		{"mod", M_mod_nodes_Y},
		{"pchar", M_print_char_Y},
		{"pstr", M_print_str_Y},
		{"rotl", M_rotl_Y},
		{"rotr", M_rotr_Y},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			M_acall_fun_Y(func_list[i].f, opcode, value, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		M_err_Y(3, ln, opcode);
}


/**
 * M_acall_fun_Y - Calls the required function.
 * @func: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @format: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void M_acall_fun_Y(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			M_err_Y(5, ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				M_err_Y(5, ln);
		}
		node = create_node(atoi(val) * flag);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			M_add_to_queue_Y(&node, ln);
	}
	else
		func(&head, ln);
}
