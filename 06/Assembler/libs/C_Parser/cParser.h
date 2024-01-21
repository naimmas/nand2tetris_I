/**
 * @file cParser.h
 * @author Naim MASRI (naimmas@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-01-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define COMP_TABLE_SIZE 28
#define DEST_TABLE_SIZE 8
#define JUMP_TABLE_SIZE 8
#define C_INSTRUCTION_SIZE 17

typedef struct cInstructTable cInstruct_t;
struct cInstructTable
{
    char *key;
    char *value;
};
extern const cInstruct_t compTable[];
extern const cInstruct_t destTable[];
extern const cInstruct_t jumpTable[];

int get_instruction(const cInstruct_t* table, int size, char* target);
void parse_c_instruction(char *line, size_t len, char* bin_dest);