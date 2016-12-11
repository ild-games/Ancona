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
         * @brief Gets an input stream from a desired file on the system.
         *
         * @param desiredFile Path to the given file.
         *
         * @return Input Stream for the file, null if file is not found.
         */
        static std::unique_ptr<std::istream> GetInputFileStream(const std::string & desiredFile);          

        /**
         * @brief Gets an output stream from a desired file on the system.
         *
         * @param desiredFile Path to the given file.
         *
         * @return Output Stream for the file, null if file is not found.
         */
        static std::unique_ptr<std::ofstream> GetOutputFileStream(const std::string & desiredFile);          

        /**
         * @brief Determines if a desired file exists.
         * 
         * @param desiredFile Path to the file we want to determine exists.
         *
         * @return True if the file exists, otherwise false.
         */
        static bool FileExists(const std::string & desiredFile);

        /**
         * @brief Gets the full directory (minus the actual file) for a given filepath.
         *
         * @param filePath Filepath to get the directory from.
         *
         * @return Just the path potion of the filepath.
         */
        static std::string GetDirName(const std::string & filePath);

        /**
         * @brief Determines if the given directory path is an existing directory.
         *
         * @param dirPath Path to check.
         *
         * @return True if the directory exists, otherwise false.
         */
        static bool IsDir(const std::string & dirPath);

        /**
         * @brief Determines if the given file is an existing file.
         *
         * @param filePath Filepath to chec.
         *
         * @return True if the file exists, otherwise false.
         */
        static bool IsFile(const std::string & filePath);

        /**
         * @brief Creates the directory specified by the given directory path. Will recursively
         *        create the directory structure if needed.
         *
         * @param dirPath Path for the desired directory structure.
         *
         * @return True if the directory didn't exist and was made, false if the directory already exists.
         */
        static bool CreateDirectory(const std::string & dirPath);
};

}

#endif
