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
#include "vaf/output_sync_stream.h"
#include <string>
#include "demo/app_module1.h"

namespace demo {


/*
  Generated based on configuration in ../../model/app_module1.py

  Provider interfaces
  ===================
    Data element API example for ICDataSTRING of type vaf::string
     - ::vaf::Result<::vaf::DataPtr<vaf::string>> Allocate_ICDataSTRING()
     - ::vaf::Result<void> SetAllocated_ICDataSTRING(::vaf::DataPtr<vaf::string>&& data)
     - ::vaf::Result<void> Set_ICDataSTRING(const vaf::string& data)

    - AppProviderIC_ : ic_string::ICDataInterfaceSTRINGProvider
      - Data elements
        - ICDataSTRING : vaf::string
    - MSRAProviderZC_ : zc_uint8::ZCDataInterfaceUINT8Provider
      - Data elements
        - ZCDataUINT8 : std::uint8_t
    - MSRAProviderIPC_ : ipc_uint8::IPCDataInterfaceUINT8Provider
      - Data elements
        - IPCDataUINT8 : std::uint8_t
    - MSRAProviderSOMEIP_ : someip_uint8::SOMEIPDataInterfaceUINT8Provider
      - Data elements
        - SOMEIPDataUINT8 : std::uint8_t
*/

/**********************************************************************************************************************
  Constructor
**********************************************************************************************************************/
AppModule1::AppModule1(ConstructorToken&& token)
    : AppModule1Base(std::move(token))
{
  // Insert your code here...
}

/**********************************************************************************************************************
  1 periodic task(s)
**********************************************************************************************************************/
// Task with name PeriodicTask and a period of 200ms.
void AppModule1::PeriodicTask() {
  const auto *string_msg = "Internally communicating in a executable!";
  vaf::OutputSyncStream{} << "Sending :" << string_msg << " using internal communication channel of vaf!\n";
  AppProviderIC_->Set_ICDataSTRING(string_msg);

  uint8_msg_++;
  vaf::OutputSyncStream{} << "Sending " << std::to_string(uint8_msg_) << " using IPC, SOMEIP and ZC deployments of MSRA!\n";
  MSRAProviderIPC_->Set_IPCDataUINT8(uint8_msg_);
  MSRAProviderSOMEIP_->Set_SOMEIPDataUINT8(uint8_msg_);
  MSRAProviderZC_->Allocate_ZCDataUINT8()
      .InspectError([](auto) { vaf::OutputSyncStream{} << "Failed to allocate uint8 msg\n"; })
      .AndThen([this](auto allocated_uint8) {
        *allocated_uint8 = uint8_msg_;
        auto send_result = MSRAProviderZC_->SetAllocated_ZCDataUINT8(std::move(allocated_uint8));
        if(!send_result.HasValue()){
          vaf::OutputSyncStream{} << "SetAllocated_ZCDataUINT8 is unsuccessful!\n";
        }
        return vaf::Result<void>{};
      });
}


} // namespace demo
