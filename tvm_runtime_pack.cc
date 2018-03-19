/*!
 * \brief This is an all in one TVM runtime file.
 *
 *   You only have to use this file to compile libtvm_runtime to
 *   include in your project.
 *
 *  - Copy this file into your project which depends on tvm runtime.
 *  - Compile with -std=c++11
 *  - Add the following include path
 *     - /path/to/tvm/include/
 *     - /path/to/tvm/dmlc-core/include/
 *     - /path/to/tvm/dlpack/include/
 *   - Add -lpthread -ldl to the linked library.
 *   - You are good to go.
 *   - See the Makefile in the same folder for example.
 *
 *  The include files here are presented with relative path
 *  You need to remember to change it to point to the right file.
 *
 */
#include "../../nnvm/tvm/src/runtime/c_runtime_api.cc"
#include "../../nnvm/tvm/src/runtime/cpu_device_api.cc"
#include "../../nnvm/tvm/src/runtime/workspace_pool.cc"
#include "../../nnvm/tvm/src/runtime/module_util.cc"
#include "../../nnvm/tvm/src/runtime/module.cc"
#include "../../nnvm/tvm/src/runtime/registry.cc"
#include "../../nnvm/tvm/src/runtime/file_util.cc"
#include "../../nnvm/tvm/src/runtime/thread_pool.cc"

// NOTE: all the files after this are optional modules
// that you can include remove, depending on how much feature you use.

// Likely we only need to enable one of the following
// If you use Module::Load, use dso_module
// For system packed library, use system_lib_module
#include "../../nnvm/tvm/src/runtime/dso_module.cc"
#include "../../nnvm/tvm/src/runtime/system_lib_module.cc"

// Graph runtime
#include "../../nnvm/tvm/src/runtime/graph/graph_runtime.cc"

// Uncomment the following lines to enable RPC
// #include "../nnvm/tvm/src/runtime/rpc/rpc_session.cc"
// #include "../nnvm/tvm/src/runtime/rpc/rpc_event_impl.cc"
// #include "../nnvm/tvm/src/runtime/rpc/rpc_server_env.cc"

// These macros enables the device API when uncommented.
#define TVM_CUDA_RUNTIME 1
#define TVM_METAL_RUNTIME 1
#define TVM_OPENCL_RUNTIME 1

// Uncomment the following lines to enable Metal
// #include "../nnvm/tvm/src/runtime/metal/metal_device_api.mm"
// #include "../nnvm/tvm/src/runtime/metal/metal_module.mm"

// Uncomment the following lines to enable CUDA
// #include "../nnvm/tvm/src/runtime/cuda/cuda_device_api.cc"
// #include "../nnvm/tvm/src/runtime/cuda/cuda_runtime.cc"

// Uncomment the following lines to enable OpenCL
// #include "../nnvm/tvm/src/runtime/opencl/opencl_device_api.cc"
// #include "../nnvm/tvm/src/runtime/opencl/opencl_module.cc"
