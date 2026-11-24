#include <cw.h>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;
using namespace cw::ads;

#define THIS_ID "ProfilePage"
inline constexpr auto THIS_HOOK_ID = THIS_ID;

class $modify(AdsProfilePage, ProfilePage) {
    PLAYERADS_DELEGATE_HOOKS(THIS_ID);

    bool init(int p0, bool p1) {
        if (!ProfilePage::init(p0, p1)) return false;

        if (win::isWide()) {
            nodes::placeAd(m_mainLayer, AdType::Skyscraper, Anchor::Left, { 30.0f, 0.0f });
            nodes::placeAd(m_mainLayer, AdType::Skyscraper, Anchor::Right, { -30.0f, 0.0f });
        };

        return true;
    }
};

PLAYERADS_HOOK_LISTENER(THIS_HOOK_ID);