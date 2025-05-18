#pragma once

/**
 * @file Constants.h
 * @brief Defines shared, application-wide constants for NeuroSim.
 *
 * All constants are defined as `constexpr` within the `Constants` namespace
 * to ensure type safety, scope-localization, and easy maintenance.
 */
namespace Constants {

    /**
     * @brief Number of neurons in the simulation (for a 3×3 grid).
     */
    constexpr int NeuronCount = 3 * 3;

    /**
     * @brief Width of the heatmap visualization grid.
     *
     * This determines how many columns to generate when rendering the heatmap.
     */
    constexpr int HeatmapRenderWidth = 3;

    /**
     * @brief Height of the heatmap visualization grid.
     *
     * This determines how many rows to generate when rendering the heatmap.
     */
    constexpr int HeatmapRenderHeight = 3;

    /**
     * @brief Time step (in milliseconds) used for each simulation update.
     *
     * This value is passed to the Simulation::step(dt) method.
     */
    constexpr double SimulationTimeStep = 0.1;

    /**
     * @brief Interval (in milliseconds) between successive calls to updateSimulation().
     */
    constexpr int SimulationIntervalMs = 100;

    /**
     * @brief Default input current applied to each neuron.
     */
    constexpr double DefaultInputCurrent = 10.0;
}
