//
// Created by Ginakira on 2023/11/27.
//

#ifndef SETTING_FLAGS_H
#define SETTING_FLAGS_H

namespace NomuSettingFlags {

// Flags
constexpr auto TotalDrinkTimes = "total_drink_times";
constexpr auto RemindIntervalMin = "remind_interval_min";
constexpr auto ReminderImagePath = "reminder_image_path";

// Default values
constexpr int DefaultTotalDrinkTimes = 0;
constexpr int DefaultRemindIntervalMin = 30;
constexpr auto DefaultReminderImagePath = ":/icon/nomu.jpg";

}// namespace NomuSettingFlags

#endif//SETTING_FLAGS_H
