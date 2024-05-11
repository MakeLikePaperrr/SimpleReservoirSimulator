#include "PermeabilityFileReader.h"

PermeabilityFileReader::PermeabilityFileReader(std::string fileName) :
	FileName(fileName), ReadFileSuccessfull(false)
{
}

void PermeabilityFileReader::ReadDoubles()
{
    std::ifstream file(FileName);
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file: " << FileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        double value;
        if (iss >> value)
        {
            Permeability.push_back(value);
        }
        else
        {
            std::cerr << "Failed to parse line as double: " << line << std::endl;
        }
    }
    file.close();
    ReadFileSuccessfull = true;
}
