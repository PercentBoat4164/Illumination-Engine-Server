add_library(Resources
        ResourceDelegator.cpp SharedResource.cpp
        SharedResources/SharedFlag.inl SharedResources/SharedFlag.hpp
        SharedResources/SharedMap.inl SharedResources/SharedMap.hpp
        generated/BundleFactory.cpp generated/BundleFactory.hpp)