#!/bin/bash
set -e

export CUDA_VISIBLE_DEVICES=3

. /home/marcel/Elasticity/Repository/kungfu-mindspore/ld_library_path.sh
export LD_LIBRARY_PATH=$(ld_library_path /home/marcel/Elasticity/Repository/kungfu-mindspore/mindspore)

python run_squad_nondeterminism.py  \
    --device_target="GPU" \
    --do_train="true" \
    --do_eval="false" \
    --device_id=0 \
    --epoch_num=1 \
    --num_class=2 \
    --train_data_shuffle="true" \
    --eval_data_shuffle="false" \
    --train_batch_size=12 \
    --eval_batch_size=1 \
    --vocab_file_path="/home/marcel/Mindspore/bert_uncased_L-12_H-768_A-12/vocab.txt" \
    --save_finetune_checkpoint_path="./checkpoint" \
    --load_pretrain_checkpoint_path="/data/bert/bert_base_squad.ckpt" \
    --train_data_file_path="/data/squad1/train.tf_record" \
    --eval_json_path="/data/squad1/dev-v1.1.json" \
    --schema_file_path="/data/squad1/squad_schema.json" > squad.log 2>&1