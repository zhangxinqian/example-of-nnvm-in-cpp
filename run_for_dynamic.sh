#!/bin/bash

export LD_LIBRARY_PATH=../../nnvm/tvm/lib:${LD_LIBRARY_PATH}
export DYLD_LIBRARY_PATH=../../nnvm/tvm/lib:${DYLD_LIBRARY_PATH}

./resnet18_v1_dynamic
