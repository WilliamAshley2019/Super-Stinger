#pragma once
#include <JuceHeader.h>
#include "PresetManager.h"

//==============================================================================
// The Stinger — A tribute to the EDP Wasp (1978)
// AlphaAudio by William Ashley Music
//==============================================================================

namespace WaspParams
{
    // Oscillator 1
    static constexpr const char* OSC1_SHAPE = "osc1_shape";
    static constexpr const char* OSC1_COARSE = "osc1_coarse";
    static constexpr const char* OSC1_FINE = "osc1_fine";
    static constexpr const char* OSC1_AMOUNT = "osc1_amount";

    // Oscillator 2
    static constexpr const char* OSC2_SHAPE = "osc2_shape";
    static constexpr const char* OSC2_COARSE = "osc2_coarse";
    static constexpr const char* OSC2_FINE = "osc2_fine";
    static constexpr const char* OSC2_AMOUNT = "osc2_amount";

    // Oscillator 3 (Sub / Noise osc)
    static constexpr const char* OSC3_SHAPE = "osc3_shape";
    static constexpr const char* OSC3_AMOUNT = "osc3_amount";

    // Mix / Modulation
    static constexpr const char* OSC_MIX = "osc_mix";
    static constexpr const char* PULSE_WIDTH = "pulse_width";
    static constexpr const char* FM_AMOUNT = "fm_amount";
    static constexpr const char* RM_AMOUNT = "rm_amount";

    // Amp Envelope
    static constexpr const char* AMP_ATTACK = "amp_attack";
    static constexpr const char* AMP_DECAY = "amp_decay";
    static constexpr const char* AMP_SUSTAIN = "amp_sustain";
    static constexpr const char* AMP_RELEASE = "amp_release";

    // Filter Envelope
    static constexpr const char* FLT_ATTACK = "flt_attack";
    static constexpr const char* FLT_DECAY = "flt_decay";
    static constexpr const char* FLT_SUSTAIN = "flt_sustain";
    static constexpr const char* FLT_RELEASE = "flt_release";

    // Filter
    static constexpr const char* FLT_KEYTRACK = "flt_keytrack";
    static constexpr const char* FLT_TYPE = "flt_type";
    static constexpr const char* FLT_CUTOFF = "flt_cutoff";
    static constexpr const char* FLT_RESO = "flt_reso";
    static constexpr const char* FLT_ENV_AMT = "flt_env_amt";

    // Filter 2
    static constexpr const char* FLT2_KEYTRACK = "flt2_keytrack";
    static constexpr const char* FLT2_TYPE = "flt2_type";
    static constexpr const char* FLT2_CUTOFF = "flt2_cutoff";
    static constexpr const char* FLT2_RESO = "flt2_reso";
    static constexpr const char* FLT2_ENV_AMT = "flt2_env_amt";
    static constexpr const char* FLT_ROUTING = "flt_routing";
    static constexpr const char* FLT_PARALLEL_MIX = "flt_parallel_mix";

    static constexpr const char* FLT_MODEL = "flt_model";
    static constexpr const char* FLT2_MODEL = "flt2_model";

    // LFO 1
    static constexpr const char* LFO1_SHAPE = "lfo1_shape";
    static constexpr const char* LFO1_TARGET = "lfo1_target";
    static constexpr const char* LFO1_AMOUNT = "lfo1_amount";
    static constexpr const char* LFO1_FREQ = "lfo1_freq";
    static constexpr const char* LFO1_SYNC = "lfo1_sync";
    static constexpr const char* LFO1_RESET = "lfo1_reset";

    // LFO 2
    static constexpr const char* LFO2_SHAPE = "lfo2_shape";
    static constexpr const char* LFO2_TARGET = "lfo2_target";
    static constexpr const char* LFO2_AMOUNT = "lfo2_amount";
    static constexpr const char* LFO2_FREQ = "lfo2_freq";
    static constexpr const char* LFO2_SYNC = "lfo2_sync";
    static constexpr const char* LFO2_RESET = "lfo2_reset";

    // FX / Character
    static constexpr const char* DIST_ON = "dist_on";
    static constexpr const char* DIST_DRIVE = "dist_drive";
    static constexpr const char* DIST_TONE = "dist_tone";
    static constexpr const char* DIST_MIX = "dist_mix";
    static constexpr const char* DIST_TYPE = "dist_type";
    static constexpr const char* DUAL_VOICE = "dual_voice";
    static constexpr const char* WASP_CHAR = "wasp_char";
    static constexpr const char* VCO_BINARY = "vco_binary";

    // Delay
    static constexpr const char* DELAY_TIME_MS = "delay_time_ms";
    static constexpr const char* DELAY_FEEDBACK = "delay_feedback";
    static constexpr const char* DELAY_MIX = "delay_mix";

    static constexpr const char* MASTER_VOLUME = "master_volume";
    static constexpr const char* CMOS_FILTER = "cmos_filter";
    static constexpr const char* CV_AMOUNT = "cv_amount";
    static constexpr const char* CV_TARGET = "cv_target";

    // Mod Env
    static constexpr const char* MODENV_ATTACK = "modenv_attack";
    static constexpr const char* MODENV_DECAY = "modenv_decay";
    static constexpr const char* MODENV_AMOUNT = "modenv_amount";
    static constexpr const char* MODENV_DEST = "modenv_dest";

    static constexpr const char* VEL_TO_AMP = "vel_to_amp";
    static constexpr const char* VEL_TO_FILTER = "vel_to_filter";

    static constexpr const char* LFO1_DELAY = "lfo1_delay";
    static constexpr const char* LFO2_DELAY = "lfo2_delay";
    static constexpr const char* DUAL_DETUNE = "dual_detune";

    // DX FM Module
    static constexpr const char* DXFM_ENABLE = "dxfm_enable";
    static constexpr const char* DXFM_BLEND = "dxfm_blend";
    static constexpr const char* DXFM_CAR_ATK = "dxfm_car_atk";
    static constexpr const char* DXFM_CAR_DEC = "dxfm_car_dec";
    static constexpr const char* DXFM_CAR_REL = "dxfm_car_rel";
    static constexpr const char* DXFM_WAVE = "dxfm_wave";
    static constexpr const char* DXFM_MOD_INIT = "dxfm_mod_init";
    static constexpr const char* DXFM_MOD_DEC = "dxfm_mod_dec";
    static constexpr const char* DXFM_MOD_SUS = "dxfm_mod_sus";
    static constexpr const char* DXFM_MOD_REL = "dxfm_mod_rel";
    static constexpr const char* DXFM_MOD_VEL = "dxfm_mod_vel";
    static constexpr const char* DXFM_COARSE = "dxfm_coarse";
    static constexpr const char* DXFM_FINE = "dxfm_fine";
    static constexpr const char* DXFM_MOD_THRU = "dxfm_mod_thru";
    static constexpr const char* DXFM_OCTAVE = "dxfm_octave";
    static constexpr const char* DXFM_TUNE = "dxfm_tune";

    // Voice stack (Super Saw / Dual / Quad / Sub Layer)
    static constexpr const char* VOICE_CONFIG = "voice_config";
    static constexpr const char* VOICE_SPREAD = "voice_spread";

    // CPU Saver — one bypass toggle per signal-chain stage. Every stage
    // that can be switched off now has a corresponding parameter, including
    // Filter 1 and LFO 1 which were previously missing from the UI.
    static constexpr const char* BYPASS_FILTER1 = "bypass_filter1";
    static constexpr const char* BYPASS_FILTER2 = "bypass_filter2";
    static constexpr const char* BYPASS_DELAY = "bypass_delay";
    static constexpr const char* BYPASS_DIST = "bypass_dist";
    static constexpr const char* BYPASS_LFO1 = "bypass_lfo1";
    static constexpr const char* BYPASS_LFO2 = "bypass_lfo2";
    static constexpr const char* BYPASS_MODENV = "bypass_modenv";
    static constexpr const char* BYPASS_CV = "bypass_cv";
    static constexpr const char* BYPASS_DUALVOICE = "bypass_dualvoice";
    static constexpr const char* BYPASS_WASPCHAR = "bypass_waspchar";
    static constexpr const char* BYPASS_VCOBIN = "bypass_vcobin";
}

//==============================================================================
// Voice configuration enum — selects how many oscillators make up a voice
// and how they're spread.
//==============================================================================
enum class VoiceConfig
{
    Single = 0,     // 1 standard voice
    Dual,           // 2-voice detuned pair
    Quad,           // 4-voice symmetric stack
    Supersaw7,      // 7-voice JP-8000 style Super Saw
    SubLayer        // Octave-stacked voices
};

//==============================================================================
// Moog-style ladder filter
//==============================================================================
struct WaspFilter
{
    double s[4] = { 0.0, 0.0, 0.0, 0.0 };
    double sampleRate = 44100.0;

    void reset() { for (auto& x : s) x = 0.0; }
    void setSampleRate(double sr) { sampleRate = sr; }

    float process(float input, float cutoffHz, float resonance, int type, bool cmosMode = false)
    {
        if (!std::isfinite(input)) input = 0.0f;

        double f = 2.0 * juce::MathConstants<double>::pi * (double)cutoffHz / sampleRate;
        f = juce::jlimit(0.001, 0.499, f);
        double k = (double)juce::jlimit(0.0f, 1.0f, resonance) * 3.99;
        double t1 = f * 0.9892;
        double x = (double)input - k * s[3];

        double y0, y1, y2, y3;

        if (cmosMode)
        {
            double kCmos = (double)juce::jlimit(0.0f, 1.0f, resonance) * 1.8;
            double xC = (double)input - kCmos * s[3];
            auto cmosClip = [](double v) -> double { return v / (1.0 + std::abs(v)); };
            y0 = cmosClip(s[0] + t1 * (xC - s[0]));
            y1 = cmosClip(s[1] + t1 * (y0 - s[1]));
            y2 = cmosClip(s[2] + t1 * (y1 - s[2]));
            y3 = cmosClip(s[3] + t1 * (y2 - s[3]));
        }
        else
        {
            y0 = x * t1 + s[0] * (1.0 - t1);
            y1 = y0 * t1 + s[1] * (1.0 - t1);
            y2 = y1 * t1 + s[2] * (1.0 - t1);
            y3 = y2 * t1 + s[3] * (1.0 - t1);
        }

        if (!std::isfinite(y0)) y0 = 0.0;
        if (!std::isfinite(y1)) y1 = 0.0;
        if (!std::isfinite(y2)) y2 = 0.0;
        if (!std::isfinite(y3)) y3 = 0.0;

        s[0] = y0;  s[1] = y1;  s[2] = y2;  s[3] = y3;

        float out;
        switch (type)
        {
        case 1: out = (float)y3;          break;
        case 2: out = (float)(x - y2);    break;
        case 3: out = (float)(y1 - y3);   break;
        default: out = (float)y1;         break;
        }

        if (cmosMode)
        {
            constexpr float kCmosMakeupGain = 1.4f;
            out *= kCmosMakeupGain;
        }

        if (!std::isfinite(out)) out = 0.0f;
        return out;
    }
};

//==============================================================================
// Chamberlin State Variable Filter — oversampled, production-safe.
//
// The Chamberlin SVF is fundamentally unstable at high cutoff × high
// resonance because of the one-sample delay in its feedback path. No
// coefficient clamp alone can fully fix this without restricting the filter
// to unusably low cutoffs — the digital stability boundary is well below the
// analog one, and it shrinks as Q rises.
//
// The correct fix, and what commercial plugins do, is to oversample the
// filter. Running the Chamberlin at 2× the host rate doubles the internal
// Nyquist, so a 10 kHz cutoff at 48 kHz host rate processes at 96 kHz
// internally where it sits comfortably inside the stable region. The
// oversampler also band-limits the resonance peak, eliminating the
// self-aliasing that was destabilising the filter at high frequencies.
//
// Every filter instance owns its own oversampler, so polyphony has no
// shared state. All allocation happens in setSampleRate(), which is called
// from prepareToPlay() on the message thread — never on the audio thread.
//==============================================================================
struct ChamberlinFilter
{
    double low = 0.0;
    double band = 0.0;
    double dcX1 = 0.0;
    double dcY1 = 0.0;
    double sampleRate = 44100.0;

    static constexpr int kOversampleStages = 1;   // 1 stage = 2× factor
    static constexpr int kOversampleChans = 2;   // JUCE needs a fixed chan count

    std::unique_ptr<juce::dsp::Oversampling<float>> oversampler;
    juce::AudioBuffer<float> scratch;
    bool prepared = false;

    void reset()
    {
        low = band = 0.0;
        dcX1 = dcY1 = 0.0;
        if (oversampler) oversampler->reset();
    }

    void setSampleRate(double sr)
    {
        const double safeSr = (sr > 100.0 && sr < 400000.0) ? sr : 44100.0;

        if (prepared && std::abs(safeSr - sampleRate) < 0.5)
            return;

        sampleRate = safeSr;

        constexpr int blockSize = 1;

        oversampler = std::make_unique<juce::dsp::Oversampling<float>>(
            (size_t)kOversampleChans,
            (size_t)kOversampleStages,
            juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR,
            true,
            false);

        oversampler->initProcessing((size_t)blockSize);

        scratch.setSize(kOversampleChans, blockSize, false, true, false);
        prepared = true;
    }

    inline float coreStep(float in, double cutoffHz, double reso01,
        int type, double fs, bool& ok)
    {
        ok = true;
        if (!std::isfinite(in)) in = 0.0f;

        const double Q = 0.5 + juce::jlimit(0.0, 1.0, reso01) * 19.5;

        // Q-dependent stability clamp on the *internal* Fn. Because we
        // oversample 2×, the internal Fn for a given host-rate cutoff is
        // already halved, so the clamp can be permissive. The oversampler
        // does the heavy lifting.
        double maxNorm = (Q > 1.0) ? juce::jmin(1.8 / Q, 0.40) : 0.40;
        maxNorm = juce::jmax(maxNorm, 0.001);

        const double norm = juce::jlimit(0.0005, maxNorm, cutoffHz / fs);
        const double f = 2.0 * std::sin(juce::MathConstants<double>::pi * norm);

        double Q1 = 1.0 / Q;
        Q1 = juce::jlimit(0.05, 2.0, Q1);

        double L = low;
        double B = band;

        double H = (double)in - L - Q1 * B;
        B = f * H + B;
        L = f * B + L;

        if (!std::isfinite(L) || !std::isfinite(B) || !std::isfinite(H))
        {
            low = band = 0.0;
            dcX1 = dcY1 = 0.0;
            ok = false;
            return 0.0f;
        }

        low = L;
        band = B;

        float out;
        switch (type)
        {
        case 1:
        {
            constexpr double kDcCoeff = 0.995;
            double y = H - dcX1 + kDcCoeff * dcY1;
            dcX1 = H;
            dcY1 = y;
            if (!std::isfinite(y)) { dcX1 = dcY1 = 0.0; y = 0.0; }
            out = (float)y;
            break;
        }
        case 2: out = (float)B; break;
        default: out = (float)L; break;
        }

        if (!std::isfinite(out)) { out = 0.0f; ok = false; }
        return out;
    }

    float process(float input, float cutoffHz, float resonance, int type)
    {
        if (!prepared || oversampler == nullptr)
        {
            // Fallback: un-oversampled, tight clamp.
            bool ok = true;
            const double Q = 0.5 + juce::jlimit(0.0, 1.0, (double)resonance) * 19.5;
            double maxFn = (Q > 1.0) ? juce::jmin(1.0 / Q, 0.12) : 0.12;
            maxFn = juce::jmax(maxFn, 0.001);

            const double norm = juce::jlimit(0.0005, maxFn,
                (double)cutoffHz / sampleRate);
            const double clampedCutoff = norm * sampleRate;

            return coreStep(input, clampedCutoff,
                juce::jlimit(0.0, 1.0, (double)resonance),
                type, sampleRate, ok);
        }

        scratch.setSample(0, 0, input);
        scratch.setSample(1, 0, 0.0f);

        juce::dsp::AudioBlock<float> hostBlock(scratch);
        auto oversampledBlock = oversampler->processSamplesUp(hostBlock);

        const double internalFs = sampleRate * (double)(1 << kOversampleStages);
        const double reso01 = juce::jlimit(0.0, 1.0, (double)resonance);

        const int numOversampled = (int)oversampledBlock.getNumSamples();
        float* chan0 = oversampledBlock.getChannelPointer(0);

        for (int i = 0; i < numOversampled; ++i)
        {
            bool ok = true;
            chan0[i] = coreStep(chan0[i], cutoffHz, reso01, type,
                internalFs, ok);
        }

        oversampler->processSamplesDown(hostBlock);

        float out = scratch.getSample(0, 0);
        if (!std::isfinite(out)) out = 0.0f;
        return out;
    }
};

//==============================================================================
// Simple ADSR
//==============================================================================
struct WaspEnv
{
    enum class Stage { Idle, Attack, Decay, Sustain, Release };
    Stage stage = Stage::Idle;
    double value = 0.0;
    double sampleRate = 44100.0;

    void setSampleRate(double sr) { sampleRate = sr; }
    void noteOn() { stage = Stage::Attack; }
    void noteOff() { if (stage != Stage::Idle) stage = Stage::Release; }
    bool isActive() const { return stage != Stage::Idle; }

    double tick(double attack, double decay, double sustain, double release)
    {
        switch (stage)
        {
        case Stage::Attack:
            value += 1.0 / (attack * sampleRate + 1.0);
            if (value >= 1.0) { value = 1.0; stage = Stage::Decay; }
            break;
        case Stage::Decay:
            value -= (1.0 - sustain) / (decay * sampleRate + 1.0);
            if (value <= sustain) { value = sustain; stage = Stage::Sustain; }
            break;
        case Stage::Sustain:
            value = sustain;
            break;
        case Stage::Release:
            value -= value / (release * sampleRate + 1.0);
            if (value < 0.0001) { value = 0.0; stage = Stage::Idle; }
            break;
        default: value = 0.0; break;
        }
        return value;
    }
};

//==============================================================================
// One-shot AD Mod Env
//==============================================================================
struct WaspModEnv
{
    enum class Stage { Idle, Attack, Decay };
    Stage  stage = Stage::Idle;
    double value = 0.0;
    double sampleRate = 44100.0;

    void setSampleRate(double sr) { sampleRate = sr; }
    void noteOn() { stage = Stage::Attack; value = 0.0; }

    double tick(double attack, double decay)
    {
        switch (stage)
        {
        case Stage::Attack:
            value += 1.0 / (attack * sampleRate + 1.0);
            if (value >= 1.0) { value = 1.0; stage = Stage::Decay; }
            break;
        case Stage::Decay:
            value -= 1.0 / (decay * sampleRate + 1.0);
            if (value <= 0.0) { value = 0.0; stage = Stage::Idle; }
            break;
        default: value = 0.0; break;
        }
        return value;
    }
};

//==============================================================================
// Simple single-tap feedback delay
//==============================================================================
struct SimpleDelay
{
    std::vector<float> buffer;
    int    writePos = 0;
    double sampleRate = 44100.0;

    void prepare(double sr, double maxSeconds = 2.5)
    {
        sr = juce::jlimit(8000.0, 384000.0, sr);
        sampleRate = sr;
        size_t numSamples = (size_t)juce::jmax(4.0, sr * maxSeconds) + 4;
        buffer.assign(numSamples, 0.0f);
        writePos = 0;
    }

    void reset()
    {
        std::fill(buffer.begin(), buffer.end(), 0.0f);
        writePos = 0;
    }

    float process(float in, float delaySeconds, float feedback, float mix)
    {
        if (buffer.empty()) return in;
        if (!std::isfinite(in)) in = 0.0f;

        int delaySamples = (int)juce::jlimit(1.0, (double)buffer.size() - 2.0, delaySeconds * sampleRate);
        int readPos = writePos - delaySamples;
        if (readPos < 0) readPos += (int)buffer.size();

        float delayed = buffer[(size_t)readPos];
        buffer[(size_t)writePos] = in + delayed * feedback;

        writePos = (writePos + 1) % (int)buffer.size();

        float out = in * (1.0f - mix) + delayed * mix;
        if (!std::isfinite(out)) out = 0.0f;
        return out;
    }
};

//==============================================================================
// LFO
//==============================================================================
struct WaspLfo
{
    double phase = 0.0;
    double sampleRate = 44100.0;
    double holdValue = 0.0;
    double delayTimer = 0.0;

    void setSampleRate(double sr) { sampleRate = sr; }
    void reset() { phase = 0.0; delayTimer = 0.0; }
    void resetDelay() { delayTimer = 0.0; }

    double delayGain(double delayTimeSeconds)
    {
        if (sampleRate <= 0.0) return 1.0;
        delayTimer += 1.0 / sampleRate;
        if (delayTimeSeconds <= 0.0) return 1.0;
        double past = delayTimer - delayTimeSeconds;
        if (past <= 0.0) return 0.0;
        return juce::jlimit(0.0, 1.0, past * sampleRate / 480.0);
    }

    double tick(double freqHz, int shape)
    {
        double out = 0.0;
        switch (shape)
        {
        case 0: out = std::sin(phase * juce::MathConstants<double>::twoPi); break;
        case 1: out = (phase < 0.5) ? (phase * 4.0 - 1.0) : (3.0 - phase * 4.0); break;
        case 2: out = 1.0 - 2.0 * phase; break;
        case 3: out = 2.0 * phase - 1.0; break;
        case 4: out = (phase < 0.5) ? 1.0 : -1.0; break;
        case 5:
        {
            double oldPhase = phase;
            double inc = freqHz / sampleRate;
            double newPhase = oldPhase + inc;
            if (newPhase >= 1.0 || oldPhase == 0.0)
                holdValue = (double)juce::Random::getSystemRandom().nextFloat() * 2.0 - 1.0;
            out = holdValue;
            phase = newPhase >= 1.0 ? newPhase - 1.0 : newPhase;
            return out;
        }
        default: break;
        }
        phase += freqHz / sampleRate;
        if (phase >= 1.0) phase -= 1.0;
        return out;
    }
};

//==============================================================================
// Super Saw oscillator — 7-voice JP-8000 stack
//==============================================================================
struct SuperSawOsc
{
    static constexpr int kNumVoices = 7;
    double phases[kNumVoices] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    double hpfZ = 0.0;
    double sampleRate = 44100.0;

    void setSampleRate(double sr) { sampleRate = sr; }

    void resetPhasesRandom()
    {
        auto& rng = juce::Random::getSystemRandom();
        for (auto& p : phases)
            p = rng.nextDouble();
        hpfZ = 0.0;
    }

    void reset()
    {
        for (auto& p : phases) p = 0.0;
        hpfZ = 0.0;
    }

    static double detuneCurve(double x)
    {
        x = juce::jlimit(0.0, 1.0, x);
        const double c[12] = {
             0.0030115596,
             0.6717417634,
           -24.1878824391,
           404.2703938388,
         -3425.0836591318,
         17019.9518580080,
        -53046.9642751875,
        106649.6679158292,
       -138150.6761080548,
        111363.4808729368,
        -50818.8652045924,
         10028.7312891634
        };
        double y = 0.0, xp = 1.0;
        for (int i = 0; i < 12; ++i) { y += c[i] * xp; xp *= x; }
        return juce::jlimit(0.0, 1.0, y);
    }

    static void detuneMultipliers(double detune01, double mult[kNumVoices])
    {
        const double offsets[kNumVoices] = {
            -0.11002313, -0.06288439, -0.01952356,
             0.0,
             0.01991221,  0.06216538,  0.10745242
        };
        const double curve = detuneCurve(detune01);
        for (int i = 0; i < kNumVoices; ++i)
            mult[i] = 1.0 + offsets[i] * curve;
    }

    static void mixGains(double mix01, float& centerGain, float sideGain[kNumVoices - 1])
    {
        centerGain = (float)juce::jlimit(0.0, 1.0, -0.55366 * mix01 + 0.99785);
        const double side = juce::jlimit(0.0, 1.0,
            -0.73764 * mix01 * mix01 + 1.2841 * mix01 + 0.044372);
        for (int i = 0; i < kNumVoices - 1; ++i) sideGain[i] = (float)side;
    }

    float tick(double baseFreq, double detune01, double mix01,
        bool useHPF, double hpfCutoffHz)
    {
        double mult[kNumVoices];
        detuneMultipliers(detune01, mult);

        float centerGain = 1.0f;
        float sideGain[kNumVoices - 1] = { 0.0f };
        mixGains(mix01, centerGain, sideGain);

        float out = 0.0f;
        int sideIdx = 0;
        for (int i = 0; i < kNumVoices; ++i)
        {
            float s = (float)(1.0 - 2.0 * phases[i]);

            float g = (i == 3) ? centerGain : sideGain[sideIdx++];
            out += s * g;

            phases[i] += (baseFreq * mult[i]) / sampleRate;
            if (phases[i] >= 1.0) phases[i] -= 1.0;
            if (!std::isfinite(phases[i])) phases[i] = 0.0;
        }
        out *= 0.25f;

        if (useHPF && hpfCutoffHz > 20.0)
        {
            const double f = juce::jlimit(0.0001, 0.25, hpfCutoffHz / sampleRate);
            const double a = 1.0 / (1.0 + 2.0 * juce::MathConstants<double>::pi * f);
            hpfZ = (double)out * (1.0 - a) + hpfZ * a;
            if (!std::isfinite(hpfZ)) hpfZ = 0.0;
            out = (float)((double)out - hpfZ);
        }

        if (!std::isfinite(out)) out = 0.0f;
        return out;
    }
};

//==============================================================================
// Multi-voice stack oscillator
//==============================================================================
struct VoiceStackOsc
{
    static constexpr int kMaxStack = 7;
    double phases[kMaxStack] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    double subPhase = 0.0;
    double sampleRate = 44100.0;

    void setSampleRate(double sr) { sampleRate = sr; }

    void reset()
    {
        for (auto& p : phases) p = 0.0;
        subPhase = 0.0;
    }

    void randomise()
    {
        auto& rng = juce::Random::getSystemRandom();
        for (auto& p : phases)
            p = rng.nextDouble();
        subPhase = rng.nextDouble();
    }

    float tick(double basePhase, double phaseInc, int shape, double pw,
        VoiceConfig config, double spread)
    {
        switch (config)
        {
        case VoiceConfig::Single:
            return 0.0f;

        case VoiceConfig::Dual:
        {
            const double det = juce::jlimit(0.0, 1.0, spread) * 0.005;
            const double incA = phaseInc * (1.0 - det);
            const double incB = phaseInc * (1.0 + det);

            float a = renderShape(phases[0], shape, pw);
            float b = renderShape(phases[1], shape, pw);
            phases[0] += incA; phases[1] += incB;
            wrap(phases[0]);   wrap(phases[1]);
            return (a + b) * 0.5f;
        }

        case VoiceConfig::Quad:
        {
            const double d = juce::jlimit(0.0, 1.0, spread) * 0.008;
            const double incs[4] = {
                phaseInc * (1.0 - d),
                phaseInc * (1.0 - d * 0.4),
                phaseInc * (1.0 + d * 0.4),
                phaseInc * (1.0 + d)
            };
            float sum = 0.0f;
            for (int i = 0; i < 4; ++i)
            {
                sum += renderShape(phases[i], shape, pw);
                phases[i] += incs[i];
                wrap(phases[i]);
            }
            return sum * 0.25f;
        }

        case VoiceConfig::Supersaw7:
            return 0.0f;

        case VoiceConfig::SubLayer:
        {
            const double sub1 = phaseInc * 0.5;
            const double sub2 = phaseInc * 0.25;

            float main = renderShape(basePhase, shape, pw);
            float s1 = (phases[0] < 0.5) ? 1.0f : -1.0f;
            float s2 = (phases[1] < 0.5) ? 1.0f : -1.0f;

            const double mixAmt = juce::jlimit(0.0, 1.0, spread);
            phases[0] += sub1; wrap(phases[0]);
            phases[1] += sub2; wrap(phases[1]);

            return main * (1.0f - 0.4f * (float)mixAmt)
                + (s1 * 0.3f + s2 * 0.1f) * (float)mixAmt;
        }

        default:
            return 0.0f;
        }
    }

private:
    static float renderShape(double phase, int shape, double pw)
    {
        switch (shape)
        {
        case 0: return (float)(1.0 - 2.0 * phase);
        case 1:
        {
            double pwc = juce::jlimit(0.05, 0.95, pw);
            return (phase < pwc) ? 1.0f : -1.0f;
        }
        case 2:
            return (float)((phase < 0.5) ? (4.0 * phase - 1.0) : (3.0 - 4.0 * phase));
        case 3:
            return (float)std::sin(phase * juce::MathConstants<double>::twoPi);
        case 4:
        {
            constexpr double curve = 3.0;
            const double expNorm = 1.0 - std::exp(-curve);
            double shaped = (1.0 - std::exp(-curve * phase)) / expNorm;
            return (float)(1.0 - 2.0 * shaped);
        }
        default: return 0.0f;
        }
    }

    static void wrap(double& phase)
    {
        while (phase >= 1.0) phase -= 1.0;
        while (phase < 0.0) phase += 1.0;
        if (!std::isfinite(phase)) phase = 0.0;
    }
};

//==============================================================================
// DX FM voice state
//==============================================================================
struct DxVoiceState
{
    double carPhase = 0.0;
    double modPhase = 0.0;
    double mod0 = 0.0;
    double mod1 = 0.0;
    double dmod = 0.0;
    double menv = 0.0;
    double mlev = 0.0;
    double mdec = 0.0;
    double cenv = 0.0;
    double env = 0.0;
    double catt = 0.0;
    double cdec = 0.0;
    double dcar = 0.0;
    bool   active = false;

    void reset()
    {
        carPhase = modPhase = 0.0;
        mod0 = mod1 = dmod = 0.0;
        menv = mlev = mdec = 0.0;
        cenv = env = catt = cdec = 0.0;
        dcar = 0.0;
        active = false;
    }
};

//==============================================================================
// Voice
//==============================================================================
struct WaspVoice
{
    int    midiNote = -1;
    double baseFreq = 0.0;
    double tuning = 1.0;
    bool   noteHeld = false;
    bool   isActive = false;
    float  velocity = 1.0f;

    double osc1Phase = 0.0;
    double osc2Phase = 0.0;
    double osc3Phase = 0.0;
    double osc1PhaseB = 0.0;
    double osc2PhaseB = 0.0;

    VoiceStackOsc stackOsc1;
    VoiceStackOsc stackOsc2;
    SuperSawOsc  superSaw1;
    SuperSawOsc  superSaw2;

    WaspFilter       filter;
    WaspFilter       filter2;
    ChamberlinFilter chamberlinF;
    ChamberlinFilter chamberlinF2;
    WaspEnv          ampEnv;
    WaspEnv          fltEnv;
    WaspModEnv       modEnv;
    DxVoiceState     dx;

    double sampleRate = 44100.0;

    void setSampleRate(double sr)
    {
        sampleRate = sr;
        filter.setSampleRate(sr);
        filter2.setSampleRate(sr);
        chamberlinF.setSampleRate(sr);
        chamberlinF2.setSampleRate(sr);
        ampEnv.setSampleRate(sr);
        fltEnv.setSampleRate(sr);
        modEnv.setSampleRate(sr);
        stackOsc1.setSampleRate(sr);
        stackOsc2.setSampleRate(sr);
        superSaw1.setSampleRate(sr);
        superSaw2.setSampleRate(sr);
    }

    void noteOn(int note, double freq, float vel)
    {
        midiNote = note;
        baseFreq = freq;
        noteHeld = true;
        isActive = true;
        velocity = vel;
        osc1Phase = osc2Phase = osc3Phase = 0.0;
        osc1PhaseB = osc2PhaseB = 0.0;
        tuning = std::exp(0.05776226505 * (double)note);

        stackOsc1.randomise();
        stackOsc2.randomise();
        superSaw1.resetPhasesRandom();
        superSaw2.resetPhasesRandom();

        ampEnv.noteOn();
        fltEnv.noteOn();
        modEnv.noteOn();
        dx.reset();
    }

    void noteOff()
    {
        noteHeld = false;
        ampEnv.noteOff();
        fltEnv.noteOff();
    }

    float oscSample(double& phase, double freq, int shape, double pw)
    {
        float out = 0.0f;
        switch (shape)
        {
        case 0: out = (float)(1.0 - 2.0 * phase); break;
        case 1:
        {
            double pwClamped = juce::jlimit(0.05, 0.95, pw);
            out = (phase < pwClamped) ? 1.0f : -1.0f;
            break;
        }
        case 2: out = (float)((phase < 0.5) ? (4.0 * phase - 1.0) : (3.0 - 4.0 * phase)); break;
        case 3: out = (float)std::sin(phase * juce::MathConstants<double>::twoPi); break;
        case 4:
        {
            constexpr double curve = 3.0;
            const double expNorm = 1.0 - std::exp(-curve);
            double shaped = (1.0 - std::exp(-curve * phase)) / expNorm;
            out = (float)(1.0 - 2.0 * shaped);
            break;
        }
        default: break;
        }
        phase += freq / sampleRate;
        if (phase >= 1.0) phase -= 1.0;
        if (!std::isfinite(phase)) phase = 0.0;
        return out;
    }

    float osc3Sample(double& phase, double baseFreq_, int shape)
    {
        float out = 0.0f;
        switch (shape)
        {
        case 0:
        {
            double f = baseFreq_ * 0.5;
            out = (phase < 0.5) ? 1.0f : -1.0f;
            phase += f / sampleRate;
            if (phase >= 1.0) phase -= 1.0;
            break;
        }
        case 1:
        {
            double f = baseFreq_ * 0.25;
            out = (phase < 0.5) ? 1.0f : -1.0f;
            phase += f / sampleRate;
            if (phase >= 1.0) phase -= 1.0;
            break;
        }
        case 2:
            out = (float)(juce::Random::getSystemRandom().nextFloat() * 2.0f - 1.0f);
            break;
        default: break;
        }
        return out;
    }
};

//==============================================================================
// Main Processor
//==============================================================================
class WASPAlphaAudioProcessor : public juce::AudioProcessor,
    public juce::AudioProcessorValueTreeState::Listener
{
public:
    WASPAlphaAudioProcessor();
    ~WASPAlphaAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "The Stinger"; }
    bool acceptsMidi()  const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 8.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    void parameterChanged(const juce::String& paramID, float newValue) override;

    juce::AudioProcessorValueTreeState apvts;
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    PresetManager& getPresetManager() { return *presetManager; }
    const PresetManager& getPresetManager() const { return *presetManager; }

private:
    static constexpr int MAX_VOICES = 8;
    WaspVoice voices[MAX_VOICES];

    WaspLfo lfo1, lfo2;
    SimpleDelay delayL, delayR;
    std::unique_ptr<PresetManager> presetManager;

    std::vector<float> distDryL, distDryR;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>> distToneFilter;

    double currentSampleRate = 44100.0;
    int    currentBlockSize = 512;
    bool   isPrepared = false;
    float  lastDistTone = -1.0f;

    float  modWheelValue = 0.0f;
    float  dxTune = 0.0f;
    float  dxRatio = 0.0f;
    float  dxDepth = 0.0f;
    float  dxDept2 = 0.0f;
    float  dxCatt = 0.0f;
    float  dxCdec = 0.0f;
    float  dxCrel = 0.0f;
    float  dxMdec = 0.0f;
    float  dxMrel = 0.0f;
    float  dxRich = 0.0f;
    float  dxModMix = 0.0f;
    float  dxVolume = 0.0035f;
    double pitchBendGlobal = 1.0;

    void updateDxParams();
    void renderDxVoice(WaspVoice& v, float& out, float ampEnv);
    void initDxVoice(WaspVoice& v, int midiNote, int velocity);
    void handleMidiEvent(const juce::MidiMessage& msg);
    int  findFreeVoice();
    int  findVoiceForNote(int midiNote);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WASPAlphaAudioProcessor)
};