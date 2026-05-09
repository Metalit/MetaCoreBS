#include "main.hpp"

#include "events.hpp"
#include "hooks.hpp"
#include "input.hpp"
#include "types.hpp"
#include "scotland2/shared/modloader.h"

#include "UnityEngine/GameObject.hpp"

static modloader::ModInfo modInfo = {MOD_ID, VERSION, 0};

static void RegisterButtonEvents() {
    for (int i = 0; i <= MetaCore::Input::ButtonsMax; i++) {
        MetaCore::Events::RegisterEvent(MetaCore::Input::PressEvents, i);
        MetaCore::Events::RegisterEvent(MetaCore::Input::ReleaseEvents, i);
        MetaCore::Events::RegisterEvent(MetaCore::Input::HoldEvents, i);
    }
}

extern "C" METACORE_EXPORT void setup(CModInfo* info) {
    *info = modInfo.to_c();
    Paper::Logger::RegisterFileContextId(MOD_ID);
    RegisterButtonEvents();
    logger.info("Completed setup!");
}

extern "C" METACORE_EXPORT void late_load() {
    custom_types::Register::AutoRegister();
    Hooks::Install();
}
