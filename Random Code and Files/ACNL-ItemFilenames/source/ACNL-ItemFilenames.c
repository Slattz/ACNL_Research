/*
********************************
Main Code and Research by Slattz
********************************
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

typedef uint16_t u16;
typedef uint32_t u32;

FILE *g_Items_WA = NULL;

//Get's the accurate string length of a UTF-8 String
int UTF8_strlen(char* str) {
    char* data = str;
    u32 len = 0;

    while (*data) {
        len += (*data++ & 0xC0) != 0x80;
    }

    return len;
}

//strncmp but ignores case of letters
int strncmpi(char *ps1, char *ps2, int n) {
    char *px1, *px2;
    int indicator, i = 0;
    px1 = ps1;
    px2 = ps2;
    indicator = 9999;
    while (indicator == 9999)
    {
        if (++i > n)
            indicator = 0;
        else
        {
            if (*px1 == '\0')
            {
                if (*px2 == '\0')
                    indicator = 0;
                else
                    indicator = -1;
            }
            else
            {
                if (toupper((int)*px1) < toupper((int)*px2))
                    indicator = -1;
                else
                {
                    if (toupper((int)*px1) > toupper((int)*px2))
                        indicator = 1;
                    else
                    {
                        px1 += 1;
                        px2 += 1;
                    }
                }
            }
        }
    }
    return indicator;
}

char* GetItemNameWA(u16 item) {
    char itemid[10];
    char* line = malloc(100);
    snprintf(itemid, 8, "0x%04X", item);

    rewind(g_Items_WA);
    while (fgets(line, 100, g_Items_WA) != NULL) /* read each line */
    {
        if (strncmpi(itemid, line, 6) == 0) /* If itemID in txt is same as our ID */
        {
            return line + 8; //+8 so the itemID and spaces before actual name aren't included
        }
    }

    return "???";
}

int main(void) {
    char spaces[100];
    char *filepath = malloc(70);

    g_Items_WA = fopen("Items_WA.txt", "r"); //Get this file from https://github.com/Slattz/NLTK/blob/master/assets/romfs/Items_en.txt and rename it
    FILE *codebin_EUR = fopen("code.bin", "rb"); //Must be EUR 1.5, otherwise change the 0x771958 offset below to the suitable offset for your code.bin

    printf("  Item ID   |                      Item Name                     |            Filepath\n\n");

    for(u16 ItemID = 0; ItemID < 0x172B; ItemID++) {
        u32 ptr = 0;
        strncpy(spaces, "\0", 100);
        strncpy(filepath, "\0", 70);
        
        char* itemname = GetItemNameWA(0x2000+ItemID); //Get the item name corresponding to the item ID

        char *pos;
        if ((pos = strchr(itemname, '\n')) != NULL) //Get rid of \n from fgets in string returned from GetItemNameWA
            *pos = '\0';

        int len = UTF8_strlen(itemname); //custom strlen needed for words containing chars that aren't ASCII, e.g. Café
        for (int k = 0; k < 50 - len; k++)
            strcat(spaces, " "); //Add spaces so item names can be aligned with their titles

        fseek(codebin_EUR, 0x771958+(ItemID*4), SEEK_SET); //Go to offset of itemname offset
        int res = fread(&ptr, 1, sizeof(u32), codebin_EUR); //Read itemname Offset

        if (ptr == 0 || ptr < 0x100000 || res != sizeof(u32)) {
            printf("  0x%04X    | %s%s |    No Model (Likely a Sprite)\n", 0x2000 + ItemID, itemname, spaces);
            continue;
        }

        else {
            fseek(codebin_EUR, ptr-0x100000, SEEK_SET); //Go to itemname Offset
            if (fgets(filepath, 69, codebin_EUR) == NULL) {
                printf("  0x%04X    | %s%s |    fgets function Error\n", 0x2000 + ItemID, itemname, spaces);
                continue;
            }

            else {
                printf("  0x%04X    | %s%s |    romfs:/Item/Model/%s.bcres\n", 0x2000 + ItemID, itemname, spaces, filepath);
                continue;
            }
            
        }
    }

    fclose(g_Items_WA);
    fclose(codebin_EUR);

    return 0;
}