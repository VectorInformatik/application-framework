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
#include "nsprototype/nsserviceinterface/nshvacstatus/hvac_status_consumer_mock.h"
#include "demo/data_exchange_interface_provider_mock.h"
#include "demo/app_module1.h"

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

    class AppModule1UnitTest : public ::testing::Test {
    protected:
      AppModule1UnitTest() {}

      virtual ~AppModule1UnitTest() {}

      virtual void SetUp() {
        InitializeSignalHandling();
      }

      virtual void TearDown() {
      }
    };

    TEST_F(AppModule1UnitTest, Test_1) {
      auto HvacStatusConsumerMock = std::make_shared<nsprototype::nsserviceinterface::nshvacstatus::HvacStatusConsumerMock>();
      auto DataExchangeProviderMock = std::make_shared<demo::DataExchangeInterfaceProviderMock>();

      EXPECT_CALL(*DataExchangeProviderMock, RegisterOperationHandler_MyFunction(_)).Times(1);

      auto AppModule1 = std::make_shared<demo::AppModule1>( demo::AppModule1 ::ConstructorToken{
        HvacStatusConsumerMock,
        DataExchangeProviderMock
      });
    }

    TEST_F(AppModule1UnitTest, Test_2) {
      auto HvacStatusConsumerMock = std::make_shared<nsprototype::nsserviceinterface::nshvacstatus::HvacStatusConsumerMock>();
      auto DataExchangeProviderMock = std::make_shared<demo::DataExchangeInterfaceProviderMock>();

      EXPECT_CALL(*DataExchangeProviderMock, RegisterOperationHandler_MyFunction(_)).Times(1);

      auto AppModule1 = std::make_shared<demo::AppModule1>( demo::AppModule1 ::ConstructorToken{
        HvacStatusConsumerMock,
        DataExchangeProviderMock
      });

      std::uint32_t test_value{7};

      // Verify the expected calls and also avoid uninteresting mock call warning.
      EXPECT_CALL(*HvacStatusConsumerMock, Get_CompressorStatus()).Times(1).WillOnce(Return(test_value));
      EXPECT_CALL(*HvacStatusConsumerMock, Get_ValveStatus()).Times(1).WillOnce(Return(test_value));
      EXPECT_CALL(*HvacStatusConsumerMock, Get_FanLeftSpeed()).Times(1).WillOnce(Return(test_value));
      EXPECT_CALL(*HvacStatusConsumerMock, Get_FanRightSpeed()).Times(1).WillOnce(Return(test_value));

      EXPECT_CALL(*DataExchangeProviderMock, Set_MyValue(100)).Times(1);

      AppModule1->PeriodicTask();
    }
} // namespace vaf
