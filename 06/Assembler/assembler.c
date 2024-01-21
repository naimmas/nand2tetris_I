#include "inc.h"
#define MAX_LINE_SIZE 256


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        ERR_PRINT("Invalid number of arguments. Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        ERR_PRINT("Failed to open the file.\n");
        return 1;
    }
    char *line_p = malloc(sizeof(char) * MAX_LINE_SIZE);
    size_t line_no = 0;
    init_predefined_symbols();
    while (fgets(line_p, MAX_LINE_SIZE, file))
    {
        line_p[strcspn(line_p, "\r\n")] = 0;
        while (*line_p != '\0' && isspace(*line_p))
        {
            line_p++;
        }
        if (*line_p == '\0' || line_p[0] == '/')
        {
            continue;
        }

        line_p[strcspn(line_p, "//")] = 0;
        line_p[strcspn(line_p, " ")] = 0;
        line_no++;
        DEBUG_PRINT("line no: %ld\tline:%s\n", line_no, line_p);
        extract_labels(line_p, &line_no);
    }
    rewind(file);
    print_table(symbolTable, SYM_TABLE_SIZE);
    printf("\n------*****SECOND PASS*****------\n");
    line_p = malloc(sizeof(char) * MAX_LINE_SIZE);
    line_no = 0;
    int key = 16;
    char *lastDot = strrchr(argv[1], '.');
    char newFileName[256] = {'\0'};
    strncpy(newFileName, argv[1], strlen(argv[1]) - strlen(lastDot));
    strcat(newFileName, ".hack");
    FILE *output_file = fopen(newFileName, "w+");
    size_t cNo = 0, aNo = 0;
    while (fgets(line_p, MAX_LINE_SIZE, file))
    {
        line_p[strcspn(line_p, "\r\n")] = 0;
        
        while (*line_p != '\0' && isspace(*line_p))
        {
            line_p++;
        }
        if (*line_p == '\0' || line_p[0] == '/')
        {
            continue;
        }

        line_p[strcspn(line_p, "//")] = 0;
        line_p[strcspn(line_p, " ")] = 0;
        size_t len = strnlen(line_p, sizeof(line_p));
        line_no++;
        DEBUG_PRINT("line no: %ld\tline:%s\n", line_no, line_p);
        char bin_dest[C_INSTRUCTION_SIZE] = {'\0'};
        parse_a_instruction(line_p, &key, bin_dest);
        if (bin_dest[0] != '\0')
        {
            // printf("%04zu.A instruction: %s\r", line_no, bin_dest);
            aNo++;
            fprintf(output_file, "%s\n", bin_dest);
            memset(bin_dest, '\0', C_INSTRUCTION_SIZE);
            continue;
        }
        parse_c_instruction(line_p, len, bin_dest);
        if (bin_dest[0] != '\0')
        {
            // printf("%04zu.C instruction: %s\r", line_no, bin_dest);
            cNo++;
            fprintf(output_file, "%s\n", bin_dest);
            memset(bin_dest, '\0', C_INSTRUCTION_SIZE);
        }
    }
    printf("A instructions number: %zu\nC instructions number: %zu\n", aNo, cNo);
    printf("------*****PROGRAM END*****------\n");
    fclose(file);
    fclose(output_file);
}