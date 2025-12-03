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

  // vaf::Result<void> Init() override;
  // void Start() noexcept override;
  // void Stop() noexcept override;
  // void DeInit() noexcept override;
  // void OnError(const vaf::Error& error) override;

  void PeriodicTask() override;

 private:
  bool is_cs_subscribed_{false};
  bool is_vs_subscribed_{false};
  bool is_frs_subscribed_{false};
  bool is_fls_subscribed_{false};
};

}  // namespace demo

#endif  // DEMO_APP_MODULE1_H
