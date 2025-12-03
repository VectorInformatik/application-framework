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
/*!        \file  app_module3.cpp
 *         \brief
 *
 *********************************************************************************************************************/

#include "vaf/output_sync_stream.h"
#include "demo/app_module3.h"

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
    - HvacControlConsumer_ : nsprototype::nsserviceinterface::nshvaccontrol::HvacControlConsumer
      - Data elements
        - CompressorState : std::uint8_t
        - ValvePosition : std::uint8_t
        - FanSpeed : std::uint8_t

      - Operations
        - ::vaf::Future<void> ChangeTemperature(const std::uint8_t& Value)

  Provider interfaces
  ===================
    - HvacStatusProvider_ : nsprototype::nsserviceinterface::nshvacstatus::HvacStatusProvider
      - Data elements
        - CompressorStatus : std::uint32_t
        - ValveStatus : std::uint32_t
        - FanRightSpeed : std::uint32_t
        - FanLeftSpeed : std::uint32_t

      - Operations
        - void RegisterOperationHandler_SetDegree(std::function<void(const std::uint8_t&)>&& f)

*/

AppModule3::AppModule3(ConstructorToken&& token)
    : AppModule3Base(std::move(token))
{
}

void AppModule3::PeriodicTask() {
  HvacStatusProvider_->Set_CompressorStatus(1);
  HvacStatusProvider_->Set_ValveStatus(2);
  HvacStatusProvider_->Set_FanLeftSpeed(3);
  HvacStatusProvider_->Set_FanRightSpeed(4);

  unsigned compressorState = HvacControlConsumer_->Get_CompressorState();
  unsigned valvePosition = HvacControlConsumer_->Get_ValvePosition();
  unsigned fanSpeed = HvacControlConsumer_->Get_FanSpeed();

  vaf::OutputSyncStream{} << "\nAppModule3 status:" << std::endl;
  vaf::OutputSyncStream{} << "\tCompressor: \t" << compressorState << std::endl;
  vaf::OutputSyncStream{} << "\tValve: \t\t" << valvePosition << std::endl;
  vaf::OutputSyncStream{} << "\tFan speed: \t" << fanSpeed << std::endl;
}


} // namespace demo
