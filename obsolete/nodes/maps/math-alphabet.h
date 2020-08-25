#ifndef NODES_MATH_ALPHABET_H
#define NODES_MATH_ALPHABET_H

#include <string>
#include <locale>
#include <codecvt>

void match_utf32_char_variants(uint32_t* t, std::string text) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utf32conv;
    std::u32string utf32 = utf32conv.from_bytes(text);
    for(int i=0; i<text.size(); i++) {
        printf("%c\n", text[i]);
        switch (text[i]) {
        case ' ':
            t[i] = 0x000000020;//text[i] /*- 0x00000041 */ + offset;
            break;
        case 'A':
            t[i] = 0x00001D434;//text[i] /*- 0x00000041 */ + offset;
            break;
        case 'B':
            t[i] = 0x00001D435;//text[i] /*- 0x00000042 */ + offset;
            break;

        case 'C':
            t[i] = 0x00001D436;//text[i] /*- 0x00000043 */ + offset;
            break;

        case 'D':
            t[i] = 0x00001D437;//text[i] /*- 0x00000044 */ + offset;
            break;
        
        case 'E':
            t[i] = 0x00001D438; //text[i] /*- 0x00000045 */ + offset;
            break;
        
        case 'F':
            t[i] = 0x00001D439;//text[i] /*- 0x00000046 */ + offset;
            break;

        case 'G':
            t[i] = 0x00001D43A;//text[i] /*- 0x00000047 */ + offset;
            break;

        case 'H':
            t[i] = 0x00001D43B;//text[i] /*- 0x00000048 */ + offset;
            break;
        
        case 'I':
            t[i] = 0x00001D43C;//text[i] /*- 0x00000049 */ + offset;
            break;
        
        case 'J':
            t[i] = 0x00001D43D;//text[i] /*- 0x0000004A */ + offset;
            break;
    
        case 'K':
            t[i] = 0x00001D43E;//text[i] /*- 0x0000004B */ + offset;
            break;

        case 'L':
            t[i] = 0x00001D43F;//text[i] /*- 0x0000004C */ + offset;
            break;

        case 'M':
            t[i] = 0x00001D440;//text[i] /*- 0x0000004D */ + offset;
            break;

        case 'N':
            t[i] = 0x00001D441;//text[i] /*- 0x0000004E */ + offset;
            break;

        case 'O':
            t[i] = 0x00001D442;//text[i] /*- 0x0000004F */ + offset;
            break;

        case 'P':
            t[i] = 0x00001D443;//text[i] /*- 0x00000050 */ + offset;
            break;
    
        case 'Q':
            t[i] = 0x00001D444;//text[i] /*- 0x00000051 */ + offset;
            break;

        case 'R':
            t[i] = 0x00001D445;//text[i] /*- 0x00000052 */ + offset;
            break;

        case 'S':
            t[i] = 0x00001D446;//text[i] /*- 0x00000053 */ + offset;
            break;

        case 'T':
            t[i] = 0x00001D447;//text[i] /*- 0x00000054 */ + offset;
            break;

        case 'U':
            t[i] = 0x00001D448;// text[i] /*- 0x00000055 */ + offset;
            break;

        case 'V':
            t[i] = 0x00001D449;//text[i] /*- 0x00000056 */ + offset;
            break;

        case 'W':
            t[i] = 0x00001D44A; //text[i] /*- 0x00000057 */ + offset;
            break;

        case 'X':
            t[i] = 0x00001D44B;//text[i] /*- 0x00000058 */ + offset;
            break;

        case 'Y':
            t[i] = 0x00001D44C;//text[i] /*- 0x00000059 */ + offset;
            break;
    
        case 'Z':
            t[i] = 0x00001D44D;//text[i] /*- 0x0000005A */ + offset;
            break;



        case 'a':
            t[i] = 0x00001D44E; //text[i] /*- 0x00000061 */ + offset;
            break;

        case 'b':
            t[i] = 0x00001D44F;//text[i] /*- 0x00000062 */ + offset;
            break;

        case 'c':
            t[i] = 0x00001D450; //text[i] /*- 0x00000063 */ + offset;
            break;

        case 'd':
            t[i] = 0x00001D451; //text[i] /*- 0x00000064 */ + offset;
            break;
        
        case 'e':
            t[i] = 0x00001D452; //text[i] /*- 0x00000065 */ + offset;
            break;
        
        case 'f':
            t[i] = 0x00001D453; //text[i] /*- 0x00000066 */ + offset;
            break;

        case 'g':
            t[i] = 0x00001D454; //text[i] /*- 0x00000067 */ + offset;
            break;

        case 'h':
            t[i] = 0x00001D455; //text[i] /*- 0x00000068 */ + offset;
            break;
        
        case 'i':
            t[i] = 0x00001D456; //text[i] /*- 0x00000069 */ + offset;
            break;
        
        case 'j':
            t[i] = 0x00001D457; //text[i] /*- 0x0000006A */ + offset;
            break;
    
        case 'k':
            t[i] = 0x00001D458; //text[i] /*- 0x0000006B */ + offset;
            break;

        case 'l':
            t[i] = 0x00001D459; //text[i] /*- 0x0000006C */ + offset;
            break;

        case 'm':
            t[i] = 0x00001D45A; //text[i] /*- 0x0000006D */ + offset;
            break;

        case 'n':
            t[i] = 0x00001D45B; //text[i] /*- 0x0000006E */ + offset;
            break;

        case 'o':
            t[i] = 0x00001D45C; //text[i] /*- 0x0000006F */ + offset;
            break;

        case 'p':
            t[i] = 0x00001D45D; //text[i] /*- 0x00000070 */ + offset;
            break;
    
        case 'q':
            t[i] = 0x00001D45E; //text[i] /*- 0x00000071 */ + offset;
            break;

        case 'r':
            t[i] = 0x00001D45F; //text[i] /*- 0x00000072 */ + offset;
            break;

        case 's':
            t[i] = 0x00001D460; //text[i] /*- 0x00000073 */ + offset;
            break;

        case 't':
            t[i] = 0x00001D461; //text[i] /*- 0x00000074 */ + offset;
            break;

        case 'u':
            t[i] = 0x00001D462; //text[i] /*- 0x00000075 */ + offset;
            break;

        case 'v':
            t[i] = 0x00001D463; //text[i] /*- 0x00000076 */ + offset;
            break;

        case 'w':
            t[i] = 0x00001D464; //text[i] /*- 0x00000077 */ + offset;
            break;

        case 'x':
            t[i] = 0x00001D465; //text[i] /*- 0x00000078 */ + offset;
            break;

        case 'y':
            t[i] = 0x00001D466; //text[i] /*- 0x00000079 */ + offset;
            break;
    
        case 'z':
            t[i] = 0x00001D467; //text[i] /*- 0x0000007A */ + offset;
            break;

        default:
            // t[i] = 0x00001D468; //text[i];
            t[i] = utf32[i];//std::uint32_t(reinterpret_cast<char32_t const *>(asInt.data()));
            break;
        }
    }
};

#endif