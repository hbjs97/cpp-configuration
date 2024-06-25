#include "../vision/VisionConfig.h"

int main()
{
    try
    {
        VisionConfig visionConfig;
        visionConfig.print();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
