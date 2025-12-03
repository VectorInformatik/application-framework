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
/*!        \file  app_module2.cpp
 *         \brief
 *
 *********************************************************************************************************************/

#include "vaf/output_sync_stream.h"
#include "demo/app_module2.h"

namespace demo {


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
    - DataExchangeConsumer_ : demo::DataExchangeInterfaceConsumer
      - Data elements
        - MyValue : std::uint32_t

      - Operations
        - ::vaf::Future<demo::MyFunction::Output> MyFunction(const std::uint32_t& MyValueIn)

  Provider interfaces
  ===================
    - HvacControlProvider_ : nsprototype::nsserviceinterface::nshvaccontrol::HvacControlProvider
      - Data elements
        - CompressorState : std::uint8_t
        - ValvePosition : std::uint8_t
        - FanSpeed : std::uint8_t

      - Operations
        - void RegisterOperationHandler_ChangeTemperature(std::function<void(const std::uint8_t&)>&& f)

*/

AppModule2::AppModule2(ConstructorToken&& token)
    : AppModule2Base(std::move(token))
{
  DataExchangeConsumer_->RegisterDataElementHandler_MyValue(
      "AppModule2", std::bind(&AppModule2::MyValueHandler, this, std::placeholders::_1));

    HvacControlProvider_->RegisterOperationHandler_ChangeTemperature(
      std::bind(&AppModule2::ChangeTemperatureHandler, this, std::placeholders::_1));

    compressor_state = 0;
    valve_position = 0;
    fan_speed = 0;
}

void AppModule2::PeriodicTask() {
  HvacControlProvider_->Set_CompressorState(compressor_state++);
  HvacControlProvider_->Set_ValvePosition(valve_position--);
  HvacControlProvider_->Set_FanSpeed(fan_speed++);

  DataExchangeConsumer_->MyFunction(static_cast<uint32_t>(compressor_state));
}

void AppModule2::MyValueHandler(vaf::ConstDataPtr<const uint32_t> input) {
  vaf::OutputSyncStream{} << "\nAppModule2:" << std::endl;
  vaf::OutputSyncStream{} << "\tMyValue: \t" << *input << std::endl;
}

void AppModule2::ChangeTemperatureHandler(const uint8_t& temp) {
  vaf::OutputSyncStream{} << "\nAppModule2: ChangeTemperatureHandler called." << std::endl;
  vaf::OutputSyncStream{} << "\tTemperature: \t" << temp << std::endl;
}

} // namespace demo
