#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Structure to hold a run-length encoded pixel
#include "RLEPixel.h"

// Function to compress the image using run-length encoding

void compressImageP6(FILE *input, FILE *output) {
  int width, height;
  fscanf(input, "P6\n%d %d\n255\n", &width, &height);

  // Write the format type, width, and height to the output file
  fprintf(output, "P6\n%d %d\n255\n", width, height);

  // Allocate memory for the image pixels
  unsigned char *pixels = malloc(width * height * 3);

  // Read the image pixels
  fread(pixels, 1, width * height * 3, input);

  // Perform run-length encoding
  int i;
  RLEPixel currentPixel;
  currentPixel.value = pixels[0];
  currentPixel.count = 1;

  for (i = 1; i < width * height * 3; i++) {
    if (currentPixel.value == pixels[i] && currentPixel.count < 255) {
      currentPixel.count++;
    } else {
      fwrite(&currentPixel, sizeof(RLEPixel), 1, output);
      currentPixel.value = pixels[i];
      currentPixel.count = 1;
    }
  }

  // Write the last run-length encoded pixel
  fwrite(&currentPixel, sizeof(RLEPixel), 1, output);

  // Free allocated memory
  free(pixels);
}

void compressImageP5(FILE *input, FILE *output) {
  int width, height;
  fscanf(input, "P5\n%d %d\n255\n", &width, &height);

  // Write the format type, width, and height to the output file
  fprintf(output, "P5\n%d %d\n255\n", width, height);

  // Allocate memory for the image pixels
  unsigned char *pixels = malloc(width * height);

  // Read the image pixels
  fread(pixels, 1, width * height, input);

  // Perform run-length encoding
  int i;
  RLEPixel currentPixel;
  currentPixel.value = pixels[0];
  currentPixel.count = 1;

  for (i = 1; i < width * height; i++) {
    if (currentPixel.value == pixels[i] && currentPixel.count < 255) {
      currentPixel.count++;
    } else {
      fwrite(&currentPixel, sizeof(RLEPixel), 1, output);
      currentPixel.value = pixels[i];
      currentPixel.count = 1;
    }
  }

  // Write the last run-length encoded pixel
  fwrite(&currentPixel, sizeof(RLEPixel), 1, output);

  // Free allocated memory
  free(pixels);
}

void compressImageP4(FILE *input, FILE *output) {
  int width, height;
  fscanf(input, "P4\n%d %d\n", &width, &height);

  // Write the format type, width, and height to the output file
  fprintf(output, "P4\n%d %d\n", width, height);

  // Allocate memory for the image pixels
  unsigned char *pixels = malloc((width * height + 7) / 8);

  // Read the image pixels
  fread(pixels, 1, (width * height + 7) / 8, input);

  // Perform run-length encoding
  int i, j = 0;
  RLEPixel currentPixel;
  currentPixel.value = (pixels[0] >> 7) & 1;
  currentPixel.count = 1;

  for (i = 1; i < width * height; i++) {
    unsigned char pixelByte = pixels[i / 8];
    unsigned char pixelBit = (pixelByte >> (7 - (i % 8))) & 1;

    if (currentPixel.value == pixelBit && currentPixel.count < 255) {
      currentPixel.count++;
    } else {
      fwrite(&currentPixel, sizeof(RLEPixel), 1, output);
      currentPixel.value = pixelBit;
      currentPixel.count = 1;
    }
  }

  // Write the last run-length encoded pixel
  fwrite(&currentPixel, sizeof(RLEPixel), 1, output);

  // Free allocated memory
  free(pixels);
}

void compressImageP3(FILE *input, FILE *output) {
  int width, height;
  fscanf(input, "P3\n%d %d\n255\n", &width, &height);

  // Write the format type, width, and height to the output file
  fprintf(output, "P3\n%d %d\n255\n", width, height);

  // Allocate memory for the image pixels
  unsigned char *pixels = malloc(width * height * 3);

  // Read the image pixels
  int i;
  for (i = 0; i < width * height * 3; i++) {
    fscanf(input, "%hhu", &pixels[i]);
  }

  // Perform run-length encoding
  RLEPixel currentPixel;
  currentPixel.value = pixels[0];
  currentPixel.count = 1;

  for (i = 1; i < width * height * 3; i++) {
    if (currentPixel.value == pixels[i] && currentPixel.count < 255) {
      currentPixel.count++;
    } else {
      fprintf(output, "%d %d ", currentPixel.count, currentPixel.value);
      currentPixel.value = pixels[i];
      currentPixel.count = 1;
    }
  }

  // Write the last run-length encoded pixel
  fprintf(output, "%d %d\n", currentPixel.count, currentPixel.value);

  // Free allocated memory
  free(pixels);
}

void compressImageP2(FILE *input, FILE *output) {
  int width, height, maxVal;
  fscanf(input, "P2\n%d %d\n%d\n", &width, &height, &maxVal);

  // Write the format type, width, height, and maxVal to the output file
  fprintf(output, "P2\n%d %d\n%d\n", width, height, maxVal);

  // Allocate memory for the image pixels
  unsigned char *pixels = malloc(width * height);

  // Read the image pixels
  int i;
  for (i = 0; i < width * height; i++) {
    fscanf(input, "%hhu", &pixels[i]);
  }

  // Perform run-length encoding
  RLEPixel currentPixel;
  currentPixel.value = pixels[0];
  currentPixel.count = 1;

  for (i = 1; i < width * height; i++) {
    if (currentPixel.value == pixels[i] && currentPixel.count < 255) {
      currentPixel.count++;
    } else {
      fprintf(output, "%d %d\n", currentPixel.count, currentPixel.value);
      currentPixel.value = pixels[i];
      currentPixel.count = 1;
    }
  }

  // Write the last run-length encoded pixel
  fprintf(output, "%d %d\n", currentPixel.count, currentPixel.value);

  // Free allocated memory
  free(pixels);
}

void compressImageP1(FILE *input, FILE *output) {
  int width, height;
  fscanf(input, "P1\n%d %d\n", &width, &height);

  // Write the format type, width, and height to the output file
  fprintf(output, "P1\n%d %d\n", width, height);

  // Allocate memory for the image pixels
  unsigned char *pixels = malloc((width * height + 7) / 8);

  // Read the image pixels
  int i;
  for (i = 0; i < width * height; i++) {
    fscanf(input, "%hhu", &pixels[i / 8]);
  }

  // Perform run-length encoding
  RLEPixel currentPixel;
  currentPixel.value = (pixels[0] >> 7) & 1;
  currentPixel.count = 1;

  for (i = 1; i < width * height; i++) {
    unsigned char pixelByte = pixels[i / 8];
    unsigned char pixelBit = (pixelByte >> (7 - (i % 8))) & 1;

    if (currentPixel.value == pixelBit && currentPixel.count < 255) {
      currentPixel.count++;
    } else {
      fprintf(output, "%d %d\n", currentPixel.count, currentPixel.value);
      currentPixel.value = pixelBit;
      currentPixel.count = 1;
    }
  }

  // Write the last run-length encoded pixel
  fprintf(output, "%d %d\n", currentPixel.count, currentPixel.value);

  // Free allocated memory
  free(pixels);
}

int main(int argc, char **argv) {
  FILE *input = fopen(argv[1], "rb");
  FILE *output = fopen(argv[2], "wb");

  if (input == NULL || output == NULL) {
    printf("Error opening files.\n");
    return 1;
  }

  // Compress the image
  if (strcmp(argv[3], "P1") == 0) {
    compressImageP1(input, output);
  }
  if (strcmp(argv[3], "P2") == 0) {
    compressImageP2(input, output);
  }
  if (strcmp(argv[3], "P3") == 0) {
    compressImageP3(input, output);
  }
  if (strcmp(argv[3], "P4") == 0) {
    compressImageP4(input, output);
  
  }
  if (strcmp(argv[3], "P5") == 0) {
    compressImageP5(input, output);
  }
  if (strcmp(argv[3], "P6") == 0) {
    compressImageP6(input, output);
  }

  // Close the files
  fclose(input);
  fclose(output);

  printf("Image compression complete.\n");

  return 0;
}