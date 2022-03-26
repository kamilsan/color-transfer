# Image color transfer

Implementation of color transfer algorithm based on publication "Color Transfer between Images" by Erik Reinhard, Michael Ashikhmin, Bruce Gooch
and Peter Shirley.

## Build

```console
$ cmake .
$ make -j8
```

## Usage

```console
$ ./color-transfer <image-to-transform> <image-style-source> <destination-image>
```

Where:

  * `<image-to-transform>` - path to source image to be colorized
  * `<image-style-source>` - path to image whose style will be transfered onto input image
  * `<destination-image>` - path where output image can be saved

Example:

```console
$ ./color-transfer ./imgs/source_image.jpg ./imgs/source_style.jpg ./styled_image.png
```