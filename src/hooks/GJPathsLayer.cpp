#include <cw.h>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

#include <Geode/modify/GJPathsLayer.hpp>

using namespace geode::prelude;
using namespace cw::ads;

#define THIS_ID "GJPathsLayer"
static constexpr auto g_hookId = THIS_ID;

class $modify(AdsGJPathsLayer, GJPathsLayer) {
    PLAYERADS_DELEGATE_HOOKS(THIS_ID);

    bool init() {
        if (!GJPathsLayer::init()) return false;

        if (win::isWide()) {
            nodes::placeAd(m_mainLayer, AdType::Skyscraper, Anchor::Left, { 30.0f, 0.0f });
            nodes::placeAd(m_mainLayer, AdType::Skyscraper, Anchor::Right, { -30.0f, 0.0f });
        };

        return true;
    }
};

PLAYERADS_HOOK_LISTENER(g_hookId);