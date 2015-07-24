#ifndef Ancona_Systems_Android_AndroidFileOperations_H_
#define Ancona_Systems_Android_AndroidFileOperations_H_

#include <android/asset_manager.h>
#include <android/native_activity.h>
#include <android/window.h>
#include <string>

namespace ild
{

/**
 * @brief File operations specific to the android file operating system.
 *
 * @author Tucker Lein
 * @author Jeff Swenson
 */
class AndroidFileOperations
{
    public:
        /**
         * @brief Gets a file input stream from the android file system from the file specified. The file 
         *        assumes it is relative to the app's asset folder.
         *
         * @param desiredFile Relative path to the desired file from the app's asset folder.
         *
         * @return Input stream for the desired file, null if it can't be found.
         */
        static std::istream * GetAndroidFileInputStream(const std::string & desiredFile);    

        
        /* getters and setters */
        static AAssetManager * assetManager() { return _assetManager; }
        static void assetManager(AAssetManager * assetManager) { _assetManager = assetManager; }
        static const std::string & internalPath() { return _internalPath; }
        static void internalPath(const std::string & internalPath) { _internalPath = internalPath; }

    private:
        static AAssetManager * _assetManager;
        static std::string _internalPath;

        static std::ostringstream * OpenFile(const std::string & desiredFile);
        static void WriteApkFileToNonApkStorage(const std::string & filename, std::istream * streamToWrite);
        static bool FilesDirPresent();
        static void MakeFilesDir();
};

}

#endif
