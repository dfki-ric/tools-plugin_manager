#include "FloatPlugin.hpp"
#include <class_loader_melodic/register_macro.hpp>

namespace plugin_manager
{

FloatPlugin::FloatPlugin()
{

}

}

CLASS_LOADER_REGISTER_CLASS(plugin_manager::FloatPlugin, plugin_manager::BaseClass);