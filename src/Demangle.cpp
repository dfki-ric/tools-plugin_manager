#include "Demangle.hpp"
#include <cxxabi.h>
#include <boost/algorithm/string/replace.hpp>

namespace plugin_manager
{
  
std::string demangleTypeName(const std::type_index& type)
{
    int status = 0;
    std::string result;
    char* p_nice_name = abi::__cxa_demangle(type.name(), NULL, NULL, &status);
    if(0 != status) 
    {
        //if demangling failed return the mangled name
        result = type.name();
    }
    else
    {
        if(nullptr != p_nice_name)
        {
            result = p_nice_name;
            free(p_nice_name);
        }

    }
    return result;  
}

}
