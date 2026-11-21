#include "../hooks.hpp"

#include <cw.h>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw::ads;

void hooks::delegateHooks(std::string id, utils::StringMap<std::shared_ptr<Hook>> const& hooks) {
    std::vector<std::weak_ptr<Hook>> out;
    out.reserve(hooks.size());

    for (auto const& hook : hooks) out.push_back(hook.second);

    AdsDirector::get()->registerHooks(std::move(id), std::move(out));
}

void hooks::toggleHooks(std::string_view id, bool on) {
    for (auto const& hook : AdsDirector::get()->getHooks(id)) {
        if (auto h = hook.lock()) (void)h->toggle(on);
    };
}