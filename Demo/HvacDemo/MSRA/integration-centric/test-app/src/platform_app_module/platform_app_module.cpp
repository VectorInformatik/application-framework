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
/*!        \file  platform_app_module.cpp
 *         \brief
 *
 *********************************************************************************************************************/

#include "demo/platform_app_module.h"
#include "vaf/output_sync_stream.h"

namespace demo {


  /*
  Generated based on configuration in ../../model/platform_app_module.py

  Consumer interfaces
  ===================
    Data element API example for CompressorState of type std::uint8_t
      - ::vaf::Result<::vaf::ConstDataPtr<const std::uint8_t>> GetAllocated_CompressorState()
      - std::uint8_t Get_CompressorState()
      - void RegisterDataElementHandler_CompressorState(std::string owner, std::function<void(const ::vaf::ConstDataPtr<const std::uint8_t>)>&& f)

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
PlatformAppModule::PlatformAppModule(ConstructorToken&& token) : PlatformAppModuleBase(std::move(token)) {
  // Insert your code here...
}

/**********************************************************************************************************************
  1 periodic task(s)
**********************************************************************************************************************/
// Task with name PeriodicTask and a period of 200ms.
void PlatformAppModule::PeriodicTask() {
  HvacStatusProvider_->Set_CompressorStatus(1);
  HvacStatusProvider_->Set_ValveStatus(2);
  HvacStatusProvider_->Set_FanLeftSpeed(3);
  HvacStatusProvider_->Set_FanRightSpeed(4);

  std::uint8_t compressor_state = HvacControlConsumer_->Get_CompressorState();
  std::uint8_t valve_position = HvacControlConsumer_->Get_ValvePosition();
  std::uint8_t fan_speed = HvacControlConsumer_->Get_FanSpeed();
  vaf::OutputSyncStream{} << "\tHvacControl data received:" << '\n';
  vaf::OutputSyncStream{} << "\tCompressor: \t" << compressor_state << '\n';
  vaf::OutputSyncStream{} << "\tValve: \t\t" << valve_position << '\n';
  vaf::OutputSyncStream{} << "\tFan speed: \t" << fan_speed << '\n';
}

}  // namespace demo
