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
/*!        \file  app_module3.h
 *         \brief
 *
 *********************************************************************************************************************/

#ifndef DEMO_APP_MODULE3_H
#define DEMO_APP_MODULE3_H

#include "demo/app_module3_base.h"

namespace demo {

class AppModule3 : public AppModule3Base {
 public:
  AppModule3(ConstructorToken&& token);

  void PeriodicTask() override;

 private:
    std::int8_t int8_msg_=0;
};

} // namespace demo

#endif // DEMO_APP_MODULE3_H
