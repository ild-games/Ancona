#ifndef Ancona_Systems_FileOperations_H_
#define Ancona_Systems_FileOperations_H_

#include <iostream>
#include <memory>
#include <fstream>

namespace ild
{

/**
 * @brief Holds platform specific file operations.
 * 
 * @author Tucker Lein
 * @author Jeff Swenson
 */
class FileOperations
{
    public:
        /**
         * @brief 
         *
         * @param desiredFile
         *
         * @return 
         */
        static std::unique_ptr<std::istream> GetInputFileStream(const std::string & desiredFile);          

        /**
         * @brief 
         *
         * @param desiredFile
         *
         * @return 
         */
        static std::unique_ptr<std::ofstream> GetOutputFileStream(const std::string & desiredFile);          
        /**
         * @brief 
         *
         * @param filePath
         *
         * @return 
         */
        static std::string GetDirName(const std::string & filePath);

        /**
         * @brief 
         *
         * @param dirPath
         *
         * @return 
         */
        static bool IsDir(const std::string & dirPath);

        /**
         * @brief 
         *
         * @param filePath
         *
         * @return 
         */
        static bool IsFile(const std::string & filePath);

        /**
         * @brief 
         *
         * @param dirPath
         *
         * @return 
         */
        static bool CreateDirectory(const std::string & dirPath);
};

}

#endif
