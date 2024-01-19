#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check if the correct number of command-line arguments is provided
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <forensic image>\n", argv[0]);
        return 1;
    }

    // Open the forensic image file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open forensic image file.\n");
        return 1;
    }

    // Buffer to store 512 bytes at a time
    BYTE buffer[512];

    // Counter for the JPEG file names
    int jpeg_count = 0;

    // File pointer for the JPEG file
    FILE *jpeg = NULL;

    // Read until the end of the file
    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        // Check if it's the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If a JPEG is already open, close it
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }

            // Create a new JPEG file
            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_count++);
            jpeg = fopen(filename, "w");

            // Check if the file creation was successful
            if (jpeg == NULL)
            {
                fprintf(stderr, "Could not create JPEG file.\n");
                fclose(file);
                return 2;
            }
        }

        // Write the buffer to the JPEG file if it's open
        if (jpeg != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, jpeg);
        }
    }

    // Close any open files
    fclose(jpeg);
    fclose(file);

    return 0;
}
