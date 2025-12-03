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
/*!        \file  app_module3.cpp
 *         \brief
 *
 *********************************************************************************************************************/
#include "demo/app_module3.h"
#include "vaf/output_sync_stream.h"

namespace demo {

/*
  Generated based on configuration in ../../model/app_module3.py

  Consumer interfaces
  ===================
    Data element API example for CompressorState of type std::uint8_t
      - ::vaf::Result<::vaf::ConstDataPtr<const std::uint8_t>> GetAllocated_CompressorState()
      - std::uint8_t Get_CompressorState()
      - void RegisterDataElementHandler_CompressorState(vaf::String owner, std::function<void(const ::vaf::ConstDataPtr<const std::uint8_t>)>&& f)

    - HvacControlConsumer_ : nsprototype::nsserviceinterface::nshvaccontrol::HvacControlConsumer
      - Data elements
        - CompressorState : std::uint8_t
        - ValvePosition : std::uint8_t
        - FanSpeed : std::uint8_t
      - Operations
        - ::vaf::Future<void> ChangeTemperature(const std::uint8_t& Value)

  Provider interfaces
  ===================
    Data element API example for CompressorStatus of type std::uint32_t
     - ::vaf::Result<::vaf::DataPtr<std::uint32_t>> Allocate_CompressorStatus()
     - ::vaf::Result<void> SetAllocated_CompressorStatus(::vaf::DataPtr<std::uint32_t>&& data)
     - ::vaf::Result<void> Set_CompressorStatus(const std::uint32_t& data)

    - HvacStatusProvider_ : nsprototype::nsserviceinterface::nshvacstatus::HvacStatusProvider
      - Data elements
        - CompressorStatus : std::uint32_t
        - ValveStatus : std::uint32_t
        - FanRightSpeed : std::uint32_t
        - FanLeftSpeed : std::uint32_t
      - Operations
        - void RegisterOperationHandler_SetDegree(std::function<void(const std::uint8_t&)>&& f)
*/

/**********************************************************************************************************************
  Constructor
**********************************************************************************************************************/
AppModule3::AppModule3(ConstructorToken&& token) : AppModule3Base(std::move(token)) {
  // Insert your code here...
  vaf::OutputSyncStream{} << "AppModule3: Registering the data element handlers" << std::endl;
  HvacControlConsumer_->RegisterDataElementHandler_CompressorState(
      "c_handler", [&](const ::vaf::ConstDataPtr<const std::uint8_t>& data) {
        if (!is_cs_subscribed_) {
          vaf::OutputSyncStream{} << "AppModule3: HvacStatusConsumer ValveStatus is subscribed and received: "
                    << std::to_string(*data) << std::endl;
          is_cs_subscribed_ = true;
        } else {
          vaf::OutputSyncStream{} << "AppModule3: HvacStatusConsumer CompressorState is subscribed and received: "
                    << std::to_string(*data) << std::endl;
        }
      });
  HvacControlConsumer_->RegisterDataElementHandler_ValvePosition(
      "v_handler", [&](const ::vaf::ConstDataPtr<const std::uint8_t>& data) {
        if (!is_vs_subscribed_) {
          vaf::OutputSyncStream{} << "AppModule3: HvacStatusConsumer ValveStatus is subscribed and received: "
                    << std::to_string(*data) << std::endl;
          is_vs_subscribed_ = true;
        } else {
          vaf::OutputSyncStream{} << "AppModule3: HvacStatusConsumer ValvePosition is subscribed: " << std::to_string(*data)
                    << std::endl;
        }
      });
  HvacControlConsumer_->RegisterDataElementHandler_FanSpeed(
      "f_handler", [&](const ::vaf::ConstDataPtr<const std::uint8_t>& data) {
        if (!is_fs_subscribed_) {
          vaf::OutputSyncStream{} << "AppModule3: HvacStatusConsumer ValveStatus is subscribed and received: "
                    << std::to_string(*data) << std::endl;
          is_fs_subscribed_ = true;
        } else {
          vaf::OutputSyncStream{} << "AppModule3: HvacStatusConsumer FanSpeed is subscribed: " << std::to_string(*data) << std::endl;
        }
      });
}

/**********************************************************************************************************************
  1 periodic task(s)
**********************************************************************************************************************/
// Task with name PeriodicTask and a period of 200ms.
void AppModule3::PeriodicTask() {
  // Insert your code for periodic execution here...
  vaf::OutputSyncStream{} << "AppModule3: Setting the values as received by the consumer." << std::endl;
  HvacStatusProvider_->Set_CompressorStatus(HvacControlConsumer_->Get_CompressorState());
  HvacStatusProvider_->Set_ValveStatus(HvacControlConsumer_->Get_ValvePosition());
  HvacStatusProvider_->Set_FanRightSpeed(HvacControlConsumer_->Get_FanSpeed());
  HvacStatusProvider_->Set_FanLeftSpeed(HvacControlConsumer_->Get_FanSpeed());
}

// vaf::Result<void> AppModule3::Init() {
//   return vaf::Result<void>{};
// }
// void AppModule3::Start() {
//   ReportOperational();
// }
// void AppModule3::Stop() {}
// void AppModule3::DeInit() {}
// void AppModule3::OnError(const vaf::Error& error) {
//   static_cast<void>(error);
// }

}  // namespace demo
