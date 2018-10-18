#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char *argv[])
{

    // Return if incorrect arguments are provided
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize <resizevalue> <origionalimage> <resizedimage>\n");
        return 1;
    }

    char *factor = argv[1], *in = argv[2], *out = argv[3];
    int n = atoi(factor);

    FILE *infile = fopen(in, "r");
    if (!infile)
    {
        fprintf(stderr, "Could not open %s.\n", in);
        return 2;
    }

    FILE *outfile = fopen(out, "w");
    if (!outfile)
    {
        fclose(infile);
        fprintf(stderr, "Could not create %s.\n", out);
        return 3;
    }

    BITMAPFILEHEADER bf, bfFormated;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, infile);

    BITMAPINFOHEADER bi, biFormated;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, infile);

    // Check if the bitmap image type is correct
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outfile);
        fclose(infile);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    bfFormated = bf;
    biFormated = bi;

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4, magicConstant = 54; // 54 is the size of the other metadata

    // Scale the new bitmap image
    biFormated.biWidth = bi.biWidth * n;
    biFormated.biHeight = bi.biHeight * n;

 	int formatedPadding = (4 - (biFormated.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    biFormated.biSizeImage = abs(biFormated.biHeight) * (biFormated.biWidth * sizeof(RGBTRIPLE) + formatedPadding);

    // Remove the old size, and replace it with the new size
    bfFormated.bfSize = bf.bfSize - bi.biSizeImage + biFormated.biSizeImage;

    fwrite(&bfFormated, sizeof(BITMAPFILEHEADER), 1, outfile);
    fwrite(&biFormated, sizeof(BITMAPINFOHEADER), 1, outfile);

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
    	for (int foo = 0; foo < n; foo++)
    	{
    		// Start at the beginning
    		fseek(infile, magicConstant + (bi.biWidth * 3 + padding) * i, SEEK_SET);
	        for (int j = 0; j < (bi.biWidth); j++)
	        {
	            RGBTRIPLE triple;
	            fread(&triple, sizeof(RGBTRIPLE), 1, infile);
	            // Write it as many times as the scake requires
	            for (int q = 0; q < n; q++)
	            {
	                fwrite(&triple, sizeof(RGBTRIPLE), 1, outfile);
	            }
	        }
	        for (int k = 0; k < formatedPadding; k++)
	        {
	            fputc(0x00, outfile);
	        }
	    }
    }


    fclose(infile);
    fclose(outfile);
    return 0;
}