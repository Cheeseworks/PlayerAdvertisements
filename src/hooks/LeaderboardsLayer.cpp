#include <cw.h>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

#include <Geode/modify/LeaderboardsLayer.hpp>

using namespace geode::prelude;
using namespace cw::ads;

#define THIS_ID "LeaderboardsLayer"
inline constexpr auto THIS_HOOK_ID = THIS_ID;

class $modify(AdsLeaderboardsLayer, LeaderboardsLayer) {
    PLAYERADS_DELEGATE_HOOKS(THIS_ID);

    bool init(LeaderboardType type, LeaderboardStat stat) {
        if (!LeaderboardsLayer::init(type, stat)) return false;

        nodes::placeAd(this, AdType::Banner, Anchor::Bottom, { 0.0f, 30.0f });

        return true;
    }
};

PLAYERADS_HOOK_LISTENER(THIS_HOOK_ID);