#include "../include/levelManager.h"
#include <fstream>

levelManager::levelManager(int dunegonDepth, generator::BSP bspTree)
{
    bsp = bspTree;
}

void levelManager::generatePreview(std::string outputPath, int scale)
{
    std::cout << "generating preview..." << std::endl;

    int width = bsp.root.width * scale;
    int height = bsp.root.height * scale;

    std::ofstream file(outputPath);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        exit(1);
    }

    // Write the SVG header
    file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << std::endl;
    file << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" "
         << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << std::endl;
    file << "<svg width=\"" << width << "\" height=\"" << height << "\" version=\"1.1\" "
         << "xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
    file << "  <rect width=\"" << bsp.root.width * scale << "\" height=\"" << bsp.root.height  * scale<< "\" fill=\"white\" />" << std::endl;


    for (int i = 0; i < bsp.rooms.size(); i++) 
    {
        int x = bsp.rooms[i]->posX * scale;
        int y = bsp.rooms[i]->posY  * scale;

        int width = bsp.rooms[i]->width  * scale;
        int height = bsp.rooms[i]->height  * scale;

        file << "  <rect  x=\"" << bsp.rooms[i]->posX * scale << "\" y=\"" << bsp.rooms[i]->posY * scale << "\" width=\"" << bsp.rooms[i]->width  * scale << "\" height=\"" << bsp.rooms[i]->height  * scale<< "\" fill=\"gray\" />" << std::endl;
        
        file << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height
         << "\" fill=\"none\" stroke=\"black\" stroke-width=\""<< scale <<"\" />" << std::endl;
        

    }

    for (int i = 0; i < bsp.rooms.size(); i++) 
    {
        int x = bsp.rooms[i]->posX  * scale;
        int y = bsp.rooms[i]->posY  * scale;

        int width = bsp.rooms[i]->width  * scale;
        int height = bsp.rooms[i]->height * scale;

        file << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height
         << "\" fill=\"none\" stroke=\"black\" stroke-width=\""<< scale <<"\" />" << std::endl;
    }

    for (int i = 0; i < bsp.corridors.size(); i++) 
    {
        int x1 = bsp.corridors[i]->startX * scale;
        int y1 = bsp.corridors[i]->startY * scale;

        int x2 = bsp.corridors[i]->endX * scale;
        int y2 = bsp.corridors[i]->endY * scale;

        file << "  <line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2
         << "\" style=\"stroke:rgb(255,0,0);stroke-width:"<< scale <<"\" />" << std::endl;

    }

    // Write the SVG footer
    file << "</svg>" << std::endl;
}