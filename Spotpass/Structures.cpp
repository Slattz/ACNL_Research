struct Spotpass_RV //Content Datatype in Payload Content Header must be 0x00010010; Size of this struct: 0x8; Filename: camp_p.dat
{
    u32 Checksum; //This is over the next 4 bytes (see Checksum.cpp for algorithm)
    u8  Magic;    //Has to be 0x1
    u8  Padding; //Always 0
    u16 VillagerID; //No restrictions
};

union IndexForItemArray
{
    u32     raw;
    struct
    {
        u16     ID;
        u16     Flags;
    };
};

struct Spotpass_Present //Content Datatype in Payload Content Header must be 0x00010002; Size of this struct: 0xC; Filename: FGONLYT
{
    u32 Checksum; //This is over the next 8 bytes (see Checksum.cpp for algorithm)
    u8  Magic; //Has to be 0x2
    u8  Padding; //Always 0
    u16 PresentID; //This is used to ensure the player can't get the gift twice
    IndexForItemArray idx; //Game does (ID & 0xE000) && ID < 0x11AD, then gets WA item ID from g_ValidSpotpassGiftItems Array
};
