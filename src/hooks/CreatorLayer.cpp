#include <cw.h>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;
using namespace cw::ads;

#define THIS_ID "CreatorLayer"
inline constexpr auto THIS_HOOK_ID = THIS_ID;

class $modify(AdsCreatorLayer, CreatorLayer) {
    PLAYERADS_DELEGATE_HOOKS(THIS_ID);

    bool init() {
        if (!CreatorLayer::init()) return false;

        nodes::placeAd(this, AdType::Banner, Anchor::Top, { 0.0f, -30.0f });

        return true;
    }
};

PLAYERADS_HOOK_LISTENER(THIS_HOOK_ID);