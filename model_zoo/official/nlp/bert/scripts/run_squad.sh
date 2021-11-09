#!/bin/bash

# export CUDA_VISIBLE_DEVICES=0

mkdir -p ms_log
CUR_DIR=`pwd`
export GLOG_log_dir=${CUR_DIR}/ms_log

DATA_DIR="${HOME}/data"
REPO_DIR="${HOME}/Elasticity/Repo/kungfu-mindspore"

. ${REPO_DIR}/ld_library_path.sh
export LD_LIBRARY_PATH=$(ld_library_path ${REPO_DIR}/mindspore)
export KUNGFU_NO_AUTO_INIT=1

python run_squad.py  \
    --device_target="GPU" \
    --do_train="true" \
    --do_eval="false" \
    --device_id=0 \
    --epoch_num=1 \
    --num_class=2 \
    --train_data_shuffle="true" \
    --eval_data_shuffle="false" \
    --train_batch_size=32 \
    --eval_batch_size=1 \
    --vocab_file_path="${DATA_DIR}/bert/bert_uncased_L-12_H-768_A-12/vocab.txt" \
    --save_finetune_checkpoint_path="${CUR_DIR}/checkpoint" \
    --load_pretrain_checkpoint_path="${DATA_DIR}/bert/bert_base_squad.ckpt" \
    --train_data_file_path="${DATA_DIR}/squad1/train.tf_record" \
    --eval_json_path="${DATA_DIR}/squad1/dev-v1.1.json" \
    --schema_file_path="${DATA_DIR}/squad1/squad_schema.json" > squad.log 2>&1
