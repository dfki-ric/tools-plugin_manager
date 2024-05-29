find_package(Boost COMPONENTS thread system filesystem)
find_package(class_loader REQUIRED)

list(JOIN class_loader_INCLUDE_DIRS " -I"  CLASS_LOADER_DIRS)

rock_library(plugin_manager
    SOURCES PluginManager.cpp
            PluginLoader.cpp
            Demangle.cpp
    HEADERS PluginInfo.hpp
            PluginManager.hpp
            PluginLoader.hpp
            Exceptions.hpp
            Demangle.hpp
    DEPS_PKGCONFIG tinyxml base-logging
    DEPS_CMAKE Glog
    DEPS
    	class_loader::class_loader
        Boost::filesystem
        Boost::system
        Boost::thread
)

