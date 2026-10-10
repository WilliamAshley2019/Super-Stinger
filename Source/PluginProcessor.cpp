#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PresetManager.h"

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout WASPAlphaAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    using namespace WaspParams;

    // ===== Oscillator 1 =====
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ OSC1_SHAPE, 1 }, "Osc-1 Shape",
        juce::StringArray{ "Saw", "Square", "Triangle", "Sine", "303-Saw" }, 0));
    layout.add(std::make_unique<juce::AudioParameterInt>(
        juce::ParameterID{ OSC1_COARSE, 1 }, "Osc-1 Coarse", -24, 24, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ OSC1_FINE, 1 }, "Osc-1 Fine",
        juce::NormalisableRange<float>(-100.0f, 100.0f, 1.0f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ OSC1_AMOUNT, 1 }, "Osc-1 Amount",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 1.0f));

    // ===== Oscillator 2 =====
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ OSC2_SHAPE, 1 }, "Osc-2 Shape",
        juce::StringArray{ "Saw", "Square", "Triangle", "Sine", "303-Saw" }, 0));
    layout.add(std::make_unique<juce::AudioParameterInt>(
        juce::ParameterID{ OSC2_COARSE, 1 }, "Osc-2 Coarse", -24, 24, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ OSC2_FINE, 1 }, "Osc-2 Fine",
        juce::NormalisableRange<float>(-100.0f, 100.0f, 1.0f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ OSC2_AMOUNT, 1 }, "Osc-2 Amount",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 1.0f));

    // ===== Oscillator 3 (sub / noise) =====
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ OSC3_SHAPE, 1 }, "Osc-3 Shape",
        juce::StringArray{ "Sub", "Sub-Sub", "Noise" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ OSC3_AMOUNT, 1 }, "Osc-3 Amount",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));

    // ===== Mix / Modulation =====
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ OSC_MIX, 1 }, "Osc Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ PULSE_WIDTH, 1 }, "Pulse Width",
        juce::NormalisableRange<float>(0.05f, 0.95f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FM_AMOUNT, 1 }, "FM",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ RM_AMOUNT, 1 }, "RM",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));

    // ===== Amp Envelope =====
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ AMP_ATTACK, 1 }, "Amp Attack",
        juce::NormalisableRange<float>(0.001f, 8.0f, 0.001f, 0.4f), 0.01f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ AMP_DECAY, 1 }, "Amp Decay",
        juce::NormalisableRange<float>(0.001f, 8.0f, 0.001f, 0.4f), 0.1f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ AMP_SUSTAIN, 1 }, "Amp Sustain",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.7f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ AMP_RELEASE, 1 }, "Amp Release",
        juce::NormalisableRange<float>(0.001f, 8.0f, 0.001f, 0.4f), 0.3f));

    // ===== Filter Envelope =====
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_ATTACK, 1 }, "Filter Attack",
        juce::NormalisableRange<float>(0.001f, 8.0f, 0.001f, 0.4f), 0.01f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_DECAY, 1 }, "Filter Decay",
        juce::NormalisableRange<float>(0.001f, 8.0f, 0.001f, 0.4f), 0.3f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_SUSTAIN, 1 }, "Filter Sustain",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_RELEASE, 1 }, "Filter Release",
        juce::NormalisableRange<float>(0.001f, 8.0f, 0.001f, 0.4f), 0.5f));

    // ===== Filter 1 =====
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_KEYTRACK, 1 }, "Filter Keytrack",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ FLT_TYPE, 1 }, "Filter Type",
        juce::StringArray{ "LP12", "LP24", "HP12", "BP12" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_CUTOFF, 1 }, "Cutoff",
        juce::NormalisableRange<float>(20.0f, 18000.0f, 0.1f, 0.3f), 2000.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_RESO, 1 }, "Resonance",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_ENV_AMT, 1 }, "Envelope Amount",
        juce::NormalisableRange<float>(-1.0f, 1.0f, 0.001f), 0.5f));

    // ===== Filter 2 =====
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT2_KEYTRACK, 1 }, "Filter 2 Keytrack",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ FLT2_TYPE, 1 }, "Filter 2 Type",
        juce::StringArray{ "LP12", "LP24", "HP12", "BP12" }, 2));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT2_CUTOFF, 1 }, "Cutoff 2",
        juce::NormalisableRange<float>(20.0f, 18000.0f, 0.1f, 0.3f), 4000.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT2_RESO, 1 }, "Resonance 2",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT2_ENV_AMT, 1 }, "Envelope Amount 2",
        juce::NormalisableRange<float>(-1.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ FLT_ROUTING, 1 }, "Filter Routing",
        juce::StringArray{ "Filter 1 Only", "Filter 2 Only", "Series (1->2)", "Parallel" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_PARALLEL_MIX, 1 }, "Filter Parallel Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));

    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ FLT_MODEL, 1 }, "Filter Model",
        juce::StringArray{ "Ladder", "Chamberlin" }, 0));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ FLT2_MODEL, 1 }, "Filter 2 Model",
        juce::StringArray{ "Ladder", "Chamberlin" }, 0));

    // ===== LFO 1 =====
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ LFO1_SHAPE, 1 }, "Lfo-1 Shape",
        juce::StringArray{ "Sine", "Triangle", "Saw", "RevSaw", "Square", "S&H" }, 0));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ LFO1_TARGET, 1 }, "Lfo-1 Target",
        juce::StringArray{ "Pitch", "Osc1 Pitch", "Osc2 Pitch", "Pulse Width", "Filter", "Amp", "Resonance" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ LFO1_AMOUNT, 1 }, "Lfo-1 Amount",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ LFO1_FREQ, 1 }, "Lfo-1 Freq",
        juce::NormalisableRange<float>(0.01f, 20.0f, 0.001f, 0.4f), 2.0f));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ LFO1_SYNC, 1 }, "Lfo-1 Sync", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ LFO1_RESET, 1 }, "Lfo-1 Reset", false));

    // ===== LFO 2 =====
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ LFO2_SHAPE, 1 }, "Lfo-2 Shape",
        juce::StringArray{ "Sine", "Triangle", "Saw", "RevSaw", "Square", "S&H" }, 0));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ LFO2_TARGET, 1 }, "Lfo-2 Target",
        juce::StringArray{ "Pitch", "Osc1 Pitch", "Osc2 Pitch", "Pulse Width", "Filter", "Amp", "Resonance" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ LFO2_AMOUNT, 1 }, "Lfo-2 Amount",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ LFO2_FREQ, 1 }, "Lfo-2 Freq",
        juce::NormalisableRange<float>(0.01f, 20.0f, 0.001f, 0.4f), 3.0f));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ LFO2_SYNC, 1 }, "Lfo-2 Sync", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ LFO2_RESET, 1 }, "Lfo-2 Reset", false));

    // ===== Distortion =====
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ DIST_ON, 1 }, "Distortion On", false));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DIST_DRIVE, 1 }, "Dist Drive",
        juce::NormalisableRange<float>(1.0f, 20.0f, 0.01f), 1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DIST_TONE, 1 }, "Dist Tone",
        juce::NormalisableRange<float>(200.0f, 8000.0f, 1.0f, 0.4f), 2000.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DIST_MIX, 1 }, "Dist Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 1.0f));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ DIST_TYPE, 1 }, "Dist Type",
        juce::StringArray{ "Soft", "Hard" }, 0));

    // ===== Character =====
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DUAL_VOICE, 1 }, "Dual Voice",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ WASP_CHAR, 1 }, "Wasp",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ VCO_BINARY, 1 }, "VCO Binary",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));

    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ CMOS_FILTER, 1 }, "CMOS Filter", false));

    // ===== CV =====
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ CV_AMOUNT, 1 }, "CV Amount",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ CV_TARGET, 1 }, "CV Target",
        juce::StringArray{ "Filter Cutoff", "Osc2 Pitch", "Pulse Width", "Amp" }, 0));

    // ===== Mod Env =====
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ MODENV_ATTACK, 1 }, "Mod Env Attack",
        juce::NormalisableRange<float>(0.001f, 4.0f, 0.001f, 0.4f), 0.01f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ MODENV_DECAY, 1 }, "Mod Env Decay",
        juce::NormalisableRange<float>(0.001f, 4.0f, 0.001f, 0.4f), 0.2f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ MODENV_AMOUNT, 1 }, "Mod Env Amount",
        juce::NormalisableRange<float>(-1.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ MODENV_DEST, 1 }, "Mod Env Destination",
        juce::StringArray{ "Pulse Width", "LFO1 Amount", "Osc1 Level", "Osc2 Pitch" }, 0));

    // ===== Velocity =====
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ VEL_TO_AMP, 1 }, "Velocity to Amp",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ VEL_TO_FILTER, 1 }, "Velocity to Filter",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));

    // ===== LFO delays =====
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ LFO1_DELAY, 1 }, "Lfo-1 Delay",
        juce::NormalisableRange<float>(0.0f, 4.0f, 0.001f, 0.5f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ LFO2_DELAY, 1 }, "Lfo-2 Delay",
        juce::NormalisableRange<float>(0.0f, 4.0f, 0.001f, 0.5f), 0.0f));

    // ===== Legacy detune =====
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DUAL_DETUNE, 1 }, "Dual Voice Detune",
        juce::NormalisableRange<float>(0.0f, 50.0f, 0.1f), 8.0f));

    // ===== Delay =====
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DELAY_TIME_MS, 1 }, "Delay Time",
        juce::NormalisableRange<float>(1.0f, 2000.0f, 0.1f, 0.35f), 350.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DELAY_FEEDBACK, 1 }, "Delay Feedback",
        juce::NormalisableRange<float>(0.0f, 0.95f, 0.001f), 0.3f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DELAY_MIX, 1 }, "Delay Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));

    // ===== Master =====
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ MASTER_VOLUME, 1 }, "Master Volume",
        juce::NormalisableRange<float>(-60.0f, 6.0f, 0.01f, 3.0f), 0.0f));

    // ===== DX FM =====
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ DXFM_ENABLE, 1 }, "DX FM Enable", false));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_BLEND, 1 }, "DX FM Blend",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_CAR_ATK, 1 }, "DX Carrier Attack",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_CAR_DEC, 1 }, "DX Carrier Decay",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_CAR_REL, 1 }, "DX Carrier Release",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.3f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_WAVE, 1 }, "DX Waveform",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_MOD_INIT, 1 }, "DX Mod Init",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_MOD_DEC, 1 }, "DX Mod Decay",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_MOD_SUS, 1 }, "DX Mod Sus",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_MOD_REL, 1 }, "DX Mod Rel",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_MOD_VEL, 1 }, "DX Mod Vel",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_COARSE, 1 }, "DX Coarse",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_FINE, 1 }, "DX Fine",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_MOD_THRU, 1 }, "DX Mod Thru",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_OCTAVE, 1 }, "DX Octave",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_TUNE, 1 }, "DX Fine Tune",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));

    // ===== Voice Stack =====
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ VOICE_CONFIG, 1 }, "Voice Config",
        juce::StringArray{ "Single", "Dual", "Quad", "Super Saw 7", "Sub Layer" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ VOICE_SPREAD, 1 }, "Voice Spread",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));

    // ===== CPU Saver =====
    // All eleven toggles: sources, filters, modulators, effects, character.
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ BYPASS_FILTER1,   1 }, "Bypass Filter 1", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ BYPASS_FILTER2,   1 }, "Bypass Filter 2", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ BYPASS_DELAY,     1 }, "Bypass Delay", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ BYPASS_DIST,      1 }, "Bypass Distortion", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ BYPASS_LFO1,      1 }, "Bypass LFO 1", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ BYPASS_LFO2,      1 }, "Bypass LFO 2", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ BYPASS_MODENV,    1 }, "Bypass Mod Env", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ BYPASS_CV,        1 }, "Bypass CV", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ BYPASS_DUALVOICE, 1 }, "Bypass Dual Voice", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ BYPASS_WASPCHAR,  1 }, "Bypass Wasp Char", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ BYPASS_VCOBIN,    1 }, "Bypass VCO Binary", false));

    return layout;
}

//==============================================================================
WASPAlphaAudioProcessor::WASPAlphaAudioProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    apvts(*this, nullptr, "WASPAlphaState", createParameterLayout())
{
    using namespace WaspParams;
    for (auto* param : apvts.processor.getParameters())
    {
        if (auto* p = dynamic_cast<juce::RangedAudioParameter*> (param))
            apvts.addParameterListener(p->getParameterID(), this);
    }
    presetManager = std::make_unique<PresetManager>(apvts);
}

WASPAlphaAudioProcessor::~WASPAlphaAudioProcessor()
{
    presetManager.reset();
    for (auto* param : apvts.processor.getParameters())
    {
        if (auto* p = dynamic_cast<juce::RangedAudioParameter*> (param))
            apvts.removeParameterListener(p->getParameterID(), this);
    }
}

//==============================================================================
void WASPAlphaAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    sampleRate = juce::jlimit(8000.0, 384000.0, sampleRate);
    samplesPerBlock = juce::jmax(1, samplesPerBlock);

    currentSampleRate = sampleRate;
    currentBlockSize = samplesPerBlock;

    for (auto& v : voices)
    {
        v.setSampleRate(sampleRate);
        v.isActive = false;
        v.noteHeld = false;
        v.filter.reset();
        v.filter2.reset();
        v.chamberlinF.reset();
        v.chamberlinF2.reset();
        v.stackOsc1.reset();
        v.stackOsc2.reset();
        v.superSaw1.reset();
        v.superSaw2.reset();
        v.dx.reset();
    }

    lfo1.setSampleRate(sampleRate);
    lfo2.setSampleRate(sampleRate);

    delayL.prepare(sampleRate);
    delayR.prepare(sampleRate);

    distDryL.assign((size_t)samplesPerBlock, 0.0f);
    distDryR.assign((size_t)samplesPerBlock, 0.0f);

    juce::dsp::ProcessSpec spec{ sampleRate, (juce::uint32)samplesPerBlock, 2u };
    distToneFilter.prepare(spec);
    *distToneFilter.state = *juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(sampleRate, 1000.0f);
    lastDistTone = 1000.0f;

    pitchBendGlobal = 1.0;
    modWheelValue = 0.0f;

    updateDxParams();
    isPrepared = true;
}

void WASPAlphaAudioProcessor::releaseResources() { isPrepared = false; }

bool WASPAlphaAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannelSet() != juce::AudioChannelSet::disabled())
        return false;
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void WASPAlphaAudioProcessor::parameterChanged(const juce::String& paramID, float newValue)
{
    juce::ignoreUnused(paramID, newValue);
}

//==============================================================================
void WASPAlphaAudioProcessor::updateDxParams()
{
    using namespace WaspParams;
    const float ifs = (float)(1.0 / currentSampleRate);

    const float pOctave = apvts.getRawParameterValue(DXFM_OCTAVE)->load();
    const float pTune = apvts.getRawParameterValue(DXFM_TUNE)->load();
    const float pCoarse = apvts.getRawParameterValue(DXFM_COARSE)->load();
    const float pFine = apvts.getRawParameterValue(DXFM_FINE)->load();
    const float pInit = apvts.getRawParameterValue(DXFM_MOD_INIT)->load();
    const float pModDec = apvts.getRawParameterValue(DXFM_MOD_DEC)->load();
    const float pModRel = apvts.getRawParameterValue(DXFM_MOD_REL)->load();
    const float pCarAtk = apvts.getRawParameterValue(DXFM_CAR_ATK)->load();
    const float pCarDec = apvts.getRawParameterValue(DXFM_CAR_DEC)->load();
    const float pCarRel = apvts.getRawParameterValue(DXFM_CAR_REL)->load();
    const float pWave = apvts.getRawParameterValue(DXFM_WAVE)->load();
    const float pThru = apvts.getRawParameterValue(DXFM_MOD_THRU)->load();

    const float octaveShift = std::floor(pOctave * 6.9f) - 2.0f;
    const float fineShift = (pTune + pTune) - 1.0f;

    dxTune = 8.175798915644f * ifs * std::pow(2.0f, octaveShift) * std::pow(2.0f, fineShift / 12.0f);

    float rati = std::floor(40.1f * pCoarse * pCoarse);
    float ratf;
    if (pFine < 0.5f) { ratf = 0.2f * pFine * pFine; }
    else
    {
        int idx = static_cast<int>(8.9f * pFine);
        switch (idx)
        {
        case 4: ratf = 0.25f;       break;
        case 5: ratf = 0.33333333f; break;
        case 6: ratf = 0.50f;       break;
        case 7: ratf = 0.66666667f; break;
        default: ratf = 0.75f;      break;
        }
    }
    dxRatio = 1.570796326795f * (rati + ratf);

    dxDepth = 0.0002f * pInit * pInit;
    dxDept2 = 0.0002f * apvts.getRawParameterValue(DXFM_MOD_SUS)->load() * apvts.getRawParameterValue(DXFM_MOD_SUS)->load();

    dxCatt = 1.0f - std::exp(-ifs * std::exp(8.0f - 8.0f * pCarAtk));
    dxCdec = (pCarDec > 0.98f) ? 1.0f : std::exp(-ifs * std::exp(5.0f - 8.0f * pCarDec));
    dxCrel = std::exp(-ifs * std::exp(5.0f - 5.0f * pCarRel));
    dxMdec = 1.0f - std::exp(-ifs * std::exp(6.0f - 7.0f * pModDec));
    dxMrel = 1.0f - std::exp(-ifs * std::exp(5.0f - 8.0f * pModRel));

    dxRich = 0.50f - 3.0f * pWave * pWave;
    dxModMix = 0.25f * pThru * pThru;
    dxVolume = 0.0035f;
}

void WASPAlphaAudioProcessor::initDxVoice(WaspVoice& v, int /*midiNote*/, int velocity)
{
    auto& d = v.dx;
    d.reset();
    d.active = true;

    const double tuning = v.tuning;
    const float modVel = apvts.getRawParameterValue(WaspParams::DXFM_MOD_VEL)->load();
    const float velScale = 64.0f + modVel * (static_cast<float>(velocity) - 64.0f);
    const double keyTrack = std::min(tuning, 50.0);

    d.menv = static_cast<double>(dxDepth) * keyTrack * velScale;
    d.mlev = static_cast<double>(dxDept2) * keyTrack * velScale;
    d.mdec = static_cast<double>(dxMdec);

    d.dcar = static_cast<double>(dxTune) * pitchBendGlobal * tuning;
    d.dmod = static_cast<double>(dxRatio) * d.dcar;
    d.mod0 = 0.0;
    d.mod1 = std::sin(d.dmod);
    d.dmod = 2.0 * std::cos(d.dmod);

    const float wave = apvts.getRawParameterValue(WaspParams::DXFM_WAVE)->load();
    d.env = (1.5f - wave) * dxVolume * (static_cast<float>(velocity) + 10.0f);
    d.catt = static_cast<double>(dxCatt);
    d.cenv = 0.0;
    d.cdec = static_cast<double>(dxCdec);
}

void WASPAlphaAudioProcessor::renderDxVoice(WaspVoice& v, float& out, float ampEnv)
{
    auto& d = v.dx;
    if (!d.active && d.env < 0.0003) return;

    d.env *= d.cdec;
    d.cenv += d.catt * (d.env - d.cenv);

    double x = d.dmod * d.mod0 - d.mod1;
    d.mod1 = d.mod0;
    d.mod0 = x;

    d.menv += d.mdec * (d.mlev - d.menv);

    const double phase = d.carPhase + d.dcar + x * d.menv;
    double wrapped = phase;
    while (wrapped > 1.0) wrapped -= 2.0;
    while (wrapped < -1.0) wrapped += 2.0;
    d.carPhase = wrapped;

    const double p2 = wrapped * wrapped;
    const double p3 = p2 * wrapped;
    const float sine = static_cast<float>(wrapped + p3 * (dxRich * p2 - 1.0 - dxRich));
    const float mix = sine + dxModMix * static_cast<float>(d.mod1);

    out += static_cast<float>(d.cenv * static_cast<double>(mix)) * ampEnv;

    if (d.cenv < 0.0003 && !v.noteHeld)
        d.active = false;
}

int WASPAlphaAudioProcessor::findFreeVoice()
{
    for (int i = 0; i < MAX_VOICES; ++i)
        if (!voices[i].isActive) return i;

    int    stealIdx = -1;
    double quietest = 1.0e9;
    for (int i = 0; i < MAX_VOICES; ++i)
    {
        if (!voices[i].noteHeld && voices[i].ampEnv.value < quietest)
        {
            quietest = voices[i].ampEnv.value;
            stealIdx = i;
        }
    }
    if (stealIdx >= 0) return stealIdx;

    stealIdx = 0;
    quietest = voices[0].ampEnv.value;
    for (int i = 1; i < MAX_VOICES; ++i)
    {
        if (voices[i].ampEnv.value < quietest)
        {
            quietest = voices[i].ampEnv.value;
            stealIdx = i;
        }
    }
    return stealIdx;
}

int WASPAlphaAudioProcessor::findVoiceForNote(int midiNote)
{
    for (int i = 0; i < MAX_VOICES; ++i)
        if (voices[i].noteHeld && voices[i].midiNote == midiNote) return i;
    return -1;
}

void WASPAlphaAudioProcessor::handleMidiEvent(const juce::MidiMessage& msg)
{
    if (msg.isNoteOn())
    {
        int note = msg.getNoteNumber();
        double freq = juce::MidiMessage::getMidiNoteInHertz(note);

        lfo1.resetDelay();
        lfo2.resetDelay();
        if (apvts.getRawParameterValue(WaspParams::LFO1_RESET)->load() > 0.5f) lfo1.reset();
        if (apvts.getRawParameterValue(WaspParams::LFO2_RESET)->load() > 0.5f) lfo2.reset();

        float vel = juce::jlimit(0.0f, 1.0f, msg.getFloatVelocity());
        int vi = findFreeVoice();
        voices[vi].noteOn(note, freq, vel);
        voices[vi].filter.reset();
        voices[vi].filter2.reset();
        voices[vi].chamberlinF.reset();
        voices[vi].chamberlinF2.reset();

        if (apvts.getRawParameterValue(WaspParams::DXFM_ENABLE)->load() > 0.5f)
            initDxVoice(voices[vi], note, msg.getVelocity());
    }
    else if (msg.isNoteOff())
    {
        int vi = findVoiceForNote(msg.getNoteNumber());
        if (vi >= 0)
        {
            voices[vi].noteOff();
            auto& d = voices[vi].dx;
            if (d.active)
            {
                d.cdec = static_cast<double>(dxCrel);
                d.mlev = 0.0;
                d.mdec = static_cast<double>(dxMrel);
            }
        }
    }
    else if (msg.isAllNotesOff() || msg.isAllSoundOff())
    {
        for (auto& v : voices)
        {
            v.noteOff();
            v.isActive = false;
            v.noteHeld = false;
            v.dx.reset();
        }
    }
    else if (msg.isController() && msg.getControllerNumber() == 1)
    {
        modWheelValue = static_cast<float>(msg.getControllerValue()) / 127.0f;
    }
    else if (msg.isPitchWheel())
    {
        const float bend = (static_cast<float>(msg.getPitchWheelValue()) - 8192.0f) / 8192.0f;
        pitchBendGlobal = static_cast<double>(std::pow(2.0f, bend * 2.0f / 12.0f));
    }
}

//==============================================================================
static double midiToHz(int note, int coarse, float fineCents)
{
    double totalCents = (double)(note + coarse) * 100.0 + (double)fineCents;
    return 440.0 * std::pow(2.0, (totalCents - 6900.0) / 1200.0);
}

static float softClip(float x, float drive)
{
    float driven = x * drive;
    float ax = std::abs(driven);
    float z = driven * (27.0f + ax * ax) / (27.0f + 9.0f * ax * ax);
    // Partial drive compensation: louder drive stays louder, but the wet
    // signal doesn't collapse to nothing. sqrt gives a natural "more drive,
    // more output" curve without pinning the meter.
    return z / std::sqrt(drive);
}

static float hardClip(float x, float drive)
{
    const float driven = x * drive;
    return juce::jlimit(-1.0f, 1.0f, driven) / std::sqrt(drive);
}

static float processFilterStage(int model, WaspFilter& ladder, ChamberlinFilter& cham,
    float in, float cutoff, float reso, int type, bool cmos)
{
    if (model == 1)
        return cham.process(in, cutoff, reso, type);
    return ladder.process(in, cutoff, reso, type, cmos);
}

//==============================================================================
void WASPAlphaAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    if (!isPrepared) return;

    using namespace WaspParams;

    // ===== Oscillator parameter reads =====
    float pOsc1Shape = apvts.getRawParameterValue(OSC1_SHAPE)->load();
    float pOsc1Coarse = apvts.getRawParameterValue(OSC1_COARSE)->load();
    float pOsc1Fine = apvts.getRawParameterValue(OSC1_FINE)->load();
    float pOsc1Amt = apvts.getRawParameterValue(OSC1_AMOUNT)->load();

    float pOsc2Shape = apvts.getRawParameterValue(OSC2_SHAPE)->load();
    float pOsc2Coarse = apvts.getRawParameterValue(OSC2_COARSE)->load();
    float pOsc2Fine = apvts.getRawParameterValue(OSC2_FINE)->load();
    float pOsc2Amt = apvts.getRawParameterValue(OSC2_AMOUNT)->load();

    float pOsc3Shape = apvts.getRawParameterValue(OSC3_SHAPE)->load();
    float pOsc3Amt = apvts.getRawParameterValue(OSC3_AMOUNT)->load();
    float pOscMix = apvts.getRawParameterValue(OSC_MIX)->load();
    float pPW = apvts.getRawParameterValue(PULSE_WIDTH)->load();
    float pFM = apvts.getRawParameterValue(FM_AMOUNT)->load();
    float pRM = apvts.getRawParameterValue(RM_AMOUNT)->load();

    // ===== Envelope parameter reads =====
    float pAmpA = apvts.getRawParameterValue(AMP_ATTACK)->load();
    float pAmpD = apvts.getRawParameterValue(AMP_DECAY)->load();
    float pAmpS = apvts.getRawParameterValue(AMP_SUSTAIN)->load();
    float pAmpR = apvts.getRawParameterValue(AMP_RELEASE)->load();
    float pFltA = apvts.getRawParameterValue(FLT_ATTACK)->load();
    float pFltD = apvts.getRawParameterValue(FLT_DECAY)->load();
    float pFltS = apvts.getRawParameterValue(FLT_SUSTAIN)->load();
    float pFltR = apvts.getRawParameterValue(FLT_RELEASE)->load();

    // ===== Filter parameter reads =====
    float pFltKT = apvts.getRawParameterValue(FLT_KEYTRACK)->load();
    float pFltType = apvts.getRawParameterValue(FLT_TYPE)->load();
    float pCutoff = apvts.getRawParameterValue(FLT_CUTOFF)->load();
    float pReso = apvts.getRawParameterValue(FLT_RESO)->load();
    float pFltEnv = apvts.getRawParameterValue(FLT_ENV_AMT)->load();

    float pFlt2KT = apvts.getRawParameterValue(FLT2_KEYTRACK)->load();
    float pFlt2Type = apvts.getRawParameterValue(FLT2_TYPE)->load();
    float pCutoff2 = apvts.getRawParameterValue(FLT2_CUTOFF)->load();
    float pReso2 = apvts.getRawParameterValue(FLT2_RESO)->load();
    float pFlt2Env = apvts.getRawParameterValue(FLT2_ENV_AMT)->load();
    int   pFltRoute = (int)apvts.getRawParameterValue(FLT_ROUTING)->load();
    float pFltParMix = apvts.getRawParameterValue(FLT_PARALLEL_MIX)->load();
    int   pFltModel = (int)apvts.getRawParameterValue(FLT_MODEL)->load();
    int   pFlt2Model = (int)apvts.getRawParameterValue(FLT2_MODEL)->load();

    // ===== Delay and output =====
    float pDelayTimeMs = apvts.getRawParameterValue(DELAY_TIME_MS)->load();
    float pDelayFb = apvts.getRawParameterValue(DELAY_FEEDBACK)->load();
    float pDelayMix = apvts.getRawParameterValue(DELAY_MIX)->load();
    float pMasterVolDb = apvts.getRawParameterValue(MASTER_VOLUME)->load();
    float pMasterGain = juce::Decibels::decibelsToGain(pMasterVolDb, -60.0f);

    // ===== LFO 1 parameter reads (the missing set) =====
    float pL1Shape = apvts.getRawParameterValue(LFO1_SHAPE)->load();
    float pL1Target = apvts.getRawParameterValue(LFO1_TARGET)->load();
    float pL1Amt = apvts.getRawParameterValue(LFO1_AMOUNT)->load();
    float pL1Freq = apvts.getRawParameterValue(LFO1_FREQ)->load();

    // ===== LFO 2 parameter reads =====
    float pL2Shape = apvts.getRawParameterValue(LFO2_SHAPE)->load();
    float pL2Target = apvts.getRawParameterValue(LFO2_TARGET)->load();
    float pL2Amt = apvts.getRawParameterValue(LFO2_AMOUNT)->load();
    float pL2Freq = apvts.getRawParameterValue(LFO2_FREQ)->load();

    // ===== Distortion / character =====
    float pDistOn = apvts.getRawParameterValue(DIST_ON)->load();
    float pDistDrv = apvts.getRawParameterValue(DIST_DRIVE)->load();
    int   pDistType = (int)apvts.getRawParameterValue(DIST_TYPE)->load();
    float pDistTone = apvts.getRawParameterValue(DIST_TONE)->load();
    float pDistMix = apvts.getRawParameterValue(DIST_MIX)->load();
    float pDualV = apvts.getRawParameterValue(DUAL_VOICE)->load();
    float pWasp = apvts.getRawParameterValue(WASP_CHAR)->load();
    float pVCOBin = apvts.getRawParameterValue(VCO_BINARY)->load();
    bool  pCmos = apvts.getRawParameterValue(CMOS_FILTER)->load() > 0.5f;
    float pCVAmt = apvts.getRawParameterValue(CV_AMOUNT)->load();
    int   pCVTarget = (int)apvts.getRawParameterValue(CV_TARGET)->load();

    // ===== Mod Env =====
    float pModEnvA = apvts.getRawParameterValue(MODENV_ATTACK)->load();
    float pModEnvD = apvts.getRawParameterValue(MODENV_DECAY)->load();
    float pModEnvAmt = apvts.getRawParameterValue(MODENV_AMOUNT)->load();
    int   pModEnvDest = (int)apvts.getRawParameterValue(MODENV_DEST)->load();

    // ===== Velocity =====
    float pVelAmp = apvts.getRawParameterValue(VEL_TO_AMP)->load();
    float pVelFlt = apvts.getRawParameterValue(VEL_TO_FILTER)->load();

    // ===== LFO delays + detune =====
    float pLfo1Delay = apvts.getRawParameterValue(LFO1_DELAY)->load();
    float pLfo2Delay = apvts.getRawParameterValue(LFO2_DELAY)->load();
    float pDualDetune = apvts.getRawParameterValue(DUAL_DETUNE)->load();

    // ===== Voice stack =====
    int         voiceConfigInt = (int)apvts.getRawParameterValue(VOICE_CONFIG)->load();
    float       pVoiceSpread = apvts.getRawParameterValue(VOICE_SPREAD)->load();
    VoiceConfig voiceConfig = (VoiceConfig)juce::jlimit(0, 4, voiceConfigInt);

    // ===== DX FM =====
    const bool  dxOn = apvts.getRawParameterValue(DXFM_ENABLE)->load() > 0.5f;
    const float dxBlend = apvts.getRawParameterValue(DXFM_BLEND)->load();

    // ===== CPU Saver bypass reads =====
    const bool bpFilter1 = apvts.getRawParameterValue(BYPASS_FILTER1)->load() > 0.5f;
    const bool bpFilter2 = apvts.getRawParameterValue(BYPASS_FILTER2)->load() > 0.5f;
    const bool bpDelay = apvts.getRawParameterValue(BYPASS_DELAY)->load() > 0.5f;
    const bool bpDist = apvts.getRawParameterValue(BYPASS_DIST)->load() > 0.5f;
    const bool bpLfo1 = apvts.getRawParameterValue(BYPASS_LFO1)->load() > 0.5f;
    const bool bpLfo2 = apvts.getRawParameterValue(BYPASS_LFO2)->load() > 0.5f;
    const bool bpModEnv = apvts.getRawParameterValue(BYPASS_MODENV)->load() > 0.5f;
    const bool bpCv = apvts.getRawParameterValue(BYPASS_CV)->load() > 0.5f;
    const bool bpDualV = apvts.getRawParameterValue(BYPASS_DUALVOICE)->load() > 0.5f;
    const bool bpWaspChar = apvts.getRawParameterValue(BYPASS_WASPCHAR)->load() > 0.5f;
    const bool bpVcoBin = apvts.getRawParameterValue(BYPASS_VCOBIN)->load() > 0.5f;

    if (dxOn) updateDxParams();
    if (buffer.getNumChannels() != 2) return;

    float* left = buffer.getWritePointer(0);
    float* right = buffer.getWritePointer(1);
    int    numSamples = buffer.getNumSamples();

    auto midiIt = midiMessages.begin();

    for (int sample = 0; sample < numSamples; ++sample)
    {
        while (midiIt != midiMessages.end())
        {
            auto meta = *midiIt;
            if (meta.samplePosition > sample) break;
            handleMidiEvent(meta.getMessage());
            ++midiIt;
        }

        // ===== LFO 1 tick =====
        double lfo1Gain = 0.0;
        double lfo1Val = 0.0;
        if (!bpLfo1)
        {
            lfo1Gain = lfo1.delayGain((double)pLfo1Delay);
            lfo1Val = lfo1.tick((double)pL1Freq, (int)pL1Shape) * (double)pL1Amt * lfo1Gain;
        }

        // ===== LFO 2 tick =====
        double lfo2Gain = 0.0;
        double lfo2Val = 0.0;
        if (!bpLfo2)
        {
            lfo2Gain = lfo2.delayGain((double)pLfo2Delay);
            lfo2Val = lfo2.tick((double)pL2Freq, (int)pL2Shape) * (double)pL2Amt * lfo2Gain;
        }

        float mixOut = 0.0f;
        int   activeCount = 0;

        for (auto& v : voices)
        {
            if (!v.isActive) continue;

            double f1 = midiToHz(v.midiNote, (int)pOsc1Coarse, pOsc1Fine);
            double f2 = midiToHz(v.midiNote, (int)pOsc2Coarse, pOsc2Fine);

            // ===== Mod Env =====
            double modEnvRaw = 0.0;
            double modEnvSig = 0.0;
            if (!bpModEnv)
            {
                modEnvRaw = v.modEnv.tick((double)pModEnvA, (double)pModEnvD);
                modEnvSig = modEnvRaw * (double)pModEnvAmt;
            }

            double lfo1ValLocal = lfo1Val;
            double lfo2ValLocal = lfo2Val;
            if (!bpModEnv && pModEnvDest == 1)
                lfo1ValLocal *= juce::jlimit(0.0, 2.0, 1.0 + modEnvSig);

            if (!bpModEnv && pModEnvDest == 3)
                f2 *= std::pow(2.0, modEnvSig * 12.0 / 12.0);

            // ===== LFO pitch modulation =====
            double pitchLfo1 = 0.0, pitchLfo2 = 0.0;
            if (!bpLfo1)
            {
                if ((int)pL1Target == 0) { pitchLfo1 = lfo1ValLocal; }
                if ((int)pL1Target == 1) { f1 *= std::pow(2.0, lfo1ValLocal * 2.0 / 12.0); }
                if ((int)pL1Target == 2) { f2 *= std::pow(2.0, lfo1ValLocal * 2.0 / 12.0); }
            }
            if (!bpLfo2)
            {
                if ((int)pL2Target == 0) { pitchLfo2 = lfo2ValLocal; }
                if ((int)pL2Target == 1) { f1 *= std::pow(2.0, lfo2ValLocal * 2.0 / 12.0); }
                if ((int)pL2Target == 2) { f2 *= std::pow(2.0, lfo2ValLocal * 2.0 / 12.0); }
            }

            f1 *= std::pow(2.0, (pitchLfo1 + pitchLfo2) * 2.0 / 12.0);
            f2 *= std::pow(2.0, (pitchLfo1 + pitchLfo2) * 2.0 / 12.0);
            f1 *= pitchBendGlobal;
            f2 *= pitchBendGlobal;

            // ===== VCO Binary =====
            if (!bpVcoBin && pVCOBin > 0.0f)
            {
                double stepsOctave = 4.0;
                auto quantize = [&](double freq) {
                    double midiF = 12.0 * std::log2(freq / 440.0) + 69.0;
                    double step = std::round(midiF * stepsOctave / 12.0);
                    double qMidi = step * 12.0 / stepsOctave;
                    return 440.0 * std::pow(2.0, (qMidi - 69.0) / 12.0);
                    };
                double qf1 = quantize(f1);
                double qf2 = quantize(f2);
                f1 = f1 + pVCOBin * (qf1 - f1);
                f2 = f2 + pVCOBin * (qf2 - f2);
            }

            // ===== Pulse width modulation =====
            double pw = (double)pPW;
            if (!bpLfo1 && (int)pL1Target == 3) pw = juce::jlimit(0.05, 0.95, pw + lfo1ValLocal * 0.4);
            if (!bpLfo2 && (int)pL2Target == 3) pw = juce::jlimit(0.05, 0.95, pw + lfo2ValLocal * 0.4);
            if (!bpModEnv && pModEnvDest == 0) pw = juce::jlimit(0.05, 0.95, pw + modEnvSig * 0.4);

            // ===== Oscillators (with voice stack) =====
            float osc1Raw = 0.0f;

            if (voiceConfig == VoiceConfig::Single)
            {
                osc1Raw = v.oscSample(v.osc1Phase, f1, (int)pOsc1Shape, pw) * pOsc1Amt;
            }
            else if (voiceConfig == VoiceConfig::Supersaw7)
            {
                osc1Raw = v.superSaw1.tick(f1, (double)pVoiceSpread, (double)pVoiceSpread,
                    true, f1) * pOsc1Amt;
            }
            else
            {
                double inc = f1 / currentSampleRate;
                float stack = v.stackOsc1.tick(v.osc1Phase, inc, (int)pOsc1Shape, pw,
                    voiceConfig, (double)pVoiceSpread);
                osc1Raw = stack * pOsc1Amt;
                v.osc1Phase += inc;
                if (v.osc1Phase >= 1.0) v.osc1Phase -= 1.0;
            }

            // ===== CV =====
            double cvSig = 0.0;
            double f2CV = f2;
            double pwCV = pw;
            double cvCutoffMult = 1.0;
            double cvAmpMod = 1.0;
            if (!bpCv && pCVAmt > 0.0f)
            {
                cvSig = (double)osc1Raw * (double)pCVAmt;
                switch (pCVTarget)
                {
                case 0: cvCutoffMult = std::pow(2.0, cvSig * 3.0); break;
                case 1: f2CV *= std::pow(2.0, cvSig * 2.0 / 12.0); break;
                case 2: pwCV = juce::jlimit(0.05, 0.95, pw + cvSig * 0.4); break;
                case 3: cvAmpMod = juce::jlimit(0.0, 1.0, 0.5 + cvSig * 0.5); break;
                default: break;
                }
            }

            if (!bpModEnv && pModEnvDest == 2)
                osc1Raw *= (float)juce::jlimit(0.0, 1.0, 1.0 + modEnvSig);

            double fmMod = 1.0 + (double)pFM * (double)osc1Raw * 4.0;

            float osc2Raw = 0.0f;
            if (voiceConfig == VoiceConfig::Single)
            {
                osc2Raw = v.oscSample(v.osc2Phase, f2CV * fmMod, (int)pOsc2Shape, pwCV) * pOsc2Amt;
            }
            else if (voiceConfig == VoiceConfig::Supersaw7)
            {
                osc2Raw = v.superSaw2.tick(f2CV * fmMod, (double)pVoiceSpread, (double)pVoiceSpread,
                    true, f2CV * fmMod) * pOsc2Amt;
            }
            else
            {
                double inc = (f2CV * fmMod) / currentSampleRate;
                float stack = v.stackOsc2.tick(v.osc2Phase, inc, (int)pOsc2Shape, pwCV,
                    voiceConfig, (double)pVoiceSpread);
                osc2Raw = stack * pOsc2Amt;
                v.osc2Phase += inc;
                if (v.osc2Phase >= 1.0) v.osc2Phase -= 1.0;
            }

            // ===== RM =====
            float rmSig = osc1Raw * osc2Raw;
            float osc12 = osc1Raw * (1.0f - pOscMix) + osc2Raw * pOscMix;
            osc12 = osc12 * (1.0f - pRM) + rmSig * pRM;

            // ===== Legacy Dual Voice =====
            if (!bpDualV && pDualV > 0.0f)
            {
                double detuneMult = std::pow(2.0, (double)pDualDetune / 1200.0);
                float osc1B = v.oscSample(v.osc1PhaseB, f1 * detuneMult, (int)pOsc1Shape, pw) * pOsc1Amt;
                float osc2B = v.oscSample(v.osc2PhaseB, f2CV * detuneMult * fmMod, (int)pOsc2Shape, pwCV) * pOsc2Amt;
                float osc12B = osc1B * (1.0f - pOscMix) + osc2B * pOscMix;
                osc12 = osc12 * (1.0f - 0.5f * pDualV) + osc12B * (0.5f * pDualV);
            }

            // ===== Osc 3 (sub / noise) =====
            float osc3Raw = v.osc3Sample(v.osc3Phase, v.baseFreq, (int)pOsc3Shape);
            float osc3Mix = osc12 * (1.0f - pOsc3Amt) + osc3Raw * pOsc3Amt;

            // ===== Wasp character =====
            float waspSig = osc3Mix;
            if (!bpWaspChar && pWasp > 0.0f)
            {
                float quant = std::round(osc3Mix * 8.0f) / 8.0f;
                waspSig = osc3Mix * (1.0f - pWasp) + quant * pWasp;
            }

            // ===== Filter envelope =====
            double fltEnvVal = v.fltEnv.tick((double)pFltA, (double)pFltD, (double)pFltS, (double)pFltR);
            double fltVelScale = (1.0 - (double)pVelFlt) + (double)pVelFlt * std::sqrt((double)v.velocity);
            fltEnvVal *= fltVelScale;

            double baseNote = 60.0;
            double noteSemis = (double)v.midiNote - baseNote;
            double ktMult = std::pow(2.0, noteSemis * (double)pFltKT / 12.0);
            double cutoffFlt = (double)pCutoff * ktMult;

            double envMod = (double)pFltEnv * fltEnvVal;
            cutoffFlt *= std::pow(2.0, envMod * 3.0);
            cutoffFlt *= cvCutoffMult;

            if (!bpLfo1 && (int)pL1Target == 4) cutoffFlt *= std::pow(2.0, lfo1ValLocal * 2.0);
            if (!bpLfo2 && (int)pL2Target == 4) cutoffFlt *= std::pow(2.0, lfo2ValLocal * 2.0);
            cutoffFlt = juce::jlimit(20.0, (currentSampleRate * 0.45), cutoffFlt);

            double cutoffFlt2 = 0.0;
            const bool needFlt2 = !bpFilter2 && (pFltRoute == 1 || pFltRoute == 2 || pFltRoute == 3);
            if (needFlt2)
            {
                double ktMult2 = std::pow(2.0, noteSemis * (double)pFlt2KT / 12.0);
                cutoffFlt2 = (double)pCutoff2 * ktMult2;
                double envMod2 = (double)pFlt2Env * fltEnvVal;
                cutoffFlt2 *= std::pow(2.0, envMod2 * 3.0);
                cutoffFlt2 *= cvCutoffMult;
                if (!bpLfo1 && (int)pL1Target == 4) cutoffFlt2 *= std::pow(2.0, lfo1ValLocal * 2.0);
                if (!bpLfo2 && (int)pL2Target == 4) cutoffFlt2 *= std::pow(2.0, lfo2ValLocal * 2.0);
                cutoffFlt2 = juce::jlimit(20.0, (currentSampleRate * 0.45), cutoffFlt2);
            }

            // ===== LFO -> Resonance =====
            float resoFlt = pReso;
            float resoFlt2 = pReso2;
            if (!bpLfo1 && (int)pL1Target == 6) resoFlt = juce::jlimit(0.0f, 1.0f, resoFlt + (float)lfo1ValLocal * 0.5f);
            if (!bpLfo2 && (int)pL2Target == 6) resoFlt = juce::jlimit(0.0f, 1.0f, resoFlt + (float)lfo2ValLocal * 0.5f);
            if (!bpLfo1 && (int)pL1Target == 6) resoFlt2 = juce::jlimit(0.0f, 1.0f, resoFlt2 + (float)lfo1ValLocal * 0.5f);
            if (!bpLfo2 && (int)pL2Target == 6) resoFlt2 = juce::jlimit(0.0f, 1.0f, resoFlt2 + (float)lfo2ValLocal * 0.5f);

            // ===== Filter routing with per-filter bypass =====
            const int effectiveRoute = bpFilter2 ? 0 : pFltRoute;

            float filtered;
            switch (effectiveRoute)
            {
            case 1: // Filter 2 only
                filtered = processFilterStage(pFlt2Model, v.filter2, v.chamberlinF2,
                    waspSig, (float)cutoffFlt2, resoFlt2, (int)pFlt2Type, pCmos);
                break;

            case 2: // Series: F1 -> F2
            {
                float stage1 = bpFilter1
                    ? waspSig
                    : processFilterStage(pFltModel, v.filter, v.chamberlinF,
                        waspSig, (float)cutoffFlt, resoFlt, (int)pFltType, pCmos);
                filtered = processFilterStage(pFlt2Model, v.filter2, v.chamberlinF2,
                    stage1, (float)cutoffFlt2, resoFlt2, (int)pFlt2Type, pCmos);
                break;
            }

            case 3: // Parallel
            {
                float stage1 = bpFilter1
                    ? waspSig
                    : processFilterStage(pFltModel, v.filter, v.chamberlinF,
                        waspSig, (float)cutoffFlt, resoFlt, (int)pFltType, pCmos);
                float stage2 = processFilterStage(pFlt2Model, v.filter2, v.chamberlinF2,
                    waspSig, (float)cutoffFlt2, resoFlt2, (int)pFlt2Type, pCmos);
                filtered = stage1 * (1.0f - pFltParMix) + stage2 * pFltParMix;
                break;
            }

            default: // Filter 1 only
                filtered = bpFilter1
                    ? waspSig
                    : processFilterStage(pFltModel, v.filter, v.chamberlinF,
                        waspSig, (float)cutoffFlt, resoFlt, (int)pFltType, pCmos);
                break;
            }

            // ===== Amp envelope =====
            double ampEnvVal = v.ampEnv.tick((double)pAmpA, (double)pAmpD, (double)pAmpS, (double)pAmpR);
            double velocityCurved = std::sqrt((double)v.velocity);
            double ampVelScale = (1.0 - (double)pVelAmp) + (double)pVelAmp * velocityCurved;
            ampEnvVal *= ampVelScale;

            double ampMod = cvAmpMod;
            if (!bpLfo1 && (int)pL1Target == 5) ampMod *= juce::jlimit(0.0, 1.0, 1.0 + lfo1ValLocal);
            if (!bpLfo2 && (int)pL2Target == 5) ampMod *= juce::jlimit(0.0, 1.0, 1.0 + lfo2ValLocal);

            float voiceSig = filtered * (float)(ampEnvVal * ampMod);

            // ===== DX FM =====
            float dxOut = 0.0f;
            if (dxOn) renderDxVoice(v, dxOut, (float)ampEnvVal);

            if (dxOn && dxBlend > 0.0f)
            {
                voiceSig *= (1.0f - 0.5f * dxBlend);
                voiceSig += dxOut * dxBlend;
            }

            if (!std::isfinite(voiceSig)) voiceSig = 0.0f;

            mixOut += voiceSig;
            ++activeCount;

            if (v.ampEnv.isActive() == false)
                v.isActive = false;
        }

        constexpr float kVoiceGain = 0.5f;
        mixOut *= kVoiceGain;
        juce::ignoreUnused(activeCount);

        if (!std::isfinite(mixOut)) mixOut = 0.0f;

        left[sample] = mixOut;
        right[sample] = mixOut;
    }

    // ===== Distortion (with drive compensation fixed) =====
    if (!bpDist && pDistOn > 0.5f)
    {
        if ((int)distDryL.size() < numSamples) distDryL.resize((size_t)numSamples);
        if ((int)distDryR.size() < numSamples) distDryR.resize((size_t)numSamples);

        for (int i = 0; i < numSamples; ++i)
        {
            distDryL[(size_t)i] = left[i];
            distDryR[(size_t)i] = right[i];
            if (pDistType == 1)
            {
                left[i] = hardClip(left[i], pDistDrv);
                right[i] = hardClip(right[i], pDistDrv);
            }
            else
            {
                left[i] = softClip(left[i], pDistDrv);
                right[i] = softClip(right[i], pDistDrv);
            }
        }

        if (!juce::approximatelyEqual(pDistTone, lastDistTone))
        {
            lastDistTone = pDistTone;
            *distToneFilter.state = *juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(currentSampleRate, pDistTone);
        }

        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> ctx(block);
        distToneFilter.process(ctx);

        for (int i = 0; i < numSamples; ++i)
        {
            left[i] = distDryL[(size_t)i] * (1.0f - pDistMix) + left[i] * pDistMix;
            right[i] = distDryR[(size_t)i] * (1.0f - pDistMix) + right[i] * pDistMix;
        }
    }

    // ===== Delay =====
    if (!bpDelay && pDelayMix > 0.0001f)
    {
        for (int i = 0; i < numSamples; ++i)
        {
            left[i] = delayL.process(left[i], pDelayTimeMs / 1000.0f, pDelayFb, pDelayMix);
            right[i] = delayR.process(right[i], pDelayTimeMs / 1000.0f, pDelayFb, pDelayMix);
        }
    }

    // ===== Master + limiter =====
    constexpr float kLimiterThreshold = 1.6f;
    for (int i = 0; i < numSamples; ++i)
    {
        left[i] = std::tanh((left[i] * pMasterGain) / kLimiterThreshold) * kLimiterThreshold;
        right[i] = std::tanh((right[i] * pMasterGain) / kLimiterThreshold) * kLimiterThreshold;
    }
}

//==============================================================================
juce::AudioProcessorEditor* WASPAlphaAudioProcessor::createEditor()
{
    return new WASPAlphaAudioProcessorEditor(*this);
}

void WASPAlphaAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void WASPAlphaAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml != nullptr && xml->hasTagName(apvts.state.getType()))
        apvts.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WASPAlphaAudioProcessor();
}