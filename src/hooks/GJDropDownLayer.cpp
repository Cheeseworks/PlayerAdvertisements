#include <cw.h>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

#include <Geode/modify/GJDropDownLayer.hpp>

using namespace geode::prelude;
using namespace cw::ads;

#define THIS_ID "GJDropDownLayer"
inline constexpr auto THIS_HOOK_ID = THIS_ID;

class $modify(AdsGJDropDownLayer, GJDropDownLayer) {
    PLAYERADS_DELEGATE_HOOKS(THIS_ID);

    bool init(const char* p0, float p1, bool p2) {
        if (!GJDropDownLayer::init(p0, p1, p2)) return false;

        nodes::placeAd(m_mainLayer, AdType::Banner, Anchor::Top, { 0.0f, -30.0f });

        if (win::isWide() && !m_mainLayer->getChildByID("hide-dropdown-menu")) {
            nodes::placeAd(m_mainLayer, AdType::Skyscraper, Anchor::Left, { 30.0f, 0.0f });
            nodes::placeAd(m_mainLayer, AdType::Skyscraper, Anchor::Right, { -30.0f, 0.0f });
        };

        return true;
    }
};

PLAYERADS_HOOK_LISTENER(THIS_HOOK_ID);