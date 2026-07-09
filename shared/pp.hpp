#pragma once

#include "export.h"
#include "reflectcpp/include/rfl.hpp"

#include "GlobalNamespace/BeatmapKey.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"

namespace MetaCore::PP {
    /// @brief The BeatLeader ratings for speed-changing modifiers specifically
    struct BLSpeedModifiers {
        float ssPassRating;
        float ssAccRating;
        float ssTechRating;
        float fsPassRating;
        float fsAccRating;
        float fsTechRating;
        float sfPassRating;
        float sfAccRating;
        float sfTechRating;
    };

    /// @brief BeatLeader ranking information for a specific characteristic/difficulty of a map
    struct BLSongDiff {
        rfl::Rename<"difficultyName", std::string> difficulty;
        rfl::Rename<"modeName", std::string> characteristic;
        rfl::Rename<"status", int> rankedStatus;
        float stars;
        float predictedAcc;
        float passRating;
        float accRating;
        float techRating;
        std::map<std::string, float> modifierValues;
        std::optional<BLSpeedModifiers> modifiersRating;
    };

    /// @brief BeatLeader ranking information for a map
    struct BLSong {
        std::vector<BLSongDiff> difficulties;
    };

    /// @brief ScoreSaber ranking information for a specific characteristic/difficulty of a map (just a star rating)
    using SSSongDiff = float;

    /// @brief The acc to PP calculation cure for BeatLeader
    METACORE_EXPORT extern std::vector<std::pair<double, double>> const BeatLeaderCurve;
    /// @brief The acc to PP calculation cure for ScoreSaber
    METACORE_EXPORT extern std::vector<std::pair<double, double>> const ScoreSaberCurve;

    /// @brief Maps gameplay modifiers to their BeatLeader two-letter string representations
    /// @param modifiers The gameplay modifiers class instance
    /// @param speeds If speed-changing modifiers should be included
    /// @param failed If No Fail should be included, if enabled at all
    /// @return A consistently ordered vector of the lowercase representations of the modifiers
    METACORE_EXPORT std::vector<std::string> GetModStringsBL(GlobalNamespace::GameplayModifiers* modifiers, bool speeds, bool failed);
    /// @brief Calculates the curve value for a given accuracy
    /// @param accuracy The accuracy value from 0 to 1
    /// @param curve BeatLeaderCurve or ScoreSaberCurve
    /// @return The value of the curve at the given accuracy, interpolated if there is not an exact point in the curve
    METACORE_EXPORT float AccCurve(float accuracy, std::vector<std::pair<double, double>> const& curve);

    /// @brief Checks if a BeatLeader map characteristic/difficulty is ranked
    /// @param map The BeatLeader ranking information
    /// @return If the map characteristic/difficulty is ranked
    METACORE_EXPORT bool IsRanked(BLSongDiff const& map);
    /// @brief Checks if a ScoreSaber map characteristic/difficulty is ranked
    /// @param map The ScoreSaber ranking information
    /// @return If the map characteristic/difficulty is ranked
    METACORE_EXPORT bool IsRanked(SSSongDiff const& map);

    /// @brief Calculates the BeatLeader PP value for a given accuracy, map, and modifiers
    /// @param map The BeatLeader ranking information
    /// @param accuracy The accuracy value from 0 to 1
    /// @param modifiers The current gameplay modifiers
    /// @param failed If the player's health has reached 0, with or without No Fail
    /// @return The exact PP value
    METACORE_EXPORT float Calculate(BLSongDiff const& map, float accuracy, GlobalNamespace::GameplayModifiers* modifiers, bool failed);
    /// @brief Calculates the ScoreSaber PP value for a given accuracy, map, and modifiers
    /// @param map The ScoreSaber ranking information
    /// @param accuracy The accuracy value from 0 to 1
    /// @param modifiers The current gameplay modifiers
    /// @param failed If the player's health has reached 0, with or without No Fail
    /// @return The exact PP value
    METACORE_EXPORT float Calculate(SSSongDiff const& map, float accuracy, GlobalNamespace::GameplayModifiers* modifiers, bool failed);

    /// @brief Finds the BeatLeader and ScoreSaber ranking information for a given map characteristic/difficulty
    /// @param map The map characteristic/difficulty to query
    /// @param callback A callback called with the available ranking info once found
    METACORE_EXPORT void
    GetMapInfo(GlobalNamespace::BeatmapKey map, std::function<void(std::optional<BLSongDiff>, std::optional<SSSongDiff>)> callback);
}
