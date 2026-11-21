#pragma once

#include "Advertisement.hpp"

#include <util/ads.hpp>

#include <Geode/Geode.hpp>

namespace cw::ads::ui {
    class AdReportPopup final : public geode::Popup {
    private:
        struct Impl;
        std::unique_ptr<Impl> m_impl;

    protected:
        AdReportPopup();
        ~AdReportPopup();

        void onSubmitButton(geode::Button* sender, geode::LoadingSpinner* spinner);

        bool init(Ad ad);

    public:
        static AdReportPopup* create(Ad ad);
    };
};