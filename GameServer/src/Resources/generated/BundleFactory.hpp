#pragma once

#include "../SharedResource.hpp"
#include <map>

class BundleFactory {
public:
    static std::map<int, std::map<int, SharedResource*>*>* getStaticBundles();
    static std::map<int, SharedResource*> *generateBundle(int bundleType);
};