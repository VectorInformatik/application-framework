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
/*!        \file  app_module1.cpp
 *         \brief
 *
 *********************************************************************************************************************/
#include "demo/app_module1.h"
#include "vaf/output_sync_stream.h"
#include <string>

namespace demo {

/*
  Generated based on configuration in ../../model/app_module1.py

  Consumer interfaces
  ===================
    Data element API example for CompressorStatus of type std::uint32_t
      - ::vaf::Result<::vaf::ConstDataPtr<const std::uint32_t>> GetAllocated_CompressorStatus()
      - std::uint32_t Get_CompressorStatus()
      - void RegisterDataElementHandler_CompressorStatus(vaf::String owner, std::function<void(const ::vaf::ConstDataPtr<const std::uint32_t>)>&& f)

    - HvacStatusConsumer_ : nsprototype::nsserviceinterface::nshvacstatus::HvacStatusConsumer
      - Data elements
        - CompressorStatus : std::uint32_t
        - ValveStatus : std::uint32_t
        - FanRightSpeed : std::uint32_t
        - FanLeftSpeed : std::uint32_t
      - Operations
        - ::vaf::Future<void> SetDegree(const std::uint8_t& Value)

  Provider interfaces
  ===================
    Data element API example for MyValue of type std::uint32_t
     - ::vaf::Result<::vaf::DataPtr<std::uint32_t>> Allocate_MyValue()
     - ::vaf::Result<void> SetAllocated_MyValue(::vaf::DataPtr<std::uint32_t>&& data)
     - ::vaf::Result<void> Set_MyValue(const std::uint32_t& data)

    - DataExchangeProvider_ : demo::DataExchangeInterfaceProvider
      - Data elements
        - MyValue : std::uint32_t
      - Operations
        - void RegisterOperationHandler_MyFunction(std::function<demo::MyFunction::Output(const std::uint32_t&)>&& f)
*/

/**********************************************************************************************************************
  Constructor
**********************************************************************************************************************/
AppModule1::AppModule1(ConstructorToken&& token) : AppModule1Base(std::move(token)) {
  // Insert your code here...
  vaf::OutputSyncStream{} << "AppModule3: Registering the data element handlers" << std::endl;
  HvacStatusConsumer_->RegisterDataElementHandler_CompressorStatus(
      "c_handler", [&](const ::vaf::ConstDataPtr<const unsigned int>& data) {
        if (!is_cs_subscribed_) {
          vaf::OutputSyncStream{} << "AppModule1: HvacStatusConsumer CompressorStatus is subscribed and received: "
                    << std::to_string(*data) << std::endl;
          is_cs_subscribed_ = true;
        } else {
          vaf::OutputSyncStream{} << "AppModule1: HvacStatusConsumer CompressorStatus is received: " << std::to_string(*data)
                    << std::endl;
        }
      });
  HvacStatusConsumer_->RegisterDataElementHandler_ValveStatus(
      "v_handler", [&](const ::vaf::ConstDataPtr<const std::uint32_t>& data) {
        if (!is_vs_subscribed_) {
          vaf::OutputSyncStream{} << "AppModule1: HvacStatusConsumer ValveStatus is subscribed and received: "
                    << std::to_string(*data) << std::endl;
          is_vs_subscribed_ = true;
        } else {
          vaf::OutputSyncStream{} << "AppModule1: HvacStatusConsumer ValveStatus is received: " << std::to_string(*data) << std::endl;
        }
      });
  HvacStatusConsumer_->RegisterDataElementHandler_FanRightSpeed(
      "fr_handler", [&](const ::vaf::ConstDataPtr<const std::uint32_t>& data) {
        if (!is_frs_subscribed_) {
          vaf::OutputSyncStream{} << "AppModule1: HvacStatusConsumer FanRightSpeed is subscribed and received: "
                    << std::to_string(*data) << std::endl;
          is_frs_subscribed_ = true;
        } else {
          vaf::OutputSyncStream{} << "AppModule1: HvacStatusConsumer FanRightSpeed is received: " << std::to_string(*data)
                    << std::endl;
        }
      });
  HvacStatusConsumer_->RegisterDataElementHandler_FanLeftSpeed(
      "fl_handler", [&](const ::vaf::ConstDataPtr<const std::uint32_t>& data) {
        if (!is_fls_subscribed_) {
          vaf::OutputSyncStream{} << "AppModule1: HvacStatusConsumer FanLeftSpeed is subscribed and received: "
                    << std::to_string(*data) << std::endl;
          is_fls_subscribed_ = true;
        } else {
          vaf::OutputSyncStream{} << "AppModule1: HvacStatusConsumer FanLeftSpeed is received: " << std::to_string(*data)
                    << std::endl;
        }
      });
}

/**********************************************************************************************************************
  1 periodic task(s)
**********************************************************************************************************************/
// Task with name PeriodicTask and a period of 200ms.
void AppModule1::PeriodicTask() {
  // Insert your code for periodic execution here...
  vaf::OutputSyncStream{} << "AppModule1: Setting DataExchangeProvider MyValue to 1000." << std::endl;
  DataExchangeProvider_->Set_MyValue(1000);
}

// vaf::Result<void> AppModule1::Init() {
//   return vaf::Result<void>{};
// }
// void AppModule1::Start() {
//   ReportOperational();
// }
// void AppModule1::Stop() {}
// void AppModule1::DeInit() {}
// void AppModule1::OnError(const vaf::Error& error) {
//   static_cast<void>(error);
// }

}  // namespace demo
