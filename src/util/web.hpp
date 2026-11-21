#pragma once

#include "Macros.h"

#include "ads.hpp"

#include <dankmeme.argon/argon.hpp>

#include <Geode/utils/web.hpp>

namespace cw::ads {
    namespace request {
        geode::utils::web::WebRequest withAuth(std::string token);
        arc::Future<geode::utils::web::WebRequest> withAuthCo(std::string token);
    };

    namespace fetch {
        using AuthResult = geode::Result<std::string>;

        void getLevel(int id, geode::CopyableFunction<void(geode::Result<GJGameLevel*>)>&& callback, bool download = false, GJGameLevel* data = nullptr);
        void getBadge(int id, geode::CopyableFunction<void(geode::Result<AdBadge>)>&& callback, bool local = false);

        inline constexpr auto getRating(GJGameLevel* level) {
            switch (level->m_isEpic) {
                default: break;

                case 1: return LevelRating::Epic;
                case 2: return LevelRating::Legendary;
                case 3: return LevelRating::Mythic;
            };

            if (level->m_featured != 0) return LevelRating::Featured;
            if (level->m_stars.value() != 0) return LevelRating::Star;

            return LevelRating::None;
        }

        inline constexpr auto getDiffSpriteNum(GJGameLevel* level) {
            if (level->m_demon.value() == 1) {
                switch (level->m_demonDifficulty) {
                    default: return 6;

                    case 3: return 7;
                    case 4: return 8;
                    case 5: return 9;
                    case 6: return 10;
                };
            };

            if (level->m_autoLevel) return -1;
            return level->getAverageDifficulty();
        }
    };
};