#pragma once

namespace cw::ads {
    namespace hooks {
        void delegateHooks(std::string id, geode::utils::StringMap<std::shared_ptr<geode::Hook>> const& hooks);
        void toggleHooks(std::string_view id, bool on);
    };
};