/**
 * Copyright 2021 Huawei Technologies Co., Ltd
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

#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_GELU_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_GELU_H_

#include <vector>
#include "include/errorcode.h"
#include "src/lite_kernel.h"
#include "nnacl/gelu_parameter.h"

namespace mindspore::kernel {
class GeluCPUKernel : public LiteKernel {
 public:
  GeluCPUKernel(OpParameter *parameter, const std::vector<lite::Tensor *> &inputs,
                const std::vector<lite::Tensor *> &outputs, const lite::InnerContext *ctx,
                const mindspore::lite::PrimitiveC *primitive)
      : LiteKernel(parameter, inputs, outputs, ctx, primitive), thread_count_(ctx->thread_num_) {}
  ~GeluCPUKernel() = default;

  int Init() override;
  int ReSize() override;
  int Run() override;
  int DoGelu(int task_id);

 private:
  bool approximate_ = true;
  float *in_data_ = nullptr;
  float *out_data_ = nullptr;
  int thread_count_ = 0;
};
}  // namespace mindspore::kernel

#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_GELU_H_