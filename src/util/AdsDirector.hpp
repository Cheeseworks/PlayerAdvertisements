#pragma once

#include <util/ads.hpp>

#include <Geode/Geode.hpp>

namespace cw::ads {
    class AdsDirector final {
    private:
        asp::SmallVec<Ad, 25> m_seenAds;
        geode::utils::StringMap<std::vector<std::weak_ptr<geode::Hook>>> m_hooks;

        std::unordered_map<int, AdBadge> m_badges;
        std::unordered_map<int, AdLevelMetadata> m_seenLevels;

    public:
        static AdsDirector* get() noexcept;

        void registerHooks(std::string id, std::vector<std::weak_ptr<geode::Hook>> hooks);
        void addLevelToCache(GJGameLevel* level);
        void addToViewed(Ad ad);

        void saveBadge(int id, AdBadge badge);

        std::span<const std::weak_ptr<geode::Hook>> getHooks(std::string_view id) const noexcept;
        geode::Result<AdLevelMetadata> getLevelMeta(int id) const;
        std::span<const Ad> getViewedAds() const noexcept;

        geode::Result<AdBadge> getBadge(int id);
    };
};