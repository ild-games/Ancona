LOCAL_PATH := $(call my-dir)

<!--(for i,lib in enumerate(static_depend_libraries))-->
include $(CLEAR_VARS)
LOCAL_MODULE := $!lib!$
LOCAL_SRC_FILES := $!depend_lib_dir!$/lib$!lib!$.a
	<!--(for path in include_paths)-->
LOCAL_EXPORT_C_INCLUDES += $!path!$
	<!--(end)-->
include $(PREBUILT_STATIC_LIBRARY)
<!--(end)-->

<!--(for i,lib in enumerate(dynamic_depend_libraries))-->
include $(CLEAR_VARS)
LOCAL_MODULE := $!lib!$
LOCAL_SRC_FILES := $!depend_lib_dir!$/lib$!lib!$.so
	<!--(for path in include_paths)-->
LOCAL_EXPORT_C_INCLUDES += $!path!$
	<!--(end)-->
include $(PREBUILT_DYNAMIC_LIBRARY)
<!--(end)-->

<!--(for i,lib in enumerate(static_project_libraries))-->
include $(CLEAR_VARS)
LOCAL_MODULE := $!lib!$
LOCAL_SRC_FILES := $!project_lib_dir!$/lib$!lib!$.a
	<!--(for path in include_paths)-->
LOCAL_EXPORT_C_INCLUDES += $!path!$
	<!--(end)-->
include $(PREBUILT_STATIC_LIBRARY)
<!--(end)-->

<!--(for i,lib in enumerate(dynamic_project_libraries))-->
include $(CLEAR_VARS)
LOCAL_MODULE := $!lib!$
LOCAL_SRC_FILES := $!project_lib_dir!$/lib$!lib!$.so
	<!--(for path in include_paths)-->
LOCAL_EXPORT_C_INCLUDES += $!path!$
	<!--(end)-->
include $(PREBUILT_DYNAMIC_LIBRARY)
<!--(end)-->

include $(CLEAR_VARS)



LOCAL_CFLAGS := -std=gnu++11

#TODO: Change to project name
LOCAL_MODULE := sfml-example

<!--(for file in source_files)-->
LOCAL_SRC_FILES += $!file!$
<!--(end)-->

<!--(for path in include_paths)-->
LOCAL_EXPORT_C_INCLUDES += $!path!$
<!--(end)-->

<!--(for lib in static_project_libraries)-->
LOCAL_WHOLE_STATIC_LIBRARIES += $!lib!$
<!--(end)-->

<!--(for lib in dynamic_project_libraries)-->
LOCAL_SHARED_LIBRARIES += $!lib!$
<!--(end)-->

<!--(for lib in static_depend_libraries)-->
LOCAL_WHOLE_STATIC_LIBRARIES += $!lib!$
<!--(end)-->

<!--(for lib in dynamic_depend_libraries)-->
LOCAL_SHARED_LIBRARIES += $!lib!$
<!--(end)-->

include $(BUILD_SHARED_LIBRARY)
