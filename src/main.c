#include "main.h"

int main(int argc, char **argv){
    if(argc < 2){
        printf("usage: programName <romDir>\n");
        return 1;
    }
    FILE *romFile;
    romFile = fopen(argv[1], "rb");
    if(romFile == NULL){
        printf("invalid filename\n");
        return 2;
    }
    size_t size = getFileSize(romFile);
    uint8_t rom[size];
    fread(rom,sizeof(uint8_t),size,romFile);     
    printInfo(rom);
    fclose(romFile);
    return 0;
}

void printInfo(uint8_t rom[]){
    printGameTitle(rom);
    printNintentoLogoHex(rom); 
    printRegion(rom);
    printCartridgeType(rom);
    printRomSize(rom);
    printRamSize(rom);
    checkChecksum(rom);
}