#include "../AdsDirector.hpp"

#include <cw.h>

#include <rhatt/prelude.h>

#include <dankmeme.argon/argon.hpp>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw::ads;

void AdsDirector::registerHooks(std::string id, std::vector<std::weak_ptr<Hook>> hooks) {
    m_hooks[std::move(id)] = std::move(hooks);
}

void AdsDirector::addLevelToCache(GJGameLevel* level) {
    m_seenLevels[level->m_levelID.value()] = AdLevelMetadata{ level->m_levelName, level->m_levelID.value(), fetch::getDiffSpriteNum(level), fetch::getRating(level) };
}

void AdsDirector::addToViewed(Ad ad) {
    if (m_seenAds.size() >= 25) m_seenAds.pop_back();
    m_seenAds.insert(m_seenAds.begin(), std::move(ad));
}

void AdsDirector::saveBadge(int id, AdBadge badge) {
    m_badges[id] = std::move(badge);
}

std::span<const std::weak_ptr<Hook>> AdsDirector::getHooks(std::string_view id) const noexcept {
    if (auto it = m_hooks.find(id); it != m_hooks.end()) return it->second;
    return {};
}

Result<AdLevelMetadata> AdsDirector::getLevelMeta(int id) const {
    if (auto it = m_seenLevels.find(id); it != m_seenLevels.end()) return Ok(it->second);
    return Err("Level not in cache");
}

std::span<const Ad> AdsDirector::getViewedAds() const noexcept {
    return m_seenAds;
}

Result<AdBadge> AdsDirector::getBadge(int id) {
    if (auto it = m_badges.find(id); it != m_badges.end()) return Ok(it->second);
    return Err("Badge not found");
}

AdsDirector* AdsDirector::get() noexcept {
    static AdsDirector inst;
    return &inst;
}