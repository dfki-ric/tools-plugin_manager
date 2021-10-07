find_package(Boost COMPONENTS thread system filesystem)

rock_library(plugin_manager
    SOURCES PluginManager.cpp
            PluginLoader.cpp
            Demangle.cpp
    HEADERS PluginInfo.hpp
            PluginManager.hpp
            PluginLoader.hpp
            Exceptions.hpp
            Demangle.hpp
    DEPS_PKGCONFIG class_loader tinyxml base-logging
    DEPS_CMAKE Glog 
    DEPS_PLAIN
        Boost_FILESYSTEM
	Boost_SYSTEM
	Boost_THREAD
)

