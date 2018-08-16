#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>


///////////////////////////////////////////////////////////////////////////////////////////////////////////
////ERROR HANDLER SECTION////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

//Types of error for this project.
#define OUT_OF_MEMORY      0
#define STACK_OVERFLOW     1
#define STACK_UNDERFLOW    2
#define UNEXPECTED_TOKEN   3
#define ZERO_DIVISION      4
#define ROOT_OF_NEGATIVE   5
#define LOG_OF_ZERO        6
#define LOG_OF_NEGATIVE    7
#define UNEXPECTED_ALIAS   8
#define DICT_OUT_OF_MEMORY 9

/**********************************************************************************************************
NAME  : THROW ERROR
LIBS  : stdlib.h, stdio.h
NOTES : this function was created for handling errors that are specific to this project. List of existing
        error types located above.
**********************************************************************************************************/
void throw_error(int error_code)
{
	switch (error_code)
	{
		case OUT_OF_MEMORY :
			fprintf(stderr, "Out of memory\n");
			exit(EXIT_FAILURE);

		case STACK_OVERFLOW :
			fprintf(stderr, "Stack overflow\n");
			exit(EXIT_FAILURE);

		case STACK_UNDERFLOW :
			fprintf(stderr, "Stack underflow\n");
			exit(EXIT_FAILURE);

		case UNEXPECTED_TOKEN:
			fprintf(stderr, "Unexpected token\n");
			exit(EXIT_FAILURE);

		case ZERO_DIVISION:
			fprintf(stderr, "Zero division\n");
			exit(EXIT_FAILURE);

		case ROOT_OF_NEGATIVE:
			fprintf(stderr, "Root of negative\n");
			exit(EXIT_FAILURE);

		case LOG_OF_ZERO:
			fprintf(stderr, "Logarithm of zero\n");
			exit(EXIT_FAILURE);

		case LOG_OF_NEGATIVE:
			fprintf(stderr, "Logarithm of negative\n");
			exit(EXIT_FAILURE);

		case UNEXPECTED_ALIAS:
			fprintf(stderr, "Unexpected alias\n");
			exit(EXIT_FAILURE);

		case DICT_OUT_OF_MEMORY:
			fprintf(stderr, "There is no room in the dictionary");
			exit(EXIT_FAILURE);

		default :
			fprintf(stderr, "Unknown exeption\n");
			exit(EXIT_FAILURE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////ERROR HANDLER SECTION END///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////
////DICTIONARY SECTION//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************************************************
NAME  : DICTIONARY ENTRY
LIBS  : -
NOTES : -
**********************************************************************************************************/
struct dictionary_entry
{
	char* key;
	char* value;
};


/**********************************************************************************************************
NAME  : DICTIONARY
LIBS  : -
NOTES : -
**********************************************************************************************************/
struct dictionary
{
	struct dictionary_entry* current_entry;
	struct dictionary_entry* origin_position;
	int dictionary_capacity;
	int current_entry_count;
};


/**********************************************************************************************************
NAME  : DICTIONARY INITIALIZE
LIBS  : -
NOTES : -
**********************************************************************************************************/
struct dictionary* dictionary_initialize(int dictionary_capacity)
{
	struct dictionary* dictionary = calloc(1, sizeof(struct dictionary));
	if (dictionary == NULL)
	{
		throw_error(OUT_OF_MEMORY);
	}

	dictionary->current_entry = calloc(dictionary_capacity, sizeof(struct dictionary_entry));
	if (dictionary->current_entry == NULL)
	{
		throw_error(OUT_OF_MEMORY);
	}
	
	dictionary->origin_position = dictionary->current_entry;
	dictionary->dictionary_capacity = dictionary_capacity;
	dictionary->current_entry_count = 0;

	return dictionary;
}


/**********************************************************************************************************
NAME  : DICTIONARY FREE
LIBS  : -
NOTES : always use this function when finish work with dictionary.
**********************************************************************************************************/
void dictionary_free(struct dictionary* dictionary)
{
	dictionary->current_entry = dictionary->origin_position;

	for (size_t i = 0; i < dictionary->dictionary_capacity; i++)
	{
		if (dictionary->current_entry->key != NULL && dictionary->current_entry->key != NULL)
		{
			free(dictionary->current_entry->key);
			free(dictionary->current_entry->value);
		}

		dictionary->current_entry++;
	}

	dictionary->current_entry = dictionary->origin_position;
	free(dictionary->current_entry);
	free(dictionary);
}


/**********************************************************************************************************
NAME  : DICTIONARY ADD
LIBS  : -
NOTES : -
**********************************************************************************************************/
void dictionary_add(struct dictionary* dictionary, char* key, char* value)
{
	dictionary->current_entry = dictionary->origin_position;
	for (size_t i = 0; i <= dictionary->dictionary_capacity; i++)
	{
		if (dictionary->current_entry->key == NULL && dictionary->current_entry->value == NULL)
		{
			dictionary->current_entry->key = _strdup(key);
			if (dictionary->current_entry->key == NULL)
			{
				throw_error(OUT_OF_MEMORY);
			}

			dictionary->current_entry->value = _strdup(value);
			if (dictionary->current_entry->value == NULL)
			{
				throw_error(OUT_OF_MEMORY);
			}

			return;
		}
		dictionary->current_entry++;
	}

	throw_error(DICT_OUT_OF_MEMORY);
}


/**********************************************************************************************************
NAME  : DICTIONARY DELETE
LIBS  : -
NOTES : if this function will not find an entry with given key, it will do nothing.
**********************************************************************************************************/
void dictionary_delete(struct dictionary* dictionary, char* key)
{
	struct dictionary_entry* search_pointer = dictionary->origin_position;

	for (size_t i = 0; i <= dictionary->dictionary_capacity; i++)
	{
		if (search_pointer->key == key)
		{
			free(search_pointer->key);
			free(search_pointer->value);
			search_pointer->key = NULL;
			search_pointer->value = NULL;

			dictionary->current_entry_count--;
			break;
		}
		else
		{
			search_pointer++;
		}
	}
}


/**********************************************************************************************************
NAME  : DICTIONARY FIND
LIBS  : -
NOTES : if this function will not find an entry with given key, it will return NULL pointer.
**********************************************************************************************************/
char* dictionary_find(struct dictionary* dictionary, char* key)
{
	char* found_value = NULL;

	dictionary->current_entry = dictionary->origin_position;
	for (size_t i = 0; i < dictionary->dictionary_capacity; i++)
	{
		if (dictionary->current_entry->key != NULL && strcmp(dictionary->current_entry->key, key) == 0)
		{
			found_value = dictionary->current_entry->value;
			break;
		}
		else
		{
			dictionary->current_entry++;
		}
	}

	return found_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////DICTIONARY SECTION END//////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////
////DOUBLE STACK SECTION////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************************************************
NAME  : STACK DOUBLE
LIBS  : -
NOTES : this structure describes stack of double precision data.
**********************************************************************************************************/
struct stack_double
{
	double* head_element;
	double* origin_position;
	size_t stack_capacity;
	size_t current_elements_count;
};


/**********************************************************************************************************
NAME  : STACK DOUBLE INITIALIZE
LIBS  : stdlib.h, stdion.h
NOTES : -
**********************************************************************************************************/
struct stack_double* stack_double_initialize(size_t stack_capacity)
{
	struct stack_double* stack_double = calloc(1, sizeof(struct stack_double));
	if (stack_double == NULL)
	{
		throw_error(OUT_OF_MEMORY);
	}

	stack_double->head_element = calloc(stack_capacity, sizeof(double));
	if (stack_double->head_element == NULL)
	{
		throw_error(OUT_OF_MEMORY);
	}
	stack_double->origin_position = stack_double->head_element;
	stack_double->stack_capacity = stack_capacity;
	stack_double->current_elements_count = 0;

	return stack_double;
}


/**********************************************************************************************************
NAME  : PUSH STACK DOUBLE
LIBS  : -
NOTES : -
**********************************************************************************************************/
void push_stack_double(struct stack_double* stack_pointer, double value_to_push)
{
	if (stack_pointer->current_elements_count != stack_pointer->stack_capacity)
	{
		stack_pointer->head_element++;
		*(stack_pointer->head_element) = value_to_push;
		stack_pointer->current_elements_count++;
	}
	else
	{
		throw_error(STACK_OVERFLOW);
	}
}


/**********************************************************************************************************
NAME  : POP STACK DOUBLE
LIBS  : -
NOTES : -
**********************************************************************************************************/
double pop_stack_double(struct stack_double* stack_pointer)
{
	if (stack_pointer->current_elements_count != 0)
	{
		double popped_element = *(stack_pointer->head_element);
		stack_pointer->head_element--;
		stack_pointer->current_elements_count--;

		return popped_element;
	}
	else
	{
		throw_error(STACK_UNDERFLOW);
	}
}


/**********************************************************************************************************
NAME  : STACK DOUBLE FREE
LIBS  : -
NOTES : always use this function when finish work with double stack.
**********************************************************************************************************/
void stack_double_free(struct stack_double* stack_pointer)
{
	stack_pointer->head_element = stack_pointer->origin_position;
	free(stack_pointer->head_element);
	free(stack_pointer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////DOUBLE STACK SECTION END////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////
////STACK STRING SECTION////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************************************************
NAME  : STRING
LIBS  : -
NOTES : -
**********************************************************************************************************/
struct string
{
	char* char_pointer;
};


/**********************************************************************************************************
NAME  : STACK STRING
LIBS  : -
NOTES : -
**********************************************************************************************************/
struct stack_string
{
	struct string* head_element;
	struct string* origin_position;
	size_t stack_capacity;
	size_t current_elements_count;
};


/**********************************************************************************************************
NAME  : STACK STRING INITIALIZE
LIBS  : stdlib.h, stdio.h
NOTES : -
**********************************************************************************************************/
struct stack_string* stack_string_initialize(size_t stack_capacity)
{
	struct stack_string* stack_string = calloc(1, sizeof(struct stack_string));

	if (stack_string == NULL)
	{
		throw_error(OUT_OF_MEMORY);
	}

	const size_t BUFFER_BYTE = 1;
	stack_string->head_element = calloc(stack_capacity + BUFFER_BYTE, sizeof(struct string));

	stack_string->origin_position = stack_string->head_element;

	//fill buffer byte with zero character.
	stack_string->head_element->char_pointer = _strdup("");
	stack_string->head_element++;

	stack_string->stack_capacity = stack_capacity;
	stack_string->current_elements_count = 0;

	

	if (stack_string->head_element == NULL)
	{
		throw_error(OUT_OF_MEMORY);
	}

	return stack_string;
}


/**********************************************************************************************************
NAME  : PUSH STACK STRING
LIBS  : string.h
NOTES : -
**********************************************************************************************************/
void push_stack_string(struct stack_string* stack_pointer, struct string* value_to_push)
{
	char* char_pointer = _strdup(value_to_push->char_pointer);
	if (char_pointer == NULL)
	{
		throw_error(OUT_OF_MEMORY);
	}

	if (stack_pointer->current_elements_count != stack_pointer->stack_capacity)
	{
		stack_pointer->head_element++;
		stack_pointer->head_element->char_pointer = char_pointer;
		stack_pointer->current_elements_count++;
	}
	else
	{
		throw_error(STACK_OVERFLOW);
	}
}


/**********************************************************************************************************
NAME  : POP STACK STRING
LIBS  : -
NOTES : -
**********************************************************************************************************/
struct string* pop_stack_string(struct stack_string* stack_pointer)
{
	if (stack_pointer->current_elements_count != 0)
	{
		struct string* popped_element = stack_pointer->head_element;
		stack_pointer->head_element--;
		stack_pointer->current_elements_count--;

		return popped_element;
	}
	else
	{
		throw_error(STACK_UNDERFLOW);
	}
}


/**********************************************************************************************************
NAME  : PEEK STACK STRING
LIBS  : -
NOTES : -
**********************************************************************************************************/
struct string* peek_stack_string(struct stack_string* stack_pointer)
{
	struct string* peeked_element;
	if (stack_pointer->head_element->char_pointer != NULL)
	{
		peeked_element = stack_pointer->head_element;
	}
	else
	{
		stack_pointer->head_element--;
		peeked_element = stack_pointer->head_element;
		stack_pointer->head_element++;
	}
	return peeked_element;
}


/**********************************************************************************************************
NAME  : STACK STRING FREE
LIBS  : -
NOTES : always use this function when finish work with string stack.
**********************************************************************************************************/
void stack_string_free(struct stack_string* stack_pointer)
{
	stack_pointer->head_element = stack_pointer->origin_position;

	for (size_t i = 0; i < stack_pointer->stack_capacity; i++)
	{
		free(stack_pointer->head_element->char_pointer);
		stack_pointer->head_element++;
	}

	stack_pointer->head_element = stack_pointer->origin_position;

	free(stack_pointer->head_element);
	free(stack_pointer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////STACK STRING SECTION END////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////
////STACK MATHEMATICAL FUNCTIONS SECTION////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/*

If you want to add new math operation you need:
1. Increase ARRAY_CAPACITY constant in function "get_math_operations_entries_array()" by one;

2. Add new operation entry within OPERATIONS SECTION by template:

operation_entry_array->function_entry_pointer->function_alias = "operation alias";
operation_entry_array->operation_entry_pointer->operator_associativity = *operation associativity*;
operation_entry_array->function_entry_pointer->pointer_on_function = *addres of function which handle this
operation*;
operation_entry_array->function_entry_pointer++;


If you want to add new math function you need:
1. Increase ARRAY_CAPACITY constant in function "get_math_function_entries_array()" by one;

2. Add new operation entry within FUNCTIONS SECTION by template:

func_entry_array->function_entry_pointer->function_alias = "function alias";
func_entry_array->function_entry_pointer->pointer_on_function = *addres of function which handle this
function*;
func_entry_array->function_entry_pointer++;

*/

/**********************************************************************************************************
NAME  : STACK ADD
LIBS  : -
NOTES : this function implement stack add operation.
**********************************************************************************************************/
void stack_add(struct stack_double* stack_pointer)
{
	double second_operand = pop_stack_double(stack_pointer);
	double first_operand = pop_stack_double(stack_pointer);

	double sum = first_operand + second_operand;

	push_stack_double(stack_pointer, sum);
}


/**********************************************************************************************************
NAME  : STACK SUBTRACT
LIBS  : -
NOTES : this function implement stack subtract operation.
**********************************************************************************************************/
void stack_subtract(struct stack_double* stack_pointer)
{
	double second_operand = pop_stack_double(stack_pointer);
	double first_operand = pop_stack_double(stack_pointer);

	double difference = first_operand - second_operand;

	push_stack_double(stack_pointer, difference);
}


/**********************************************************************************************************
NAME  : STACK MULTIPLY
LIBS  : -
NOTES : this function implement stack multiply operation.
**********************************************************************************************************/
void stack_multiply(struct stack_double* stack_pointer)
{
	double second_operand = pop_stack_double(stack_pointer);
	double first_operand = pop_stack_double(stack_pointer);

	double product = first_operand * second_operand;

	push_stack_double(stack_pointer, product);
}


/**********************************************************************************************************
NAME  : STACK DIVIDE
LIBS  : -
NOTES : this function implement stack divide operation.
**********************************************************************************************************/
void stack_divide(struct stack_double* stack_pointer)
{
	double second_operand = pop_stack_double(stack_pointer);
	double first_operand = pop_stack_double(stack_pointer);

	if (second_operand != 0)
	{
		double quotient = first_operand / second_operand;

		push_stack_double(stack_pointer, quotient);
	}
	else
	{
		throw_error(ZERO_DIVISION);
	}
}


/**********************************************************************************************************
NAME  : STACK SQRT
LIBS  : math.h
NOTES : this function implement stack operation of taking square root.
**********************************************************************************************************/
void stack_sqrt(struct stack_double* stack_pointer)
{
	double operand = pop_stack_double(stack_pointer);

	if (operand >= 0)
	{
		double taking_result = sqrt(operand);

		push_stack_double(stack_pointer, taking_result);
	}
	else
	{
		throw_error(ROOT_OF_NEGATIVE);
	}
}


/**********************************************************************************************************
NAME  : STACK POWER
LIBS  : math.h
NOTES : this function implement stack operation of exponentiation.
**********************************************************************************************************/
void stack_power(struct stack_double* stack_pointer)
{
	double second_operand = pop_stack_double(stack_pointer);
	double first_operand = pop_stack_double(stack_pointer);

	double power_result = pow(first_operand, second_operand);

	push_stack_double(stack_pointer, power_result);
}


/**********************************************************************************************************
NAME  : STACK NEGATIVE
LIBS  : math.h
NOTES : this function implement stack operation of changing sign.
**********************************************************************************************************/
void stack_negative(struct stack_double* stack_pointer)
{
	double operand = pop_stack_double(stack_pointer);

	double negative_result = operand * -1;

	push_stack_double(stack_pointer, negative_result);
}


/**********************************************************************************************************
NAME  : STACK ABS
LIBS  : math.h
NOTES : this function implement stack operation of calculating absolute value of number.
**********************************************************************************************************/
void stack_abs(struct stack_double* stack_pointer)
{
	double operand = pop_stack_double(stack_pointer);

	double abs_result = fabs(operand);

	push_stack_double(stack_pointer, abs_result);
}


/**********************************************************************************************************
NAME  : STACK SIN
LIBS  : math.h
NOTES : this function implement stack operation of calculating sinus.
**********************************************************************************************************/
void stack_sin(struct stack_double* stack_pointer)
{
	double operand = pop_stack_double(stack_pointer);

	double sin_result = sin(operand);

	push_stack_double(stack_pointer, sin_result);
}


/**********************************************************************************************************
NAME  : STACK COS
LIBS  : math.h
NOTES : this function implement stack operation of calculating cosine.
**********************************************************************************************************/
void stack_cos(struct stack_double* stack_pointer)
{
	double operand = pop_stack_double(stack_pointer);

	double cos_result = cos(operand);

	push_stack_double(stack_pointer, cos_result);
}


/**********************************************************************************************************
NAME  : STACK ARCCOS
LIBS  : math.h
NOTES : this function implement stack operation of calculating arccosine.
**********************************************************************************************************/
void stack_arccos(struct stack_double* stack_pointer)
{
	double operand = pop_stack_double(stack_pointer);

	double arccos_result = acos(operand);

	push_stack_double(stack_pointer, arccos_result);
}


/**********************************************************************************************************
NAME  : STACK TAN
LIBS  : math.h
NOTES : this function implement stack operation of calculating tangent.
**********************************************************************************************************/
void stack_tan(struct stack_double* stack_pointer)
{
	double operand = pop_stack_double(stack_pointer);

	double tan_result = tan(operand);
	
	push_stack_double(stack_pointer, tan_result);
}


/**********************************************************************************************************
NAME  : STACK COTAN
LIBS  : math.h
NOTES : this function implement stack operation of calculating cotangent.
**********************************************************************************************************/
void stack_cotan(struct stack_double* stack_pointer)
{
	double operand = pop_stack_double(stack_pointer);

	double cotan_result = 1 / tan(operand);

	push_stack_double(stack_pointer, cotan_result);
}


/**********************************************************************************************************
NAME  : STACK LN
LIBS  : math.h
NOTES : this function implement stack operation of calculating natural logarithm.
**********************************************************************************************************/
void stack_ln(struct stack_double* stack_pointer)
{
	double operand = pop_stack_double(stack_pointer);

	if (operand > 0)
	{
		double natlog_result = log(operand);

		push_stack_double(stack_pointer, natlog_result);
	}
	else
	{
		if (operand == 0)
			throw_error(LOG_OF_ZERO);
		else
			throw_error(LOG_OF_NEGATIVE);
	}
}


/**********************************************************************************************************
NAME  : STACK MORE
LIBS  : ?
NOTES : ?
**********************************************************************************************************/
void stack_more(struct stack_double* stack_pointer)
{
	double second_operand = pop_stack_double(stack_pointer);
	double first_operand = pop_stack_double(stack_pointer);

	int result = 0;
	if (first_operand > second_operand)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}

	push_stack_double(stack_pointer, result);
}


/**********************************************************************************************************
NAME  : STACK LESS
LIBS  : ?
NOTES : ?
**********************************************************************************************************/
void stack_less(struct stack_double* stack_pointer)
{
	double second_operand = pop_stack_double(stack_pointer);
	double first_operand = pop_stack_double(stack_pointer);

	int result = 0;
	if (first_operand < second_operand)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}

	push_stack_double(stack_pointer, result);
}


/**********************************************************************************************************
NAME  : STACK EQUALS
LIBS  : ?
NOTES : ?
**********************************************************************************************************/
void stack_equals(struct stack_double* stack_pointer)
{
	double second_operand = pop_stack_double(stack_pointer);
	double first_operand = pop_stack_double(stack_pointer);

	int result = 0;
	if (first_operand == second_operand)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}

	push_stack_double(stack_pointer, (double)result);
}


/**********************************************************************************************************
NAME  : STACK DIV
LIBS  : ?
NOTES : ?
**********************************************************************************************************/
void stack_div(struct stack_double* stack_pointer)
{
	double second_operand = pop_stack_double(stack_pointer);
	double first_operand = pop_stack_double(stack_pointer);

	if (second_operand != 0)
	{
		div_t division_result = div(first_operand, second_operand);

		push_stack_double(stack_pointer, (double)division_result.quot);
	}
	else
	{
		throw_error(ZERO_DIVISION);
	}
}


/**********************************************************************************************************
NAME  : STACK MOD
LIBS  : ?
NOTES : ?
**********************************************************************************************************/
void stack_mod(struct stack_double* stack_pointer)
{
	double second_operand = pop_stack_double(stack_pointer);
	double first_operand = pop_stack_double(stack_pointer);

	if (second_operand != 0)
	{
		div_t division_result = div(first_operand, second_operand);

		push_stack_double(stack_pointer, (double)division_result.rem);
	}
	else
	{
		throw_error(ZERO_DIVISION);
	}
}


/**********************************************************************************************************
NAME  : STACK OR
LIBS  : ?
NOTES : ?
**********************************************************************************************************/
void stack_or(struct stack_double* stack_pointer)
{
	double second_operand = pop_stack_double(stack_pointer);
	double first_operand = pop_stack_double(stack_pointer);

	int result = 0;
	if (first_operand == 1 || second_operand == 1)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	push_stack_double(stack_pointer, (double)result);
}


/**********************************************************************************************************
NAME  : OPERATION ENTRY
LIBS  : -
NOTES : -
**********************************************************************************************************/
struct operation_entry
{
	char* operation_alias;
	int operator_associativity;
	void(*pointer_on_function)(struct stack_double*);
};


/**********************************************************************************************************
NAME  : FUNCTION ENTRY
LIBS  : -
NOTES : -
**********************************************************************************************************/
struct function_entry
{
	char* function_alias;
	void(*pointer_on_function)(struct stack_double*);
};


/**********************************************************************************************************
NAME  : OPERATOR ENTRY ARRAY
LIBS  : -
NOTES : -
**********************************************************************************************************/
struct operation_entry_array
{
	struct operation_entry* operation_entry_pointer;
	struct operation_entry* operation_entry_pointer_origin_position;
	size_t array_capacity;
};


/**********************************************************************************************************
NAME  : FUNCTION ENTRY ARRAY
LIBS  : -
NOTES : -
**********************************************************************************************************/
struct function_entry_array
{
	struct function_entry* function_entry_pointer;
	struct function_entry* function_entry_pointer_origin_position;
	size_t array_capacity;
};


/**********************************************************************************************************
NAME  : FREE OPERATION ENTRY ARRAY
LIBS  : -
NOTES : always use this function when finish work with array of operation entry.
**********************************************************************************************************/
void free_operation_entry_array(struct operation_entry_array* operation_entry_array)
{
	operation_entry_array->operation_entry_pointer =
		operation_entry_array->operation_entry_pointer_origin_position;

	free(operation_entry_array->operation_entry_pointer);
	free(operation_entry_array);
}


/**********************************************************************************************************
NAME  : FREE FUNCTION ENTRY ARRAY
LIBS  : -
NOTES : always use this function when finish work with array of function entry.
**********************************************************************************************************/
void free_function_entry_array(struct function_entry_array* func_entry_array)
{
	func_entry_array->function_entry_pointer = func_entry_array->function_entry_pointer_origin_position;

	free(func_entry_array->function_entry_pointer);
	free(func_entry_array);
}


/**********************************************************************************************************
NAME  : GET MATH OPERATIONS ENTRIES ARRAY
LIBS  : -
NOTES : this function contain operation section where all mathematical operations listed.
**********************************************************************************************************/
struct operation_entry_array* get_math_operations_entries_array()
{
	size_t ARRAY_CAPACITY = 10;

	struct operation_entry_array* operation_entry_array = calloc(1, sizeof(struct operation_entry_array));
	if (operation_entry_array == NULL)
	{
		throw_error(OUT_OF_MEMORY);
	}

	operation_entry_array->operation_entry_pointer = 
		calloc(ARRAY_CAPACITY, sizeof(struct operation_entry));
	if (operation_entry_array->operation_entry_pointer == NULL)
	{
		throw_error(OUT_OF_MEMORY);
	}

	operation_entry_array->array_capacity = ARRAY_CAPACITY;
	operation_entry_array->operation_entry_pointer_origin_position = 
		operation_entry_array->operation_entry_pointer;

	////OPERATIONS SECTION BEGIN////

	//adding addition operation entry
	operation_entry_array->operation_entry_pointer->operation_alias = "+";
	operation_entry_array->operation_entry_pointer->operator_associativity = 2;
	operation_entry_array->operation_entry_pointer->pointer_on_function = &stack_add;
	operation_entry_array->operation_entry_pointer++;

	//adding subtract operation entry
	operation_entry_array->operation_entry_pointer->operation_alias = "-";
	operation_entry_array->operation_entry_pointer->operator_associativity = 2;
	operation_entry_array->operation_entry_pointer->pointer_on_function = &stack_subtract;
	operation_entry_array->operation_entry_pointer++;

	//adding multiply operation entry
	operation_entry_array->operation_entry_pointer->operation_alias = "*";
	operation_entry_array->operation_entry_pointer->operator_associativity = 3;
	operation_entry_array->operation_entry_pointer->pointer_on_function = &stack_multiply;
	operation_entry_array->operation_entry_pointer++;

	//adding divide operation entry
	operation_entry_array->operation_entry_pointer->operation_alias = "/";
	operation_entry_array->operation_entry_pointer->operator_associativity = 3;
	operation_entry_array->operation_entry_pointer->pointer_on_function = &stack_divide;
	operation_entry_array->operation_entry_pointer++;

	//adding "more" operation entry
	operation_entry_array->operation_entry_pointer->operation_alias = ">";
	operation_entry_array->operation_entry_pointer->operator_associativity = 1;
	operation_entry_array->operation_entry_pointer->pointer_on_function = &stack_more;
	operation_entry_array->operation_entry_pointer++;

	//adding "less" operation entry
	operation_entry_array->operation_entry_pointer->operation_alias = "<";
	operation_entry_array->operation_entry_pointer->operator_associativity = 1;
	operation_entry_array->operation_entry_pointer->pointer_on_function = &stack_less;
	operation_entry_array->operation_entry_pointer++;

	//adding "equals" operation entry
	operation_entry_array->operation_entry_pointer->operation_alias = "=";
	operation_entry_array->operation_entry_pointer->operator_associativity = 1;
	operation_entry_array->operation_entry_pointer->pointer_on_function = &stack_equals;
	operation_entry_array->operation_entry_pointer++;

	//adding "or" operation entry
	operation_entry_array->operation_entry_pointer->operation_alias = "OR";
	operation_entry_array->operation_entry_pointer->operator_associativity = 0;
	operation_entry_array->operation_entry_pointer->pointer_on_function = &stack_or;
	operation_entry_array->operation_entry_pointer++;

	//adding "div" operation entry
	operation_entry_array->operation_entry_pointer->operation_alias = "DIV";
	operation_entry_array->operation_entry_pointer->operator_associativity = 3;
	operation_entry_array->operation_entry_pointer->pointer_on_function = &stack_div;
	operation_entry_array->operation_entry_pointer++;

	//adding "mod" operation entry
	operation_entry_array->operation_entry_pointer->operation_alias = "MOD";
	operation_entry_array->operation_entry_pointer->operator_associativity = 3;
	operation_entry_array->operation_entry_pointer->pointer_on_function = &stack_mod;
	operation_entry_array->operation_entry_pointer++;

	////OPERATIONS SECTION END////

	operation_entry_array->operation_entry_pointer =
		operation_entry_array->operation_entry_pointer_origin_position;

	return operation_entry_array;
}


/**********************************************************************************************************
NAME  : GET MATH FUNCTIONS ENTRIES ARRAY
LIBS  : -
NOTES : this function contain function section where all mathematical functions listed.
**********************************************************************************************************/
struct function_entry_array* get_math_functions_entries_array()
{
	size_t ARRAY_CAPACITY = 10;

	struct function_entry_array* func_entry_array = calloc(1, sizeof(struct function_entry_array));
	if (func_entry_array == NULL)
	{
		throw_error(OUT_OF_MEMORY);
	}

	func_entry_array->function_entry_pointer = calloc(ARRAY_CAPACITY, sizeof(struct function_entry));
	if (func_entry_array->function_entry_pointer == NULL)
	{
		throw_error(OUT_OF_MEMORY);
	}

	func_entry_array->array_capacity = ARRAY_CAPACITY;
	func_entry_array->function_entry_pointer_origin_position = func_entry_array->function_entry_pointer;

	////FUNCTIONS SECTION BEGIN////

	//adding sqrt function entry
	func_entry_array->function_entry_pointer->function_alias = "sqrt";
	func_entry_array->function_entry_pointer->pointer_on_function = &stack_sqrt;
	func_entry_array->function_entry_pointer++;

	//adding power function entry
	func_entry_array->function_entry_pointer->function_alias = "pow";
	func_entry_array->function_entry_pointer->pointer_on_function = &stack_power;
	func_entry_array->function_entry_pointer++;

	//adding negative function entry
	func_entry_array->function_entry_pointer->function_alias = "neg";
	func_entry_array->function_entry_pointer->pointer_on_function = &stack_negative;
	func_entry_array->function_entry_pointer++;

	//adding abs function entry
	func_entry_array->function_entry_pointer->function_alias = "abs";
	func_entry_array->function_entry_pointer->pointer_on_function = &stack_abs;
	func_entry_array->function_entry_pointer++;

	//adding sinus function entry
	func_entry_array->function_entry_pointer->function_alias = "sin";
	func_entry_array->function_entry_pointer->pointer_on_function = &stack_sin;
	func_entry_array->function_entry_pointer++;

	//adding cosin function entry
	func_entry_array->function_entry_pointer->function_alias = "cos";
	func_entry_array->function_entry_pointer->pointer_on_function = &stack_cos;
	func_entry_array->function_entry_pointer++;

	//adding arccosin function entry
	func_entry_array->function_entry_pointer->function_alias = "arccos";
	func_entry_array->function_entry_pointer->pointer_on_function = &stack_arccos;
	func_entry_array->function_entry_pointer++;

	//adding tangent function entry
	func_entry_array->function_entry_pointer->function_alias = "tan";
	func_entry_array->function_entry_pointer->pointer_on_function = &stack_tan;
	func_entry_array->function_entry_pointer++;

	//adding cotangent function entry
	func_entry_array->function_entry_pointer->function_alias = "cotan";
	func_entry_array->function_entry_pointer->pointer_on_function = &stack_cotan;
	func_entry_array->function_entry_pointer++;

	//adding natual logarithm function entry
	func_entry_array->function_entry_pointer->function_alias = "ln";
	func_entry_array->function_entry_pointer->pointer_on_function = &stack_ln;
	func_entry_array->function_entry_pointer++;

	////FUNCTION SECTION END////

	func_entry_array->function_entry_pointer = func_entry_array->function_entry_pointer_origin_position;

	return func_entry_array;
}


/**********************************************************************************************************
NAME  : IS OPERATION
LIBS  : string.h
NOTES : return 0 if there is no operation with such alias, 1 if there is operation with such alias.
**********************************************************************************************************/
int is_operation(char* operation_alias)
{
	struct operation_entry_array* operation_entry_array = get_math_operations_entries_array();

	for (size_t i = 0; i < operation_entry_array->array_capacity; i++)
	{
		if (strcmp(operation_alias, operation_entry_array->operation_entry_pointer->operation_alias) == 0)
		{
			free_operation_entry_array(operation_entry_array);
			return 1;
		}
		else
		{
			operation_entry_array->operation_entry_pointer++;
		}
	}

	free_operation_entry_array(operation_entry_array);
	return 0;
}


/**********************************************************************************************************
NAME  : IS FUNCTION
LIBS  : string.h
NOTES : return 0 if there is no function with such alias, 1 if there is function with such alias.
**********************************************************************************************************/
int is_function(char* function_alias)
{
	struct function_entry_array* func_entry_array = get_math_functions_entries_array();

	for (size_t i = 0; i < func_entry_array->array_capacity; i++)
	{
		if (strcmp(function_alias, func_entry_array->function_entry_pointer->function_alias) == 0)
		{
			free_function_entry_array(func_entry_array);
			return 1;
		}
		else
		{
			func_entry_array->function_entry_pointer++;
		}
	}

	free_function_entry_array(func_entry_array);
	return 0;
}


/**********************************************************************************************************
NAME  : CALCULATE STACK OPERATION
LIBS  : string.h
NOTES : -
**********************************************************************************************************/
void calculate_stack_operation(char* operation_alias, struct stack_double* stack_double)
{
	struct operation_entry_array* operation_entry_array = get_math_operations_entries_array();

	for (size_t i = 0; i < operation_entry_array->array_capacity; i++)
	{
		if (strcmp(operation_alias, operation_entry_array->operation_entry_pointer->operation_alias) == 0)
		{
			operation_entry_array->operation_entry_pointer->pointer_on_function(stack_double);
			free_operation_entry_array(operation_entry_array);
			return;
		}
		else
		{
			operation_entry_array->operation_entry_pointer++;
		}
	}

	throw_error(UNEXPECTED_ALIAS);
}


/**********************************************************************************************************
NAME  : CALCULATE STACK FUNCTION
LIBS  : -
NOTES : -
**********************************************************************************************************/
void calculate_stack_function(char* function_alias, struct stack_double* stack_double)
{
	struct function_entry_array* func_entry_array = get_math_functions_entries_array();

	for (size_t i = 0; i < func_entry_array->array_capacity; i++)
	{
		if (strcmp(function_alias, func_entry_array->function_entry_pointer->function_alias) == 0)
		{
			func_entry_array->function_entry_pointer->pointer_on_function(stack_double);
			free_function_entry_array(func_entry_array);
			return;
		}
		else
		{
			func_entry_array->function_entry_pointer++;
		}
	}

	throw_error(UNEXPECTED_ALIAS);
}


/**********************************************************************************************************
NAME  : GET OPERATOR ASSOCIATIVITY
LIBS  : -
NOTES : -
**********************************************************************************************************/
int get_operator_associativity(const char* operation_alias)
{
	struct operation_entry_array* operation_entry_array = get_math_operations_entries_array();

	for (size_t i = 0; i < operation_entry_array->array_capacity; i++)
	{
		if (strcmp(operation_alias, operation_entry_array->operation_entry_pointer->operation_alias) == 0)
		{
			return operation_entry_array->operation_entry_pointer->operator_associativity;
		}
		else
		{
			operation_entry_array->operation_entry_pointer++;
		}
	}

	throw_error(UNEXPECTED_ALIAS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////STACK MATHEMATICAL FUNCTIONS SECTION END////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////
////STACK MACHINE SECTION///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************************************************
NAME  : IS NUMBER
LIBS  : string.h, ctype.h
NOTES : return 1 if string is a number, 0 if not.
**********************************************************************************************************/
int is_number(char* string_pointer)
{
	//check for first character (must be minus or digit).
	char MINUS[] = { "-" };
	if (*string_pointer != MINUS[0] && isdigit(*string_pointer) == 0)
	{
		return 0;
	}

	string_pointer++;

	//check for dot (only one dot permitted, it must be digits to the left and right of dot).
	const char DOT[] = { "." };
	int is_there_dot = 0; //false
	size_t string_length = strlen(string_pointer);
	for (size_t i = 0; i < string_length; i++)
	{
		if (*string_pointer == DOT[0])
		{
			if (is_there_dot == 0)
			{
				if (isdigit(*(string_pointer - 1)) != 0 && isdigit(*(string_pointer + 1)) != 0)
				{
					is_there_dot = 1;
					string_pointer++;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
		//check for digit.
		else if (isdigit(*string_pointer) != 0)
		{
			string_pointer++;
		}
		else
		{
			return 0;
		}
	}

	if (strcmp(--string_pointer, "-") == 0 && strlen(string_pointer) == 1)
	{
		return 0;
	}

	return 1;
}


/**********************************************************************************************************
NAME  : CONVERT INFIX TO POSTFIX
LIBS  : string.h
NOTES : -
**********************************************************************************************************/
char* convert_infix_to_postfix(char* expression)
{
	const char TOKEN_DELIMITER[2]     = " ";
	const char ARGUMENTS_DELIMITER[2] = ",";
	const char OPENING_BRACKET[2]     = "(";
	const char CLOSING_BRACKET[2]     = ")";

	const size_t STACK_CAPACITY = 64;
	struct stack_string* stack = stack_string_initialize(STACK_CAPACITY);

	const size_t MAX_CHARACTERS = 256;
	char* result_postfix_expression = calloc(MAX_CHARACTERS, sizeof(char));

	char* token;

	token = strtok(expression, TOKEN_DELIMITER);
	struct string* token_as_string = calloc(1, sizeof(struct string));
	token_as_string->char_pointer = token;

	//Using shunting-yard algorithm
	while (token != NULL)
	{
		token_as_string->char_pointer = token;
		if (is_number(token) == 1)
		{
			strcat(result_postfix_expression, token);
			strcat(result_postfix_expression, TOKEN_DELIMITER);
		}
		else if (is_function(token) == 1)
		{
			push_stack_string(stack, token_as_string);
		}
		else if (strcmp(token, ARGUMENTS_DELIMITER) == 0)
		{
			while (strcmp(peek_stack_string(stack)->char_pointer, OPENING_BRACKET) != 0)
			{
				struct string* operator = pop_stack_string(stack);
				strcat(result_postfix_expression, operator->char_pointer);
				strcat(result_postfix_expression, TOKEN_DELIMITER);
			}
		}
		else if (is_operation(token) == 1)
		{
			while (is_operation(peek_stack_string(stack)->char_pointer) == 1)
			{
				if (get_operator_associativity(token) <=
					get_operator_associativity(peek_stack_string(stack)->char_pointer))
				{
					strcat(result_postfix_expression, pop_stack_string(stack)->char_pointer);
					strcat(result_postfix_expression, TOKEN_DELIMITER);
				}
				else
				{
					break;
				}
			}

			push_stack_string(stack, token_as_string);
		}
		else if (strcmp(token, OPENING_BRACKET) == 0)
		{
			push_stack_string(stack, token_as_string);
		}
		else if (strcmp(token, CLOSING_BRACKET) == 0)
		{
			while (strcmp(peek_stack_string(stack)->char_pointer, OPENING_BRACKET) != 0)
			{
				strcat(result_postfix_expression, pop_stack_string(stack)->char_pointer);
				strcat(result_postfix_expression, TOKEN_DELIMITER);
			}

			pop_stack_string(stack);

			if (is_function(peek_stack_string(stack)->char_pointer) == 1)
			{
				strcat(result_postfix_expression, pop_stack_string(stack)->char_pointer);
				strcat(result_postfix_expression, TOKEN_DELIMITER);
			}
		}

		token = strtok(NULL, TOKEN_DELIMITER);
	}

	while (stack->current_elements_count != 0)
	{
		strcat(result_postfix_expression, pop_stack_string(stack)->char_pointer);
		strcat(result_postfix_expression, TOKEN_DELIMITER);
	}

	stack_string_free(stack);
	return result_postfix_expression;
}


/**********************************************************************************************************
NAME  : IS THERE WHERE KEYWORD
LIBS  : string.h
NOTES : return 1 if string contains "where" keyword, 0 if not.
**********************************************************************************************************/
int is_there_where_keyword(const char* expression)
{
	const char* TOKEN_DELIMITER = " ";
	const char* WHERE_KEYWORD = "|";

	const size_t MAX_CHARACTERS = 256;
	char* this_expression = calloc(MAX_CHARACTERS, sizeof(char));
	this_expression = strcpy(this_expression, expression);

	int is_there_where = 0; //false
	char* token = strtok(this_expression, TOKEN_DELIMITER);
	while (token != NULL)
	{
		if (strcmp(token, WHERE_KEYWORD) == 0)
		{
			is_there_where = 1;
			break;
		}
		else
		{
			token = strtok(NULL, TOKEN_DELIMITER);
		}
	}

	free(this_expression);

	return is_there_where;
}


/**********************************************************************************************************
NAME  : GET FORMULA FROM EXPRESSION
LIBS  : string.h
NOTES : returned pointer on formula must be passed to "free()" after use.
**********************************************************************************************************/
char* get_formula_from_expression(char* expression)
{
	const char* SPLIT_KEYWORD = "|";

	char* this_expression = _strdup(expression);
	char* formula = strtok(this_expression, SPLIT_KEYWORD);

	return formula;
}


/**********************************************************************************************************
NAME  : GET VALUES FROM EXPRESSION
LIBS  : string.h
NOTES : returned pointer on values must be passed to "free()" after use.
**********************************************************************************************************/
char* get_values_from_expression(char* expression)
{
	const char* SPLIT_KEYWORD = "|";

	char* this_expression = _strdup(expression);

	char* values;
	values = strtok(this_expression, SPLIT_KEYWORD);
	strcpy(values, strtok(NULL, SPLIT_KEYWORD));

	return values;
}


/**********************************************************************************************************
NAME  : GET VALUE DICTIONARY
LIBS  : string.h
NOTES : -
**********************************************************************************************************/
struct dictionary* get_value_dictionary(char* values)
{
	const char* EQUALS_SIGN = '=';
	const char* TOKEN_DELIMITER = " ";

	int dictionary_capacity = 0;
	char* current_char = values;
	const char* NULL_CHARACTER = "\0";
	while (strcmp(current_char, NULL_CHARACTER) != 0)
	{
		if (current_char[0] == EQUALS_SIGN)
		{
			dictionary_capacity++;
		}
		current_char++;
	}
	struct dictionary* dictionary = dictionary_initialize(dictionary_capacity);

	const size_t MAX_CHARACTER = 256;
	char* previous_token = calloc(MAX_CHARACTER, sizeof(char));
	char* token = strtok(values, TOKEN_DELIMITER);
	while (token != NULL)
	{
		if (token[0] == EQUALS_SIGN)
		{
			token = strtok(NULL, TOKEN_DELIMITER);
			dictionary_add(dictionary, previous_token, token);
		}
		else
		{
			previous_token = strcpy(previous_token, token);
			token = strtok(NULL, TOKEN_DELIMITER);
		}
	}

	return dictionary;
}


/**********************************************************************************************************
NAME  : TURN FORMULA INTO EXPRESSION
LIBS  : string.h
NOTES : -
**********************************************************************************************************/
char* turn_formula_into_expression(char* formula, struct dictionary* value_dictionary)
{
	const char* TOKEN_DELIMITER = " ";

	const size_t MAX_CHARACTERS = 256;
	char* result_expression = calloc(MAX_CHARACTERS, sizeof(char));

	char* token = strtok(formula, TOKEN_DELIMITER);
	while (token != NULL)
	{
		char* value = dictionary_find(value_dictionary, token);

		if (value != NULL)
		{
			strcat(result_expression, value);
		}
		else
		{
			strcat(result_expression, token);
		}
		strcat(result_expression, TOKEN_DELIMITER);

		token = strtok(NULL, TOKEN_DELIMITER);
	}

	return result_expression;
}


/**********************************************************************************************************
NAME  : CALCULATE EXPRESSION
LIBS  : stdio.h, stype.h, stdlib.h
NOTES : -
**********************************************************************************************************/
double calculate_expression(char* expression)
{
	char* converted_expression = convert_infix_to_postfix(expression);

	const size_t STACK_CAPACITY = 64;
	struct stack_double* stack = stack_double_initialize(STACK_CAPACITY);

	const char DELIMITER[2] = " ";
	char* token;

	token = strtok(converted_expression, DELIMITER);

	while (token != NULL)
	{
		if (is_number(token))
		{
			double pushing_value = 0;
			pushing_value = atof(token);
			push_stack_double(stack, pushing_value);
		}
		else if (is_operation(token) == 1)
		{
			calculate_stack_operation(token, stack);
		}
		else if (is_function(token) == 1)
		{
			calculate_stack_function(token, stack);
		}
		else
		{
			throw_error(UNEXPECTED_TOKEN);
		}

		token = strtok(NULL, DELIMITER);
	}

	double result = *(stack->head_element);
	
	stack_double_free(stack);

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////STACK MACHINE SECTION END///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////
////UI SECTION//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************************************************
NAME  : PRINT ASSIGNMENT SPECIFICATION
LIBS  : stdio.h
NOTES : -
**********************************************************************************************************/
void print_assignment_specification()
{
	fputs("----------------------------------------\n", stdout);
	fputs("Laboratory assignment #2\n", stdout);
	fputs("Arsenii Fatykov\n", stdout);
	fputs("FF-105\n", stdout);
	fputs("17.3.2017\n", stdout);
	fputs("----------------------------------------\n", stdout);
}


/**********************************************************************************************************
NAME  : PRINT PROGRAM SPECIFICATION
LIBS  : stdio.h
NOTES : -
**********************************************************************************************************/
void print_program_specification()
{
	fputs("----------------------------------------\n", stdout);
	fputs("Programming practicum v0\n", stdout);
	fputs("Arsenii Fatykov\n", stdout);
	fputs("3.3.2017\n", stdout);
	fputs("----------------------------------------\n", stdout);
}


/**********************************************************************************************************
NAME  : PRINT MATH PARSER SPECIFICATION
LIBS  : stdio.h
NOTES : -
**********************************************************************************************************/
void print_math_parser_specification()
{
	fputs("----------------------------------------\n", stdout);
	fputs("Mathematical parser v0\n", stdout);
	fputs("----------------------------------------\n", stdout);
}


/**********************************************************************************************************
NAME  : PRINT MAIN MENU ITEMS
LIBS  : stdio.h
NOTES : -
**********************************************************************************************************/
void print_main_menu_items()
{
	fputs("----------------------------------------\n", stdout);
	fputs("Main menu:\n", stdout);
	fputs("1 - Mathematical parser\n", stdout);
	fputs("0 - Exit\n\n", stdout);
	fputs("----------------------------------------\n", stdout);
}


/**********************************************************************************************************
NAME  : CALL INPUT
LIBS  : stdio.h, string.h
NOTES : returned pointer on string must be passed to "free()" after use.
**********************************************************************************************************/
char* call_input()
{
	const size_t MAX_CHARACTERS = 256;
	const size_t BYTE_FOR_NEW_LINE_CHARACTER = 1;

	char* input_string = calloc(MAX_CHARACTERS + BYTE_FOR_NEW_LINE_CHARACTER, sizeof(char));

	fgets(input_string, MAX_CHARACTERS + BYTE_FOR_NEW_LINE_CHARACTER, stdin);
	input_string[strcspn(input_string, "\n")] = 0;

	return input_string;
}


/**********************************************************************************************************
NAME  : CALL MATH PARSER
LIBS  : stdio.h
NOTES : -
**********************************************************************************************************/
void call_math_parser()
{
	print_math_parser_specification();

	fputs("Enter expression: ", stdout);
	char* expression = call_input();

	if (is_there_where_keyword(expression) == 1)
	{
		char* formula = get_formula_from_expression(expression);
		char* values = get_values_from_expression(expression);

		struct dictionary* value_dictionary = get_value_dictionary(values);
		expression = turn_formula_into_expression(formula, value_dictionary);

		free(formula);
		free(values);
		dictionary_free(value_dictionary);
	}

	double result = calculate_expression(expression);
	free(expression);
	printf("Result: %f\n", result);
	getchar();
}

/**********************************************************************************************************
NAME  : CALL MAIN MENU
LIBS  : stdio.h, stdlib.h
NOTES : -
**********************************************************************************************************/
void call_main_menu()
{
	print_program_specification();
	print_assignment_specification();
	
	for (;;)
	{
		print_main_menu_items();

		fputs("Choose item: ", stdout);
		char* input_item = call_input();
		fputs("\n", stdout);
		int input_item_as_int = atoi(input_item);

		switch (input_item_as_int)
		{
			case 1:
				call_math_parser();
				break;

			case 0:
				exit(EXIT_SUCCESS);

			default:
				exit(EXIT_FAILURE);
		}

	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////UI SECTION END//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	call_main_menu();

	return 0;
}	