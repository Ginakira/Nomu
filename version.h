//
// Created by Ginakira on 2023/9/15.
//

#ifndef NOMU_VERSION_H_
#define NOMU_VERSION_H_

#include <QVersionNumber>

namespace Nomu {

constexpr int MAJOR_VERSION = 1;
constexpr int MINOR_VERSION = 0;
constexpr int BUILD_VERSION = 20230917;
constexpr auto APPLICATION_NAME = "Nomu";

inline QVersionNumber GetApplicationVersion() {
  QVersionNumber version(MAJOR_VERSION, MINOR_VERSION);
  return version;
}

}// namespace Nomu
#endif// NOMU_VERSION_H_
