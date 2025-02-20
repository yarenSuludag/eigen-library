# Binary Image Processing and Dilation using OpenCV and Eigen

- **Project Name:** BinaryEdge-Dilate  
- **Description:**  
  - A C++ application that processes a grayscale PGM image by converting it into a binary matrix using a threshold, detecting transition edges between black and white regions, and applying a dilation operation to enhance these edges. The final dilated image is then saved as a new PGM file.
- **Tools and Libraries:**  
  - **OpenCV:** For image reading, processing, dilation, and writing the output image.  
  - **Eigen:** For matrix operations and handling the binary conversion of the image.

## Table of Contents
- Overview
- Features
- Dependencies
- Installation
- Usage
- Code Structure
- How It Works
- License

## Overview
- **Purpose:**  
  - To convert a grayscale PGM image into a binary matrix by thresholding.
  - To detect transition regions (edges) where the pixel value changes between black and white.
  - To apply a dilation operation to these detected edges, thereby accentuating them.
  - To save the processed (dilated) image into a new PGM file.
- **Motivation:**  
  - Learn the integration of image processing (OpenCV) with matrix operations (Eigen) in C++.
  - Understand basic operations like thresholding, edge detection, and morphological transformations.

## Features
- **Image Thresholding:**  
  - Reads a PGM image and converts it into a binary matrix using a fixed threshold (e.g., 128).
- **Transition Detection:**  
  - Scans through the binary matrix to identify pixels where there is a transition between black (0) and white (255) in the 8-neighborhood.
- **Edge Block Extraction:**  
  - Stores the detected transition pixels in a separate matrix (transitionBlock).
- **Dilation Operation:**  
  - Applies a dilation (expansion) using a rectangular structuring element to enhance edge regions.
- **Output Generation:**  
  - Saves the final dilated image as a new PGM file ("yeni_dunya_sisirilmis.pgm") and outputs detailed pixel information to the console.

## Dependencies
- **OpenCV:**  
  - For image I/O and processing functions such as `imread()`, `imwrite()`, `dilate()`, and `getStructuringElement()`.
- **Eigen:**  
  - For efficient handling of matrix operations and converting image data into a binary matrix.
- **C++ Compiler:**  
  - Compatible with C++11 or higher.
- **Build Tools:**  
  - CMake or a direct compilation using a command-line compiler like g++.

## Installation
- **Install OpenCV:**  
  - Follow the installation instructions on the [OpenCV official website](https://opencv.org/).
- **Install Eigen:**  
  - Download and install Eigen from the [Eigen official website](http://eigen.tuxfamily.org/).
- **Compiler Setup:**  
  - Ensure you have a C++ compiler (e.g., g++) that supports C++11 or later.

## Usage
- **Compilation:**  
  - Using g++ (adjust include paths as necessary):
    ```bash
    g++ -std=c++11 -I/path/to/eigen -I/path/to/opencv/include binary_edge_dilate.cpp -o binary_edge_dilate `pkg-config --cflags --libs opencv4`
    ```
  - Replace `/path/to/eigen` and `/path/to/opencv/include` with your actual installation paths.
- **Execution:**  
  - Place the input image (`yeni_dunya.pgm`) in the same directory as the executable.
  - Run the executable:
    ```bash
    ./binary_edge_dilate
    ```
- **Output:**  
  - The program will output the binary matrix and transition block details to the console.
  - A new PGM image (`yeni_dunya_sisirilmis.pgm`) will be created, containing the dilated image.

## Code Structure
- **Main Function:**  
  - Reads a grayscale PGM image.
  - Converts the image to an Eigen matrix and applies a threshold to create a binary matrix.
  - Iterates through the matrix to detect transition pixels and stores them in a separate matrix.
  - Applies a dilation operation using OpenCV’s morphological functions.
  - Converts the dilated matrix back to an OpenCV Mat and writes it to a new PGM file.
- **Key Libraries:**  
  - `<opencv2/opencv.hpp>` for image processing.  
  - `<Eigen/Dense>` for matrix manipulations.  
  - `<iostream>` for console output.

## How It Works
- **Image Reading and Binary Conversion:**  
  - The image "yeni_dunya.pgm" is loaded in grayscale mode.
  - The pixel values are iterated over; pixels above a set threshold (e.g., 128) are set to 255 (white), and others to 0 (black), resulting in a binary matrix stored in an Eigen::MatrixXd.
- **Transition Detection:**  
  - The program compares each pixel with its eight neighbors.
  - If a pixel's value differs from any of its neighbors, it is considered a transition pixel and is logged.
- **Transition Block Extraction:**  
  - Detected transition pixels are stored in a new Eigen matrix called `transitionBlock`.
  - The program outputs the position and value of these transition pixels.
- **Dilation:**  
  - A dilation operation is applied to `transitionBlock` using OpenCV’s `dilate()` function with a rectangular structuring element.
  - The result is a dilated image that emphasizes the detected edges.
- **Output Saving:**  
  - The dilated image is converted from an Eigen matrix to an OpenCV Mat.
  - The final image is saved as "yeni_dunya_sisirilmis.pgm".

## License
- This project is licensed under the MIT License. For more details, refer to the LICENSE file.
