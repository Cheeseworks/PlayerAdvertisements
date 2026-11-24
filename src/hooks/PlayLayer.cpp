#include <cw.h>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;
using namespace cw::ads;

#define THIS_ID "PlayLayer"
inline constexpr auto THIS_HOOK_ID = THIS_ID;

class $modify(AdsPlayLayer, PlayLayer) {
    PLAYERADS_DELEGATE_HOOKS(THIS_ID);

    struct Fields final {
        asp::Instant lastTime;

        Advertisement* bannerTop = nullptr;
        Advertisement* bannerBottom = nullptr;
        Advertisement* skyscraperRight = nullptr;
        Advertisement* skyscraperLeft = nullptr;
    };

    void setupHasCompleted() {
        auto f = m_fields.self();

        f->bannerBottom = nodes::placeAd(m_uiLayer, AdType::Banner, Anchor::Bottom, { 0.0f, 30.0f });
        f->bannerBottom = nodes::placeAd(m_uiLayer, AdType::Banner, Anchor::Bottom, { 0.0f, 30.0f });

        if (win::isWide()) {
            f->skyscraperLeft = nodes::placeAd(m_uiLayer, AdType::Skyscraper, Anchor::Left, { 30.0f, 0.0f });
            f->skyscraperRight = nodes::placeAd(m_uiLayer, AdType::Skyscraper, Anchor::Right, { -30.0f, 0.0f });
        };

#ifdef CW_TESTING
        log::trace("setting up scheduler for auto ad refresh");
#endif
        scheduleOnce(schedule_selector(AdsPlayLayer::schedReload), cw::rng::get(12.5f, 2.5f));

        PlayLayer::setupHasCompleted();
    }

    void fullReset() {
        reloadAllAds();
        PlayLayer::fullReset();
    }

    void resetLevelFromStart() {
        reloadAllAds();
        PlayLayer::resetLevelFromStart();
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) {
        PlayLayer::destroyPlayer(player, object);
        if (player->m_isDead) reloadAllAds();
    }

    void reloadAllAds() {
        auto f = m_fields.self();

        if (asp::Instant::now().durationSince(f->lastTime).seconds() < 12.5f) return;

        if (f->bannerTop) f->bannerTop->loadRandom();
        if (f->bannerBottom) f->bannerBottom->loadRandom();
        if (f->skyscraperRight) f->skyscraperRight->loadRandom();
        if (f->skyscraperLeft) f->skyscraperLeft->loadRandom();

#ifdef CW_TESTING
        log::debug("All ads are now reloading");
#endif

        f->lastTime = asp::Instant::now();
    }

    void schedReload(float dt) {
#ifdef CW_TESTING
        log::debug("reloading ads after {}s...", dt);
#endif
        reloadAllAds();

        scheduleOnce(schedule_selector(AdsPlayLayer::schedReload), cw::rng::get(12.5f, 2.5f));
    }
};

PLAYERADS_HOOK_LISTENER(THIS_HOOK_ID);