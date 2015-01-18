LOCAL_PATH := $(call my-dir)

<!--(for i,lib in enumerate(static_libraries))-->
include $(CLEAR_VARS)
LOCAL_MODULE := $!lib!$
LOCAL_SRC_FILES := $!build_dir!$/lib/lib$!lib!$.a
	<!--(if i==0)-->
		<!--(for path in include_paths)-->
LOCAL_EXPORT_C_INCLUDES += $!path!$
		<!--(end)-->
	<!--(end)-->
include $(PREBUILT_STATIC_LIBRARY)

<!--(end)-->
<!--(for lib in dynamic_libraries)-->
include $(CLEAR_VARS)
LOCAL_MODULE := $!module!$
LOCAL_SRC_FILES := $!build_dir!$/lib/lib$!lib!$.so
	<!--(if i==0)-->
		<!--(for path in include_paths)-->
LOCAL_EXPORT_C_INCLUDES += $!path!$
		<!--(end)-->
	<!--(end)-->
include $(PREBUILT_DYNAMIC_LIBRARY)

<!--(end)-->
include $(CLEAR_VARS)

LOCAL_MODULE := sfml-example

<!--(for file in source_files)-->
LOCAL_SRC_FILES += $!file!$
<!--(end)-->

LOCAL_CFLAGS := -std=gnu++11

LOCAL_SHARED_LIBRARIES := sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network
<!--(for lib in dynamic_libraries)-->
LOCAL_SHARED_LIBRARIES += $!lib!$
<!--(end)-->

<!--(for lib in static_libraries)-->
LOCAL_WHOLE_STATIC_LIBRARIES += $!lib!$
<!--(end)-->
LOCAL_WHOLE_STATIC_LIBRARIES += sfml-main


include $(BUILD_SHARED_LIBRARY)

$(call import-module,sfml)
