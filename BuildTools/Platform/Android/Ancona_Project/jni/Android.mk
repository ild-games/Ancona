LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := Ancona_Engine
LOCAL_SRC_FILES := libAncona_Engine.a
LOCAL_EXPORT_C_INCLUDES := /home/jeff/Code/ILikeDucks/Ancona/Src
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Ancona_Game
LOCAL_SRC_FILES := libAncona_Game.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Ancona_Util
LOCAL_SRC_FILES := libAncona_Util.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := FlappyBird 
LOCAL_SRC_FILES := libFlappyBirdLib.a
LOCAL_EXPORT_C_INCLUDES := /home/jeff/Code/ILikeDucks/Ancona/Test/Prototype/FlappyBirdTest
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := sfml-example

LOCAL_SRC_FILES := main.cpp

LOCAL_CFLAGS := -std=gnu++11

LOCAL_SHARED_LIBRARIES := sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network
LOCAL_WHOLE_STATIC_LIBRARIES := FlappyBird
LOCAL_WHOLE_STATIC_LIBRARIES += Ancona_Util
LOCAL_WHOLE_STATIC_LIBRARIES += Ancona_Engine
LOCAL_WHOLE_STATIC_LIBRARIES += Ancona_Game
LOCAL_WHOLE_STATIC_LIBRARIES += sfml-main

include $(BUILD_SHARED_LIBRARY)

$(call import-module,sfml)
