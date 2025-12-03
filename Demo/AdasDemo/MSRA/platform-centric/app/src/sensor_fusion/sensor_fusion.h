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
/*!        \file  sensor_fusion.h
 *         \brief
 *
 *********************************************************************************************************************/

#ifndef NSAPPLICATIONUNIT_NSSENSORFUSION_SENSOR_FUSION_H
#define NSAPPLICATIONUNIT_NSSENSORFUSION_SENSOR_FUSION_H

#include "nsapplicationunit/nssensorfusion/sensor_fusion_base.h"

namespace NsApplicationUnit {
namespace NsSensorFusion {

class SensorFusion : public SensorFusionBase {
 public:
  SensorFusion(ConstructorToken&& token);

  void OnVelocity(vaf::ConstDataPtr<const datatypes::Velocity> velocity);
  ::adas::interfaces::ObjectDetectionList DoDetection(const datatypes::Image&, const datatypes::Image&,
                                                      datatypes::SteeringAngle, datatypes::Velocity);

  void OnError(const vaf::Error& error) override;

  void PeriodicTask() override;

 private:
  constexpr static uint16_t kMaxVelocity{100};
  bool is_enabled_{true};
  vaf::Future<af::adas_demo_app::services::image_scaling_factor_FieldGetter::Output>
      image_scaling_factor_getter_future_{};
};

}  // namespace NsSensorFusion
}  // namespace NsApplicationUnit

#endif  // NSAPPLICATIONUNIT_NSSENSORFUSION_SENSOR_FUSION_H
