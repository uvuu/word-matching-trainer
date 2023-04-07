cmake_minimum_required(VERSION 3.14)

# Keep here all resources that must be included into the main project target
set(RESOURCE_SOURCES
    res/res.qrc
    # Include and compile the resource with a Windows app icon
    $<$<PLATFORM_ID:Windows>:windows/icon.rc>
    PARENT_SCOPE
)

# Obtain all additional resources for Android and Windows
file(GLOB_RECURSE ANDROID_ADDITIONS "android/*")
file(GLOB_RECURSE WINDOWS_ADDITIONS "windows/*")

# This is a common way to show extra files on the project tree
add_custom_target(${PROJECT_NAME}-additions
    SOURCES
        ${ANDROID_ADDITIONS}
        ${WINDOWS_ADDITIONS}
)

# The source_group() command may help to create groups under existing targets
# on project tree but it should operate only files included in those targets.
source_group(android FILES ${ANDROID_ADDITIONS})
source_group(windows FILES ${WINDOWS_ADDITIONS})
