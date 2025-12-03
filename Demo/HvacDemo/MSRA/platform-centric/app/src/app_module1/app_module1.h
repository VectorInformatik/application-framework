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
/*!        \file  app_module1.h
 *         \brief
 *
 *********************************************************************************************************************/

#ifndef DEMO_APP_MODULE1_H
#define DEMO_APP_MODULE1_H

#include "demo/app_module1_base.h"

namespace demo {

class AppModule1 : public AppModule1Base {
 public:
  AppModule1(ConstructorToken&& token);

  void PeriodicTask() override;

 private:
  uint32_t my_value;
  MyFunction::Output MyFunctionHandler(const std::uint32_t &value_in);
};

} // namespace demo

#endif // DEMO_APP_MODULE1_H
