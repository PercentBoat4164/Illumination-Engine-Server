#include "ResourceDelegator.hpp"
#include "SharedResource.hpp"
#include "generated/BundleFactory.hpp"

ResourceDelegator::ResourceDelegator() : m_resourceBundles(BundleFactory::getStaticBundles()) {
    m_randomNumberGenerator = std::mt19937(std::random_device{}());
    m_bundleIDGenerator = std::uniform_int_distribution<int>(10000, sizeof(int64_t));
}

bool ResourceDelegator::createNewBundle(int bundleType, int bundleID) {
    if (bundleID == -1) {
        bundleID = m_bundleIDGenerator(m_randomNumberGenerator);
    }

    if (m_resourceBundles->contains(bundleID)) {
        return false;
    }

    std::map<int, SharedResource*> *newbundle = BundleFactory::generateBundle(bundleType);

    if (newbundle == nullptr) {
        return false;
    }

    m_resourceBundles->insert({bundleID, newbundle});

    return true;
}

bool ResourceDelegator::deleteBundle(int bundleID) {
    if (m_resourceBundles->contains(bundleID)) {
        m_resourceBundles->erase(bundleID);
        return true;
    }

    return false;
}

SharedResource* ResourceDelegator::getResource(int bundleID, int resID) {
    if (!m_resourceBundles->contains(bundleID)) {
        return nullptr;
    }

    if (!m_resourceBundles->at(bundleID)->contains(resID)) {
        return nullptr;
    }

    return m_resourceBundles->at(bundleID)->at(resID);
}