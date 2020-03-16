//
// Curly
// scopes.h: Header file for scopes.c.
//
// jenra
// March 15 2020
//

#ifndef scopes_h
#define scopes_h

#include <stdbool.h>

// Represents a type.
typedef enum
{
	SCOPE_CURLY_TYPE_INT,
	SCOPE_CURLY_TYPE_FLOAT,
	SCOPE_CURLY_TYPE_STRING
} curly_type_t;

// Represents a single scope.
struct s_scope
{
	// Whether the scope was generated by a function call or something else.
	bool call;

	// The names of the variables in use.
	char** names;

	// The type of the variable in use.
	curly_type_t* types;

	// The amount of memory allocated for the list.
	int size;

	// The number of items in the list.
	int count;

	// The scope that created this scope.
	struct s_scope* last;
};

// Contains all scopes.
typedef struct
{
	struct s_scope global;
	struct s_scope* local;
} scopes_t;

// init_scopes(scopes_t*) -> void
// Initialises a stack of scopes.
void init_scopes(scopes_t* scope);

// clean_scopes(scopes_t*) -> void
// Cleans a stack of scopes.
void clean_scopes(scopes_t* scope);

#endif /* scopes_h */