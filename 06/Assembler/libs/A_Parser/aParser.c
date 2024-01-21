#include "../../inc.h"

const aInstruct_t labelTable[LABEL_TABLE_SIZE] = {
    {"R0", 0},
    {"R1", 1},
    {"R2", 2},
    {"R3", 3},
    {"R4", 4},
    {"R5", 5},
    {"R6", 6},
    {"R7", 7},
    {"R8", 8},
    {"R9", 9},
    {"R10", 10},
    {"R11", 11},
    {"R12", 12},
    {"R13", 13},
    {"R14", 14},
    {"R15", 15},
    {"SCREEN", 16384},
    {"KBD", 24576},
    {"SP", 0},
    {"LCL", 1},
    {"ARG", 2},
    {"THIS", 3},
    {"THAT", 4},
};

aInstruct_t symbolTable[SYM_TABLE_SIZE];
aInstruct_t varsTable[VAR_TABLE_SIZE];
int add_to_table(aInstruct_t *table, char *key, int value)
{
    for (int i = 0; i < (1 << 16); i++)
    {
        if (table[i].value == -1)
        {
            DEBUG_PRINT("Adding to table: %s->%d\n", key, value);
            table[i].key = strdup(key);
            table[i].value = value;
            return i;
        }
    }
    return -1;
}
int get_from_table(aInstruct_t *table, char *key, size_t table_size)
{
    DEBUG_PRINT("Searching for: %s\n", key);
    for (int i = 0; i < table_size; i++)
    {
        if (table[i].value != -1 && strncmp(table[i].key, key, 256) == 0)
        {
            return table[i].value;
        }
    }
    return -1;
}
void print_table(aInstruct_t *table, size_t table_size)
{
    printf("-----Symbols Table-----\n");
    for (int i = 0; i < table_size; i++)
    {
        if (table[i].value != -1)
        {
            printf("%-35s\t%s\t%d\n", table[i].key, "->", table[i].value);
        }
    }
}
void init_predefined_symbols()
{
    for (int i = 0; i < (1 << 16); i++)
    {
        symbolTable[i].value = -1;
        varsTable[i].value = -1;
    }
}

void extract_labels(char *line, size_t *line_no)
{
    if (*line != '(')
        return;
    line++;
    line[strcspn(line, ")")] = '\0';
    (*line_no) -= 1;
    int index = add_to_table(symbolTable, line, *line_no);
    DEBUG_PRINT("Label: (%s) inserted from line: %zu at: %d\n", line, *line_no, index);
    // hash_table_put(symbol_table, line, (value_u *)line_no);
}
void decimalToBinaryString(int number, char *binaryString)
{
    if (binaryString == NULL)
    {
        return;
    }

    for (int i = 16 - 1; i >= 0; i--)
    {
        binaryString[i] = (number & 1) ? '1' : '0'; // Get the least significant bit
        number >>= 1;                               // Right shift the number by 1
    }
}
void parse_a_instruction(char *line, int *var_val, char *bin_dest)
{
    if (line[0] == '@')
    {
        line++;
        if (isdigit(*line))
        {
            DEBUG_PRINT("Number found: %s\n", line);
            decimalToBinaryString(atoi(line), bin_dest);
            return;
        }
        int index;
        index = get_from_table(symbolTable, line, SYM_TABLE_SIZE);
        if (-1 != index)
        {
            decimalToBinaryString(index, bin_dest);
            DEBUG_PRINT("Symbol found: %s address: %d (%s)\n", line, index, bin_dest);
            return;
        }
        index = get_from_table(labelTable, line, LABEL_TABLE_SIZE);
        if (-1 != index)
        {
            decimalToBinaryString(index, bin_dest);
            DEBUG_PRINT("Label found: %s address: %d (%s)\n", line, index, bin_dest);
            return;
        }
        index = get_from_table(varsTable, line, VAR_TABLE_SIZE);
        if (-1 != index)
        {
            decimalToBinaryString(index, bin_dest);
            DEBUG_PRINT("Variable found: %s address: %d (%s)\n", line, index, bin_dest);
            return;
        }
        else
        {
            DEBUG_PRINT("Variable not found: %s, adding to table...\n", line);
            decimalToBinaryString(*var_val, bin_dest);
            add_to_table(varsTable, line, *var_val);
            (*var_val) += 1;
            return;
        }
    }
    else
    {
        return;
    }
}