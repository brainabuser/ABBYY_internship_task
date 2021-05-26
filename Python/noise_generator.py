from PIL import Image, ImageFilter

from pdf2image import convert_from_path

png_dir = 'png/'
pdf_dir = 'pdf/'
filtered_dir = 'filtered_tiff/'
img_name = 'nature'

# Save converted image in png/ dir
convert_from_path(f'{pdf_dir}{img_name}.pdf')[0] \
    .save(f'{png_dir}{img_name}.png')

image = Image.open(f'{png_dir}{img_name}.png')

# To reduce the number of rows below
im_f = ImageFilter
filters = [im_f.CONTOUR, im_f.BLUR, im_f.EMBOSS, im_f.EDGE_ENHANCE, im_f.EDGE_ENHANCE_MORE]

filtered_images = [image.filter(f) for f in filters]

# Save filtered images to .tif doc
if __name__ == '__main__':
    filtered_images[0].save(f'{filtered_dir}{img_name}.tif', compression='tiff_deflate',
                            save_all=True, append_images=filtered_images[1:])
