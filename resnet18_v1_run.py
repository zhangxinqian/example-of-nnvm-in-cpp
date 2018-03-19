import tvm
import numpy as np
from PIL import Image

# tvm module for compiled functions.
loaded_lib = tvm.module.load("./model/model_lib.so")
# json graph
loaded_json = open("./model/model_graph.json").read()
# parameters in binary
loaded_params = bytearray(open("./model/model_graph.params", "rb").read())
# data of png
image = Image.open('./data/cat.png').resize((224, 224))

def transform_image(image):
    image = np.array(image) - np.array([123., 117., 104.])
    image /= np.array([58.395, 57.12, 57.375])
    image = image.transpose((2, 0, 1))
    image = image[np.newaxis, :]
    return image

x = transform_image(image)

fcreate = tvm.get_global_func("tvm.graph_runtime.create")
ctx = tvm.cpu(0)
gmodule = fcreate(loaded_json, loaded_lib, ctx.device_type, ctx.device_id)
set_input, get_output, run = gmodule["set_input"], gmodule["get_output"], gmodule["run"]
set_input("data", tvm.nd.array(x.astype('float32')))
gmodule["load_params"](loaded_params)
run()
out = tvm.nd.empty((1000,), "float32")
get_output(0, out)
top1 = np.argmax(out.asnumpy())
print('TVM prediction top-1:', top1)