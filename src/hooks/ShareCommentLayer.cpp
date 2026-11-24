#include <cw.h>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

#include <Geode/modify/ShareCommentLayer.hpp>

using namespace geode::prelude;
using namespace cw::ads;

#define THIS_ID "ShareCommentLayer"
inline constexpr auto THIS_HOOK_ID = THIS_ID;

class $modify(AdsShareCommentLayer, ShareCommentLayer) {
    PLAYERADS_DELEGATE_HOOKS(THIS_ID);

    bool init(std::string title, int charLimit, CommentType type, int ID, std::string desc) {
        if (!ShareCommentLayer::init(std::move(title), charLimit, type, ID, std::move(desc))) return false;

        if (auto adSquareLeft = nodes::placeAd(m_mainLayer, nodes::formatIDForAd(AdType::Square, Anchor::BottomLeft), AdType::Square, Anchor::Bottom, { -144.0f, 90.0f })) positionForCommentType(adSquareLeft, type);
        if (auto adSquareCenter = nodes::placeAd(m_mainLayer, AdType::Square, Anchor::Bottom, { 0.0f, 90.0f })) positionForCommentType(adSquareCenter, type);
        if (auto adSquareRight = nodes::placeAd(m_mainLayer, nodes::formatIDForAd(AdType::Square, Anchor::BottomRight), AdType::Square, Anchor::Bottom, { 144.0f, 90.0f })) positionForCommentType(adSquareRight, type);

        if (win::isWide()) {
            nodes::placeAd(m_mainLayer, AdType::Skyscraper, Anchor::Left, { 30.0f, 0.0f });
            nodes::placeAd(m_mainLayer, AdType::Skyscraper, Anchor::Right, { -30.0f, 0.0f });
        };

        return true;
    }

    // for da squarez
    void positionForCommentType(Advertisement* ad, CommentType type) {
        if (type == CommentType::FriendRequest) {
#ifdef CW_TESTING
            log::debug("comment type is friend request");
#endif
            if (ad) ad->setPositionY(ad->getPositionY() - 25.0f);
        };
    }
};

PLAYERADS_HOOK_LISTENER(THIS_HOOK_ID);