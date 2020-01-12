#include "common.h"

typedef struct PACKED {
    u16 VillagerID;
    u8 Species;
    u8 BirthDay;
    u32 Unk2;
    u16 Unk3;
    char ModelFilename[6];
    char UnkName1[4];
    char UnkName2[4];
    char UnkName3[4];
    u8 Unk4 : 4;
    u8 Personality : 4;
    u8 Unk5 : 4;
    u8 BirthMonth : 4;
    u16 Unk6;
    u16 Unk7;
} VillagerConst_s;

VillagerConst_s ModifyConst(VillagerConst_s Slot) {
    Slot.Unk2 = 0;
    Slot.Unk3 = 0;
    Slot.Unk4 = 0;
    Slot.Unk5 = 0;
    Slot.Unk6 = 0;
    Slot.Unk7 = 0;
    return Slot;
}

int main(int argc, char* argv[])
{
    FILE *ConstP_orig = fopen("ConstPack_orig.bin", "rb");
    FILE *ConstP_new = fopen("ConstPack.bin", "wb");
    u16 Zero = 0;

    if (ConstP_orig == NULL) {
        printf("ConstPack_orig.bin isn't open! Does it exist???");
        return 0;
    }

    else if (ConstP_new == NULL) {
        printf("ConstPack.bin wasn't created!");
        return 0;
    }

    for(int i = 0; i < 399; i++) {
        VillagerConst_s Slot;
        fread((u8*)&Slot, sizeof(VillagerConst_s), 1, ConstP_orig);
        Slot = ModifyConst(Slot);
        fwrite((u8*)&Slot, sizeof(VillagerConst_s), 1, ConstP_new);
    }
    fwrite(&Zero, sizeof(u16), 1, ConstP_new); //Orig file has a u16 0 at the end so let's do it too so filesize is same
    fflush(ConstP_new);
    fclose(ConstP_new);
    fclose(ConstP_orig);

    return 0;
}
