/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stats_service_stub_test.h"
#include "stats_log.h"

#include <message_parcel.h>

#include "stats_errors.h"
#include "stats_log.h"
#include "ibattery_stats.h"
#include "battery_stats_proxy.h"
#include "battery_stats_service.h"
#include "battery_stats_stub.h"
#include "battery_stats_info.h"

using namespace OHOS;
using namespace OHOS::PowerMgr;
using namespace std;
using namespace testing::ext;

namespace {
/**
 * @tc.name: StatsServiceStubTest_001
 * @tc.desc: test BatteryStatsStub
 * @tc.type: FUNC
 * @tc.require: issueI663DX
 */
HWTEST_F (StatsServiceStubTest, StatsServiceStubTest_001, TestSize.Level0)
{
    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_001 start");
    sptr<BatteryStatsService> statsService = BatteryStatsService::GetInstance();
    sptr<BatteryStatsStub> statsStub = static_cast<sptr<BatteryStatsStub>>(statsService);

    MessageParcel data;
    MessageParcel reply;
    MessageOption option;

    int ret = statsStub->OnRemoteRequest(
        static_cast<uint32_t>(PowerMgr::IBatteryStatsIpcCode::COMMAND_GET_BATTERY_STATS_IPC),
        data, reply, option);
    EXPECT_EQ(ret, ERR_TRANSACTION_FAILED);
    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_001 end");
}

/**
 * @tc.name: StatsServiceStubTest_002
 * @tc.desc: test BatteryStatsStub
 * @tc.type: FUNC
 * @tc.require: issueI663DX
 */
HWTEST_F (StatsServiceStubTest, StatsServiceStubTest_002, TestSize.Level0)
{
    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_002 start");
    sptr<BatteryStatsService> statsService = BatteryStatsService::GetInstance();
    sptr<BatteryStatsStub> statsStub = static_cast<sptr<BatteryStatsStub>>(statsService);

    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    data.WriteInterfaceToken(BatteryStatsProxy::GetDescriptor());

    uint32_t invalidCode =
        static_cast<uint32_t>(PowerMgr::IBatteryStatsIpcCode::COMMAND_GET_BATTERY_STATS_IPC) + 100;
    int ret = statsStub->OnRemoteRequest(invalidCode, data, reply, option);
    EXPECT_NE(ret, ERR_OK);
    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_002 end");
}

/**
 * @tc.name: StatsServiceStubTest_003
 * @tc.desc: test size of ShellDumpStub param exceed Max limit
 * @tc.type: FUNC
 * @tc.require: issueI6ARNA
 */
HWTEST_F (StatsServiceStubTest, StatsServiceStubTest_003, TestSize.Level0)
{
    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_003 start.");
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    sptr<BatteryStatsService> statsService = BatteryStatsService::GetInstance();
    sptr<BatteryStatsStub> statsStub = static_cast<sptr<BatteryStatsStub>>(statsService);

    data.WriteInterfaceToken(BatteryStatsProxy::GetDescriptor());
    const int32_t PARAM_MAX_NUM = 1024000;
    data.WriteUint32(PARAM_MAX_NUM);
    uint32_t code = static_cast<uint32_t>(PowerMgr::IBatteryStatsIpcCode::COMMAND_SHELL_DUMP_IPC);
    int32_t ret = statsStub->OnRemoteRequest(code, data, reply, option);
    EXPECT_EQ(ret, ERR_INVALID_DATA) << " ret:" << ret;

    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_003 end.");
}

/**
 * @tc.name: StatsServiceStubTest_004
 * @tc.desc: test GetBatteryStats
 * @tc.type: FUNC
 * @tc.require: issueI6ARNA
 */
HWTEST_F (StatsServiceStubTest, StatsServiceStubTest_004, TestSize.Level0)
{
    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_004 start.");
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    sptr<BatteryStatsService> statsService = BatteryStatsService::GetInstance();
    sptr<BatteryStatsStub> statsStub = static_cast<sptr<BatteryStatsStub>>(statsService);

    data.WriteInterfaceToken(BatteryStatsProxy::GetDescriptor());
    ParcelableBatteryStatsList batteryStats;
    batteryStats.statsList_.push_back(nullptr);
    bool ret = reply.WriteParcelable(&batteryStats);
    EXPECT_TRUE(ret);

    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_004 end.");
}

/**
 * @tc.name: StatsServiceStubTest_005
 * @tc.desc: test GetBatteryStats
 * @tc.type: FUNC
 * @tc.require: issueI6ARNA
 */
HWTEST_F (StatsServiceStubTest, StatsServiceStubTest_005, TestSize.Level0)
{
    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_005 start.");
    MessageParcel data;
    Parcel reply;
    MessageOption option;
    sptr<BatteryStatsService> statsService = BatteryStatsService::GetInstance();
    sptr<BatteryStatsStub> statsStub = static_cast<sptr<BatteryStatsStub>>(statsService);

    data.WriteInterfaceToken(BatteryStatsProxy::GetDescriptor());
    const int32_t PARAM_MAX_NUM = 1024000;
    reply.WriteInt32(PARAM_MAX_NUM);
    ParcelableBatteryStatsList* result = ParcelableBatteryStatsList::Unmarshalling(reply);
    EXPECT_EQ(result, nullptr);

    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_005 end.");
}

/**
 * @tc.name: StatsServiceStubTest_006
 * @tc.desc: test GetBatteryStats
 * @tc.type: FUNC
 * @tc.require: issueI6ARNA
 */
HWTEST_F (StatsServiceStubTest, StatsServiceStubTest_006, TestSize.Level0)
{
    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_006 start.");
    MessageParcel data;
    Parcel reply;
    MessageOption option;
    sptr<BatteryStatsService> statsService = BatteryStatsService::GetInstance();
    sptr<BatteryStatsStub> statsStub = static_cast<sptr<BatteryStatsStub>>(statsService);
    data.WriteInterfaceToken(BatteryStatsProxy::GetDescriptor());
    const int32_t PARAM_ZERO = 0;
    reply.WriteInt32(PARAM_ZERO);
    ParcelableBatteryStatsList* result = ParcelableBatteryStatsList::Unmarshalling(reply);
    EXPECT_NE(result, nullptr);
    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_006 end.");
}

/**
 * @tc.name: StatsServiceStubTest_007
 * @tc.desc: test GetBatteryStats
 * @tc.type: FUNC
 * @tc.require: issueI6ARNA
 */
HWTEST_F (StatsServiceStubTest, StatsServiceStubTest_007, TestSize.Level0)
{
    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_007 start.");
    MessageParcel data;
    Parcel reply;
    MessageOption option;
    sptr<BatteryStatsService> statsService = BatteryStatsService::GetInstance();
    sptr<BatteryStatsStub> statsStub = static_cast<sptr<BatteryStatsStub>>(statsService);
    data.WriteInterfaceToken(BatteryStatsProxy::GetDescriptor());
    const int32_t PARAM_MINUS_ONE = -1;
    reply.WriteInt32(PARAM_MINUS_ONE);
    ParcelableBatteryStatsList* result = ParcelableBatteryStatsList::Unmarshalling(reply);
    EXPECT_EQ(result, nullptr);
    STATS_HILOGI(LABEL_TEST, "StatsServiceStubTest_007 end.");
}
}