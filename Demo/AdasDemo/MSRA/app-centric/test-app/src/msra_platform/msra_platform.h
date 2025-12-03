/*!********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2024 by Vector Informatik GmbH. All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  msra_platform.h
 *         \brief
 *
 *********************************************************************************************************************/

#ifndef NSAPPLICATIONUNIT_NSMSRAPLATFORM_MSRA_PLATFORM_H
#define NSAPPLICATIONUNIT_NSMSRAPLATFORM_MSRA_PLATFORM_H

#include "nsapplicationunit/nsmsraplatform/msra_platform_base.h"

namespace NsApplicationUnit {
namespace NsMsraPlatform {

class MsraPlatform : public MsraPlatformBase {
 public:
  MsraPlatform(ConstructorToken&& token);

  void OnBrakePressure(vaf::ConstDataPtr<const datatypes::BrakePressure> brake_pressure);

  void PeriodicTask() override;

 private:
  std::uint64_t field_value_{0};
  datatypes::SteeringAngle steering_angle_{0, 0};
  datatypes::Velocity velocity_{0, 0};
  constexpr static uint16_t kMaxBrakePressure{100};
  bool is_enabled_{true};
  vaf::Future<af::adas_demo_app::services::brake_summand_coefficient_FieldGetter::Output>
      brake_summand_coefficient_getter_future_{};
};

}  // namespace NsMsraPlatform
}  // namespace NsApplicationUnit

#endif  // NSAPPLICATIONUNIT_NSMSRAPLATFORM_MSRA_PLATFORM_H
