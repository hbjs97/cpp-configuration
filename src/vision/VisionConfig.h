#ifndef VISION_CONFIG_H
#define VISION_CONFIG_H

#include "../configuration/BaseConfig.h"
#include "Position.h"

class VisionConfig : public BaseConfig
{
public:
    VisionConfig()
        : BaseConfig(),
          param1(loadProperty<std::string>("vision.param1")),
          param2(loadProperty<std::string>("vision.child.param2")),
          param3(loadProperty<int>("vision.child.param3")),
          param4(loadProperty<double>("vision.position.x"), loadProperty<double>("vision.position.y")),
          param5(loadProperty<std::vector<int>>("vision.list"))
    {
        validate();
    }

    void validate() const override
    {
        if (param1.empty())
        {
            throw std::runtime_error("param1 is empty");
        }

        if (param2.empty())
        {
            throw std::runtime_error("param2 is empty");
        }

        if (param3 < 0)
        {
            throw std::runtime_error("param3 is negative");
        }

        if (!param4.isValid())
        {
            throw std::runtime_error("param4 is invalid");
        }

        if (param5.empty())
        {
            throw std::runtime_error("param5 is empty");
        }
    }

    void print() const
    {
        std::cout << "param1: " << param1 << std::endl;
        std::cout << "param2: " << param2 << std::endl;
        std::cout << "param3: " << param3 << std::endl;
        std::cout << "param4: (" << param4.getX() << ", " << param4.getY() << ")" << std::endl;
        std::cout << "param5: ";
        for (const auto &element : param5)
        {
            std::cout << element << " ";
        }
    }

private:
    const std::string param1;
    const std::string param2;
    const int param3;
    const Position param4;
    const std::vector<int> param5;
};

#endif // VISION_CONFIG_H
