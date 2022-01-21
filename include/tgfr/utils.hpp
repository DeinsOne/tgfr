#pragma once

#include <string>
#include <random>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <json/json.h>
#include <fstream>

#include <tgbot/types/InlineKeyboardMarkup.h>
#include <tgbot/types/InlineKeyboardButton.h>

/**
 * @brief Additional utilities. Mainly oriented on string operations
 */
namespace utils {

    /**
     * @brief Converts utf-8 string to lower case string
     * 
     * @param convert String to be converted
     * @return std::string Converted string
     */
    inline std::string toLower(const std::string& convert) {
        std::string rt;
        std::for_each(convert.begin(), convert.end(), [&](const char& c) { rt += ::tolower(c); } );
        return rt;
    }

    /**
     * @brief Converts utf-8 string to upper case string
     * 
     * @param convert String to be converted
     * @return std::string Converted string
     */
    inline std::string toUpper(const std::string& convert) {
        std::string rt;
        std::for_each(convert.begin(), convert.end(), [&](const char& c) { rt += ::toupper(c); } );
        return rt;
    }

    /**
     * @brief Erases case sensetive substr from string
     * 
     * @param str Original string where remove substring
     * @param sub String to be removed
     * @return std::string
     */
    inline std::string eraseMatch(const std::string& str, const std::string& sub) {
        std::string rt = str;
        size_t pos = rt.find(sub);
        while (pos != std::string::npos) { rt.erase(pos, sub.length()); pos = rt.find(sub); }
        return rt;
    }

    /**
     * @brief Erases case insensitive substr from string
     * 
     * @param str Original string where remove substring
     * @param sub String to be removed
     * @return std::string 
     */
    inline std::string eraseAny(const std::string& str, const std::string& sub) {
        std::string rt = str;
        size_t pos = toLower(rt).find(toLower(sub));
        while (pos != std::string::npos) { rt.erase(pos, sub.length()); pos = toLower(rt).find(toLower(sub)); }
        return rt;
    }

    /**
     * @brief Find pos of every substring from str
     * @note Case sensetive search
     * 
     * @param str Original string where remove substring
     * @param sub String to be found
     * @return std::vector<std::size_t> 
     */
    inline std::vector<std::size_t> findEvery(const std::string& str, const std::string& sub) {
        std::vector<std::size_t> positions;
        std::size_t pos = str.find(sub, 0);
        while(pos != std::string::npos) { positions.push_back(pos); pos = str.find(sub,pos+1); }
        return positions;
    }

    /**
     * @brief Splits string by given delimeter
     * 
     * @param _str Original string
     * @param delimeter Delimeter to split string with
     * @return std::vector<std::string>
     */
    inline std::vector<std::string> splitString(const std::string& _str, const std::string& delimeter) {
        std::string str = _str;
        std::vector<std::string> splittedStrings = {};
        size_t pos = 0;
        while ((pos = str.find(delimeter)) != std::string::npos) {
            std::string token = str.substr(0, pos);
            if (token.length() > 0)
                splittedStrings.push_back(token);
            str.erase(0, pos + delimeter.length());
        }
        if (str.length() > 0)
            splittedStrings.push_back(str);
        return splittedStrings;
    }

    /**
     * @brief Generates random string
     * @details Uses numbers and latin letters, includeing upper and lover case 
     * 
     * @param length Length of generated string
     * @return std::string New random string
     */
    inline std::string randomId(std::size_t length) {
        static const std::string chars("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890");

        static const std::size_t charsLen = chars.length();
        std::string result;

        std::random_device randomDevice;
        std::mt19937 randomSeed(randomDevice());
        std::uniform_int_distribution<int> generator(0, charsLen - 1);

        for (std::size_t i = 0; i < length; ++i) {
            result += chars[generator(randomSeed)];
        }
        return result.c_str();
    }

    /**
     * @brief Reads content of file to string
     * 
     * @param path Relative or absolute path to the file
     * @return std::string File content
     */
    inline std::string readFile(const std::string& path) {
        std::stringstream str;
        std::ifstream stream(path);
        if (stream.is_open()) {
            while(stream.peek() != EOF) str << (char) stream.get();
            stream.close();
            return str.str();
        }
        return "";
    }

} // namespace utils

namespace tgfr {

    /**
     * @brief Creates inline keyboard object and returns it to user.
     * 
     * @param layout Represents keyboard raws and columns. std::pair<std::string,std::string> must contain text and callback_data.
     * @return TgBot::InlineKeyboardMarkup::Ptr New keyboard
    */
    inline TgBot::InlineKeyboardMarkup::Ptr createInlineKeyboard(const std::vector<std::vector<std::pair<std::string,std::string>>>& layout) {
        TgBot::InlineKeyboardMarkup::Ptr kb = std::shared_ptr<TgBot::InlineKeyboardMarkup>(new TgBot::InlineKeyboardMarkup);

        for (auto i : layout) {
            std::vector<TgBot::InlineKeyboardButton::Ptr> row;
            for (auto j : i) {
                TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
                button->text = j.first;
                button->callbackData = j.second;
                row.emplace_back(button);
            }
            kb->inlineKeyboard.emplace_back(row);
        }

        return kb;
    }

    /**
     * @brief Formats given string to Bold
     * 
     * @param str Original string
     * @param parse_mode "Html" or "Markdown" mode is case insensitive
     * @return std::string Formated string
     */
    inline std::string formatBold(const std::string& str, const std::string parse_mode = "html") {
        auto mode = utils::toLower(parse_mode);
        if (mode == "html") return "<b>" + str + "</b>";
        else if (mode == "markdown") return "**" + str + "**";
        return str;
    }

    /**
     * @brief Formats given string to Italic
     * 
     * @param str Original string
     * @param parse_mode "Html" or "Markdown" mode is case insensitive
     * @return std::string Formated string
     */
    inline std::string formatItalic(const std::string& str, const std::string parse_mode = "html") {
        auto mode = utils::toLower(parse_mode);
        if (mode == "html") return "<i>" + str + "</i>";
        else if (mode == "markdown") return "*" + str + "*";
        return str;
    }

    /**
     * @brief Formats given string to Stroke
     * 
     * @param str Original string
     * @param parse_mode "Html" or "Markdown" mode is case insensitive
     * @return std::string Formated string
     */
    inline std::string formatStroke(const std::string& str, const std::string parse_mode = "html") {
        auto mode = utils::toLower(parse_mode);
        if (mode == "html") return "<s>" + str + "</s>";
        else if (mode == "markdown") return "~~" + str + "~~";
        return str;
    }

    /**
     * @brief Formats given string to Underline
     * 
     * @param str Original string
     * @param parse_mode "Html" or "Markdown" mode is case insensitive
     * @return std::string Formated string
     */
    inline std::string formatUnderline(const std::string& str) {
        return "<u>" + str + "</u>";
    }

    /**
     * @brief Formats given string to Code
     * 
     * @param str Original string
     * @param parse_mode "Html" or "Markdown" mode is case insensitive
     * @return std::string Formated string
     */
    inline std::string formatCode(const std::string& str, const std::string parse_mode = "html") {
        auto mode = utils::toLower(parse_mode);
        if (mode == "html") return "<code>" + str + "</code>";
        else if (mode == "markdown") return "`" + str + "`";
        return str;
    }


} // namespace tgfr
