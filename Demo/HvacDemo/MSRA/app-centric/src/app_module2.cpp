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
/*!        \file  app_module2.cpp
 *         \brief
 *
 *********************************************************************************************************************/
#include "demo/app_module2.h"
#include "vaf/output_sync_stream.h"

namespace demo {

/*
  Generated based on configuration in ../../model/app_module2.py

  Consumer interfaces
  ===================
    Data element API example for MyValue of type std::uint32_t
      - ::vaf::Result<::vaf::ConstDataPtr<const std::uint32_t>> GetAllocated_MyValue()
      - std::uint32_t Get_MyValue()
      - void RegisterDataElementHandler_MyValue(vaf::String owner, std::function<void(const ::vaf::ConstDataPtr<const std::uint32_t>)>&& f)

    - DataExchangeConsumer_ : demo::DataExchangeInterfaceConsumer
      - Data elements
        - MyValue : std::uint32_t
      - Operations
        - ::vaf::Future<demo::MyFunction::Output> MyFunction(const std::uint32_t& MyValueIn)

  Provider interfaces
  ===================
    Data element API example for CompressorState of type std::uint8_t
     - ::vaf::Result<::vaf::DataPtr<std::uint8_t>> Allocate_CompressorState()
     - ::vaf::Result<void> SetAllocated_CompressorState(::vaf::DataPtr<std::uint8_t>&& data)
     - ::vaf::Result<void> Set_CompressorState(const std::uint8_t& data)

    - HvacControlProvider_ : nsprototype::nsserviceinterface::nshvaccontrol::HvacControlProvider
      - Data elements
        - CompressorState : std::uint8_t
        - ValvePosition : std::uint8_t
        - FanSpeed : std::uint8_t
      - Operations
        - void RegisterOperationHandler_ChangeTemperature(std::function<void(const std::uint8_t&)>&& f)
*/

/**********************************************************************************************************************
  Constructor
**********************************************************************************************************************/
AppModule2::AppModule2(ConstructorToken&& token) : AppModule2Base(std::move(token)) {
  // Insert your code here...
  DataExchangeConsumer_->RegisterDataElementHandler_MyValue(
      "m_handler", [&](const ::vaf::ConstDataPtr<const std::uint32_t>& data) {
        if (!is_data_subscribed_) {
          vaf::OutputSyncStream{} << "AppModule2: DataExchangeConsumer MyValue is subscribed and received: " << std::to_string(*data)
                    << std::endl;
          is_data_subscribed_ = true;
        } else {
          vaf::OutputSyncStream{} << "AppModule2: DataExchangeConsumer MyValue is received: " << std::to_string(*data) << std::endl;
        }
      });
}

/**********************************************************************************************************************
  1 periodic task(s)
**********************************************************************************************************************/
// Task with name PeriodicTask and a period of 200ms.
void AppModule2::PeriodicTask() {
  // Insert your code for periodic execution here...
  vaf::OutputSyncStream{}
      << "AppModule2: Setting HvacControlProvider CompressorState, ValvePosition and FanSpeed to 50, 100 and 150."
      << std::endl;
  HvacControlProvider_->Set_CompressorState(static_cast<std::uint8_t>(50));
  HvacControlProvider_->Set_ValvePosition(static_cast<std::uint8_t>(100));
  HvacControlProvider_->Set_FanSpeed(static_cast<std::uint8_t>(150));
}

// vaf::Result<void> AppModule2::Init() {
//   return vaf::Result<void>{};
// }
// void AppModule2::Start() {
//   ReportOperational();
// }
// void AppModule2::Stop() {}
// void AppModule2::DeInit() {}
// void AppModule2::OnError(const vaf::Error& error) {
//   static_cast<void>(error);
// }

}  // namespace demo
