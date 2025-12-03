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
#include "vaf/output_sync_stream.h"
#include "demo/app_module2.h"

namespace demo {


/*
  Generated based on configuration in ../../model/app_module2.py

  Consumer interfaces
  ===================
    Data element API example for ICDataSTRING of type vaf::string
      - ::vaf::Result<::vaf::ConstDataPtr<const vaf::string>> GetAllocated_ICDataSTRING()
      - vaf::string Get_ICDataSTRING()
      - void RegisterDataElementHandler_ICDataSTRING(vaf::String owner, std::function<void(const ::vaf::ConstDataPtr<const vaf::string>)>&& f)

    - AppConsumerIC_ : ic_string::ICDataInterfaceSTRINGConsumer
      - Data elements
        - ICDataSTRING : vaf::string
    - MSRAConsumerZC_ : zc_int8::ZCDataInterfaceINT8Consumer
      - Data elements
        - ZCDataINT8 : std::int8_t
    - MSRAConsumerIPC_ : ipc_int8::IPCDataInterfaceINT8Consumer
      - Data elements
        - IPCDataINT8 : std::int8_t
    - MSRAConsumerSOMEIP_ : someip_int8::SOMEIPDataInterfaceINT8Consumer
      - Data elements
        - SOMEIPDataINT8 : std::int8_t
*/

/**********************************************************************************************************************
  Constructor
**********************************************************************************************************************/
AppModule2::AppModule2(ConstructorToken&& token)
    : AppModule2Base(std::move(token))
{
  // Insert your code here...
}

/**********************************************************************************************************************
  1 periodic task(s)
**********************************************************************************************************************/
// Task with name PeriodicTask and a period of 200ms.
void AppModule2::PeriodicTask() {
  vaf::OutputSyncStream{} << "Received internal communication channel msg :" << AppConsumerIC_->Get_ICDataSTRING() << std::endl; ;

  vaf::OutputSyncStream{} << "Received IPC msg : " << std::to_string(MSRAConsumerIPC_->Get_IPCDataINT8()) << std::endl;
  vaf::OutputSyncStream{} << "Received SOMEIP msg : " << std::to_string(MSRAConsumerSOMEIP_->Get_SOMEIPDataINT8()) << std::endl;
  MSRAConsumerZC_->GetAllocated_ZCDataINT8()
    .InspectError(
        [](const vaf::Error& error) {
         vaf::OutputSyncStream{} << "Failed to receive uint8 msg : " << error.Message() << std::endl; })
        .AndThen([](auto received_int8) {
           vaf::OutputSyncStream{} << "Received ZC msg : " << std::to_string(*received_int8) << std::endl;
        return vaf::Result<void>{};
      });
}


} // namespace demo
