// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: fileComponents.hpp - Version 1.0.0
// Author: cdrisko
// Date: 01/31/2020-15:39:15
// Description: Classes representing the contents of a file and the file's name

#ifndef UTILITIES_API_FILECOMPONENTS_HPP
#define UTILITIES_API_FILECOMPONENTS_HPP

#include <fstream>
#include <string>
#include <string_view>
#include <vector>

#include "filesystem.hpp"
#include "../Errors/errorUtilities.hpp"

namespace Utilities_API::Files
{
    class FileName
    {
    private:
        std::string fullFileName;
        std::string baseFileName;
        std::string relativePathToFile {""};
        std::string fileExtension {""};

        void splitFileName()
        {
            size_t pathLocation { fullFileName.find_last_of("/") };
            size_t extensionLocation { fullFileName.find_last_of(".") };

            if (pathLocation == std::string::npos)
            {
                baseFileName = fullFileName;

                if (extensionLocation != std::string::npos)
                    fileExtension = fullFileName.substr(extensionLocation + 1);
            }
            else
            {
                relativePathToFile = fullFileName.substr(0, pathLocation);
                baseFileName = fullFileName.substr(pathLocation + 1);
                fileExtension = fullFileName.substr(extensionLocation + 1);
            }
        }

    public:
        explicit FileName(std::string_view FullFileName) : fullFileName{FullFileName}
        {
            splitFileName();
        }

        std::string getFullFileName() const { return fullFileName; }
        std::string getBaseFileName() const { return baseFileName; }
        std::string getFileExtension() const { return fileExtension; }
        std::string getRelativePathToFile() const { return relativePathToFile; }
    };


    class FileContents
    {
    private:
        FileName fileName;
        std::vector<std::string> contentInFile;
        Errors::ErrorMessagePtr errorMessage;

        void setContentInFile()
        {
            std::string baseFileName { fileName.getBaseFileName() };
            std::string relativePath { fileName.getRelativePathToFile() };

            std::ifstream inputFile { ((relativePath != "") ? relativePath + "/" : relativePath) + baseFileName };

            std::string line;

            if (inputFile)
            {
                while ( getline(inputFile, line) )
                    if ( !line.empty() )
                        contentInFile.push_back(line);
            }
            else
            {
                errorMessage = std::make_shared<Errors::FatalErrorMessage>("Utilities-API", 1);

                errorMessage->printErrorMessage("Unable to open file: " + baseFileName + ".");
            }
        }

    public:
        explicit FileContents(const FileName& FileName) : fileName{FileName}
        {
            setContentInFile();
        }

        std::vector<std::string> getContentInFile() { return contentInFile; }
    };
}

#endif
