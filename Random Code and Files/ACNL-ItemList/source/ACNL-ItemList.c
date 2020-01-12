#include "common.h"
#include <ctype.h>

void MakeUpper(char string[]) {     
    int i;
    int x = strlen(string); // You want to get the length of the whole string.
    for (i=0; i<x; i++) {
        if (isalpha(string[i]) && (string[i-1] == ' ' || (string[i-1] == '-' && isalpha(string[i-2])) || 
            	(string[i-1] == '(' && string[i-2] == ' ') || (string[i-1] == '[' && string[i-2] == ' '))) { // only first letters of a word.
            //if (string[i] != 'o' && string[i+1] != 'f')
                string[i]= toupper(string[i]);
        }
    }
}

bool NoItemID(char string[]) {
    int num = 0;

    if (isxdigit(string[0])) num++;
    if (isxdigit(string[1])) num++;
    if (isxdigit(string[2])) num++;
    if (isxdigit(string[3])) num++;
    if (string[4] == ' ') num++;

    return num != 5;
}

int main(int argc, char* argv[])
{
    FILE *g_Items_WA = fopen("Items_WA.txt", "r");

    char* line = malloc(100);

    while (fgets(line, 100, g_Items_WA) != NULL) /* read each line */
    {
        u16 itemid = 0;
        char* itemname;

        if (line[0] == '-' || line[1] == '-' || line[0] == '\n' || (line[0] == '\r' && line[1] == '\n')) continue;

        itemid = strtol(line, &itemname, 16);
        MakeUpper(itemname);
        
        if (itemid == 0 || NoItemID(line)) {
            printf("//%s", line);
        }
        
        else printf("0x%04X,%s", itemid, itemname);
    }

    fclose(g_Items_WA);

    return 0;
}
