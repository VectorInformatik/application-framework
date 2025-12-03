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
/*!        \file  msra_platform.cpp
 *         \brief
 *
 *********************************************************************************************************************/

#include "nsapplicationunit/nsmsraplatform/msra_platform.h"
#include "vaf/output_sync_stream.h"

namespace NsApplicationUnit {
namespace NsMsraPlatform {

/*
  Data element API example for MyDataElement of type std::uint64_t
  ================================================================
  - Provider
    ::vaf::Result<::vaf::DataPtr<std::uint64_t>> Allocate_MyDataElement()
    ::vaf::Result<void> SetAllocated_MyDataElement(::vaf::DataPtr<std::uint64_t>&& data)
    ::vaf::Result<void> Set_MyDataElement(const std::uint64_t& data)
  - Consumer
    ::vaf::Result<::vaf::ConstDataPtr<const std::uint64_t>> GetAllocated_MyDataElement()
    std::uint64_t Get_MyDataElement()
    std::function<void(const ::vaf::ConstDataPtr<const std::uint64_t>)>
    void RegisterDataElementHandler_MyDataElement(std::string owner, std::function<void(const ::vaf::ConstDataPtr<const std::uint64_t>)>&& f)

  Consumer interfaces
  ===================
    - BrakeServiceConsumer_ : af::adas_demo_app::services::BrakeServiceConsumer
      - Data elements
        - brake_action : datatypes::BrakePressure
        - brake_summand_coefficient_FieldNotifier : std::uint64_t

      - Operations
        - ::vaf::Future<af::adas_demo_app::services::SumTwoSummands::Output> SumTwoSummands(const std::uint16_t& summand_one, const std::uint16_t& summand_two)
        - ::vaf::Future<af::adas_demo_app::services::brake_summand_coefficient_FieldGetter::Output> brake_summand_coefficient_FieldGetter()
        - ::vaf::Future<void> brake_summand_coefficient_FieldSetter(const std::uint64_t& data)

  Provider interfaces
  ===================
    - ImageServiceProvider1_ : af::adas_demo_app::services::ImageServiceProvider
      - Data elements
        - camera_image : datatypes::Image
        - image_scaling_factor_FieldNotifier : std::uint64_t

      - Operations
        - void RegisterOperationHandler_GetImageSize(std::function<af::adas_demo_app::services::GetImageSize::Output()>&& f)
        - void RegisterOperationHandler_image_scaling_factor_FieldGetter(std::function<af::adas_demo_app::services::image_scaling_factor_FieldGetter::Output()>&& f)
        - void RegisterOperationHandler_image_scaling_factor_FieldSetter(std::function<void(const std::uint64_t&)>&& f)

    - ImageServiceProvider2_ : af::adas_demo_app::services::ImageServiceProvider
      - Data elements
        - camera_image : datatypes::Image
        - image_scaling_factor_FieldNotifier : std::uint64_t

      - Operations
        - void RegisterOperationHandler_GetImageSize(std::function<af::adas_demo_app::services::GetImageSize::Output()>&& f)
        - void RegisterOperationHandler_image_scaling_factor_FieldGetter(std::function<af::adas_demo_app::services::image_scaling_factor_FieldGetter::Output()>&& f)
        - void RegisterOperationHandler_image_scaling_factor_FieldSetter(std::function<void(const std::uint64_t&)>&& f)

    - SteeringAngleServiceProvider_ : af::adas_demo_app::services::SteeringAngleServiceProvider
      - Data elements
        - steering_angle : datatypes::SteeringAngle

    - VelocityServiceProvider_ : af::adas_demo_app::services::VelocityServiceProvider
      - Data elements
        - car_velocity : datatypes::Velocity


*/

MsraPlatform::MsraPlatform(ConstructorToken&& token) : MsraPlatformBase(std::move(token)) {
  BrakeServiceConsumer_->RegisterDataElementHandler_brake_action(
      GetName(), [this](vaf::ConstDataPtr<const datatypes::BrakePressure> brake_pressure) {
        OnBrakePressure(std::move(brake_pressure));
      });
  BrakeServiceConsumer_->RegisterDataElementHandler_brake_summand_coefficient_FieldNotifier(
      GetName(), [this](vaf::ConstDataPtr<const std::uint64_t> data) {
        vaf::OutputSyncStream{}  << "Received brake_summand_coefficient Field Notifier value: " << *data << std::endl;
      });

  ImageServiceProvider1_->RegisterOperationHandler_GetImageSize(
      [this]() -> af::adas_demo_app::services::GetImageSize::Output {
        af::adas_demo_app::services::GetImageSize::Output output{};
        vaf::OutputSyncStream{} << "ImageServiceProvider1::GetImageSize Handler gets called\n";
        output.width = 100;
        output.height = 100;
        return output;
      });

  ImageServiceProvider1_->RegisterOperationHandler_image_scaling_factor_FieldSetter(
      [this](std::uint64_t const& data) -> void {
        vaf::OutputSyncStream{} << "ImageServiceProvider1::image_scaling_factor_FieldSetter Handler gets called\n";
        field_value_ = data;
      });
  ImageServiceProvider1_->RegisterOperationHandler_image_scaling_factor_FieldGetter(
      [this]() -> ::af::adas_demo_app::services::image_scaling_factor_FieldGetter::Output {
        ::af::adas_demo_app::services::image_scaling_factor_FieldGetter::Output output{};
        vaf::OutputSyncStream{} << "ImageServiceProvider1::image_scaling_factor_FieldGetter Handler gets called\n";
        output.data = field_value_;
        return output;
      });

  ImageServiceProvider2_->RegisterOperationHandler_GetImageSize(
      [this]() -> af::adas_demo_app::services::GetImageSize::Output {
        af::adas_demo_app::services::GetImageSize::Output output{};
        vaf::OutputSyncStream{} << "ImageServiceProvider2::GetImageSize Handler gets called\n";
        output.width = 100;
        output.height = 100;
        return output;
      });

  ImageServiceProvider2_->RegisterOperationHandler_image_scaling_factor_FieldSetter(
      [this](std::uint64_t const& data) -> void {
        vaf::OutputSyncStream{} << "ImageServiceProvider2::image_scaling_factor_FieldSetter Handler gets called\n";
        field_value_ = data;
      });
  ImageServiceProvider2_->RegisterOperationHandler_image_scaling_factor_FieldGetter(
      [this]() -> ::af::adas_demo_app::services::image_scaling_factor_FieldGetter::Output {
        ::af::adas_demo_app::services::image_scaling_factor_FieldGetter::Output output{};
        vaf::OutputSyncStream{} << "ImageServiceProvider2::image_scaling_factor_FieldGetter Handler gets called\n";
        output.data = field_value_;
        return output;
      });
}

void MsraPlatform::OnBrakePressure(vaf::ConstDataPtr<const datatypes::BrakePressure> brake_pressure) {
  is_enabled_ = brake_pressure->value < kMaxBrakePressure;
}

void MsraPlatform::PeriodicTask() {
  vaf::OutputSyncStream{} << "MsraPlatform sending image scaling factors Field Notifier\n";
  ImageServiceProvider1_->Set_image_scaling_factor_FieldNotifier(field_value_);
  ImageServiceProvider2_->Set_image_scaling_factor_FieldNotifier(field_value_);

  vaf::OutputSyncStream{} << "MsraPlatform sending steering angle and car velocity\n";
  SteeringAngleServiceProvider_->Set_steering_angle(steering_angle_);
  VelocityServiceProvider_->Set_car_velocity(velocity_);

  velocity_.timestamp++;
  velocity_.value++;
  steering_angle_.timestamp++;
  steering_angle_.value++;

  if (is_enabled_) {
    vaf::OutputSyncStream{} << "MsraPlatform::step\n";
    static std::uint64_t counter = 33;
    counter++;
    BrakeServiceConsumer_->brake_summand_coefficient_FieldSetter(counter);
    brake_summand_coefficient_getter_future_ = BrakeServiceConsumer_->brake_summand_coefficient_FieldGetter();

    if (brake_summand_coefficient_getter_future_.valid()) {
      brake_summand_coefficient_getter_future_.wait();
      auto brake_summand_coefficient_getter_result{brake_summand_coefficient_getter_future_.GetResult()};
      if (brake_summand_coefficient_getter_result.HasValue()) {
        vaf::OutputSyncStream{} << "Getter of brake_summand_coefficient_Field results in: "
                  << brake_summand_coefficient_getter_result.Value().data << "\n";
      } else {
        vaf::OutputSyncStream{} << "Getter of brake_summand_coefficient_Field failed: "
                  << brake_summand_coefficient_getter_result.Error().Message();
      }
      brake_summand_coefficient_getter_future_ = vaf::Future<
          af::adas_demo_app::services::brake_summand_coefficient_FieldGetter::Output>{};
    }
  }
}

}  // namespace NsMsraPlatform
}  // namespace NsApplicationUnit
