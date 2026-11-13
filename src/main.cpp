#include "main.hpp"

#include "events.hpp"
#include "hooks.hpp"
#include "input.hpp"
#include "types.hpp"
#include "metacore/shared/unity.hpp"
#include "scotland2/shared/modloader.h"

#include "GlobalNamespace/OVRInput.hpp"
#include "UnityEngine/GameObject.hpp"

static modloader::ModInfo modInfo = {MOD_ID, VERSION, 0};

using namespace MetaCore;

static std::map<int, std::set<int>> pressedButtons = [] {
    decltype(pressedButtons) set;
    for (int i = 0; i <= Input::ControllersMax; i++)
        set.emplace(i, std::set<int>());
    return set;
}();

static void UpdateInputs() {
    // TODO: replace OVRInput with our own input handling, since it will likely be removed in the future
    // (just reimplementing the relevant APIs would probably be fine, instead of going through unity/openxr)
    GlobalNamespace::OVRInput::Update();
    for (int i = 0; i <= Input::ButtonsMax; i++) {
        for (int j = 0; j <= Input::ControllersMax; j++) {
            auto& specificPressed = pressedButtons[j];
            bool pressed = Input::GetPressed((Input::Controllers) j, (Input::Buttons) i);
            bool wasPressed = specificPressed.contains(i);
            if (pressed && !wasPressed) {
                Events::Broadcast(Input::ForController(Input::PressEvents, (Input::Controllers) j), i);
                specificPressed.emplace(i);
            }
            if (pressed)
                Events::Broadcast(Input::ForController(Input::HoldEvents, (Input::Controllers) j), i);
            if (!pressed && wasPressed) {
                Events::Broadcast(Input::ForController(Input::ReleaseEvents, (Input::Controllers) j), i);
                specificPressed.erase(i);
            }
        }
    }
}

static void RegisterButtonEvents() {
    for (int i = 0; i <= Input::ButtonsMax; i++) {
        for (int j = 0; j <= Input::ControllersMax; j++) {
            Events::RegisterEvent(Input::ForController(Input::PressEvents, (Input::Controllers) j), i);
            Events::RegisterEvent(Input::ForController(Input::ReleaseEvents, (Input::Controllers) j), i);
            Events::RegisterEvent(Input::ForController(Input::HoldEvents, (Input::Controllers) j), i);
        }
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
    Engine::ScheduleOnUpdate(UpdateInputs);
}
