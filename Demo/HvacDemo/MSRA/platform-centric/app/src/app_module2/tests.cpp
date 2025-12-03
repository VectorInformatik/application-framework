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
/*!        \file  tests.cpp
 *         \brief
 *
 *********************************************************************************************************************/
#include <cstddef>
#include <cstdint>
#include <csignal>
#include "vaf/output_sync_stream.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "demo/data_exchange_interface_consumer_mock.h"
#include "nsprototype/nsserviceinterface/nshvaccontrol/hvac_control_provider_mock.h"
#include "demo/app_module2.h"

// Put inside test to skip
//GTEST_SKIP() << "Skipping single test";
using ::testing::Return;
using ::testing::_;

namespace vaf {
    /*!
     * \brief Initializes the signal handling.
     * \return void.
     */
    void InitializeSignalHandling() noexcept {
      bool success{true};
      sigset_t signals;

      /* Block all signals except the SIGABRT, SIGBUS, SIGFPE, SIGILL, SIGSEGV signals because blocking them will lead to
       * undefined behavior. Their default handling shall not be changed (dependent on underlying POSIX environment, usually
       * process is killed and a dump file is written). Signal mask will be inherited by subsequent threads. */

      success = success && (0 == sigfillset(&signals));
      success = success && (0 == sigdelset(&signals, SIGABRT));
      success = success && (0 == sigdelset(&signals, SIGBUS));
      success = success && (0 == sigdelset(&signals, SIGFPE));
      success = success && (0 == sigdelset(&signals, SIGILL));
      success = success && (0 == sigdelset(&signals, SIGSEGV));
      success = success && (0 == pthread_sigmask(SIG_SETMASK, &signals, nullptr));

      if (!success) {
        // Exit
      }
    }

    class AppModule2UnitTest : public ::testing::Test {
    protected:
      AppModule2UnitTest() {}

      virtual ~AppModule2UnitTest() {}

      virtual void SetUp() {
        InitializeSignalHandling();
      }

      virtual void TearDown() {
      }
    };

    TEST_F(AppModule2UnitTest, Test_1) {
      auto DataExchangeConsumerMock = std::make_shared<demo::DataExchangeInterfaceConsumerMock>();
      auto HvacControlProviderMock = std::make_shared<nsprototype::nsserviceinterface::nshvaccontrol::HvacControlProviderMock>();

      EXPECT_CALL(*DataExchangeConsumerMock, RegisterDataElementHandler_MyValue("AppModule2", _)).Times(1);

      EXPECT_CALL(*HvacControlProviderMock, RegisterOperationHandler_ChangeTemperature(_)).Times(1);

      auto AppModule2 = std::make_shared<demo::AppModule2>( demo::AppModule2 ::ConstructorToken{
        DataExchangeConsumerMock,
        HvacControlProviderMock
      });
    }


    TEST_F(AppModule2UnitTest, Test_2) {
      auto DataExchangeConsumerMock = std::make_shared<demo::DataExchangeInterfaceConsumerMock>();
      auto HvacControlProviderMock = std::make_shared<nsprototype::nsserviceinterface::nshvaccontrol::HvacControlProviderMock>();

      EXPECT_CALL(*DataExchangeConsumerMock, RegisterDataElementHandler_MyValue("AppModule2", _)).Times(1);

      EXPECT_CALL(*HvacControlProviderMock, RegisterOperationHandler_ChangeTemperature(_)).Times(1);

      auto AppModule2 = std::make_shared<demo::AppModule2>( demo::AppModule2 ::ConstructorToken{
        DataExchangeConsumerMock,
        HvacControlProviderMock
      });

      EXPECT_CALL(*HvacControlProviderMock, Set_CompressorState(0)).Times(1);
      EXPECT_CALL(*HvacControlProviderMock, Set_ValvePosition(0)).Times(1);
      EXPECT_CALL(*HvacControlProviderMock, Set_FanSpeed(0)).Times(1);

      EXPECT_CALL(*DataExchangeConsumerMock, MyFunction(1)).Times(1);

      AppModule2->PeriodicTask();
    }
} // namespace vaf
