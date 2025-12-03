/*!********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2025 by Vector Informatik GmbH. All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  collision_detection.cpp
 *         \brief
 *
 *********************************************************************************************************************/

#include "nsapplicationunit/nscollisiondetection/collision_detection.h"
#include "vaf/output_sync_stream.h"

namespace NsApplicationUnit {
namespace NsCollisionDetection {

/*
  Generated based on configuration in ../../model/collision_detection.py

  Consumer interfaces
  ===================
    Data element API example for object_detection_list of type adas::interfaces::ObjectDetectionList
      - ::vaf::Result<::vaf::ConstDataPtr<const adas::interfaces::ObjectDetectionList>> GetAllocated_object_detection_list()
      - adas::interfaces::ObjectDetectionList Get_object_detection_list()
      - void RegisterDataElementHandler_object_detection_list(vaf::String owner, std::function<void(const ::vaf::ConstDataPtr<const adas::interfaces::ObjectDetectionList>)>&& f)
      - ObjectDetectionListModule_ : adas::interfaces::ObjectDetectionListInterfaceConsumer
      - Data elements
        - object_detection_list : adas::interfaces::ObjectDetectionList

  Provider interfaces
  ===================
    Data element API example for brake_action of type datatypes::BrakePressure
     - ::vaf::Result<::vaf::DataPtr<datatypes::BrakePressure>> Allocate_brake_action()
     - ::vaf::Result<void> SetAllocated_brake_action(::vaf::DataPtr<datatypes::BrakePressure>&& data)
     - ::vaf::Result<void> Set_brake_action(const datatypes::BrakePressure& data)

    - BrakeServiceProvider_ : af::adas_demo_app::services::BrakeServiceProvider
      - Data elements
        - brake_action : datatypes::BrakePressure
        - brake_summand_coefficient_FieldNotifier : std::uint64_t
      - Operations
        - void RegisterOperationHandler_SumTwoSummands(std::function<af::adas_demo_app::services::SumTwoSummands::Output(const std::uint16_t&, const std::uint16_t&)>&& f)
        - void RegisterOperationHandler_brake_summand_coefficient_FieldGetter(std::function<af::adas_demo_app::services::brake_summand_coefficient_FieldGetter::Output()>&& f)
        - void RegisterOperationHandler_brake_summand_coefficient_FieldSetter(std::function<void(const std::uint64_t&)>&& f)
*/

/**********************************************************************************************************************
  Constructor
**********************************************************************************************************************/
CollisionDetection::CollisionDetection(ConstructorToken&& token) : CollisionDetectionBase(std::move(token)) {
  ObjectDetectionListModule_->RegisterDataElementHandler_object_detection_list(
      GetName(),  // TODO(virmlj) can we get rid of the name paramater here?
      [this](vaf::ConstDataPtr<const ::adas::interfaces::ObjectDetectionList> object_detection_list) {
        OnObjectList(object_detection_list);
      });
  BrakeServiceProvider_->RegisterOperationHandler_SumTwoSummands(
      [this](
          std::uint16_t const& summand_one,
          std::uint16_t const& summand_two) -> af::adas_demo_app::services::SumTwoSummands::Output {
        ::af::adas_demo_app::services::SumTwoSummands::Output output{};
        output.sum = summand_one + summand_two;
        return output;
      });
  BrakeServiceProvider_->RegisterOperationHandler_brake_summand_coefficient_FieldSetter(
      [this](std::uint64_t const& data) -> void {
        vaf::OutputSyncStream{} << "Setter Handler gets called with value: " << data << "\n";
        field_value_ = data;
      });
  BrakeServiceProvider_->RegisterOperationHandler_brake_summand_coefficient_FieldGetter(
      [this]() -> ::af::adas_demo_app::services::brake_summand_coefficient_FieldGetter::Output {
        ::af::adas_demo_app::services::brake_summand_coefficient_FieldGetter::Output output{};
        vaf::OutputSyncStream{} << "Getter Handler gets called" << std::endl;
        output.data = field_value_;
        return output;
      });
}

/**********************************************************************************************************************
  1 periodic task(s)
**********************************************************************************************************************/
// Task with name PeriodicTask and a period of 200ms.
void CollisionDetection::PeriodicTask() {
  vaf::OutputSyncStream{} << "Collision detection is active\n";
  BrakeServiceProvider_->Set_brake_summand_coefficient_FieldNotifier(field_value_);
}

void CollisionDetection::OnObjectList(vaf::ConstDataPtr<const ::adas::interfaces::ObjectDetectionList>& object_list) {
  vaf::OutputSyncStream{} << "Collision onObjectList\n";
  ::datatypes::BrakePressure brake_pressure = ComputeBrakePressure(object_list);
  BrakeServiceProvider_->Set_brake_action(brake_pressure);

  BrakeServiceProvider_->Allocate_brake_action()
      .InspectError([](auto) { vaf::OutputSyncStream{} << "Failed to allocate break action\n"; })
      .AndThen([this, &brake_pressure](auto allocated_break_action) {
        *allocated_break_action = brake_pressure;
        BrakeServiceProvider_->SetAllocated_brake_action(std::move(allocated_break_action));
        return vaf::Result<void>{};
      });
}

::datatypes::BrakePressure CollisionDetection::ComputeBrakePressure(
    vaf::ConstDataPtr<const ::adas::interfaces::ObjectDetectionList>& object_list) {
  // internal logic
  static_cast<void>(object_list);
  for (auto& brake_pressure_pair : brake_pressure_) {
    brake_pressure_pair.second++;
  }
  return brake_pressure_;
}

void CollisionDetection::OnError(const vaf::Error& error) {
  ReportError(error, true);
}

}  // namespace NsCollisionDetection
}  // namespace NsApplicationUnit
