#pragma once

#include <Geode/Geode.hpp>

namespace cw::ads {
    enum class AdType : uint8_t {
        Banner = 1,
        Square = 2,
        Skyscraper = 3
    };

    struct Ad final {
    private:
        uint64_t m_id = 0;
        std::string m_image;
        int m_level = 0;
        std::string m_user;
        AdType m_type = AdType::Banner;
        uint64_t m_viewCount = 0;
        uint64_t m_clickCount = 0;
        uint8_t m_glowLevel = 0;

    public:
        Ad() = default;

        Ad(
            uint64_t id,
            std::string image,
            int level,
            AdType type,
            std::string user,
            uint64_t viewCount = 0,
            uint64_t clickCount = 0,
            uint8_t glowLevel = 0
        );

        uint64_t getID() const noexcept;
        geode::ZStringView getImage() const noexcept;
        int getLevel() const noexcept;
        geode::ZStringView getUser() const noexcept;
        AdType getType() const noexcept;
        uint64_t getViews() const noexcept;
        uint64_t getClicks() const noexcept;
        uint8_t getGlowLevel() const noexcept;
    };

    struct AdBadge final {
        int user = 0;
        bool owner = false;
        bool dev = false;
        bool admin = false;
        bool staff = false;
        bool verified = false;
        bool contributor = false;
        std::string discord;
    };

    enum class LevelRating : uint8_t {
        None = 0,
        Star = 1,
        Featured = 2,
        Epic = 3,
        Legendary = 4,
        Mythic = 5,
    };

    struct AdLevelMetadata final {
        std::string name;
        int id;
        int difficulty;
        LevelRating rating;
    };

    namespace nodes {
        inline constexpr auto getIDForType(AdType type) noexcept {
            switch (type) {
                default: [[fallthrough]];

                case AdType::Banner: return "banner";
                case AdType::Square: return "square";
                case AdType::Skyscraper: return "skyscraper";
            };
        }

        inline constexpr auto getIDForAnchor(geode::Anchor anchor) noexcept {
            using namespace geode;

            switch (anchor) {
                default: [[fallthrough]];

                case Anchor::TopLeft: return "top-left";
                case Anchor::Top: return "top";
                case Anchor::TopRight: return "top-right";
                case Anchor::Left: return "left";
                case Anchor::Center: return "center";
                case Anchor::Right: return "right";
                case Anchor::BottomLeft: return "bottom-left";
                case Anchor::Bottom: return "bottom";
                case Anchor::BottomRight: return "bottom-right";
            };
        }

        inline auto formatIDForAd(AdType type, geode::Anchor anchor) {
            return fmt::format("{}-{}"_spr, getIDForType(type), getIDForAnchor(anchor));
        }
    };

    namespace win {
        inline constexpr auto isWide() noexcept {
            if (auto dir = cocos2d::CCDirector::sharedDirector()) {
                auto const size = dir->getWinSize();

#ifdef CW_TESTING
                geode::log::trace("{}", size.width / size.height);
#endif

                return (size.width / size.height) >= 1.7f;
            };

            return false;
        }
    };
};

template <>
struct matjson::Serialize<cw::ads::Ad> final {
    static geode::Result<cw::ads::Ad> fromJson(matjson::Value const& value);
    static matjson::Value toJson(cw::ads::Ad const& value);
};

template <>
struct matjson::Serialize<cw::ads::AdBadge> final {
    static geode::Result<cw::ads::AdBadge> fromJson(matjson::Value const& value);
    static matjson::Value toJson(cw::ads::AdBadge const& value);
};