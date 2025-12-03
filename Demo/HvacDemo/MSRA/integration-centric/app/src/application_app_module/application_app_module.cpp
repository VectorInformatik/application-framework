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
/*!        \file  application_app_module.cpp
 *         \brief
 *
 *********************************************************************************************************************/

#include "demo/application_app_module.h"
#include "vaf/output_sync_stream.h"

namespace demo {

/**********************************************************************************************************************
  Constructor
**********************************************************************************************************************/
ApplicationAppModule::ApplicationAppModule(ConstructorToken&& token) : ApplicationAppModuleBase(std::move(token)) {
  // Insert your code here...
}

/**********************************************************************************************************************
  1 periodic task(s)
**********************************************************************************************************************/
// Task with name PeriodicTask and a period of 200ms.
void ApplicationAppModule::PeriodicTask() {
  AppHvacControlProvider_->Set_CompressorState("25");
  AppHvacControlProvider_->Set_ValvePosition("50");
  AppHvacControlProvider_->Set_FanSpeed("75");

  vaf::OutputSyncStream{} << "\tHvacStatus data received: " << '\n';
  vaf::OutputSyncStream{} << "\tCompressor: \t" << AppHvacStatusConsumer_->Get_CompressorStatus() << '\n';
  vaf::OutputSyncStream{} << "\tValve: \t\t" << AppHvacStatusConsumer_->Get_ValveStatus() << '\n';
  vaf::OutputSyncStream{} << "\tFan right speed: \t" << AppHvacStatusConsumer_->Get_FanRightSpeed() << '\n';
  vaf::OutputSyncStream{} << "\tFan left speed: \t" << AppHvacStatusConsumer_->Get_FanLeftSpeed() << '\n';
}

}  // namespace demo
