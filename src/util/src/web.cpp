#include "../web.hpp"

#include <cw.h>

#include <rhatt/prelude.h>

#include <dankmeme.argon/argon.hpp>

#include <asp/iter.hpp>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw::ads;

web::WebRequest request::withAuth(std::string token) {
    auto acc = argon::getGameAccountData();

    return cw::request::base()
        .param("account_id", acc.accountId)
        .param("authtoken", std::move(token))
        .param("user_id", acc.userId)
        .param("username", std::move(acc.username));
}

arc::Future<web::WebRequest> request::withAuthCo(std::string token) {
    co_return *co_await async::waitForMainThread<web::WebRequest>([t = std::move(token)]() mutable {
        return withAuth(std::move(t));
    });
}

void fetch::getLevel(int id, CopyableFunction<void(Result<GJGameLevel*>)>&& callback, bool download, GJGameLevel* data) {
    if (auto glm = GameLevelManager::sharedState()) {
        if (auto level = glm->getSavedLevel(id)) return callback(Ok(level));
    };

    auto reqForm = fmt::format("secret=Wmfd2893gb7&{}={}", download ? "levelID" : "type=0&str", id);

    if (argon::signedIn()) {
        auto const auth = argon::getGameAccountData();
        reqForm = fmt::format("{}&accountID={}&gjp2={}", reqForm, auth.accountId, auth.gjp2);
    };

    auto req = web::WebRequest()
                   .bodyString(reqForm)
                   .userAgent("");

    // this might be a little bit cursed owo
    async::spawn(
        req.post(fmt::format("https://www.boomlings.com/database/{}.php", download ? "downloadGJLevel22" : "getGJLevels21")),
        [cb = std::move(callback), id, download, data](web::WebResponse res) {
            if (res.error()) {
                log::error("Error getting user information: {}", res.errorMessage());
                return cb(Err("An error occurred while fetching user information"));
            };

            auto strRes = res.string();
            if (strRes.isErr()) return cb(Err(fmt::format("An error occurred while processing user information: {}", std::move(strRes).unwrapErr())));

            auto const str = std::move(strRes).unwrap();
            if (str == "-1") return cb(Err("Boomlings request returned an unknown error"));

            auto const parts = asp::iter::split(str, "#").collect();
            if (parts.empty()) return cb(Err("Malformed Boomlings response"));

            if (download) {
                if (!data) return cb(Err("Missing level data"));
                if (data->m_levelID != id) return cb(Err("Requested ID and level ID do not match"));

                auto const& levelStr = parts[0];
                auto dict = Ref(CCDictionary::create());

                auto const kv = asp::iter::split(levelStr, ":").collect();
                for (size_t i = 0; i + 1 < kv.size(); i += 2) dict->setObject(CCString::create(std::string{ kv[i + 1] }), std::string{ kv[i] });

                data->m_levelString = dict->charForKey(cw::fmtNum(4));

                cb(Ok(data));
            } else {
                auto levelsRaw = asp::iter::split(parts[0], "|").collect();
                if (levelsRaw.empty()) return cb(Err("No levels returned"));

                auto creatorsRaw = asp::iter::split(parts[1], "|").collect();
                if (creatorsRaw.empty()) return cb(Err("No creators returned"));

                auto const& levelStr = levelsRaw[0];
                auto const kvLvl = asp::iter::split(levelStr, ":").collect();

                auto const& creatorStr = creatorsRaw[0];
                auto const creatorData = asp::iter::split(creatorStr, ":").collect();

                auto dict = CCDictionary::create();
                for (size_t i = 0; i + 1 < kvLvl.size(); i += 2) dict->setObject(CCString::create(std::string{ kvLvl[i + 1] }), std::string{ kvLvl[i] });

                auto lvl = GJGameLevel::create(dict, download);  // siiiiigh
                lvl->m_creatorName = std::string{ creatorData[1] };
                lvl->setAccountID(numFromString<int>(creatorData[2]).unwrapOrDefault());

                cb(Ok(lvl));
            };
        }
    );
}

void fetch::getBadge(int id, CopyableFunction<void(Result<AdBadge>)>&& callback, bool local) {
    auto res = AdsDirector::get()->getBadge(id);
    if (res.isOk()) return callback(std::move(res));

    if (local) return callback(Err("Badge not found"));

    auto req = cw::request::base()
                   .param("id", id);

    async::spawn(
        req.get("https://ads.cheeseworks.gay/api/badge"),
        [cb = std::move(callback)](web::WebResponse res) {
            auto const fallback = [&cb](std::string err) {
                log::error("{}", err);
                return cb(Err(std::move(err)));
            };

            if (res.error()) return fallback(std::string{ res.errorMessage() });

            auto jsonRes = res.json();
            if (jsonRes.isErr()) return fallback(std::move(jsonRes).unwrapErr());

            auto json = std::move(jsonRes).unwrap();

            auto badgeRes = std::move(json).as<AdBadge>();
            if (badgeRes.isErr()) return fallback(std::move(badgeRes).unwrapErr());

            return cb(Ok(std::move(badgeRes).unwrap()));
        }
    );
}