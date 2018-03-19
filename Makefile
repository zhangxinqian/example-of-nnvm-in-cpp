TVM_ROOT=$(shell cd ../../nnvm/tvm; pwd)
NNVM_PATH=$(shell cd ../../nnvm; pwd)
DMLC_CORE=${TVM_ROOT}/dmlc-core

PKG_CFLAGS = -std=c++11 -g -O0 -fPIC\
	-I${TVM_ROOT}/include\
	-I${DMLC_CORE}/include\
	-I${TVM_ROOT}/dlpack/include\

PKG_LDFLAGS = -L${TVM_ROOT}/lib -ldl -lpthread

.PHONY: clean all

all: resnet18_v1_pack resnet18_v1_dynamic

libtvm_runtime_pack.o: tvm_runtime_pack.cc
	@mkdir -p $(@D)
	$(CXX) -c $(PKG_CFLAGS) -o $@  $^

resnet18_v1_pack: cpp_deploy.cc libtvm_runtime_pack.o
	@mkdir -p $(@D)
	$(CXX) $(PKG_CFLAGS) -o $@  $^ $(PKG_LDFLAGS)

resnet18_v1_dynamic: cpp_deploy.cc
	@mkdir -p $(@D)
	$(CXX) $(PKG_CFLAGS) -o $@  $^ $(PKG_LDFLAGS) -ltvm_runtime
