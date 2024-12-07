
#include <iostream>
#include <mimalloc.h>
#include <pugixml.hpp>
#define USE_MIMALLOC true
#if USE_MIMALLOC
#    include <mimalloc-new-delete.h>    // 全局替换new和delete，将内存操作指向mimalloc
#endif                                  // USE_MIMALLOC

static bool has_set_pugi_mem_func = false;

void init_mimalloc_to_pugi()
{
#if USE_MIMALLOC
    if (!has_set_pugi_mem_func) {
        pugi::set_memory_management_functions(mi_malloc, mi_free);
        has_set_pugi_mem_func = true;
        std::cout << "set_memory_management_functions" << mi_malloc << " " << mi_free << "\n";
    }
#endif    // USE_MIMALLOC
}
