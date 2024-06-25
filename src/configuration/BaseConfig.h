#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <string>
#include <sstream>
#include <yaml-cpp/yaml.h>

class BaseConfig
{
public:
    BaseConfig()
    {
        /**
         * @brief BaseConfig 을 상속하는 Config 클래스들이 다수 있어도 yaml 파일을 한번만 읽도록 함
         */
        if (properties.IsNull())
        {
            properties = loadProperties();
        }
        printProperties();
    }

    virtual void validate() const = 0;

protected:
    static const YAML::Node &getProperties()
    {
        return properties;
    }

    template <typename T>
    T loadProperty(const std::string &key) const
    {
        YAML::Node node = deepCopy(properties); // 항상 루트 노드에서 시작
        std::stringstream ss(key);
        std::string segment;

        while (std::getline(ss, segment, '.'))
        {
            if (node[segment])
            {
                node = node[segment];
            }
            else
            {
                std::cerr << "Property not found at segment: " << segment << std::endl;
                throw std::runtime_error("Property not found: " + key);
            }
        }

        return node.as<T>();
    }

    template <typename T>
    T loadOptionalProperty(const std::string &key) const
    {
        YAML::Node node = deepCopy(properties); // 항상 루트 노드에서 시작
        std::stringstream ss(key);
        std::string segment;

        while (std::getline(ss, segment, '.'))
        {
            if (node[segment])
            {
                node = node[segment];
            }
            else
            {
                return T(); // 기본값 반환 (예: 빈 문자열, 0 등)
            }
        }

        return node.as<T>();
    }

    void printProperties() const
    {
        std::cout << "===================== Loaded properties ====================" << std::endl;
        std::cout << properties << std::endl;
        std::cout << "============================================================"
                  << std::endl
                  << std::endl;
    }

private:
    static YAML::Node loadProperties()
    {
        const std::string configFilePath = "config.yaml";
        std::cout << "Attempting to load configuration from: " << configFilePath << std::endl;

        YAML::Node config;
        try
        {
            config = YAML::LoadFile(configFilePath);
            std::cout << "Configuration loaded successfully." << std::endl;
        }
        catch (const YAML::Exception &e)
        {
            std::cerr << "Failed to load configuration: " << e.what() << std::endl;
            throw; // 예외를 다시 던져서 프로그램이 중단되도록 함
        }

        return config;
    }

    static YAML::Node properties;

    /**
     * @brief deepCopy 사용하지 않으면 properties 를 얕은복사하여 컨텍스트가 유지되지 않는다.
     *
     * @param node
     * @return YAML::Node
     */
    YAML::Node deepCopy(const YAML::Node &node) const
    {
        YAML::Node copy;
        if (node.IsScalar())
        {
            copy = node.Scalar();
        }
        else if (node.IsSequence())
        {
            for (std::size_t i = 0; i < node.size(); ++i)
            {
                copy.push_back(deepCopy(node[i]));
            }
        }
        else if (node.IsMap())
        {
            for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
            {
                copy[it->first] = deepCopy(it->second);
            }
        }
        return copy;
    }
};

// Static member definition
YAML::Node BaseConfig::properties = YAML::Node();

#endif // CONFIGURATION_H
