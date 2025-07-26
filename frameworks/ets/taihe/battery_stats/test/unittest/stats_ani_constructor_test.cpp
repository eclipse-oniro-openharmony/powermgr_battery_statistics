/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <gtest/gtest.h>

#include "ohos.batteryStatistics.ani.hpp"
#include "stats_log.h"

using namespace OHOS::PowerMgr;

using namespace testing;
using namespace testing::ext;
namespace {
ani_status g_status1 = ANI_OK;
ani_status g_status2 = ANI_OK;
}

namespace ohos::batteryStatistics {
ani_status ANIRegister(ani_env *env)
{
    return g_status1;
}
}

namespace {
class StatsAniConstructorTest : public ::testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

static ani_status GetEnv(ani_vm *vm, uint32_t version, ani_env **result)
{
    return g_status2;
}
/**
 * @tc.name: StatsAniConstructorTest_001
 * @tc.desc: test AniConstructor
 * @tc.type: FUNC
 * @tc.require: issue#ICAK9Z
 */
HWTEST_F(StatsAniConstructorTest, StatsAniConstructorTest_001, TestSize.Level1)
{
    STATS_HILOGI(LABEL_TEST, "StatsAniConstructorTest_001 start");
    ani_vm vm;
    __ani_vm_api mock_c_api = {.GetEnv = GetEnv};
    vm.c_api = &mock_c_api;
    uint32_t result = 0;

    ani_status status = ANI_Constructor(&vm, &result);

    EXPECT_EQ(status, ANI_OK);
    EXPECT_EQ(result, ANI_VERSION_1);
    STATS_HILOGI(LABEL_TEST, "StatsAniConstructorTest_001 end");
}

/**
 * @tc.name: StatsAniConstructorTest_002
 * @tc.desc: test AniConstructor
 * @tc.type: FUNC
 * @tc.require: issue#ICAK9Z
 */
HWTEST_F(StatsAniConstructorTest, StatsAniConstructorTest_002, TestSize.Level1)
{
    STATS_HILOGI(LABEL_TEST, "StatsAniConstructorTest_002 start");
    ani_vm vm;
    __ani_vm_api mock_c_api = {.GetEnv = GetEnv};
    vm.c_api = &mock_c_api;
    uint32_t result = 0;

    g_status1 = ANI_ERROR;
    ani_status status = ANI_Constructor(&vm, &result);

    EXPECT_EQ(status, ANI_ERROR);
    STATS_HILOGI(LABEL_TEST, "StatsAniConstructorTest_002 end");
}

/**
 * @tc.name: StatsAniConstructorTest_003
 * @tc.desc: test AniConstructor
 * @tc.type: FUNC
 * @tc.require: issue#ICAK9Z
 */
HWTEST_F(StatsAniConstructorTest, StatsAniConstructorTest_003, TestSize.Level1)
{
    STATS_HILOGI(LABEL_TEST, "StatsAniConstructorTest_003 start");
    ani_vm vm;
    __ani_vm_api mock_c_api = {.GetEnv = GetEnv};
    vm.c_api = &mock_c_api;
    uint32_t result = 0;

    g_status1 = ANI_OK;
    g_status2 = ANI_ERROR;
    ani_status status = ANI_Constructor(&vm, &result);

    EXPECT_EQ(status, ANI_ERROR);
    STATS_HILOGI(LABEL_TEST, "StatsAniConstructorTest_003 end");
}
}