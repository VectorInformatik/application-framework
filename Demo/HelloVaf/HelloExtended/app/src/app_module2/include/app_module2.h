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
/*!        \file  app_module2.h
 *         \brief
 *
 *********************************************************************************************************************/

#ifndef DEMO_APP_MODULE2_H
#define DEMO_APP_MODULE2_H

#include "demo/app_module2_base.h"

namespace demo {

class AppModule2 : public AppModule2Base {
 public:
  AppModule2(ConstructorToken&& token);

  void PeriodicTask() override;

 private:
};

} // namespace demo

#endif // DEMO_APP_MODULE2_H
