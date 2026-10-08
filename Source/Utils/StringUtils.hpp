#pragma once

#include <string>
#include <charconv>

namespace StringUtils {
    inline int64_t toInt(const std::string& str, const bool strict)
    {
        int64_t constant = 0;
        auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), constant);
        if (ec != std::errc{}) {
            if (ec == std::errc::invalid_argument) {
                throw std::invalid_argument("Не удалось распарсить число: неверный формат строки");
            }
            if (ec == std::errc::result_out_of_range) {
                throw std::out_of_range("Число вышло за границы диапазона int64_t");
            }
        }
        if (strict && ptr != str.data() + str.size()) {
            throw std::invalid_argument("Строка содержит лишние символы в конце");
        }
        return constant;
    }

    inline double toDouble(const std::string& str, const bool strict)
    {
        double constant = 0.0;
        auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), constant);
        if (ec != std::errc{}) {
            if (ec == std::errc::invalid_argument) {
                throw std::invalid_argument("Не удалось распарсить число: неверный формат строки");
            }
            if (ec == std::errc::result_out_of_range) {
                throw std::out_of_range("Число вышло за границы диапазона int64_t");
            }
        }
        if (strict && ptr != str.data() + str.size()) {
            throw std::invalid_argument("Строка содержит лишние символы в конце");
        }
        return constant;
    }
}
