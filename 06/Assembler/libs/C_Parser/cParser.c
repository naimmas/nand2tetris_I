/**
 * @file cParser.c
 * @author Naim MASRI (naimmas@outlook.com)
 * @brief C instruction parser
 * @version 0.1
 * @date 2024-01-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../../inc.h"

const cInstruct_t compTable[] = {
    {"!A", "1110110001"},
    {"!D", "1110001101"},
    {"!M", "1111110001"},
    {"-1", "1110111010"},
    {"-A", "1110110011"},
    {"-D", "1110001111"},
    {"-M", "1111110011"},
    {"0", "1110101010"},
    {"1", "1110111111"},
    {"A", "1110110000"},
    {"A+1", "1110110111"},
    {"A-1", "1110110010"},
    {"A-D", "1110000111"},
    {"D", "1110001100"},
    {"D&A", "1110000000"},
    {"D&M", "1111000000"},
    {"D+1", "1110011111"},
    {"D+A", "1110000010"},
    {"D+M", "1111000010"},
    {"D-1", "1110001110"},
    {"D-A", "1110010011"},
    {"D-M", "1111010011"},
    {"D|A", "1110010101"},
    {"D|M", "1111010101"},
    {"M", "1111110000"},
    {"M+1", "1111110111"},
    {"M-1", "1111110010"},
    {"M-D", "1111000111"}};

const cInstruct_t destTable[] = {
    {"null", "000"},
    {"A", "100"},
    {"AD", "110"},
    {"AM", "101"},
    {"AMD", "111"},
    {"D", "010"},
    {"M", "001"},
    {"MD", "011"}};

const cInstruct_t jumpTable[] = {
    {"JEQ", "010"},
    {"JGE", "011"},
    {"JGT", "001"},
    {"JLE", "110"},
    {"JLT", "100"},
    {"JMP", "111"},
    {"JNE", "101"},
    {"null", "000"}};

int get_instruction(const cInstruct_t *table, int size, char *target)
{
    int start = 0, end = size - 1;

    while (start <= end)
    {
        int mid = start + (end - start) / 2;

        int result = strncmp(table[mid].key, target, 5);
        if (result == 0)
        {
            // Found the target
            return mid;
        }
        else if (result < 0)
        {
            // Target is greater, ignore left half
            start = mid + 1;
        }
        else
        {
            // Target is smaller, ignore right half
            end = mid - 1;
        }
    }

    // Target is not present in the table
    return -1;
}

void parse_c_instruction(char *line, size_t len, char *binary_buffer)
{
    if (line[0] == '@' || line[0] == '(')
    {
        DEBUG_PRINT("A instruction. return...\n");
        return;
    }
    char *dest, *comp, *jump;

    size_t index = strcspn(line, "=");
    if (index < len)
    {
        line[index] = '\0';
        int ins_index = get_instruction(destTable, DEST_TABLE_SIZE, line);
        if (ins_index == -1)
        {
            ERR_PRINT("Invalid DEST instruction: %s\n", line);
            exit(1);
        }
        dest = destTable[ins_index].value;
        memset(line, '\0', index);
        line += index + 1;
        len -= index + 1;
    }
    else
    {
        dest = "000";
    }
    DEBUG_PRINT("\tDEST: %s\n", dest);
    index = strcspn(line, ";");
    line[index] = '\0';
    int ins_index = get_instruction(compTable, COMP_TABLE_SIZE, line);
    if (ins_index == -1)
    {
        ERR_PRINT("Invalid COMP instruction: \"%s\"\n", line);
        exit(1);
    }
    comp = compTable[ins_index].value;
    DEBUG_PRINT("\tCOMP: %s\n", comp);
    memset(line, '\0', index);
    if (index < len)
    {
        line += index + 1;
        int ins_index = get_instruction(jumpTable, JUMP_TABLE_SIZE, line);
        if (ins_index == -1)
        {
            ERR_PRINT("Invalid JUMP instruction: \"%s\"\n", line);
            exit(1);
        }
        jump = jumpTable[ins_index].value;
    }
    else
    {
        jump = "000";
    }
    DEBUG_PRINT("\tJUMP: %s\n", jump);
    strcpy(binary_buffer, comp);
    strcat(binary_buffer, dest);
    strcat(binary_buffer, jump);
    DEBUG_PRINT("binary_buffer: %s\n", binary_buffer);
}