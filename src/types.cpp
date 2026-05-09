#include "types.hpp"

DEFINE_TYPE(MetaCore, EndDragHandler);
DEFINE_TYPE(MetaCore, KeyboardCloseHandler);

void MetaCore::EndDragHandler::OnPointerUp(UnityEngine::EventSystems::PointerEventData* eventData) {
    if (callback)
        callback();
}
