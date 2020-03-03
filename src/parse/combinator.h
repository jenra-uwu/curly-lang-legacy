//
// Curly parser combinator
// combinator.h: Header file for combinator.c.
//
// jenra
// February 25 2020
//

#ifndef combinator_h
#define combinator_h

#include <stdbool.h>

#include "lexer.h"

// Represents a node in an abstract syntax tree.
typedef struct ast_node
{
	// The name of the node.
	char* name;

	// The value of the node.
	char* value;

	// The line the node was generated from.
	int line;

	// The character position the node was generated from.
	int char_pos;

	// The number of child nodes.
	unsigned int children_count;

	// The child nodes.
	struct ast_node* children;
} ast_t;

// Represents a parsing error.
typedef struct
{
	// The cause of the error.
	// This has to be void since otherwise there's stupid circular referencing stuff.
	void* cause;

	// The string in which the error was caused.
	char* string;

	// The position of the error.
	size_t position;

	// The line of the error.
	int line;

	// The horizontal position of the error.
	int char_pos;
} parse_error_t;

// Represents a parsing result.
typedef struct
{
	bool succ;
	bool ignore;

	union
	{
		ast_t ast;
		parse_error_t error;
	};
} parse_result_t;

// *comb_fn (comb_t*, lexer_t*, void*) -> parse_result_t
// Represents a combinator function.
// self has to be void since otherwise there's a lot of stupid circular referencing stuff.
typedef parse_result_t (*comb_fn)(void* self, lexer_t* lex, void* args);

// Represents a combinator with certain arguments.
typedef struct comb_s
{
	// The function of the comb.
	comb_fn func;

	// The arguments passed into the function.
	void* args;

	// If true, tells the lexer to ignore whitespace.
	bool ignore_whitespace;

	// The error message outputted by the comb.
	char* error_msg;

	// The next comb in the linked list (used for deleting).
	struct comb_s* next;
} comb_t;

// init_combinator(void) -> comb_t*
// Initialises an empty parser.
comb_t* init_combinator();



// c_char(char) -> comb_t*
// Creates a parser valid for a given character.
comb_t* c_char(char c);

// c_str(char*) -> comb_t*
// Creates a parser valid for a given string.
comb_t* c_str(char* str);

// c_regex(char*) -> comb_t*
// Creates a parser valid for a given regex.
comb_t* c_regex(char* pattern);

// c_next(void) -> comb_t*
// Creates a parser that's always valid.
comb_t* c_next();

// c_eof(comb_t*) -> comb_t*
// Creates a parser valid if a given parser parses the whole file.
comb_t* c_eof(comb_t* c);

// c_or(comb_t*, comb_t*, ...) -> comb_t*
// Creates a parser valid if any given parser is valid.
// comb_t* list must end with NULL.
comb_t* c_or(comb_t* c1, comb_t* c2, ...);

// c_seq(comb_t*, comb_t*, ...) -> comb_t*
// Creates a parser valid if all given parsers are valid in order.
// comb_t* list must end with NULL.
comb_t* c_seq(comb_t* c1, comb_t* c2, ...);

// c_zmore(comb_t*) -> comb_t*
// Creats a parser valid if a given parser appears at least zero times.
comb_t* c_zmore(comb_t* c);

// c_zmore(comb_t*) -> comb_t*
// Creats a parser valid if a given parser appears at least once.
comb_t* c_omore(comb_t* c);

// c_optional(comb_t*) -> comb_t*
// Creates a parser valid regardless of if the given parser is valid.
comb_t* c_optional(comb_t* c);

// c_not(comb_t*) -> comb_t*
// Creates a parser valid if the given parser is invalid.
comb_t* c_not(comb_t* c);

// c_ignore(comb_t*) -> comb_t*
// Creates a parser that ignores the output of a given parser.
// Validity is still dependent on the given parser.
comb_t* c_ignore(comb_t* c);

// c_name(char*, comb_t*) -> comb_t*
// Creates a parser that gives a name to a given parser.
comb_t* c_name(char* name, comb_t* c);



// c_set(comb_t*, comb_t*) -> void
// Sets one parser to another.
//
// To use this, a must be an empty parser. This function is used as follows:
// comb_t* recursive_parser = init_combinator();
// comb_t* value = some_parser_stuff_in_terms_of(recursive_parser);
// c_set(recursive_parser, value);
//
void c_set(comb_t* a, comb_t* b);

// c_error(comb_t*, char*) -> comb_t*
// Sets the error message of the parser and returns it.
comb_t* c_error(comb_t* comb, char* msg);

// parse(comb_t*, char*) -> parse_result_t
// Parses a string and returns the result.
parse_result_t parse(comb_t* parser, char* string);

// print_parse_result(parse_result_t) -> void
// Prints out a parse result.
void print_parse_result(parse_result_t result);

// clean_parse_result(parse_result_t*) -> void
// Cleans up a parse result.
void clean_parse_result(parse_result_t* result);

// clean_ast_node(ast_t*) -> void
// Cleans up an ast node.
void clean_ast_node(ast_t* node);

// clean_combinator(comb_t*) -> void
// Deletes a comb parser.
void clean_combinator(comb_t* comb);

#endif /* combinator_h */
