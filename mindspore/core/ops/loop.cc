/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ops/loop.h"
#include "ops/op_utils.h"
#include "utils/check_convert_utils.h"

namespace mindspore {
namespace ops {
void Loop::Init(const int64_t sub_graph_index) { this->set_sub_graph_index(sub_graph_index); }

void Loop::set_sub_graph_index(const int64_t sub_graph_index) {
  this->AddAttr(kSubGraphIndex, MakeValue(sub_graph_index));
}

int64_t Loop::get_sub_graph_index() const {
  auto value_ptr = this->GetAttr(kSubGraphIndex);
  return GetValue<int64_t>(value_ptr);
}
REGISTER_PRIMITIVE_C(kNameLoop, Loop);
}  // namespace ops
}  // namespace mindspore
