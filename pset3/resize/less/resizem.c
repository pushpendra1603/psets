// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // remember filenamessw
    float size_mul = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // ensure proper usage
    if (size_mul > 100)
	printf("size_mul cannot be more than 100 (%f)", size_mul);
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize size_mul infile outfile\n");
        return 1;
    }


    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //Making Changes to outfile
   
    int inp_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int old_width = bi.biWidth;
    int old_height = bi.biHeight;
    int out = bi.biHeight * size_mul;
    bi.biWidth *= size_mul;
    bi.biHeight *= size_mul;
    int w_fact = old_width/bi.biWidth;
    int h_fact = old_height/bi.biHeight;
    int out_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_size = (sizeof(bf) + sizeof(bi)) + ((bi.biWidth))*sizeof(RGBTRIPLE)*abs(bi.biHeight);
    printf("%d, %d, %d\n", new_size, sizeof(bf), sizeof(bi)); 
    printf("%d, %d, %f, %d, factor(w, h) = (%d, %d)", old_height, bi.biHeight, size_mul, out, w_fact, h_fact);

    bf.bfSize = new_size;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    // printf("%d", out_padding);
    RGBTRIPLE pixel_array[bi.biWidth];// * sizeof(RGBTRIPLE)); 
    // iterate over infile's scanlines
    
    // for (int i = 0; i < abs(bi.biHeight); i++)
    // {
    //     // iterate over pixels in scanline
    //     for (int j = 0; j < bi.biWidth; j++)
    //     {
    //         // temporary storage
    //         RGBTRIPLE triple;

    //         // read RGB triple from infile
    //         fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
    //         pixel_array[j] = triple;

    //         // for(int k=1;k<w_fact;k++)
    //         // {
    //             fread(&triple, sizeof(RGBTRIPLE), (w_fact-1), inptr);
    //         // }

    //         if (j == (bi.biWidth-1))
    //             fread(&triple, sizeof(RGBTRIPLE), (h_fact*(old_width+inp_padding)), inptr);
    //     }

    //    // skip over padding, if any
    //    fseek(inptr, inp_padding, SEEK_CUR);
    //    fwrite(pixel_array, sizeof(pixel_array),1, outptr);
    //    for (int t = 0; t < out_padding; t++)
    //     {
    //         fputc(0x00, outptr);
    //     }
    // }


    for (int i = 0; i < abs(old_height); i++)
    {
        int curr_indx = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < old_width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            if(i%h_fact == 0 && j%w_fact == 0)
            {
                pixel_array[curr_indx] = triple;
                curr_indx++;
            }
        }

       // skip over padding, if any
       fseek(inptr, inp_padding, SEEK_CUR);
       if(i%h_fact == 0) {fwrite(pixel_array, sizeof(pixel_array),1, outptr);
       for (int t = 0; t < out_padding; t++)
        {
            fputc(0x00, outptr);
        }}
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
