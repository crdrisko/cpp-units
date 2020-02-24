// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: textFile.cpp - Version 1.0.0
// Author: cdrisko
// Date: 01/31/2020-15:22:50
// Description: Constructors and non-inline functions from the TextFile class

#include "../../include/internal/Files/textFile.hpp"

namespace Utilities_API::Files
{
    using std::vector;
    using std::string;

    TextFile::TextFile(std::string_view FullFileName, string Comments, vector<string> MetaDataKeywords)
        : InputFile{FullFileName}, comments{Comments}, metaDataKeywords{MetaDataKeywords}
    {
        this->separateFileData();
    }

    void TextFile::separateFileData()
    {
        vector<string> allDataVector { this->getFileContents()->getContentInFile() };

        for (const auto& line : allDataVector)
        {
            if (metaDataKeywords[0] != "Null Selection" && Strings::stringFinder(comments, line))
            {
                for (const auto& selection : metaDataKeywords)
                    if ( Strings::stringFinder(selection, line) )
                        metaDataVector.push_back(line);
            }
            else if ( (metaDataKeywords[0] == "Null Selection") && (Strings::stringFinder(comments, line)) )
                metaDataVector.push_back(line);

            else if ( !Strings::stringFinder(comments, line) )
                dataVector.push_back(line);
        }
    }
}
