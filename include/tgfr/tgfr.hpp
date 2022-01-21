#ifndef __TGFR_HPP
#define __TGFR_HPP

#include <tgfr/Logger.h>
#include <tgfr/Bot.hpp>
#include <tgfr/manager/EventManager.hpp>
#include <tgfr/handler/EventHandler.hpp>

/**
 * @brief Tgfr main namespace
 */
namespace tgfr {

    /**
     * @brief Function to initialize tgfr stuff
     * 
     * @note Should be called before any tgfr call
     */
    void Init() {
        Logger::Init();
    }
} // namespace tgfr

#endif // __TGFR_HPP
