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
#ifndef MINDSPORE_LITE_INCLUDE_TRAIN_TRAIN_CFG_H_
#define MINDSPORE_LITE_INCLUDE_TRAIN_TRAIN_CFG_H_
#include <string>

namespace mindspore {
namespace lite {

/// \brief MixPrecisionCfg defined for holding mix precision training configuration.
class MixPrecisionCfg {
 public:
  MixPrecisionCfg() {
    this->dynamic_loss_scale_ = false;
    this->loss_scale_ = 128.0f;
    this->keep_batchnorm_fp32_ = true;
    this->num_of_not_nan_iter_th_ = 1000;
  }
  MixPrecisionCfg(const MixPrecisionCfg &rhs) {
    this->dynamic_loss_scale_ = rhs.dynamic_loss_scale_;
    this->loss_scale_ = rhs.loss_scale_;
    this->keep_batchnorm_fp32_ = rhs.keep_batchnorm_fp32_;
    this->num_of_not_nan_iter_th_ = rhs.num_of_not_nan_iter_th_;
  }
  MixPrecisionCfg &operator=(MixPrecisionCfg const &rhs) {
    this->dynamic_loss_scale_ = rhs.dynamic_loss_scale_;
    this->loss_scale_ = rhs.loss_scale_;
    this->keep_batchnorm_fp32_ = rhs.keep_batchnorm_fp32_;
    this->num_of_not_nan_iter_th_ = rhs.num_of_not_nan_iter_th_;
    return *this;
  }
  bool dynamic_loss_scale_;    /**< Enable\disable dynamic loss scale during mix precision training */
  float loss_scale_;           /**< Initial loss scale factor  */
  bool keep_batchnorm_fp32_;   /**< Keep batch norm in FP32 while training */
  int num_of_not_nan_iter_th_; /**< a threshold for modifying loss scale when dynamic loss scale is enabled */
};

/// \brief TrainCfg defined for holding train configuration.
class TrainCfg {
 public:
  TrainCfg() { this->loss_name_ = "_loss_fn"; }
  TrainCfg(const TrainCfg &rhs) {
    this->loss_name_ = rhs.loss_name_;
    this->mix_precision_cfg_ = rhs.mix_precision_cfg_;
  }
  TrainCfg &operator=(const TrainCfg &rhs) {
    this->loss_name_ = rhs.loss_name_;
    this->mix_precision_cfg_ = rhs.mix_precision_cfg_;
    return *this;
  }
  std::string loss_name_;             /**< Set part of the name that identify a loss kernel */
  MixPrecisionCfg mix_precision_cfg_; /**< Mix precision configuration */
};

typedef enum {
  FT_FLATBUFFER,  // Flatbuffer format
  FT_MIBDIR       // MINDIR format
} FormatType;

typedef enum {
  QT_DEFAULT,  // the quantization of the original model will apply
  QT_NONE,     // apply no quantization
  QT_WEIGHT    // apply weight quantization
} QuantType;

typedef enum {
  MT_TRAIN,     // Both Train and Inference part of the compiled model are serialized
  MT_INFERENCE  // Only the Inference part of the compiled model is serialized
} ModelType;

}  // namespace lite
}  // namespace mindspore
#endif  // MINDSPORE_LITE_INCLUDE_TRAIN_TRAIN_CFG_H_