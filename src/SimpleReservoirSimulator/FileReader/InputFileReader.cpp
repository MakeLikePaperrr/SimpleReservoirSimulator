#include "InputFileReader.h"

InputFileReader::InputFileReader(std::string fileName) :
	FileName(fileName), ReadFileSuccessfull(false)
{
}

void InputFileReader::ReadInputFile()
{
    std::ifstream file(FileName);
    if (!file.is_open()) 
    {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    // Read the file line by line and extract keywords with values starting with #
    std::string line;
    while (std::getline(file, line)) 
    {
        // Check if the line starts with #
        if (!line.empty() && line[0] == '#') 
        {
            // Extract the keyword and its value (assuming they are separated by a space)
            std::size_t spacePos = line.find(' ');
            if (spacePos != std::string::npos) 
            {
                std::string keyword = line.substr(1, spacePos - 1); // Remove #
                std::string value = line.substr(spacePos + 1);
                KeywordValueMap[keyword] = value;
            }
        }
    }
    file.close();
    ReadFileSuccessfull = true;

    std::cout << "Keywords with values starting with #:" << std::endl;
    for (const auto& pair : KeywordValueMap) 
    {
        std::cout << "Keyword: " << pair.first << ", Value: " << pair.second << std::endl;
    }
}
