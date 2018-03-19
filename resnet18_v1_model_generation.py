import nnvm
import numpy as np
from mxnet.gluon.model_zoo.vision import get_model
from PIL import Image

block = get_model('resnet18_v1', pretrained=True)
image = Image.open('./data/cat.png').resize((224, 224))

def transform_image(image):
    image = np.array(image) - np.array([123., 117., 104.])
    image /= np.array([58.395, 57.12, 57.375])
    image = image.transpose((2, 0, 1))
    image = image[np.newaxis, :]
    return image

x = transform_image(image)
print(x.shape)

sym, params = nnvm.frontend.from_mxnet(block)
# we want a probability so add a softmax operator
sym = nnvm.sym.softmax(sym)

#target = 'cuda'
target = 'llvm'
shape_dict = {'data': x.shape}
graph, lib, params = nnvm.compiler.build(sym, target, shape_dict, params=params)

# x64, x is 8 bytes float, need to change to 4 bytes float
x.astype("float32").tofile("./data/cat.bin")
np.save("./data/cat.nparray", x.astype("float32"))
with open("./model/model_graph.json", "w") as fo:
    fo.write(graph.json())
with open("./model/model_graph.params", "wb") as fo:
    fo.write(nnvm.compiler.save_param_dict(params))
lib.export_library("./model/model_lib.so")
