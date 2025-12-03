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
/*!        \file  app_module1.cpp
 *         \brief
 *
 *********************************************************************************************************************/

#include "vaf/output_sync_stream.h"
#include "demo/app_module1.h"

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
    - DataExchangeProvider_ : demo::DataExchangeInterfaceProvider
      - Data elements
        - MyValue : std::uint32_t

      - Operations
        - void RegisterOperationHandler_MyFunction(std::function<demo::MyFunction::Output(const std::uint32_t&)>&& f)

*/

AppModule1::AppModule1(ConstructorToken&& token)
    : AppModule1Base(std::move(token))
{
  DataExchangeProvider_->RegisterOperationHandler_MyFunction(
    std::bind(&AppModule1::MyFunctionHandler, this, std::placeholders::_1));

  my_value = 100;
}

void AppModule1::PeriodicTask() {
  auto compressorStatus = HvacStatusConsumer_->Get_CompressorStatus();
  auto valveStatus = HvacStatusConsumer_->Get_ValveStatus();
  auto fanLeft = HvacStatusConsumer_->Get_FanLeftSpeed();
  auto fanRight = HvacStatusConsumer_->Get_FanRightSpeed();

  vaf::OutputSyncStream{} << "\nAppModule1 status:" << std::endl;
  vaf::OutputSyncStream{} << "\tCompressor: \t" << compressorStatus << std::endl;
  vaf::OutputSyncStream{} << "\tValve: \t\t" << valveStatus << std::endl;
  vaf::OutputSyncStream{} << "\tFan left: \t" << fanLeft << std::endl;
  vaf::OutputSyncStream{} << "\tFan right: \t" << fanRight << std::endl;

  DataExchangeProvider_->Set_MyValue(my_value++);
}

MyFunction::Output AppModule1::MyFunctionHandler(const std::uint32_t &value_in) {
  MyFunction::Output ret;
  vaf::OutputSyncStream{} << "\nAppModule1: MyFunctionHandler called." << std::endl;
  my_value += value_in;
  ret.MyValueOut = my_value;
  return ret;
}

} // namespace demo
