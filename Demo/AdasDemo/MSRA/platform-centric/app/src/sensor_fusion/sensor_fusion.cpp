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
/*!        \file  sensor_fusion.cpp
 *         \brief
 *
 *********************************************************************************************************************/

#include "nsapplicationunit/nssensorfusion/sensor_fusion.h"
#include "vaf/output_sync_stream.h"

namespace NsApplicationUnit {
namespace NsSensorFusion {

/*
  Generated based on configuration in ../../model/sensor_fusion.py

  Consumer interfaces
  ===================
    Data element API example for camera_image of type datatypes::Image
      - ::vaf::Result<::vaf::ConstDataPtr<const datatypes::Image>> GetAllocated_camera_image()
      - datatypes::Image Get_camera_image()
      - void RegisterDataElementHandler_camera_image(vaf::String owner, std::function<void(const ::vaf::ConstDataPtr<const datatypes::Image>)>&& f)

    - ImageServiceConsumer1_ : af::adas_demo_app::services::ImageServiceConsumer
      - Data elements
        - camera_image : datatypes::Image
        - image_scaling_factor_FieldNotifier : std::uint64_t
      - Operations
        - ::vaf::Future<af::adas_demo_app::services::GetImageSize::Output> GetImageSize()
        - ::vaf::Future<af::adas_demo_app::services::image_scaling_factor_FieldGetter::Output> image_scaling_factor_FieldGetter()
        - ::vaf::Future<void> image_scaling_factor_FieldSetter(const std::uint64_t& data)
    - ImageServiceConsumer2_ : af::adas_demo_app::services::ImageServiceConsumer
      - Data elements
        - camera_image : datatypes::Image
        - image_scaling_factor_FieldNotifier : std::uint64_t
      - Operations
        - ::vaf::Future<af::adas_demo_app::services::GetImageSize::Output> GetImageSize()
        - ::vaf::Future<af::adas_demo_app::services::image_scaling_factor_FieldGetter::Output> image_scaling_factor_FieldGetter()
        - ::vaf::Future<void> image_scaling_factor_FieldSetter(const std::uint64_t& data)
    - SteeringAngleServiceConsumer_ : af::adas_demo_app::services::SteeringAngleServiceConsumer
      - Data elements
        - steering_angle : datatypes::SteeringAngle
    - VelocityServiceConsumer_ : af::adas_demo_app::services::VelocityServiceConsumer
      - Data elements
        - car_velocity : datatypes::Velocity
      - Operations
        - ::vaf::Future<void> SetVelocity(const std::uint32_t& velocity)

  Provider interfaces
  ===================
    Data element API example for object_detection_list of type adas::interfaces::ObjectDetectionList
     - ::vaf::Result<::vaf::DataPtr<adas::interfaces::ObjectDetectionList>> Allocate_object_detection_list()
     - ::vaf::Result<void> SetAllocated_object_detection_list(::vaf::DataPtr<adas::interfaces::ObjectDetectionList>&& data)
     - ::vaf::Result<void> Set_object_detection_list(const adas::interfaces::ObjectDetectionList& data)

    - ObjectDetectionListModule_ : adas::interfaces::ObjectDetectionListInterfaceProvider
      - Data elements
        - object_detection_list : adas::interfaces::ObjectDetectionList
*/

/**********************************************************************************************************************
  Constructor
**********************************************************************************************************************/
SensorFusion::SensorFusion(ConstructorToken&& token) : SensorFusionBase(std::move(token)) {
  VelocityServiceConsumer_->RegisterDataElementHandler_car_velocity(
      GetName(), [this](vaf::ConstDataPtr<const datatypes::Velocity> velocity) { OnVelocity(std::move(velocity)); });

  ImageServiceConsumer1_->RegisterDataElementHandler_image_scaling_factor_FieldNotifier(
      GetName(), [this](vaf::ConstDataPtr<const ::std::uint64_t> data) {
        vaf::OutputSyncStream{} << "Received Field Notifier value: " << *data << std::endl;
      });
}

void SensorFusion::OnVelocity(vaf::ConstDataPtr<const datatypes::Velocity> velocity) {
  is_enabled_ = velocity->velocity < kMaxVelocity;
}

/**********************************************************************************************************************
  1 periodic task(s)
**********************************************************************************************************************/
// Task with name PeriodicTask and a period of 200ms.
void SensorFusion::PeriodicTask() {
  if (is_enabled_) {
    vaf::OutputSyncStream{} << "SensorFusion::step\n";

    static std::uint64_t counter = 23;
    counter++;
    auto setter_future = ImageServiceConsumer1_->image_scaling_factor_FieldSetter(counter);
    setter_future.wait();
    if (!image_scaling_factor_getter_future_.valid()) {
      image_scaling_factor_getter_future_ = ImageServiceConsumer1_->image_scaling_factor_FieldGetter();
    }
    if (image_scaling_factor_getter_future_.valid()) {
      if (image_scaling_factor_getter_future_.wait_for(std::chrono::nanoseconds::zero()) ==
          std::future_status::ready) {
        auto image_scaling_factor_getter_result{image_scaling_factor_getter_future_.GetResult()};
        if (image_scaling_factor_getter_result.HasValue()) {
          vaf::OutputSyncStream{} << "Getter of Field results in: " << image_scaling_factor_getter_result.Value().data << "\n";
        } else {
          vaf::OutputSyncStream{} << "Getter of Field failed: " << image_scaling_factor_getter_result.Error().Message();
        }
        image_scaling_factor_getter_future_ =
            vaf::Future<af::adas_demo_app::services::image_scaling_factor_FieldGetter::Output>{};
      }
    }

    bool no_new_image{false};

    auto image1 = ImageServiceConsumer1_->GetAllocated_camera_image().InspectError(
        [&no_new_image](const vaf::Error&) { no_new_image = true; });
    auto image2 = ImageServiceConsumer2_->GetAllocated_camera_image().InspectError(
        [&no_new_image](const vaf::Error&) { no_new_image = true; });
    auto steering_angle = SteeringAngleServiceConsumer_->Get_steering_angle();
    auto velocity = VelocityServiceConsumer_->Get_car_velocity();

    if (!no_new_image) {
      ::adas::interfaces::ObjectDetectionList object_list =
          DoDetection(*image1.Value(), *image2.Value(), steering_angle, velocity);
      vaf::OutputSyncStream{} << "SensorFusion sending detection list\n";
      ObjectDetectionListModule_->Set_object_detection_list(object_list);
    }
  }

  static uint32_t velocity{1};
  auto future{VelocityServiceConsumer_->SetVelocity(velocity++)};
  assert(future.is_ready());

  vaf::OutputSyncStream{} << "SensorFusion call method SetVelocity with: " << velocity << std::endl;
}

::adas::interfaces::ObjectDetectionList SensorFusion::DoDetection(const datatypes::Image&, const datatypes::Image&,
                                                                  datatypes::SteeringAngle, datatypes::Velocity) {
  return ::adas::interfaces::ObjectDetectionList{};  // dummy implementation
}

void SensorFusion::OnError(const vaf::Error& error) {
  vaf::OutputSyncStream{} << "Error in SensorFusion: " << error.Message() << ", " << error.UserMessage() << std::endl;
  ReportError(error, true);
}

}  // namespace NsSensorFusion
}  // namespace NsApplicationUnit
