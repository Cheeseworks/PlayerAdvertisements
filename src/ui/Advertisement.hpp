#pragma once

#include <rhatt/ui/nodes/WebSprite.hpp>

#include <util/ads.hpp>

#include <Geode/Geode.hpp>

namespace cw::ads::ui {
    class Advertisement final : public cocos2d::CCNode {
    private:
        struct Impl;
        std::unique_ptr<Impl> m_impl;

        void reload();

    protected:
        Advertisement();
        ~Advertisement();

        void onEnter() override;
        void onExit() override;

        bool init(cw::ads::AdType type);

    public:
        /**
         * Create a new advertisement
         * @param type The type of ad to create
         */
        static Advertisement* create(cw::ads::AdType type = cw::ads::AdType::Banner);

        /**
         * Load a random advertisement
         */
        void loadRandom();

        /**
         * Get the WebSprite associated with the advertisement
         */
        ::cw::ui::WebSprite* getAdSprite() const noexcept;

        /**
         * Handle the response from the advertisement fetch request
         * @param res The web response containing the advertisement data
         */
        void handleAdResponse(geode::utils::web::WebResponse const& res);
    };
};