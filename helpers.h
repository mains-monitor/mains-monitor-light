/** 
 * Допоміжні функції для використання в коді
*/
#pragma once

#include <string>
#include "esphome.h"

/**
 * @brief Форматує текст повідомлення з врахуванням часу зміни стану, якщо він відомий.
 * 
 * @param message_with_time - шаблон повідомлення, який повинен містити %s для вставки часу зміни стану
 * @param fallback_message - повідомлення, яке використовується, якщо час зміни стану невідомий
 * @return std::string - сформоване повідомлення
 */
std::string prepare_message(const char *message_with_time, const char* fallback_message)
{
    char buffer[100];
    char timediff_buffer[20];
    if (id(sntp_time).now().is_valid())
    {
        auto time = id(sntp_time).now();
        auto diff_seconds = time.timestamp - id(last_state_change_seconds);
        uint16_t minutes = diff_seconds / 60;
        uint16_t hours = 0;
        if (minutes > 60)
        {
            hours = minutes / 60;
            minutes = minutes % 60;
            sprintf(timediff_buffer, "%d год. %d хв.", hours, minutes);
        }
        else
        {
            sprintf(timediff_buffer, "%d хв.", minutes);
        }
        snprintf(buffer, sizeof(buffer), message_with_time, timediff_buffer);
    }
    else
    {
        snprintf(buffer, sizeof(buffer), fallback_message);
    }
    return std::string(buffer);
}