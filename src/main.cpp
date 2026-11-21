#include <cw.h>

#include <rhatt/prelude.h>

#include <ui/AdsDashboard.hpp>

#include <dankmeme.argon/argon.hpp>

#include <Geode/Geode.hpp>

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;
using namespace cw::ads;

namespace cw::ads {
    namespace nodes {
        static void addAdButton(CCNode* to, bool alt = true) {
            if (auto menu = typeinfo_cast<CCMenu*>(to)) {
                auto btn = CCMenuItemExt::createSpriteExtra(
                    CircleButtonSprite::createWithSpriteFrameName(
                        "adIcon.png"_spr,
                        0.875f,
                        CircleBaseColor::Green,
                        alt ? CircleBaseSize::MediumAlt : CircleBaseSize::Medium
                    ),
                    [](auto) {
                        pushSceneWithLayer(AdsDashboard::create());
                    }
                );
                btn->setID("ads-viewer-btn"_spr);

                menu->addChild(btn);
                menu->updateLayout();
            };
        }
    };
};

// $on_game(ModsLoaded) {
//     async::spawn(
//         cw::request::base().get("https://ads.cheeseworks.gay/api/badges"),
//         [](web::WebResponse res) {
//             if (res.error()) return log::error("{}", res.errorMessage());

//             auto jsonRes = res.json();
//             if (jsonRes.isErr()) return log::error("{}", std::move(jsonRes).unwrapErr());

//             auto json = std::move(jsonRes).unwrap();

//             auto arrayRes = std::move(json).asArray();
//             if (arrayRes.isErr()) return log::error("{}", std::move(arrayRes).unwrapErr());

//             auto array = std::move(arrayRes).unwrap();

//             for (auto& i : array) {
//                 auto badgeRes = std::move(i).as<AdBadge>();
//                 if (badgeRes.isErr()) return log::error("{}", std::move(badgeRes).unwrapErr());

//                 auto badge = std::move(badgeRes).unwrap();

//                 auto user = badge.user;
//                 AdsDirector::get()->saveBadge(user, std::move(badge));
//             };
//         });
// };

class $modify(PAHookMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        if (auto menu = getChildByID("bottom-menu")) nodes::addAdButton(menu);

        return true;
    }
};

class $modify(PAHookLevelInfoLayer, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        if (auto menu = getChildByID("left-side-menu")) nodes::addAdButton(menu, false);

        return true;
    }
};

Advertisement* nodes::placeAd(CCNode* to, std::optional<std::string> id, AdType type, Anchor anchor, CCPoint const& offset) {
    if (!to) return nullptr;

    if (auto ad = Advertisement::create(type)) {
        ad->setID(id.has_value() ? std::move(*id) : formatIDForAd(type, anchor));
        ad->setScale(0.975f);
        ad->setZOrder(HIGHEST_Z);

        to->addChildAtPosition(ad, anchor, offset, false);

        return ad;
    };

    return nullptr;
}

Advertisement* nodes::placeAd(cocos2d::CCNode* to, AdType type, geode::Anchor anchor, cocos2d::CCPoint const& offset) {
    return placeAd(to, std::nullopt, type, anchor, offset);
}