#pragma once

#include "util/Macros.h"

#include "ui/Include.h"
#include "util/Include.h"

#include <cue/Util.hpp>

#include <Geode/Geode.hpp>

#include <Geode/ui/GeodeUI.hpp>

#define HIGHEST_Z cocos2d::CCScene::get()->getHighestChildZ() + 1

namespace cw::ads {
    using namespace ::cw::ads::ui;

    namespace nodes {
        ui::Advertisement* placeAd(cocos2d::CCNode* to, std::optional<std::string> id = std::nullopt, AdType type = AdType::Banner, geode::Anchor anchor = geode::Anchor::Center, cocos2d::CCPoint const& offset = {});
        ui::Advertisement* placeAd(cocos2d::CCNode* to, AdType type = AdType::Banner, geode::Anchor anchor = geode::Anchor::Center, cocos2d::CCPoint const& offset = {});
    };
};

#define PLAYERADS_DELEGATE_HOOKS(id)                     \
    static void onModify(auto& self) {                   \
        cw::ads::hooks::delegateHooks(id, self.m_hooks); \
    }

#define PLAYERADS_HOOK_LISTENER(id)                                                    \
    $on_game(ModsLoaded) {                                                             \
        cw::ads::hooks::toggleHooks(id, geode::Mod::get()->getSettingValue<bool>(id)); \
                                                                                       \
        geode::listenForSettingChanges<bool>(                                          \
            id,                                                                        \
            [](bool v) {                                                               \
                cw::ads::hooks::toggleHooks(id, v);                                    \
            }                                                                          \
        );                                                                             \
    }