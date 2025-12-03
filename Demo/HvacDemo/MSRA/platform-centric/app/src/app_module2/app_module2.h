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
  uint8_t compressor_state;
  uint8_t valve_position;
  uint8_t fan_speed;
  void MyValueHandler(vaf::ConstDataPtr<const uint32_t> input);
  void ChangeTemperatureHandler(const uint8_t& temp);
};

} // namespace demo

#endif // DEMO_APP_MODULE2_H
