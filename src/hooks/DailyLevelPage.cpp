#include <cw.h>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

#include <Geode/modify/DailyLevelPage.hpp>

using namespace geode::prelude;
using namespace cw::ads;

#define THIS_ID "DailyLevelPage"
inline constexpr auto THIS_HOOK_ID = THIS_ID;

class $modify(AdsDailyLevelPage, DailyLevelPage) {
    PLAYERADS_DELEGATE_HOOKS(THIS_ID);

    bool init(GJTimedLevelType levelType) {
        if (!DailyLevelPage::init(levelType)) return false;

        nodes::placeAd(m_mainLayer, AdType::Banner, Anchor::Center, { 0.0f, -95.0f });

        if (win::isWide()) {
            nodes::placeAd(m_mainLayer, AdType::Skyscraper, Anchor::Left, { 30.0f, 0.0f });
            nodes::placeAd(m_mainLayer, AdType::Skyscraper, Anchor::Right, { -30.0f, 0.0f });
        };

        return true;
    }
};

PLAYERADS_HOOK_LISTENER(THIS_HOOK_ID);