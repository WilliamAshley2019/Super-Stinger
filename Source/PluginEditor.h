#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
// The Stinger — Look and Feel
// Warm analog rack hardware theme (orange/red panels, chrome bevel)
//==============================================================================
class WaspLookAndFeel : public juce::LookAndFeel_V4
{
public:
    // ===== Warm panel theme (no grey) =====
    static constexpr juce::uint32 COL_BODY_BG = 0xff0e0806u;  // near-black warm
    static constexpr juce::uint32 COL_WASP_STRIPE = 0xff281008u;  // dark amber stripe

    // Three alternating panel tones — cycled so adjacent sections contrast.
    static constexpr juce::uint32 COL_PANEL_A = 0xff2a0f06u;  // deep mahogany
    static constexpr juce::uint32 COL_PANEL_B = 0xff3a1508u;  // burnt amber
    static constexpr juce::uint32 COL_PANEL_C = 0xff48120au;  // dark warm red

    static constexpr juce::uint32 COL_SECTION_HDR = 0xff222222u;
    static constexpr juce::uint32 COL_HDR_TEXT_A = 0xffffd090u;  // warm cream-gold
    static constexpr juce::uint32 COL_HDR_TEXT_B = 0xffff8c50u;  // soft amber

    static constexpr juce::uint32 COL_WASP_YELLOW = 0xffffd070u;
    static constexpr juce::uint32 COL_WASP_AMBER = 0xffffa050u;
    static constexpr juce::uint32 COL_GRAD_ORANGE = 0xffffc080u;
    static constexpr juce::uint32 COL_GRAD_RED = 0xffe07040u;

    // Chrome case bevel
    static constexpr juce::uint32 COL_CASE_OUTER = 0xff0c0e10u;
    static constexpr juce::uint32 COL_CASE_MID = 0xff8890a0u;
    static constexpr juce::uint32 COL_CASE_HILITE = 0xffd8dde8u;
    static constexpr juce::uint32 COL_CASE_RIM = 0xffa0a8b4u;

    // Shiny silver knob body
    static constexpr juce::uint32 COL_KNOB_BODY_HI = 0xffc8ccd4u;
    static constexpr juce::uint32 COL_KNOB_BODY_LO = 0xff3a3e46u;
    static constexpr juce::uint32 COL_KNOB_RING = 0xff4a3a20u;
    static constexpr juce::uint32 COL_KNOB_MARKER = 0xffffe0a0u;
    static constexpr juce::uint32 COL_OUTLINE = 0xff5a4a30u;

    static constexpr juce::uint32 COL_TEXT_PRIMARY = 0xfff0d8b0u;
    static constexpr juce::uint32 COL_TEXT_SECONDARY = 0xffb8a888u;

    static constexpr juce::uint32 COL_BUTTON_OFF = 0xff2a2d34u;
    static constexpr juce::uint32 COL_COMBO_BG = 0xff191c22u;

    WaspLookAndFeel()
    {
        setColour(juce::Slider::thumbColourId, juce::Colour(COL_KNOB_MARKER));
        setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(COL_WASP_AMBER));
        setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(COL_OUTLINE));
        setColour(juce::Slider::trackColourId, juce::Colour(COL_OUTLINE));
        setColour(juce::Label::textColourId, juce::Colour(COL_TEXT_PRIMARY));
        setColour(juce::ComboBox::backgroundColourId, juce::Colour(COL_COMBO_BG));
        setColour(juce::ComboBox::textColourId, juce::Colour(COL_TEXT_PRIMARY));
        setColour(juce::ComboBox::outlineColourId, juce::Colour(COL_OUTLINE));
        setColour(juce::ComboBox::arrowColourId, juce::Colour(COL_WASP_YELLOW));
        setColour(juce::PopupMenu::backgroundColourId, juce::Colour(COL_PANEL_A));
        setColour(juce::PopupMenu::textColourId, juce::Colour(COL_TEXT_PRIMARY));
        setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colour(COL_WASP_YELLOW));
        setColour(juce::PopupMenu::highlightedTextColourId, juce::Colour(0xff000000u));
        setColour(juce::ToggleButton::textColourId, juce::Colour(COL_TEXT_PRIMARY));
        setColour(juce::ToggleButton::tickColourId, juce::Colour(COL_WASP_YELLOW));
        setColour(juce::ToggleButton::tickDisabledColourId, juce::Colour(COL_OUTLINE));
        setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2a0f06u));
        setColour(juce::TextButton::buttonOnColourId, juce::Colour(COL_GRAD_RED));
        setColour(juce::TextButton::textColourOffId, juce::Colour(COL_TEXT_PRIMARY));
        setColour(juce::TextButton::textColourOnId, juce::Colour(0xffffffffu));
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle,
        float rotaryEndAngle, juce::Slider& slider) override
    {
        juce::ignoreUnused(slider);

        auto bounds = juce::Rectangle<float>((float)x, (float)y, (float)width, (float)height).reduced(4.0f);
        const float radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.5f;
        const float centreX = bounds.getCentreX();
        const float centreY = bounds.getCentreY();
        const float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

        const float ringRadius = radius + 3.0f;
        {
            juce::Path track;
            track.addCentredArc(centreX, centreY, ringRadius, ringRadius, 0.0f,
                rotaryStartAngle, rotaryEndAngle, true);
            g.setColour(juce::Colour(COL_KNOB_RING));
            g.strokePath(track, juce::PathStrokeType(2.0f));
        }

        {
            juce::Path valueArc;
            valueArc.addCentredArc(centreX, centreY, ringRadius, ringRadius, 0.0f,
                rotaryStartAngle, angle, true);
            juce::ColourGradient arcGrad(
                juce::Colour(COL_GRAD_ORANGE),
                centreX + ringRadius * std::sin(rotaryStartAngle),
                centreY - ringRadius * std::cos(rotaryStartAngle),
                juce::Colour(COL_GRAD_RED),
                centreX + ringRadius * std::sin(rotaryEndAngle),
                centreY - ringRadius * std::cos(rotaryEndAngle),
                false);
            g.setGradientFill(arcGrad);
            g.strokePath(valueArc, juce::PathStrokeType(2.75f,
                juce::PathStrokeType::curved,
                juce::PathStrokeType::rounded));
        }

        g.setColour(juce::Colour(0xaa000000u));
        g.fillEllipse(centreX - radius + 2.0f, centreY - radius + 4.0f,
            radius * 2.0f, radius * 2.0f);

        {
            juce::ColourGradient bodyGrad(
                juce::Colour(COL_KNOB_BODY_HI), centreX - radius * 0.40f, centreY - radius * 0.50f,
                juce::Colour(COL_KNOB_BODY_LO), centreX + radius * 0.60f, centreY + radius * 0.60f, true);
            bodyGrad.addColour(0.45, juce::Colour(0xff8a8e98u));
            bodyGrad.addColour(0.75, juce::Colour(0xff50545cu));
            g.setGradientFill(bodyGrad);
            g.fillEllipse(centreX - radius, centreY - radius, radius * 2.0f, radius * 2.0f);

            juce::ColourGradient spec(
                juce::Colours::white.withAlpha(0.55f),
                centreX - radius * 0.35f, centreY - radius * 0.40f,
                juce::Colours::transparentWhite,
                centreX - radius * 0.05f, centreY - radius * 0.05f, true);
            g.setGradientFill(spec);
            g.fillEllipse(centreX - radius * 0.65f, centreY - radius * 0.65f,
                radius * 1.0f, radius * 1.0f);
        }

        g.setColour(juce::Colours::black);
        g.drawEllipse(centreX - radius, centreY - radius, radius * 2.0f, radius * 2.0f, 1.5f);
        g.setColour(juce::Colour(COL_WASP_YELLOW).withAlpha(0.45f));
        g.drawEllipse(centreX - radius + 1.5f, centreY - radius + 1.5f,
            (radius - 1.5f) * 2.0f, (radius - 1.5f) * 2.0f, 0.7f);

        {
            const float innerR = radius * 0.42f;
            const float outerR = radius * 0.92f;
            const float sx = centreX + innerR * std::sin(angle);
            const float sy = centreY - innerR * std::cos(angle);
            const float ex = centreX + outerR * std::sin(angle);
            const float ey = centreY - outerR * std::cos(angle);
            g.setColour(juce::Colour(COL_KNOB_MARKER).withAlpha(0.35f));
            g.drawLine(sx, sy, ex, ey, 4.0f);
            g.setColour(juce::Colour(COL_KNOB_MARKER));
            g.drawLine(sx, sy, ex, ey, 1.8f);
        }
    }

    void drawToggleButton(juce::Graphics& g, juce::ToggleButton& button, bool, bool) override
    {
        auto bounds = button.getLocalBounds().toFloat().reduced(1.0f);
        const bool toggled = button.getToggleState();
        const float ledSize = juce::jmin(bounds.getHeight() - 4.0f, 12.0f);
        const float ledX = bounds.getX() + 2.0f;
        const float ledY = bounds.getCentreY() - ledSize * 0.5f;

        g.setColour(juce::Colour(0xff0a0c10u));
        g.fillEllipse(ledX - 1.5f, ledY - 1.5f, ledSize + 3.0f, ledSize + 3.0f);

        g.setColour(toggled ? juce::Colour(COL_WASP_YELLOW) : juce::Colour(COL_BUTTON_OFF));
        g.fillEllipse(ledX, ledY, ledSize, ledSize);

        g.setColour(juce::Colours::black);
        g.drawEllipse(ledX, ledY, ledSize, ledSize, 1.0f);

        g.setColour(juce::Colour(toggled ? COL_TEXT_PRIMARY : COL_TEXT_SECONDARY));
        g.setFont(juce::FontOptions("Courier New", 10.0f, juce::Font::bold));
        g.drawText(button.getButtonText(), (int)(ledX + ledSize + 4.0f), (int)bounds.getY(),
            (int)(bounds.getWidth() - ledSize - 8.0f), (int)bounds.getHeight(),
            juce::Justification::centredLeft, false);
    }

    juce::Font getLabelFont(juce::Label&) override
    {
        return juce::FontOptions("Courier New", 10.0f, juce::Font::bold);
    }

    void drawComboBox(juce::Graphics& g, int width, int height, bool, int buttonX, int buttonY,
        int buttonW, int buttonH, juce::ComboBox&) override
    {
        auto bounds = juce::Rectangle<int>(0, 0, width, height).toFloat();
        g.setColour(juce::Colour(COL_COMBO_BG));
        g.fillRoundedRectangle(bounds, 2.0f);

        juce::ColourGradient underline(
            juce::Colour(COL_GRAD_ORANGE), bounds.getX(), bounds.getBottom(),
            juce::Colour(COL_GRAD_RED), bounds.getRight(), bounds.getBottom(), false);
        g.setGradientFill(underline);
        g.fillRect(bounds.getX(), bounds.getBottom() - 1.5f, bounds.getWidth(), 1.5f);

        g.setColour(juce::Colours::black);
        g.drawRoundedRectangle(bounds.reduced(0.5f), 2.0f, 1.0f);

        juce::Path arrow;
        const float ax = (float)(buttonX + buttonW / 2);
        const float ay = (float)(buttonY + buttonH / 2 - 2);
        arrow.addTriangle(ax - 4.0f, ay, ax + 4.0f, ay, ax, ay + 5.0f);
        g.setColour(juce::Colour(COL_WASP_YELLOW));
        g.fillPath(arrow);
    }
};

//==============================================================================
// Labelled rotary knob
//==============================================================================
class WaspKnob : public juce::Component
{
public:
    juce::Slider slider;
    juce::Label  label;

    WaspKnob(const juce::String& labelText, WaspLookAndFeel& laf)
    {
        slider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
        slider.setLookAndFeel(&laf);
        addAndMakeVisible(slider);

        label.setText(labelText, juce::dontSendNotification);
        label.setJustificationType(juce::Justification::centred);
        label.setFont(juce::FontOptions("Courier New", 9.0f, juce::Font::bold));
        label.setColour(juce::Label::textColourId, juce::Colour(WaspLookAndFeel::COL_TEXT_SECONDARY));
        label.setLookAndFeel(&laf);
        addAndMakeVisible(label);
    }

    ~WaspKnob() override
    {
        slider.setLookAndFeel(nullptr);
        label.setLookAndFeel(nullptr);
    }

    void resized() override
    {
        auto b = getLocalBounds();
        label.setBounds(b.removeFromBottom(14));
        slider.setBounds(b);
    }
};

//==============================================================================
// Section panel
//==============================================================================
class WaspSection : public juce::Component
{
public:
    juce::String title;
    int          paletteIndex = 0;

    WaspSection(const juce::String& t) : title(t) {}

    void setPaletteIndex(int idx) { paletteIndex = ((idx % 3) + 3) % 3; repaint(); }

    void paint(juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        juce::Colour baseCol;
        switch (paletteIndex)
        {
        case 1:  baseCol = juce::Colour(WaspLookAndFeel::COL_PANEL_B); break;
        case 2:  baseCol = juce::Colour(WaspLookAndFeel::COL_PANEL_C); break;
        default: baseCol = juce::Colour(WaspLookAndFeel::COL_PANEL_A); break;
        }

        g.setColour(baseCol);
        g.fillRoundedRectangle(b, 3.0f);

        {
            juce::Graphics::ScopedSaveState save(g);
            juce::Path clip;
            clip.addRoundedRectangle(b, 3.0f);
            g.reduceClipRegion(clip);
            g.setColour(juce::Colour(WaspLookAndFeel::COL_WASP_STRIPE).withAlpha(0.45f));
            for (float y = b.getY() + 18.0f; y < b.getBottom(); y += 3.0f)
                g.fillRect(b.getX(), y, b.getWidth(), 1.0f);
        }

        g.setColour(juce::Colours::black);
        g.drawRoundedRectangle(b.reduced(0.5f), 3.0f, 1.2f);

        juce::Rectangle<float> header(b.getX(), b.getY(), b.getWidth(), 16.0f);
        g.setColour(juce::Colour(WaspLookAndFeel::COL_SECTION_HDR));
        g.fillRoundedRectangle(header, 3.0f);
        g.fillRect(header.withTrimmedTop(4.0f));

        juce::ColourGradient textGrad(
            juce::Colour(WaspLookAndFeel::COL_HDR_TEXT_A), header.getX(), header.getCentreY(),
            juce::Colour(WaspLookAndFeel::COL_HDR_TEXT_B), header.getRight(), header.getCentreY(), false);
        g.setGradientFill(textGrad);
        g.setFont(juce::FontOptions("Courier New", 9.5f, juce::Font::bold));
        g.drawText(title, header.toNearestInt(), juce::Justification::centred, false);

        g.setColour(juce::Colour(WaspLookAndFeel::COL_WASP_AMBER).withAlpha(0.7f));
        g.fillRect(b.getX() + 2.0f, b.getY() + 15.0f, b.getWidth() - 4.0f, 1.0f);
    }
};

//==============================================================================
// Main Editor
//==============================================================================
class WASPAlphaAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    // Default / clamp dimensions. Layout is parametric via uiScale().
    static constexpr int kWindowW = 900;
    static constexpr int kWindowH = 720;
    static constexpr int kWindowWMin = 720;
    static constexpr int kWindowHMin = 560;
    static constexpr int kWindowWMax = 1600;
    static constexpr int kWindowHMax = 1200;
    static constexpr int kReferenceW = 900;

    // Layout constants — class scope so the .cpp's layout methods can read them.
    static constexpr int kKnobPx = 42;
    static constexpr int kKnobLblH = 14;
    static constexpr int kComboH = 18;
    static constexpr int kSectHdrH = 16;
    static constexpr int kInnerPad = 8;

    WASPAlphaAudioProcessorEditor(WASPAlphaAudioProcessor& p);
    ~WASPAlphaAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    WASPAlphaAudioProcessor& audioProcessor;
    WaspLookAndFeel laf;

    //==========================================================================
    // Preset bar
    //==========================================================================
    juce::ComboBox   presetSelector;
    juce::TextButton savePresetButton{ "SAVE" };
    juce::TextButton deletePresetButton{ "DEL" };
    juce::TextButton exportPresetButton{ "EXP" };
    juce::TextButton openFolderButton{ "DIR" };
    bool updatingPresetSelector = false;

    //==========================================================================
    // Sections — ordered to follow signal flow
    //==========================================================================
    WaspSection secVoice{ "VOICE STACK" };
    WaspSection secOsc{ "OSCILLATORS" };
    WaspSection secMix{ "MIX / MOD" };
    WaspSection secFilter{ "FILTER 1" };
    WaspSection secFilter2{ "FILTER 2" };
    WaspSection secRouting{ "FILTER ROUTING" };
    WaspSection secAmpEnv{ "AMP ENV" };
    WaspSection secFltEnv{ "FILTER ENV" };
    WaspSection secModEnv{ "MOD ENV" };
    WaspSection secVelocity{ "VELOCITY" };
    WaspSection secChar{ "CHARACTER" };
    WaspSection secUnison{ "UNISON" };
    WaspSection secLfo1{ "LFO 1" };
    WaspSection secLfo2{ "LFO 2" };
    WaspSection secCV{ "CONTROL VOLTAGE" };
    WaspSection secDx{ "DX FM" };
    WaspSection secFx{ "DISTORTION" };
    WaspSection secDelay{ "DELAY" };
    WaspSection secOutput{ "OUTPUT" };
    WaspSection secCpu{ "CPU SAVER" };

    //==========================================================================
    // Controls
    //==========================================================================
    // Voice stack
    juce::ComboBox voiceConfigCombo;
    WaspKnob       voiceSpread{ "SPREAD", laf };

    // Osc 1
    juce::ComboBox osc1Shape;
    WaspKnob       osc1Coarse{ "COARSE", laf };
    WaspKnob       osc1Fine{ "FINE", laf };
    WaspKnob       osc1Amount{ "AMOUNT", laf };

    // Osc 2
    juce::ComboBox osc2Shape;
    WaspKnob       osc2Coarse{ "COARSE", laf };
    WaspKnob       osc2Fine{ "FINE", laf };
    WaspKnob       osc2Amount{ "AMOUNT", laf };

    // Osc 3
    juce::ComboBox osc3Shape;
    WaspKnob       osc3Amount{ "AMOUNT", laf };

    // Mix / Mod
    WaspKnob mixKnob{ "OSC MIX", laf };
    WaspKnob pwKnob{ "PW", laf };
    WaspKnob fmKnob{ "FM", laf };
    WaspKnob rmKnob{ "RM", laf };

    // Filter 1
    juce::ComboBox fltType;
    juce::ComboBox fltModel;
    WaspKnob       cutoff{ "CUTOFF", laf };
    WaspKnob       resonance{ "RESO", laf };
    WaspKnob       fltEnvAmt{ "ENV AMT", laf };
    WaspKnob       fltKT{ "KEYTRACK", laf };

    // Filter 2
    juce::ComboBox flt2Type;
    juce::ComboBox flt2Model;
    WaspKnob       cutoff2{ "CUTOFF 2", laf };
    WaspKnob       resonance2{ "RESO 2", laf };
    WaspKnob       flt2EnvAmt{ "ENV AMT 2", laf };
    WaspKnob       flt2KT{ "KEYTRK 2", laf };

    // Routing
    juce::ComboBox fltRouting;
    WaspKnob       fltParallelMix{ "1<->2 MIX", laf };

    // Amp Env
    WaspKnob ampA{ "ATK", laf };
    WaspKnob ampD{ "DEC", laf };
    WaspKnob ampS{ "SUS", laf };
    WaspKnob ampR{ "REL", laf };

    // Filter Env
    WaspKnob fltA{ "ATK", laf };
    WaspKnob fltD{ "DEC", laf };
    WaspKnob fltS{ "SUS", laf };
    WaspKnob fltR{ "REL", laf };

    // Mod Env
    WaspKnob       modEnvAtk{ "ATK", laf };
    WaspKnob       modEnvDec{ "DEC", laf };
    WaspKnob       modEnvAmt{ "AMT", laf };
    juce::ComboBox modEnvDest;

    // Velocity
    WaspKnob velToAmp{ "AMP", laf };
    WaspKnob velToFlt{ "FILTER", laf };

    // Character
    WaspKnob           dualVoice{ "DUAL VOICE", laf };
    WaspKnob           waspChar{ "WASP", laf };
    WaspKnob           vcoBinary{ "VCO BINARY", laf };
    juce::ToggleButton cmosFilter{ "CMOS" };

    // Unison
    WaspKnob dualDetune{ "DETUNE", laf };

    // LFO 1
    juce::ComboBox     lfo1Shape;
    juce::ComboBox     lfo1Target;
    WaspKnob           lfo1Freq{ "FREQ", laf };
    WaspKnob           lfo1Amount{ "AMOUNT", laf };
    WaspKnob           lfo1Delay{ "DELAY", laf };
    juce::ToggleButton lfo1Sync{ "SYNC" };
    juce::ToggleButton lfo1Reset{ "RESET" };

    // LFO 2
    juce::ComboBox     lfo2Shape;
    juce::ComboBox     lfo2Target;
    WaspKnob           lfo2Freq{ "FREQ", laf };
    WaspKnob           lfo2Amount{ "AMOUNT", laf };
    WaspKnob           lfo2Delay{ "DELAY", laf };
    juce::ToggleButton lfo2Sync{ "SYNC" };
    juce::ToggleButton lfo2Reset{ "RESET" };

    // CV
    WaspKnob       cvAmount{ "CV AMT", laf };
    juce::ComboBox cvTarget;

    // DX FM
    juce::ToggleButton dxfmEnable{ "ENABLE" };
    WaspKnob           dxfmBlend{ "BLEND", laf };
    WaspKnob           dxCarA{ "CAR ATK", laf };
    WaspKnob           dxCarD{ "CAR DEC", laf };
    WaspKnob           dxCarR{ "CAR REL", laf };
    WaspKnob           dxWave{ "WAVE", laf };
    WaspKnob           dxModI{ "MOD INI", laf };
    WaspKnob           dxModD{ "MOD DEC", laf };
    WaspKnob           dxModS{ "MOD SUS", laf };
    WaspKnob           dxModR{ "MOD REL", laf };
    WaspKnob           dxModV{ "MOD VEL", laf };
    WaspKnob           dxCoarse{ "CRS", laf };
    WaspKnob           dxFine{ "FIN", laf };
    WaspKnob           dxThru{ "THRU", laf };
    WaspKnob           dxOctave{ "OCT", laf };
    WaspKnob           dxTune{ "TUNE", laf };

    // Distortion
    juce::ToggleButton distOn{ "ON" };
    WaspKnob           distDrive{ "DRIVE", laf };
    WaspKnob           distTone{ "TONE", laf };
    juce::ComboBox     distType;

    // Delay
    WaspKnob delayTime{ "TIME", laf };
    WaspKnob delayFeedback{ "FEEDBACK", laf };
    WaspKnob delayMix{ "MIX", laf };

    // Output
    WaspKnob masterVolume{ "VOLUME", laf };

    // CPU Saver — 11 toggles, one per signal-chain stage
    juce::ToggleButton bpFilter1Btn{ "FILTER 1" };
    juce::ToggleButton bpFilter2Btn{ "FILTER 2" };
    juce::ToggleButton bpDelayBtn{ "DELAY" };
    juce::ToggleButton bpDistBtn{ "DISTORTION" };
    juce::ToggleButton bpLfo1Btn{ "LFO 1" };
    juce::ToggleButton bpLfo2Btn{ "LFO 2" };
    juce::ToggleButton bpModEnvBtn{ "MOD ENV" };
    juce::ToggleButton bpCvBtn{ "CV" };
    juce::ToggleButton bpDualVBtn{ "DUAL VOICE" };
    juce::ToggleButton bpWaspCharBtn{ "WASP CHAR" };
    juce::ToggleButton bpVcoBinBtn{ "VCO BINARY" };

    //==========================================================================
    // APVTS attachments
    //==========================================================================
    using SliderAtt = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboAtt = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    using ButtonAtt = juce::AudioProcessorValueTreeState::ButtonAttachment;

    std::unique_ptr<ComboAtt>  attVoiceConfig;
    std::unique_ptr<SliderAtt> attVoiceSpread;

    std::unique_ptr<ComboAtt>  attOsc1Shape, attOsc2Shape, attOsc3Shape;
    std::unique_ptr<SliderAtt> attOsc1Coarse, attOsc1Fine, attOsc1Amount;
    std::unique_ptr<SliderAtt> attOsc2Coarse, attOsc2Fine, attOsc2Amount;
    std::unique_ptr<SliderAtt> attOsc3Amount;
    std::unique_ptr<SliderAtt> attMix, attPW, attFM, attRM;
    std::unique_ptr<ComboAtt>  attFltType, attFltModel;
    std::unique_ptr<SliderAtt> attCutoff, attReso, attFltEnvAmt, attFltKT;
    std::unique_ptr<SliderAtt> attAmpA, attAmpD, attAmpS, attAmpR;
    std::unique_ptr<SliderAtt> attFltA, attFltD, attFltS, attFltR;
    std::unique_ptr<ComboAtt>  attLfo1Shape, attLfo1Target;
    std::unique_ptr<SliderAtt> attLfo1Freq, attLfo1Amt, attLfo1Delay;
    std::unique_ptr<ButtonAtt> attLfo1Sync, attLfo1Reset;
    std::unique_ptr<ComboAtt>  attLfo2Shape, attLfo2Target;
    std::unique_ptr<SliderAtt> attLfo2Freq, attLfo2Amt, attLfo2Delay;
    std::unique_ptr<ButtonAtt> attLfo2Sync, attLfo2Reset;
    std::unique_ptr<ButtonAtt> attDistOn;
    std::unique_ptr<ComboAtt>  attDistType;
    std::unique_ptr<SliderAtt> attDistDrive, attDistTone;
    std::unique_ptr<SliderAtt> attDualVoice, attWaspChar, attVCOBinary, attDualDetune;
    std::unique_ptr<ButtonAtt> attCmosFilter;
    std::unique_ptr<SliderAtt> attCVAmount;
    std::unique_ptr<ComboAtt>  attCVTarget;
    std::unique_ptr<SliderAtt> attModEnvAtk, attModEnvDec, attModEnvAmt;
    std::unique_ptr<ComboAtt>  attModEnvDest;
    std::unique_ptr<SliderAtt> attVelToAmp, attVelToFlt;
    std::unique_ptr<ComboAtt>  attFlt2Type, attFltRouting, attFlt2Model;
    std::unique_ptr<SliderAtt> attCutoff2, attReso2, attFlt2EnvAmt, attFlt2KT, attFltParallelMix;
    std::unique_ptr<SliderAtt> attDelayTime, attDelayFeedback, attDelayMix;
    std::unique_ptr<SliderAtt> attMasterVolume;

    std::unique_ptr<ButtonAtt> attDxfmEnable;
    std::unique_ptr<SliderAtt> attDxfmBlend;
    std::unique_ptr<SliderAtt> attDxCarA, attDxCarD, attDxCarR, attDxWave;
    std::unique_ptr<SliderAtt> attDxModI, attDxModD, attDxModS, attDxModR, attDxModV;
    std::unique_ptr<SliderAtt> attDxCoarse, attDxFine, attDxThru, attDxOctave, attDxTune;

    std::unique_ptr<ButtonAtt> attBpFilter1, attBpFilter2, attBpDelay, attBpDist;
    std::unique_ptr<ButtonAtt> attBpLfo1, attBpLfo2, attBpModEnv, attBpCv;
    std::unique_ptr<ButtonAtt> attBpDualV, attBpWaspChar, attBpVcoBin;

    //==========================================================================
    // Helpers
    //==========================================================================
    void setupCombo(juce::ComboBox& box, const juce::StringArray& items);
    void assignSectionPalettes();

    float uiScale() const;
    int   scaled(int px) const;

    void paintBevelRing(juce::Graphics& g);

    // Row geometry — computed once in resized(), read by layout methods.
    static constexpr int kNumRows = 6;
    int mRowY[kNumRows] = { 0 };
    int mRowH[kNumRows] = { 0 };

    int rowY(int index) const;
    int rowH(int index) const;

    // Band helpers — guarantee combos and knobs never overlap.
    int comboBandY(int rowIdx) const;
    int knobBandY(int rowIdx) const;
    int comboBandH() const;
    int knobBandH() const;

    // Layout methods — one per row, following the signal-flow order.
    //   Row 1: Voice Stack | Oscillators | Mix/Mod | Output
    //   Row 2: Filter 1 | Filter 2 | Routing
    //   Row 3: Amp Env | Filter Env | Mod Env | Velocity | Distortion
    //   Row 4: LFO 1 | LFO 2 | Character | CV | Unison | Delay
    //   Row 5: DX FM
    //   Row 6: CPU Saver (full width, 11 toggles)
    void layoutRow1_VoiceOscMixVol();
    void layoutRow2_FiltersAndRouting();
    void layoutRow3_EnvsVelocityDist();
    void layoutRow4_LfosCharCvUniDelay();
    void layoutRow5_DxFm();
    void layoutRow6_CpuSaver();

    // Preset management
    void refreshPresetList();
    void onPresetSelected(int comboItemId);
    void onSavePresetClicked();
    void onDeletePresetClicked();
    void onExportPresetClicked();
    void onOpenFolderClicked();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WASPAlphaAudioProcessorEditor)
};