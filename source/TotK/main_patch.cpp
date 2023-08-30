#include "skyline/inlinehook/And64InlineHook.hpp"
#include "skyline/utils/cpputils.hpp"
#include "skyline/inlinehook/memcpy_controlled.hpp"

//69 00 80 52 08 0D 02 53
constinit uint8_t textFilter[8] = {0x69, 0x00, 0x80, 0x52, 0x08, 0x0D, 0x02, 0x53};
							 
//A9 00 80 52
constinit uint8_t textFilter_p[4] = {0xA9, 0x00, 0x80, 0x52};

//80 12 40 BD E0 03 13 AA (has 2 matches /!\)
constinit uint8_t mipmapbias[8] = {0x80, 0x12, 0x40, 0xBD, 0xE0, 0x03, 0x13, 0xAA};
							 
//00 10 3D 1E
constinit uint8_t mipmapbias_p[4] = {0x00, 0x10, 0x3D, 0x1E};

//B2 0E 30 1E [C6 38 36 1E] [A5 08 32 1E] [93 28 26 1E]
constinit uint8_t shadowDist[16] = {0xB2, 0x0E, 0x30, 0x1E, 0xC6, 0x38, 0x36, 0x1E, 0xA5, 0x08, 0x32, 0x1E, 0x93, 0x28, 0x26, 0x1E};
							 
//B2 0E 30 1E [1F 20 03 D5] [05 10 22 1E] [D3 28 26 1E]
constinit uint8_t shadowDist_p[16] = {0xB2, 0x0E, 0x30, 0x1E, 0x1F, 0x20, 0x03, 0xD5, 0x05, 0x10, 0x22, 0x1E, 0xD3, 0x28, 0x26, 0x1E};

//0B 02 38 1E EC 02 38 36
constinit uint8_t shadowRes[8] = {0x0B, 0x02, 0x38, 0x1E, 0xEC, 0x02, 0x38, 0x36};
							 
//0B 80 80 52
constinit uint8_t shadowRes_p[4] = {0x0B, 0x80, 0x80, 0x52};

//08 00 40 39 E0 03 14 AA 68 72 05 39
constinit uint8_t FXAA[12] = {0x08, 0x00, 0x40, 0x39, 0xE0, 0x03, 0x14, 0xAA, 0x68, 0x72, 0x05, 0x39};

//08 00 80 52
constinit uint8_t FXAA_p[4] = {0x08, 0x00, 0x80, 0x52};

//08 00 40 39 BF 22 00 71 68 76 05 39
constinit uint8_t FXAA_2[12] = {0x08, 0x00, 0x40, 0x39, 0xBF, 0x22, 0x00, 0x71, 0x68, 0x76, 0x05, 0x39};

//08 00 80 52
constinit uint8_t FXAA_2_p[4] = {0x08, 0x00, 0x80, 0x52}; 

//3F 09 00 71 03 08 22 1E
constinit uint8_t FXAA_char[8] = {0x3F, 0x09, 0x00, 0x71, 0x03, 0x08, 0x22, 0x1E};

//3F 05 00 71
constinit uint8_t FXAA_char_p[4] = {0x3F, 0x05, 0x00, 0x71}; 

//FF 43 01 D1 E9 23 01 6D FD 7B 02 A9 FD 83 00 91 F6 57 03 A9 F4 4F 04 A9 08 18 46 F9
constinit uint8_t res1080pRet[28] = {0xFF, 0x43, 0x01, 0xD1, 0xE9, 0x23, 0x01, 0x6D, 0xFD, 0x7B, 0x02, 0xA9, 0xFD, 0x83, 0x00, 0x91, 0xF6, 0x57, 0x03, 0xA9, 0xF4, 0x4F, 0x04, 0xA9, 0x08, 0x18, 0x46, 0xF9};

//C0 03 5F D6
constinit uint8_t res1080pRet_p[4] = {0xC0, 0x03, 0x5F, 0xD6};


bool memcmp_f (const unsigned char *s1, const unsigned char *s2, size_t count) {
    while (count-- > 0)
        if (*s1++ != *s2++) 
            return false;
    return true;
}

size_t getCodeSize() {
        return (size_t)skyline::utils::getRegionAddress(skyline::utils::region::Rodata) - (size_t)skyline::utils::getRegionAddress(skyline::utils::region::Text);
}

/* You must provide full instructions in arrays of uint8_t.
It returns pointer to first found code in main 
or 0 if nothing have been found. */
uintptr_t findTextCode(const uint8_t* code, size_t size) {
    if (size % 4 != 0) return 0;
    uintptr_t addr = (uintptr_t)skyline::utils::getRegionAddress(skyline::utils::region::Text);
    size_t addr_size = getCodeSize();	
    uintptr_t addr_start = addr;
    while (addr != addr_start + addr_size) {
        bool result = memcmp_f((const unsigned char*)addr, code, size);
        if (result) return addr;
        addr += 4;
    }
    return 0;
}

void totk_graphics_main() {	
    uintptr_t pointer = findTextCode(&textFilter[0], sizeof(textFilter));
    if (pointer) {
        sky_memcpy((void*)pointer, &textFilter_p[0], sizeof(textFilter_p));
    }
	pointer = findTextCode(&mipmapbias[0], sizeof(mipmapbias));
    if (pointer) {
        sky_memcpy((void*)pointer, &mipmapbias_p[0], sizeof(mipmapbias_p));
    }
	pointer = findTextCode(&shadowDist[0], sizeof(shadowDist));
    if (pointer) {
        sky_memcpy((void*)pointer, &shadowDist_p[0], sizeof(shadowDist_p));
    }
	pointer = findTextCode(&shadowRes[0], sizeof(shadowRes));
    if (pointer) {
        sky_memcpy((void*)pointer, &shadowRes_p[0], sizeof(shadowRes_p));
    }
	pointer = findTextCode(&FXAA[0], sizeof(FXAA));
    if (pointer) {
        sky_memcpy((void*)pointer, &FXAA_p[0], sizeof(FXAA_p));
    }
	pointer = findTextCode(&FXAA_2[0], sizeof(FXAA_2));
    if (pointer) {
        sky_memcpy((void*)pointer, &FXAA_2_p[0], sizeof(FXAA_2_p));
    }
	pointer = findTextCode(&FXAA_char[0], sizeof(FXAA_char));
    if (pointer) {
        sky_memcpy((void*)pointer, &FXAA_char_p[0], sizeof(FXAA_char_p));
    }
	pointer = findTextCode(&res1080pRet[0], sizeof(res1080pRet));
    if (pointer) {
        sky_memcpy((void*)pointer, &res1080pRet_p[0], sizeof(res1080pRet));
    }
}
