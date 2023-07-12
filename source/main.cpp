#include "main.hpp"
#include "TotK/main_patch.hpp"

#include "skyline/utils/cpputils.hpp"
#include "skyline/utils/ipc.hpp"

void skyline_main() {
    // populate our own process handle
    Handle h;
    skyline::utils::Ipc::getOwnProcessHandle(&h);
    envSetOwnProcessHandle(h);

    MHR_main();
}

extern "C" void skyline_init() {
    skyline::utils::init();
    virtmemSetup();  // needed for libnx JIT

    skyline_main();
}
