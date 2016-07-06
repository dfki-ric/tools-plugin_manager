#pragma once

#include <map>
#include <vector>
#include <string>
#include <set>
#include <boost/shared_ptr.hpp>
#include "PluginInfo.hpp"

namespace plugin_manager
{

/**
 * @class PluginManager
 * @brief A class to load xml plugin informations
 */
class PluginManager
{
public:
    typedef boost::shared_ptr<PluginInfo> PluginInfoPtr;

    /**
     * @brief Constructor for PluginManager
     * @param plugin_xml_paths The list of paths of plugin.xml files
     * @param load_environment_paths true if environment path shall be loaded
     */
    PluginManager(const std::vector<std::string>& plugin_xml_paths = std::vector<std::string>(), bool load_environment_paths = true);

    /**
     * @brief Destructor for PluginManager
     */
    virtual ~PluginManager();

    /**
     * @brief Returns a list of all available plugin paths
     * @return A vector of strings corresponding to the paths of all available plugin xml files
     */
    std::vector<std::string> getPluginXmlPaths() const;

    /**
     * @brief Returns a list of all available classes
     * @return A vector of strings corresponding to the names of all available classes
     */
    std::vector<std::string> getAvailableClasses() const;

    /**
     * @brief Returns a list of all available classes for the given base class type
     * @param base_class name of the base class
     * @return A vector of strings corresponding to the names of all available classes
     */
    std::vector<std::string> getAvailableClasses(const std::string& base_class) const;

    /**
     * @brief Return true if the given class is registered.
     * @param class_name the name of the plugin class
     * @return True if class could be found
     */
    bool isClassInfoAvailable(const std::string& class_name) const;

    /**
     * @brief Returns the base class of the given class
     * @param class_name the name of the plugin class
     * @param base_class the base class name
     * @return True if base class could be found
     */
    bool getBaseClass(const std::string& class_name, std::string& base_class) const;

    /**
     * @brief Returns a vector of all associated classes of the given class.
     *        If there are no associated classes returns false.
     * @param class_name the name of the plugin class
     * @param associated_classes names of the associated classes
     * @return True if an associated class was found
     */
    bool getAssociatedClasses(const std::string& class_name, std::vector<std::string>& associated_classes) const;

    /**
     * @brief Returns the description of the given class
     * @param class_name the name of the plugin class
     * @param class_description the class description
     * @return True if plugin description could be found
     */
    bool getClassDescription(const std::string& class_name, std::string& class_description) const;

    /**
     * @brief Returns if the class should be treated as singleton
     * @param class_name the name of the plugin class
     * @param is_singleton true if marked as singleton
     * @return True if plugin description could be found
     */
    bool getSingletonFlag(const std::string& class_name, bool& is_singleton) const;

    /**
     * @brief Returns the library path of the given class
     * @param class_name the name of the plugin class
     * @param library_path the library path of the plugin
     * @return True if the library path could be found
     */
    bool getClassLibraryPath(const std::string& class_name, std::string& library_path) const;

    /**
     * @brief Return the full class name of a given class
     * @param class_name class name without namespace
     * @param full_class_name class name with namespace
     * @return True if class coudl be found
     */
    bool getFullClassName(const std::string& class_name, std::string& full_class_name) const;

    /**
     * @brief Returns the name of a class which inherits from the given
     *        base class and is associated to the given embedded type.
     * Note: If more than one associated class is available it will always
     *       return the first one that is found.
     * @param embedded_type name of the embedded type
     * @param base_class_name name of the base class
     * @param associated_class name of the associated class
     * @return True if an associated class could be found
     */
    bool getAssociatedClassOfType(const std::string& embedded_type, const std::string& base_class_name, std::string& associated_class) const;

    /**
     * @brief Returns the libraries that are registered and can be loaded
     * @return A vector of strings corresponding to the names of registered libraries
     */
    std::set<std::string> getRegisteredLibraries() const;

    /**
     * @brief Removes the class info of the given class
     * @param class_name the name of the plugin class
     * @return True if the class was found and removed
     */
    bool removeClassInfo(const std::string& class_name);

    /**
     * @brief Clears all plugin informations.
     */
    void clear();

    /**
     * @brief Overrides the paths of the xml plugin informations.
     *        This also removes all currently known paths.
     * @param plugin_xml_paths to folders and xml files
     */
    void overridePluginXmlPaths(const std::vector<std::string>& plugin_xml_paths);

    /**
     * @brief Loads all plugin informations found in the given xml plugin paths.
     */
    void reloadXMLPluginFiles();

protected:
    /**
     * @brief Returns true if the given class name has a namespace
     */
    bool hasNamespace(const std::string& class_name) const;

    /**
     * @brief Returns true if the given class name has a embedded type. E.g. Item<int>
     */
    bool hasEmbeddedType(const std::string& class_name) const;

    /**
     * @brief Returns the embedded type name of a class. E.g. int from Item<int>
     */
    std::string extractEmbeddedType(const std::string& class_name) const;

    /**
     * @brief Returns the base type name of a class. E.g. Item from Item<int>
     */
    std::string extractBaseType(const std::string& class_name) const;

    /**
     * @brief Helper method that strips the namespace if available from the given class name
     * @param class_name the name of the plugin class
     * @return class name without namespace
     */
    std::string removeNamespace(const std::string& class_name) const;

private:
    /**
     * @brief Returns the paths in all install folders set by the environment.
     * @return A vector of paths
     */
    std::vector<std::string> getPluginXmlPathsFromEnv() const;

    /**
     * @brief Returns the available xml files in the given folder
     * @param plugin_xml_folder a plugin information folder
     * @param plugin_xml_files a set of all xml files
     */
    void determineAvailableXMLPluginFiles(const std::string& plugin_xml_folder, std::set<std::string>& plugin_xml_files) const;

    /**
     * @brief Processes a xml plugin info file
     * @param xml_file a xml file containing plugin information
     * @param class_available A vector of all plugin infos found
     * @return True if xml was successfully parsed
     */
    bool processSingleXMLPluginFile(const std::string& xml_file, std::vector<PluginInfoPtr>& class_available) const;

    /**
     * @brief Insert plugin infos to internal data structure
     * @param classes vector of plugin infos
     */
    void insertPluginInfos(const std::vector<PluginInfoPtr>& classes);

private:
    /** Path to the folders where the xml files can be found */
    std::vector<std::string> plugin_xml_paths;

    /** Mapping between full class name and plugin information */
    std::map<std::string, PluginInfoPtr> classes_available;

    /** Mapping between base class name and corresponding classes */
    std::multimap<std::string, PluginInfoPtr> base_classes_available;

    /** Mapping between class name without namespace and plugin information */
    std::multimap<std::string, PluginInfoPtr> classes_no_ns_available;
};

}