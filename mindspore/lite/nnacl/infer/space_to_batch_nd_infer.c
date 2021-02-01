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

#include "nnacl/infer/space_to_batch_nd_infer.h"
#include <limits.h>

int SpaceToBatchNdInferShape(const TensorC *const *inputs, size_t inputs_size, TensorC **outputs, size_t outputs_size,
                             OpParameter *parameter) {
  if (outputs_size != 1 || inputs_size != 1) {
    return NNACL_INPUT_TENSOR_ERROR;
  }

  const TensorC *input = inputs[0];
  if (input->format_ != Format_NHWC) {
    return NNACL_ERR;
  }

  SetDataTypeFormat(outputs[0], input);
  if (!parameter->infer_flag_) {
    return NNACL_INFER_INVALID;
  }
  if (input->shape_size_ != 4) {
    return NNACL_ERR;
  }
  SpaceToBatchParameter *param = (SpaceToBatchParameter *)parameter;
  int *block_shape = param->block_sizes_;
  size_t block_shape_size = param->m_;
  int *padding = param->paddings_;
  int padding_left = 0;
  int padding_right = 0;
  int block_w = 1;
  if (block_shape_size == 2) {
    padding_left = padding[2];
    padding_right = padding[3];
    block_w = block_shape[1];
  }
  if (block_shape[0] * block_w > INT_MAX / input->shape_[kNHWC_N]) {
    return NNACL_ERR;
  }
  outputs[0]->shape_[kNHWC_N] = input->shape_[kNHWC_N] * block_shape[0] * block_w;
  if (padding[0] + padding[1] > INT_MAX - input->shape_[kNHWC_H]) {
    return NNACL_ERR;
  }
  outputs[0]->shape_[kNHWC_H] = (input->shape_[kNHWC_H] + padding[0] + padding[1]) / block_shape[0];
  if (padding_left + padding_right > INT_MAX - input->shape_[kNHWC_W]) {
    return NNACL_ERR;
  }
  outputs[0]->shape_[kNHWC_W] = (input->shape_[kNHWC_W] + padding_left + padding_right) / block_w;
  outputs[0]->shape_[kNHWC_C] = input->shape_[kNHWC_C];
  outputs[0]->shape_size_ = input->shape_size_;
  return NNACL_OK;
}