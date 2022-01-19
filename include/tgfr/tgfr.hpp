#ifndef __TGFR_HPP
#define __TGFR_HPP

#include <tgfr/Logger.h>
#include <tgfr/Bot.hpp>
#include <tgfr/manager/EventManager.hpp>
#include <tgfr/handler/EventHandler.hpp>

namespace tgfr {
    /* Function to initialize tgfr stuff */
    void Init() {
        Logger::Init();
    }
} // namespace tgfr

#endif // __TGFR_HPP
