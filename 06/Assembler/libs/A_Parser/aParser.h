#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LABEL_TABLE_SIZE 23
#define VAR_TABLE_SIZE 1<<16
#define SYM_TABLE_SIZE 1<<16
typedef struct aInstructTable aInstruct_t;
struct aInstructTable
{
    char *key;
    int value;
};
extern const aInstruct_t labelTable[];
extern aInstruct_t symbolTable[SYM_TABLE_SIZE];
extern aInstruct_t varsTable[VAR_TABLE_SIZE];
void extract_labels(char*line, size_t* line_no);
int add_to_table(aInstruct_t* table, char* key, int value);
int get_from_table(aInstruct_t *table, char *key, size_t table_size);
void parse_a_instruction(char *line, int *var_val, char *bin_dest);
void init_predefined_symbols();
void print_table(aInstruct_t *table, size_t table_size);
