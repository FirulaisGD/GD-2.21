#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "includes.hpp"

using namespace geode::prelude;

bool safeMode = false;

class $modify(SafeModePlayLayer, PlayLayer) {

    void levelComplete() {
        bool testMode = this->m_isTestMode;
        if (safeMode) this->m_isTestMode = true;

        PlayLayer::levelComplete();

        this->m_isTestMode = testMode;
    }
    void showNewBest(bool p0, int p1, int p2, bool p3, bool p4, bool p5) {
        if (!safeMode) PlayLayer::showNewBest(p0, p1, p2, p3, p4, p5);
    }
};
$on_mod(Loaded) {
    safeMode = Mod::get()->getSettingValue<bool>("safe-mode");
    
    listenForSettingChanges("safe-mode", +[](bool enable) {
        safeMode = enable;
        log::info("Safe Mode: {}", enable ? "Activado" : "Desactivado");
    });
}