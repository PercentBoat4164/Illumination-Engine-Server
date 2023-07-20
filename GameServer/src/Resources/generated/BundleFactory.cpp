#include "../SharedResources/SharedFlag.hpp"
#include "BundleFactory.hpp"
#include <map>

std::map<int, std::map<int, SharedResource*>*>* BundleFactory::getStaticBundles() {
    return new std::map<int, std::map<int, SharedResource*>*>(
                {
                    {0,
                        new std::map<int, SharedResource*> ({
                                {0, new SharedFlag<int>(2, 0, 0,{
                                {SharedFlag<int>::m_opCodes::GetValue, 0},
                                {SharedFlag<int>::m_opCodes::SetValue, 0}
                            })},
                            {1, new SharedFlag<int>(2, 0, 1, {
                                {SharedFlag<int>::m_opCodes::GetValue, 0},
                                {SharedFlag<int>::m_opCodes::SetValue, 0}
                            })}})
                    }
                });
}

std::map<int, SharedResource*> *BundleFactory::generateBundle(int bundleType) {
    switch (bundleType) {
        default:
            return nullptr;
    }
}