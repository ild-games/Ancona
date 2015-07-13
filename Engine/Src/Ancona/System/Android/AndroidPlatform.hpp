#ifndef Ancona_Systems_Android_AndroidPlatform_H_
#define Ancona_Systems_Android_AndroidPlatform_H_

#include <android/asset_manager.h>
#include <android/log.h>
#include <android/native_activity.h>
#include <android/window.h>

class AndroidPlatform
{
    public:
        static AAssetManager * assetManager() { return _assetManager; }
        static void assetManager(AAssetManager * assetManager) { _assetManager = assetManager; }

    private:
        static AAssetManager * _assetManager;
};

#endif
