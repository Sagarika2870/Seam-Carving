# Seam-Carving

Seam carving is an image resizing technique that resizes the image pixel by pixel. A seam is a path of pixels from top to bottom or left to right of a picture. Unlike standard resizing techniques such as cropping and scaling, seam carving preserves the most intersting parts of the image. 

For this project I created a program that resizes an arbritary sized image using the seam carving technique. I computed the dual-gradient energy of each pixel which is the measurement of the perceptual importance of a pixel. The energy is high for pixels in the image where there is a rapid color gradient such as the boundary between the sea and sky and these are the pixel that are not removed.

The minimal cost seam represents seams with lower energy and thus less important in the image. After finding the minimal cost seam, the path of the seam must be recovered and then removed from the image. The process is repeated until the image is resized as desired.  


