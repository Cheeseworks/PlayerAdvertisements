#include <cw.h>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

#include <Geode/modify/LevelSelectLayer.hpp>

using namespace geode::prelude;
using namespace cw::ads;

#define THIS_ID "LevelSelectLayer"
inline constexpr auto THIS_HOOK_ID = THIS_ID;

class $modify(AdsLevelSelectLayer, LevelSelectLayer) {
    PLAYERADS_DELEGATE_HOOKS(THIS_ID);

    bool init(int page) {
        if (!LevelSelectLayer::init(page)) return false;

        nodes::placeAd(this, AdType::Banner, Anchor::Top, { 0.0f, -30.0f });

        return true;
    }
};

PLAYERADS_HOOK_LISTENER(THIS_HOOK_ID);