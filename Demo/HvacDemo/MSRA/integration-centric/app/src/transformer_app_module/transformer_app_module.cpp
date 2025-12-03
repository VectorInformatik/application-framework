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
/*!        \file  transformer_app_module.cpp
 *         \brief
 *
 *********************************************************************************************************************/

#include "demo/transformer_app_module.h"
#include "vaf/output_sync_stream.h"
#include <string>
#include "vaf/impl_type_string.h"

namespace demo {


/**********************************************************************************************************************
  Constructor
**********************************************************************************************************************/
TransformerAppModule::TransformerAppModule(ConstructorToken&& token) : TransformerAppModuleBase(std::move(token)) {
  // Insert your code here...
}

/**********************************************************************************************************************
  1 periodic task(s)
**********************************************************************************************************************/
// Task with name PeriodicTask and a period of 200ms.
void TransformerAppModule::PeriodicTask() {
  vaf::OutputSyncStream{} << "App1 handling the datatype differences between Platform and App defined interfaces..." << '\n';
  AppHvacStatusProvider_->Set_CompressorStatus(
      vaf::String(std::to_string(PlatformHvacStatusConsumer_->Get_CompressorStatus())));
  AppHvacStatusProvider_->Set_ValveStatus(vaf::String(std::to_string(PlatformHvacStatusConsumer_->Get_ValveStatus())));
  AppHvacStatusProvider_->Set_FanRightSpeed(
      vaf::String(std::to_string(PlatformHvacStatusConsumer_->Get_FanRightSpeed())));
  AppHvacStatusProvider_->Set_FanLeftSpeed(
      vaf::String(std::to_string(PlatformHvacStatusConsumer_->Get_FanLeftSpeed())));

  PlatformHvacControlProvider_->Set_CompressorState(
      static_cast<uint8_t>(std::stoi(AppHvacControlConsumer_->Get_CompressorState().c_str())));
  PlatformHvacControlProvider_->Set_ValvePosition(
      static_cast<uint8_t>(std::stoi(AppHvacControlConsumer_->Get_ValvePosition().c_str())));
  PlatformHvacControlProvider_->Set_FanSpeed(
      static_cast<uint8_t>(std::stoi(AppHvacControlConsumer_->Get_FanSpeed().c_str())));
}

}  // namespace demo
