from PIL import Image

import numpy as np

from matplotlib import pyplot as plt
from skimage.util import random_noise


def make_noise(image, mode):
    array = np.array(image)
    noised_array = random_noise(array, mode=mode, seed=None, clip=None)
    return Image.fromarray((noised_array * 255).astype(np.uint8))


pic_dir = 'pics/'
pic_name = 'bear.jpg'

image = Image.open(pic_dir + pic_name)

modes = ['gaussian', 's&p', 'localvar', 'poisson', 'salt', 'pepper', 'speckle']

images = [make_noise(image, m) for m in modes]

if __name__ == '__main__':
    for i, img in enumerate(images):
        plt.subplot(241 + i), plt.imshow(img), plt.title(modes[i])
    # plt.show()
    plt.savefig(pic_dir + 'noised_' + pic_name)
