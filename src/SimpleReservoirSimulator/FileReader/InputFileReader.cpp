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

                // Only store keyword and value, if it's a valid keyword
                auto it = _validKeywords.find(keyword);
                if (it != _validKeywords.end())
                {
                    KeywordValueMap[keyword] = value;
                }
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

double InputFileReader::TryParseKeyWordToDouble(std::string keyWord)
{
    try 
    {
        return std::stod(KeywordValueMap[keyWord]);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return NULL;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
        return NULL;
    }
}

int InputFileReader::TryParseKeyWordToInt(std::string keyWord)
{
    try
    {
        return std::stoi(KeywordValueMap[keyWord]);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return NULL;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
        return NULL;
    }
}

bool InputFileReader::ParseKeyWordToBool(std::string keyWord)
{
    std::string lowerCase;
    for (char c : KeywordValueMap[keyWord]) 
    {
        lowerCase += std::tolower(c);
    }
    return lowerCase == "true" || lowerCase == "1" || lowerCase == "yes";
}
