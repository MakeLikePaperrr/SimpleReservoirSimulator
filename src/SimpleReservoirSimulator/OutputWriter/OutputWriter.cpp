#include "OutputWriter.h"
#include <windows.h>
#include <fstream>

void OutputWriter::WriteSolutionToFile(std::vector<double> solution)
{
    // Generate Guid and open unqiue file for writing
    std::ofstream outputFile("Solution" + GenerateUniqueGuid() + ".txt");

    if (outputFile.is_open()) 
    {
        for (double singeValue : solution) 
        {
            outputFile << singeValue << std::endl;
        }

        // Close the file when done
        outputFile.close();
        std::cout << "Solution written to file successfully." << std::endl;
    }
    else 
    {
        std::cerr << "Error opening file." << std::endl;
    }
}

std::string OutputWriter::GenerateUniqueGuid()
{
    GUID guid;
    CoCreateGuid(&guid);

    wchar_t guidString[40];
    StringFromGUID2(guid, guidString, 40);

    std::wstring wideString(guidString);
    return std::string(wideString.begin(), wideString.end());
}
