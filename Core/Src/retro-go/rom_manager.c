#include <string.h>
#include <stdint.h>

#include "rom_manager.h"
#include "rg_emulators.h"
#include "utils.h"

unsigned char *ROM_DATA = NULL;
unsigned ROM_DATA_LENGTH;
retro_emulator_file_t *ACTIVE_FILE = NULL;

#include "gb_roms.c"
#include "nes_roms.c"
#include "sms_roms.c"
#include "gg_roms.c"

const rom_system_t systems[] = {
    nes_system,
    gb_system,
    sms_system,
    gg_system,
};

const rom_manager_t rom_mgr = {
    .systems = systems,
    .systems_count = ARRAY_SIZE(systems),
};

const rom_system_t *rom_manager_system(const rom_manager_t *mgr, char *name) {
    for(int i=0; i < mgr->systems_count; i++) {
        if(strcmp(mgr->systems[i].system_name, name) == 0) {
            return &mgr->systems[i];
        }
    }
    return NULL;
}

void rom_manager_set_active_file(retro_emulator_file_t *file)
{
    ACTIVE_FILE = file;
    ROM_DATA = file->address;
    ROM_DATA_LENGTH = file->size;
}
