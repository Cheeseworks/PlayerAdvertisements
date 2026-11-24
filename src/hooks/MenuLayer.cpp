#include <cw.h>

#include <rhatt/prelude.h>

#include <dankmeme.argon/argon.hpp>

#include <Geode/Geode.hpp>

#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;
using namespace cw::ads;

#define THIS_ID "MenuLayer"
inline constexpr auto THIS_HOOK_ID = THIS_ID;

class $modify(AdsMenuLayer, MenuLayer) {
    PLAYERADS_DELEGATE_HOOKS(THIS_ID);

    bool init() {
        if (!MenuLayer::init()) return false;

        nodes::placeAd(this, AdType::Banner, Anchor::Bottom, { 0.0f, 92.5f });

        return true;
    }
};

PLAYERADS_HOOK_LISTENER(THIS_HOOK_ID);