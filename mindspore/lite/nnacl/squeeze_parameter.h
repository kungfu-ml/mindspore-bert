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

#ifndef MINDSPORE_LITE_NNACL_SQUEEZE_PARAMETER_H_
#define MINDSPORE_LITE_NNACL_SQUEEZE_PARAMETER_H_
#include "nnacl/op_base.h"
#include "nnacl/int8/quantize.h"

#define SQUEEZE_OFFSET_MAX_SIZE 4

typedef struct SqueezeQuantArg {
  QuantArg *in_quant_args_;
  QuantArg *out_quant_args_;
} SqueezeQuantArg;

typedef struct SqueezeParameter {
  // primitive parameter
  OpParameter op_parameter_;
  int axis_[8];
  size_t axis_size_;

  // shape correlative
  const int *in_shape_;
  const int *out_shape_;
  int offset_size_;
  int64_t offset_[SQUEEZE_OFFSET_MAX_SIZE];
  int64_t in_offset_[SQUEEZE_OFFSET_MAX_SIZE];
  int input_dim_;
  // other parameter
  SqueezeQuantArg quant_arg;
} SqueezeParameter;

#endif  // MINDSPORE_LITE_NNACL_SQUEEZE_PARAMETER_H_
