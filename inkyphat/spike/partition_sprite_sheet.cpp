#include <iostream>
#include <string>

#include <png++/png.hpp>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cout << "Single filename argument expected with width and height of partition" << std::endl;
        return -1;
    }

    std::string fileName = std::string(argv[1]);
    png::image<png::rgb_pixel> sheet(fileName);
    int height = sheet.get_height();
    int width = sheet.get_width();

    std::cout << "W:" << width << std::endl
              << "H:" << height << std::endl;

    int partitionWidth = atoi(argv[2]);
    int partitionHeight = atoi(argv[3]);

    if (width % partitionWidth != 0)
    {
        std::cout << "Width does not divide exactly by the desired partition width" << std::endl;
        return -2;
    }
    if (height % partitionHeight != 0)
    {
        std::cout << "Height does not divide exactly by the desired partition height" << std::endl;
        return -2;
    }

    int fileCount = 0;
    for (int xStart = 0; xStart < width; xStart += partitionWidth)
    {
        for (int yStart = 0; yStart < height; yStart += partitionHeight)
        {
            png::image<png::rgb_pixel> newImage(partitionWidth, partitionHeight);
            for (int x = xStart; x < xStart + partitionWidth; ++x)
            {
                for (int y = yStart; y < yStart + partitionHeight; ++y)
                {
                    newImage[y - yStart][x - xStart] = sheet[y][x];
                }
            }
            newImage.write("Sprite" + std::to_string(fileCount++) + ".png");
        }
    }
    return 0;
}