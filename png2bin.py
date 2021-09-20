from PIL import Image

def write_image(image, filename):
    height = image.height
    width = image.width

    f = open(filename, "wb")

    f.write(height.to_bytes(2, byteorder='big'))
    f.write(width.to_bytes(2, byteorder='big'))
    img_raster = []
    for i in range(height):
        for j in range(width):
            img_raster.extend(image.getpixel((j, i))[:3])

    f.write(bytearray(img_raster))
    f.close()

def read_2bytes(f):
    bytes = f.read(2) # [int(f.read(1)), int(f.read(1))]
    return int.from_bytes(bytes, byteorder = 'big')


def read_image(filename):
    f = open(filename, "rb")
    height = read_2bytes(f)
    width = read_2bytes(f)
    image = Image.new("RGB", (width, height))
    bytes = f.read()
    for i in range(height):
        for j in range(width):
            image.putpixel((j, i), (bytes[3*(i*width + j)+0],
                                    bytes[3*(i*width + j)+1],
                                    bytes[3*(i*width + j)+2]))

    return image

#Write a png image to bin
# image = Image.open("6x5.png")
# write_image(image, "6x5.bin")
# image = Image.open("3x4.png")
# write_image(image, "3x4.bin")

#Read image from a bin file, save it to png
# im2 = read_image("img0.bin")
# im3 = read_image("img1.bin")
# im6 = read_image("img2.bin")
# im4 = read_image("img3.bin")
# im5 = read_image("img4.bin")
# im8 =
# im49 = read_image("img149.bin")
# im499 = read_image("tester1.bin")
# img = read_image("tester0.bin")
#
# im2.save("img0.png")
# im3.save("img1.png")
# im6.save("img2.png")
# im4.save("img3.png")
# im5.save("img4.png")
# im499.save("tester1.png")
# im49.save("img149.png")
# img.save("tester0.png")

# Write multiple images from bin to png
for i in range(100):
    image = read_image("img%d.bin" % i)
    image.save("img%d.png" % i)
