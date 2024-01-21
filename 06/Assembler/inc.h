#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cParser.h"
#include "aParser.h"

// #define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "[DEBUG] %s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, ##args)
#else
#define DEBUG_PRINT(fmt, args...) /* do nothing */
#endif
#define ERR_PRINT(fmt, args...) fprintf(stderr, "[ERROR] : " fmt, ##args)