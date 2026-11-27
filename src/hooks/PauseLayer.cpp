#include <cw.h>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;
using namespace cw::ads;

#define THIS_ID "PauseLayer"
inline constexpr auto THIS_HOOK_ID = THIS_ID;

class $modify(AdsPauseLayer, PauseLayer) {
    PLAYERADS_DELEGATE_HOOKS(THIS_ID);

    void customSetup() {
        PauseLayer::customSetup();

        auto levelName = m_mainLayer->getChildByID("level-name");
        levelName->setVisible(false);

        auto isPractice = PlayLayer::get()->m_isPracticeMode;
        auto isLegacyPause = GameManager::sharedState()->getGameVariable(GameVar::LegacyPauseProgress);

        if (isLegacyPause) {
            auto normalTitle = m_mainLayer->getChildByID("normal-mode-label");
            auto normalProgress = m_mainLayer->getChildByID("normal-progress-label");
            auto normalBar = m_mainLayer->getChildByID("normal-progress-bar");

            auto practiceTitle = m_mainLayer->getChildByID("practice-mode-label");
            auto practiceProgress = m_mainLayer->getChildByID("practice-progress-label");
            auto practiceBar = m_mainLayer->getChildByID("practice-progress-bar");

            if (practiceTitle && normalTitle) normalTitle->setPositionY(practiceTitle->getPositionY());
            if (practiceProgress && normalProgress) normalProgress->setPositionY(practiceProgress->getPositionY());
            if (practiceBar && normalBar) normalBar->setPositionY(practiceBar->getPositionY());

            if (normalTitle) normalTitle->setVisible(!isPractice);
            if (normalProgress) normalProgress->setVisible(!isPractice);
            if (normalBar) normalBar->setVisible(!isPractice);

            if (practiceTitle) practiceTitle->setVisible(isPractice);
            if (practiceProgress) practiceProgress->setVisible(isPractice);
            if (practiceBar) practiceBar->setVisible(isPractice);
        } else {
            auto progressBar = m_mainLayer->getChildByID("progress-bar");
            auto progressLabel = m_mainLayer->getChildByID("progress-label");
            auto modeLabel = m_mainLayer->getChildByID("mode-label");
            auto bestLabel = m_mainLayer->getChildByID("best-label");

            if (progressBar) progressBar->setPositionY(progressBar->getPositionY() - 26.0f);
            if (progressLabel) progressLabel->setPositionY(progressLabel->getPositionY() - 26.0f);
            if (modeLabel) modeLabel->setPositionY(modeLabel->getPositionY() - 26.0f);
            if (bestLabel) bestLabel->setPositionY(bestLabel->getPositionY() - 26.0f);
        };

        auto playTime = m_mainLayer->getChildByID("play-time");
        auto pointslabel = m_mainLayer->getChildByID("points-label");

        if (playTime) playTime->setPositionY(playTime->getPositionY() - 30.0f);
        if (pointslabel) pointslabel->setPositionY(pointslabel->getPositionY() - 30.0f);

        nodes::placeAd(m_mainLayer, AdType::Banner, Anchor::Top, { 0.0f, isLegacyPause ? -50.0f : -60.0f });
    }
};

PLAYERADS_HOOK_LISTENER(THIS_HOOK_ID);