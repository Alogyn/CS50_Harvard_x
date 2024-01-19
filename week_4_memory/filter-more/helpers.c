#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // declare variable for average value
    double avrg;

    // cycle rows
    for (int i = 0; i < height; i++)
    {
        // cycle columns
        for (int j = 0; j < width; j++)
        {
            // find average value
            avrg = ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0000);

            // round average value
            avrg = round(avrg);

            // assign average value to all colors aka change pixels to grayscale
            image[i][j].rgbtBlue = avrg;
            image[i][j].rgbtGreen = avrg;
            image[i][j].rgbtRed = avrg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // create temporary storage variable
    RGBTRIPLE tmp[1][1];
    int last = width;
    int first = 0;

    // cycle rows
    for (int i = 0; i < height; i++)
    {
        // counters for swaps, reset after each row
        last = width - 1;
        first = 0;

        // swap pixels
        for (int j = 0; j < width / 2; j++)
        {
            tmp[0][0] = image[i][first];
            image[i][first] = image[i][last];
            image[i][last] = tmp[0][0];

            last--;
            first++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_blur[height][width];
    double avgRed, avgGreen, avgBlue;
    float counter;

    // cycle rows
    for (int i = 0; i < height; i++)
    {
        // cycle columns
        for (int j = 0; j < width; j++)
        {
            counter = 0;
            avgRed = 0;
            avgGreen = 0;
            avgBlue = 0;

            // cycle rows within 9 cell square
            for (int s = -1; s < 2; s++)
            {
                // cycle columns within 9 cell square
                for (int n = -1; n < 2; n++)
                {
                    // work only with cells that exist
                    int d = i + s;
                    int k = j + n;

                    if (d < height && k < width && d >= 0 && k >= 0)
                    {

                        avgRed = avgRed + image[d][k].rgbtRed;
                        avgGreen = avgGreen + image[d][k].rgbtGreen;
                        avgBlue = avgBlue + image[d][k].rgbtBlue;

                        // count existing cells within 9 cell square
                        counter++;
                    }
                }
            }

            // Find average value and round double to nearest integer
            avgRed = round(avgRed / counter);
            avgGreen = round(avgGreen / counter);
            avgBlue = round(avgBlue / counter);

            // Update blured image array with average values
            image_blur[i][j].rgbtRed = avgRed;
            image_blur[i][j].rgbtGreen = avgGreen;
            image_blur[i][j].rgbtBlue = avgBlue;
        }
    }

    // overwrite the variable image with blured image

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_blur[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // declare variable to store edge data
    // solution with help from https://medium.com/swlh/cs50-pset-4-filter-8cbf734b0dbc

    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    // declare two "kernels" for edge detection
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int Gy[3][3] = {{
                        -1,
                        -2,
                        -1,
                    },
                    {
                        0,
                        0,
                        0,
                    },
                    {1, 2, 1}};

    // variables to store temporary values
    int Gx_red, Gx_green, Gx_blue, Gy_red, Gy_green, Gy_blue;

    // cycle row
    for (int i = 0; i < height; i++)
    {
        // cycle columns
        for (int j = 0; j < width; j++)
        {

            Gx_red = Gx_blue = Gx_green = Gy_red = Gy_green = Gy_blue = 0;
            // cycle nine cells near cell of intrest
            // cycle row in 9 cells
            for (int s = 0; s < 3; s++)
            {
                // cycle columns in 9 cells
                for (int n = 0; n < 3; n++)
                {
                    // detect if outside image
                    int d = i + s - 1;
                    int k = j + n - 1;

                    if (d < height && k < width && d >= 0 && k >= 0)
                    {
                        // edge in x direction
                        Gx_red += tmp[d][k].rgbtRed * Gx[s][n];
                        Gx_green += tmp[d][k].rgbtGreen * Gx[s][n];
                        Gx_blue += tmp[d][k].rgbtBlue * Gx[s][n];

                        // edge in y direction
                        Gy_red += tmp[d][k].rgbtRed * Gy[s][n];
                        Gy_green += tmp[d][k].rgbtGreen * Gy[s][n];
                        Gy_blue += tmp[d][k].rgbtBlue * Gy[s][n];
                    }
                    // no-action if outside image, edges are 0, any number multiplied by 0 is 0, therfore no action
                }
            }
            // apply Sobel filter
            int red = round(sqrt(pow(Gx_red, 2) + pow(Gy_red, 2)));
            int green = round(sqrt(pow(Gx_green, 2) + pow(Gy_green, 2)));
            int blue = round(sqrt(pow(Gx_blue, 2) + pow(Gy_blue, 2)));

            if (red > 255)
                red = 255;

            if (green > 255)
                green = 255;

            if (blue > 255)
                blue = 255;

            // overwrite the variable image with edge image
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
