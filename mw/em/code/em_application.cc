/**
 * @file em_application.cc
 * @author Bartosz Snieg (snieg45@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-02-06
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mw/em/code/em_application.h"

#include <string>
#include <unordered_map>
namespace simba {
namespace em {
EmApplication::EmApplication(/* args */) {}

EmApplication::~EmApplication() {}

core::ErrorCode EmApplication::Run(std::stop_token token) {
  this->em_service.StartApps();
  SleepMainThread();
  return core::ErrorCode::kOk;
}
/**
 * @brief This function is called to initialize the application
 *
 * @param parms map with parms
 */
core::ErrorCode EmApplication::Initialize(
    const std::unordered_map<std::string, std::string>& parms) {
  this->em_service.LoadApps();
  return core::ErrorCode::kOk;
}

}  // namespace em
}  // namespace simba