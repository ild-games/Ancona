#ifndef Ancona_Systems_Android_AndroidPlatform_H_
#define Ancona_Systems_Android_AndroidPlatform_H_

#include <android/asset_manager.h>
#include <android/log.h>
#include <android/native_activity.h>
#include <android/window.h>
#include <string>

namespace ild
{

class AndroidPlatform
{
    public:
        static std::istream * GetAndroidFileInputStream(const std::string & desiredFile);    
        static std::ostringstream * OpenFile(const std::string & desiredFile);
        
        /* getters and setters */
        static AAssetManager * assetManager() { return _assetManager; }
        static void assetManager(AAssetManager * assetManager) { _assetManager = assetManager; }
        static const std::string & internalPath() { return _internalPath; }
        static void internalPath(const std::string & internalPath) { _internalPath = internalPath; }

    private:
        static AAssetManager * _assetManager;
        static std::string _internalPath;

        static void WriteApkFileToNonApkStorage(const std::string & filename, std::istream * streamToWrite);
        static bool FilesDirPresent();
        static void MakeFilesDir();
};

}

#endif
