#include "main.h"

void printRegion(uint8_t rom[]){
    uint16_t pointer = 0x014A;
    if(rom[pointer] == 0x00){
        printf("region: Japan\n");
    }
    else if(rom[pointer] == 0x01){
        printf("region: non japan lol\n");
    }
}

void printNintentoLogoHex(uint8_t rom[]){ 
    const uint8_t nintendoLogoHex[] = {0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E};
    for (uint16_t pointer = NINTENDO_LOGO_START, i = 0; pointer <= NINTENDO_LOGO_END; pointer++, i++)
    {
        if(rom[pointer] == nintendoLogoHex[i]){
            ;
        }
        else{
            printf("nintendo logo error\n");
            return ;
        }
    }
    printf("nintendo logo works YAY");
    putchar('\n'); 
}

void printGameTitle(uint8_t rom[]){
    for (uint16_t i = TITLE_START; i <= TITLE_END; i++)
    {
        printf("%c",rom[i]);
    }
    putchar('\n');
}
size_t getFileSize(FILE* f){
    fseek(f,0,SEEK_END);
    size_t size = ftell(f);
    rewind(f);
    return size;
}

void printCartridgeType(uint8_t rom[]){
    printf("Cardridge type: %02X\n",rom[CARTRIDGE_TYPE_ADRESS]);
}

void printRomSize(uint8_t rom[]){
    printf("rom size: %x\n",rom[ROM_SIZE_ADRESS]);
}
void printRamSize(uint8_t rom[]){
    printf("ram size: %x\n",rom[RAM_SIZE_ADRESS]);
}

bool checkChecksum(uint8_t rom[]){
    if(rom[HEADER_CHECKSUM] == calculateChecksum(rom)){
        printf("checksum: fine\n");
        return true;
    }
    else{
        printf("checksum: false\n");
        return false;
    }
}

uint8_t calculateChecksum(uint8_t rom[]){
    uint8_t checksum = 0;
    for (uint16_t address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - rom[address] - 1;
    }
    return checksum;
}