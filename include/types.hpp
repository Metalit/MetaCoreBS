#pragma once

#include "custom-types/shared/macros.hpp"

#include "UnityEngine/EventSystems/IEventSystemHandler.hpp"
#include "UnityEngine/EventSystems/IPointerUpHandler.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#define UES UnityEngine::EventSystems

DECLARE_CLASS_CODEGEN_INTERFACES(MetaCore, EndDragHandler, UnityEngine::MonoBehaviour, UES::IEventSystemHandler*, UES::IPointerUpHandler*) {
    DECLARE_DEFAULT_CTOR();

    DECLARE_OVERRIDE_METHOD_MATCH(void, OnPointerUp, &UES::IPointerUpHandler::OnPointerUp, UES::PointerEventData* eventData);

   public:
    std::function<void()> callback = nullptr;
};

DECLARE_CLASS_CODEGEN(MetaCore, KeyboardCloseHandler, UnityEngine::MonoBehaviour) {
    DECLARE_DEFAULT_CTOR();

   public:
    std::function<void()> closeCallback = nullptr;
    std::function<void()> okCallback = nullptr;
};

#undef UES
