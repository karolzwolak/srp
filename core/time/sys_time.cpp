/**
 * @file sys_time.cpp
 * @author Mateusz Krajewski (matikrajek42@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <cstdio>
#include <memory>
#include <array>
#include "core/time/sys_time.hpp"
#include "core/logger/Logger.h"

namespace simba {
namespace core {
namespace time {

namespace {
    constexpr auto DATE_CMD = "date ";
}

std::optional<std::string> TimeChanger::exec(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        return {};
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}

Date_t TimeChanger::ParseDate(const std::string& dateStr) {
    Date_t date;
    char monthStr[4];
    int day, hour, minute, second, year;

    // Użycie sscanf do wyciągnięcia odpowiednich wartości
    uint8_t parsed = sscanf(dateStr.c_str(), "%*s %3s %d %d:%d:%d %*s %d",
           monthStr, &day, &hour, &minute, &second, &year);

    const std::string months = "JanFebMarAprMayJunJulAugSepOctNovDec";
    date.month = (months.find(monthStr) / 3) + 1;
    date.day = static_cast<uint8_t>(day);
    date.hour = static_cast<uint8_t>(hour);
    date.minute = static_cast<uint8_t>(minute);
    date.seconds = static_cast<uint8_t>(second);
    date.year = static_cast<uint16_t>(year);
    return date;
}

std::string TimeChanger::ConvertVariableToCommand(Date_t date) {
    std::string command = DATE_CMD;
    command += (date.month < 10) ? "0" + std::to_string(date.month) : std::to_string(date.month);
    command += (date.day < 10) ? "0" + std::to_string(date.day) : std::to_string(date.day);
    command += (date.hour < 10) ? "0" + std::to_string(date.hour) : std::to_string(date.hour);
    command += (date.minute < 10) ? "0" + std::to_string(date.minute) : std::to_string(date.minute);
    command += std::to_string(date.year);
    command += "." + ((date.seconds < 10) ? "0" + std::to_string(date.seconds) : std::to_string(date.seconds));
    return command;
}

core::ErrorCode TimeChanger::ChangeSystemTime(std::string time) {
    std::string command = DATE_CMD;
    command += time;
    int res = system(command.c_str());
    if (res == 0) {
        return core::ErrorCode::kOk;
    }
    return core::ErrorCode::kError;
}
core::ErrorCode TimeChanger::ChangeSystemTime(Date_t date) {
    std::string command = DATE_CMD;
    command += ConvertVariableToCommand(date);
    int res = system(command.c_str());
    if (res == 0) {
        return core::ErrorCode::kOk;
    }
    return core::ErrorCode::kError;
}
std::optional<Date_t> TimeChanger::ReadSystemTime() {
    auto res = exec(DATE_CMD);
    if (!res.has_value()) {
        return {};
    }
    AppLogger::Info("Current time: "+res.value());
    return ParseDate(res.value());
}
}  // namespace  time
}  // namespace  core
}  // namespace  simba
