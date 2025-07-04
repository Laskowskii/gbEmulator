#ifndef ROM_H
#define ROM_H
    #define NINTENDO_LOGO_START 0x0104
    #define NINTENDO_LOGO_END 0x0133
    #define CARTRIDGE_TYPE_ADRESS 0x0147
    #define TITLE_START 0x134
    #define TITLE_END 0x143
    #define ROM_SIZE_ADRESS 0x148
    #define RAM_SIZE_ADRESS 0x149
    #define HEADER_CHECKSUM 0x014D

    #include <stdio.h>
    #include <stdint.h>
    #include <sys/stat.h>
    #include <string.h>
    #include <stdbool.h>

    size_t getFileSize(FILE *f);
    void getRomSize(uint8_t rom[]);
    void getRamSize(uint8_t rom[]);
    void printGameTitle(uint8_t rom[]);
    void printNintentoLogoHex(uint8_t rom[]);
    void printRegion(uint8_t rom[]);
    void printInfo(uint8_t rom[]);
    void printCartridgeType(uint8_t rom[]);

    uint8_t calculateChecksum(uint8_t rom[]);
    bool checkChecksum(uint8_t rom[]);
#endif