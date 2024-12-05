
#include <iostream>
#include <mimalloc.h>
#include <pugixml.hpp>

static bool has_set_pugi_mem_func = false;

void init_mimalloc_to_pugi()
{
    if (!has_set_pugi_mem_func) {
        pugi::set_memory_management_functions(mi_malloc, mi_free);
        has_set_pugi_mem_func = true;
        std::cout << "set_memory_management_functions" << mi_malloc << " " << mi_free << "\n";
    }
   
}
