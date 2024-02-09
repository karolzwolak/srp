/**
 * @file idlt_arg.h
 * @author Bartosz Snieg (snieg45@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-02-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef MW_LOGGER_CODE_DATA_IDLT_ARG_H_
#define MW_LOGGER_CODE_DATA_IDLT_ARG_H_
#include <cstdint>
#include <vector>

namespace simba {
namespace dlt {
namespace data {
class IDLTArg {
 public:
  virtual uint16_t Length() const noexcept = 0;
  virtual std::vector<uint8_t> ParseArg() const noexcept = 0;
  virtual ~IDLTArg() {}
};
}  // namespace data
}  // namespace dlt
}  // namespace simba
#endif  // MW_LOGGER_CODE_DATA_IDLT_ARG_H_
