//
// Created by Ginakira on 2023/9/15.
//

#ifndef NOMU_VERSION_H_
#define NOMU_VERSION_H_

#include <QVersionNumber>

namespace Nomu {

constexpr int MAJOR_VERSION = 1;
constexpr int MINOR_VERSION = 2;
constexpr int BUILD_VERSION = 20231127;
constexpr auto APPLICATION_NAME = "Nomu";

inline QVersionNumber GetApplicationVersion() {
  QVersionNumber version(MAJOR_VERSION, MINOR_VERSION);
  return version;
}

}// namespace Nomu
#endif// NOMU_VERSION_H_
