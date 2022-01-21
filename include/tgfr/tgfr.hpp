/**
 * MIT License
 *
 * Copyright (c) 2022 DeinsOne

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
