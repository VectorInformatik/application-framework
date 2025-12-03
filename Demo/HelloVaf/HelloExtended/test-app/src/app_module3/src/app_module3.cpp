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
#include "vaf/output_sync_stream.h"
#include <string>
#include "demo/app_module3.h"

namespace demo {


/*
  Generated based on configuration in ../../model/app_module3.py

  Consumer interfaces
  ===================
    Data element API example for ZCDataUINT8 of type std::uint8_t
      - ::vaf::Result<::vaf::ConstDataPtr<const std::uint8_t>> GetAllocated_ZCDataUINT8()
      - std::uint8_t Get_ZCDataUINT8()
      - void RegisterDataElementHandler_ZCDataUINT8(vaf::String owner, std::function<void(const ::vaf::ConstDataPtr<const std::uint8_t>)>&& f)

    - MSRAConsumerZC_ : zc_uint8::ZCDataInterfaceUINT8Consumer
      - Data elements
        - ZCDataUINT8 : std::uint8_t
    - MSRAConsumerIPC_ : ipc_uint8::IPCDataInterfaceUINT8Consumer
      - Data elements
        - IPCDataUINT8 : std::uint8_t
    - MSRAConsumerSOMEIP_ : someip_uint8::SOMEIPDataInterfaceUINT8Consumer
      - Data elements
        - SOMEIPDataUINT8 : std::uint8_t

  Provider interfaces
  ===================
    Data element API example for ZCDataINT8 of type std::int8_t
     - ::vaf::Result<::vaf::DataPtr<std::int8_t>> Allocate_ZCDataINT8()
     - ::vaf::Result<void> SetAllocated_ZCDataINT8(::vaf::DataPtr<std::int8_t>&& data)
     - ::vaf::Result<void> Set_ZCDataINT8(const std::int8_t& data)

    - MSRAProviderZC_ : zc_int8::ZCDataInterfaceINT8Provider
      - Data elements
        - ZCDataINT8 : std::int8_t
    - MSRAProviderIPC_ : ipc_int8::IPCDataInterfaceINT8Provider
      - Data elements
        - IPCDataINT8 : std::int8_t
    - MSRAProviderSOMEIP_ : someip_int8::SOMEIPDataInterfaceINT8Provider
      - Data elements
        - SOMEIPDataINT8 : std::int8_t
*/

/**********************************************************************************************************************
  Constructor
**********************************************************************************************************************/
AppModule3::AppModule3(ConstructorToken&& token)
    : AppModule3Base(std::move(token))
{
  // Insert your code here...
}

/**********************************************************************************************************************
  1 periodic task(s)
**********************************************************************************************************************/
// Task with name PeriodicTask and a period of 200ms.
void AppModule3::PeriodicTask() {
  int8_msg_--;
  vaf::OutputSyncStream{} << "Sending " << std::to_string(int8_msg_) << " using IPC, SOMEIP and ZC deployments of MSRA!\n";
  MSRAProviderIPC_->Set_IPCDataINT8(int8_msg_);
  MSRAProviderSOMEIP_->Set_SOMEIPDataINT8(int8_msg_);
  MSRAProviderZC_->Allocate_ZCDataINT8()
      .InspectError([](auto) { vaf::OutputSyncStream{} << "Failed to allocate uint8 msg\n"; })
      .AndThen([this](auto allocated_int8) {
        *allocated_int8 = int8_msg_;
        auto send_result = MSRAProviderZC_->SetAllocated_ZCDataINT8(std::move(allocated_int8));
        if(!send_result.HasValue()){
          vaf::OutputSyncStream{} << "SetAllocated_ZCDataUINT8 is unsuccessful!\n";
        }
        return vaf::Result<void>{};
      });

  vaf::OutputSyncStream{} << "Received IPC msg : " << std::to_string(MSRAConsumerIPC_->Get_IPCDataUINT8()) << std::endl;
  vaf::OutputSyncStream{} << "Received SOMEIP msg : " << std::to_string(MSRAConsumerSOMEIP_->Get_SOMEIPDataUINT8()) << std::endl;
  MSRAConsumerZC_->GetAllocated_ZCDataUINT8()
    .InspectError(
        [](const vaf::Error& error) {
         vaf::OutputSyncStream{} << "Failed to receive uint8 msg : " << error.Message() << std::endl; })
        .AndThen([](auto received_uint8) {
           vaf::OutputSyncStream{} << "Received ZC msg : " << std::to_string(*received_uint8) << std::endl;
        return vaf::Result<void>{};
      });
}


} // namespace demo
