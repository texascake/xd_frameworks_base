/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <memory>
#include <string>
#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "androidfw/ApkAssets.h"
#include "idmap2/ResourceUtils.h"

#include "TestHelpers.h"

using ::testing::NotNull;

namespace android {
namespace idmap2 {

class ResourceUtilsTests : public Idmap2Tests {
 protected:
  void SetUp() override {
    Idmap2Tests::SetUp();

    apk_assets_ = ApkAssets::Load(GetTargetApkPath());
    ASSERT_THAT(apk_assets_, NotNull());

    am_.SetApkAssets({apk_assets_.get()});
  }

  const AssetManager2& GetAssetManager() {
    return am_;
  }

 private:
  AssetManager2 am_;
  std::unique_ptr<const ApkAssets> apk_assets_;
};

TEST_F(ResourceUtilsTests, ResToTypeEntryName) {
  bool lookup_ok;
  std::string name;
  std::tie(lookup_ok, name) = utils::ResToTypeEntryName(GetAssetManager(), 0x7f010000u);
  ASSERT_TRUE(lookup_ok);
  ASSERT_EQ(name, "integer/int1");
}

TEST_F(ResourceUtilsTests, ResToTypeEntryNameNoSuchResourceId) {
  bool lookup_ok;
  std::tie(lookup_ok, std::ignore) = utils::ResToTypeEntryName(GetAssetManager(), 0x7f123456u);
  ASSERT_FALSE(lookup_ok);
}

}  // namespace idmap2
}  // namespace android
