#include "../ads.hpp"

#include <cw.h>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw::ads;

Result<Ad> matjson::Serialize<Ad>::fromJson(matjson::Value const& value) {
    GEODE_UNWRAP_INTO(auto id, value["ad_id"].asUInt());
    GEODE_UNWRAP_INTO(auto image, value["image_url"].asString());
    GEODE_UNWRAP_INTO(auto level, value["level_id"].asInt());
    GEODE_UNWRAP_INTO(auto _type, value["type"].asUInt());
    GEODE_UNWRAP_INTO(auto user, value["user_id"].asString());
    GEODE_UNWRAP_INTO(auto viewCount, value["views"].asUInt());
    GEODE_UNWRAP_INTO(auto clickCount, value["clicks"].asUInt());

    uint8_t glow = 0;
    GEODE_UNWRAP_INTO_IF_OK(glow, value["glow"].asUInt());

    return Ok(
        Ad{
            id,
            std::move(image),
            (int)level,
            (AdType)_type,
            std::move(user),
            viewCount,
            clickCount,
            glow,
        }
    );
}

matjson::Value matjson::Serialize<Ad>::toJson(Ad const& value) {
    matjson::Value obj;
    obj["ad_id"] = value.getID();
    obj["image_url"] = value.getImage();
    obj["level_id"] = value.getLevel();
    obj["type"] = static_cast<uint8_t>(value.getType());
    obj["user_id"] = value.getUser();
    obj["views"] = value.getViews();
    obj["clicks"] = value.getClicks();
    obj["glow"] = value.getGlowLevel();

    return obj;
}

Ad::Ad(
    uint64_t id,
    std::string image,
    int level,
    AdType type,
    std::string user,
    uint64_t viewCount,
    uint64_t clickCount,
    uint8_t glowLevel
) :
    m_id(id),
    m_image(std::move(image)),
    m_level(level),
    m_type(type),
    m_user(std::move(user)),
    m_viewCount(viewCount),
    m_clickCount(clickCount),
    m_glowLevel(glowLevel) {}

uint64_t Ad::getID() const noexcept {
    return m_id;
}

ZStringView Ad::getImage() const noexcept {
    return m_image;
}

int Ad::getLevel() const noexcept {
    return m_level;
}

AdType Ad::getType() const noexcept {
    return m_type;
}

ZStringView Ad::getUser() const noexcept {
    return m_user;
}

uint64_t Ad::getViews() const noexcept {
    return m_viewCount;
}

uint64_t Ad::getClicks() const noexcept {
    return m_clickCount;
}

uint8_t Ad::getGlowLevel() const noexcept {
    return m_glowLevel;
}

Result<AdBadge> matjson::Serialize<cw::ads::AdBadge>::fromJson(matjson::Value const& value) {
    if (!value.isObject()) return Err("Expected an object");

    GEODE_UNWRAP_INTO(auto user, value["user"].asInt());
    GEODE_UNWRAP_INTO(auto owner, value["owner"].asBool());
    GEODE_UNWRAP_INTO(auto dev, value["dev"].asBool());
    GEODE_UNWRAP_INTO(auto admin, value["admin"].asBool());
    GEODE_UNWRAP_INTO(auto staff, value["staff"].asBool());
    GEODE_UNWRAP_INTO(auto verified, value["verified"].asBool());
    GEODE_UNWRAP_INTO(auto contributor, value["contributor"].asBool());
    GEODE_UNWRAP_INTO(auto discord, value["discord"].asString());

    return Ok(
        AdBadge{
            (int)user,
            owner,
            dev,
            admin,
            staff,
            verified,
            contributor,
            std::move(discord),
        }
    );
}

matjson::Value matjson::Serialize<cw::ads::AdBadge>::toJson(AdBadge const& value) {
    matjson::Value obj;
    obj["user"] = value.user;
    obj["owner"] = value.owner;
    obj["dev"] = value.dev;
    obj["admin"] = value.admin;
    obj["staff"] = value.staff;
    obj["verified"] = value.verified;
    obj["contributor"] = value.contributor;
    obj["discord"] = value.discord;

    return obj;
}