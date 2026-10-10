#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WASPAlphaAudioProcessorEditor::WASPAlphaAudioProcessorEditor(WASPAlphaAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    using namespace WaspParams;

    setSize(kWindowW, kWindowH);
    setResizable(true, true);
    setResizeLimits(kWindowWMin, kWindowHMin, kWindowWMax, kWindowHMax);
    if (auto* c = getConstrainer())
        c->setFixedAspectRatio((double)kWindowW / (double)kWindowH);

    // ===== VOICE STACK =====
    setupCombo(voiceConfigCombo, { "SINGLE", "DUAL", "QUAD", "SUPER SAW 7", "SUB LAYER" });
    addAndMakeVisible(secVoice);
    addAndMakeVisible(voiceConfigCombo);
    addAndMakeVisible(voiceSpread);

    // ===== OSCILLATORS =====
    setupCombo(osc1Shape, { "SAW", "SQR", "TRI", "SIN", "303" });
    setupCombo(osc2Shape, { "SAW", "SQR", "TRI", "SIN", "303" });
    setupCombo(osc3Shape, { "SUB", "SUB2", "NOISE" });
    addAndMakeVisible(secOsc);
    addAndMakeVisible(osc1Shape); addAndMakeVisible(osc1Coarse); addAndMakeVisible(osc1Fine); addAndMakeVisible(osc1Amount);
    addAndMakeVisible(osc2Shape); addAndMakeVisible(osc2Coarse); addAndMakeVisible(osc2Fine); addAndMakeVisible(osc2Amount);
    addAndMakeVisible(osc3Shape); addAndMakeVisible(osc3Amount);

    // ===== MIX / MOD =====
    addAndMakeVisible(secMix);
    addAndMakeVisible(mixKnob); addAndMakeVisible(pwKnob); addAndMakeVisible(fmKnob); addAndMakeVisible(rmKnob);

    // ===== FILTER 1 =====
    setupCombo(fltType, { "LP12", "LP24", "HP12", "BP12" });
    setupCombo(fltModel, { "LADDER", "CHAMBERLIN" });
    addAndMakeVisible(secFilter);
    addAndMakeVisible(fltType); addAndMakeVisible(fltModel);
    addAndMakeVisible(cutoff); addAndMakeVisible(resonance); addAndMakeVisible(fltEnvAmt); addAndMakeVisible(fltKT);

    // ===== FILTER 2 =====
    setupCombo(flt2Type, { "LP12", "LP24", "HP12", "BP12" });
    setupCombo(flt2Model, { "LADDER", "CHAMBERLIN" });
    addAndMakeVisible(secFilter2);
    addAndMakeVisible(flt2Type); addAndMakeVisible(flt2Model);
    addAndMakeVisible(cutoff2); addAndMakeVisible(resonance2); addAndMakeVisible(flt2EnvAmt); addAndMakeVisible(flt2KT);

    // ===== FILTER ROUTING =====
    setupCombo(fltRouting, { "F1", "F2", "SERIES", "PARALLEL" });
    addAndMakeVisible(secRouting);
    addAndMakeVisible(fltRouting); addAndMakeVisible(fltParallelMix);

    // ===== ENVELOPES =====
    addAndMakeVisible(secAmpEnv);
    addAndMakeVisible(ampA); addAndMakeVisible(ampD); addAndMakeVisible(ampS); addAndMakeVisible(ampR);
    addAndMakeVisible(secFltEnv);
    addAndMakeVisible(fltA); addAndMakeVisible(fltD); addAndMakeVisible(fltS); addAndMakeVisible(fltR);

    // ===== MOD ENV =====
    setupCombo(modEnvDest, { "PW", "LFO1", "O1 LVL", "O2 PTCH" });
    addAndMakeVisible(secModEnv);
    addAndMakeVisible(modEnvAtk); addAndMakeVisible(modEnvDec);
    addAndMakeVisible(modEnvAmt); addAndMakeVisible(modEnvDest);

    // ===== VELOCITY =====
    addAndMakeVisible(secVelocity);
    addAndMakeVisible(velToAmp); addAndMakeVisible(velToFlt);

    // ===== CHARACTER =====
    cmosFilter.setLookAndFeel(&laf);
    addAndMakeVisible(secChar);
    addAndMakeVisible(dualVoice); addAndMakeVisible(waspChar);
    addAndMakeVisible(vcoBinary); addAndMakeVisible(cmosFilter);

    // ===== UNISON =====
    addAndMakeVisible(secUnison);
    addAndMakeVisible(dualDetune);

    // ===== LFO 1 =====
    setupCombo(lfo1Shape, { "SIN", "TRI", "SAW", "RSAW", "SQR", "S+H" });
    setupCombo(lfo1Target, { "PITCH", "O1", "O2", "PW", "FLT", "AMP", "RESO" });
    lfo1Sync.setLookAndFeel(&laf);
    lfo1Reset.setLookAndFeel(&laf);
    addAndMakeVisible(secLfo1);
    addAndMakeVisible(lfo1Shape); addAndMakeVisible(lfo1Target);
    addAndMakeVisible(lfo1Freq); addAndMakeVisible(lfo1Amount); addAndMakeVisible(lfo1Delay);
    addAndMakeVisible(lfo1Sync); addAndMakeVisible(lfo1Reset);

    // ===== LFO 2 =====
    setupCombo(lfo2Shape, { "SIN", "TRI", "SAW", "RSAW", "SQR", "S+H" });
    setupCombo(lfo2Target, { "PITCH", "O1", "O2", "PW", "FLT", "AMP", "RESO" });
    lfo2Sync.setLookAndFeel(&laf);
    lfo2Reset.setLookAndFeel(&laf);
    addAndMakeVisible(secLfo2);
    addAndMakeVisible(lfo2Shape); addAndMakeVisible(lfo2Target);
    addAndMakeVisible(lfo2Freq); addAndMakeVisible(lfo2Amount); addAndMakeVisible(lfo2Delay);
    addAndMakeVisible(lfo2Sync); addAndMakeVisible(lfo2Reset);

    // ===== CV =====
    setupCombo(cvTarget, { "FLT", "O2 PTCH", "PW", "AMP" });
    addAndMakeVisible(secCV);
    addAndMakeVisible(cvAmount); addAndMakeVisible(cvTarget);

    // ===== DX FM =====
    dxfmEnable.setLookAndFeel(&laf);
    addAndMakeVisible(secDx);
    addAndMakeVisible(dxfmEnable); addAndMakeVisible(dxfmBlend);
    addAndMakeVisible(dxCarA); addAndMakeVisible(dxCarD); addAndMakeVisible(dxCarR); addAndMakeVisible(dxWave);
    addAndMakeVisible(dxModI); addAndMakeVisible(dxModD); addAndMakeVisible(dxModS); addAndMakeVisible(dxModR); addAndMakeVisible(dxModV);
    addAndMakeVisible(dxCoarse); addAndMakeVisible(dxFine); addAndMakeVisible(dxThru);
    addAndMakeVisible(dxOctave); addAndMakeVisible(dxTune);

    // ===== DISTORTION =====
    distOn.setLookAndFeel(&laf);
    setupCombo(distType, { "SOFT", "HARD" });
    addAndMakeVisible(secFx);
    addAndMakeVisible(distOn); addAndMakeVisible(distDrive); addAndMakeVisible(distTone); addAndMakeVisible(distType);

    // ===== DELAY =====
    addAndMakeVisible(secDelay);
    addAndMakeVisible(delayTime); addAndMakeVisible(delayFeedback); addAndMakeVisible(delayMix);

    // ===== OUTPUT =====
    addAndMakeVisible(secOutput);
    addAndMakeVisible(masterVolume);

    // ===== CPU SAVER — 11 toggles =====
    bpFilter1Btn.setLookAndFeel(&laf);
    bpFilter2Btn.setLookAndFeel(&laf);
    bpDelayBtn.setLookAndFeel(&laf);
    bpDistBtn.setLookAndFeel(&laf);
    bpLfo1Btn.setLookAndFeel(&laf);
    bpLfo2Btn.setLookAndFeel(&laf);
    bpModEnvBtn.setLookAndFeel(&laf);
    bpCvBtn.setLookAndFeel(&laf);
    bpDualVBtn.setLookAndFeel(&laf);
    bpWaspCharBtn.setLookAndFeel(&laf);
    bpVcoBinBtn.setLookAndFeel(&laf);
    addAndMakeVisible(secCpu);
    addAndMakeVisible(bpFilter1Btn); addAndMakeVisible(bpFilter2Btn);
    addAndMakeVisible(bpDelayBtn);   addAndMakeVisible(bpDistBtn);
    addAndMakeVisible(bpLfo1Btn);    addAndMakeVisible(bpLfo2Btn);
    addAndMakeVisible(bpModEnvBtn);  addAndMakeVisible(bpCvBtn);
    addAndMakeVisible(bpDualVBtn);   addAndMakeVisible(bpWaspCharBtn);
    addAndMakeVisible(bpVcoBinBtn);

    // ===== PRESET BAR =====
    presetSelector.setLookAndFeel(&laf);
    presetSelector.setTextWhenNothingSelected("SELECT PRESET");
    savePresetButton.setLookAndFeel(&laf);
    deletePresetButton.setLookAndFeel(&laf);
    exportPresetButton.setLookAndFeel(&laf);
    openFolderButton.setLookAndFeel(&laf);
    addAndMakeVisible(presetSelector);
    addAndMakeVisible(savePresetButton);
    addAndMakeVisible(deletePresetButton);
    addAndMakeVisible(exportPresetButton);
    addAndMakeVisible(openFolderButton);

    refreshPresetList();

    presetSelector.onChange = [this] { if (updatingPresetSelector) return; onPresetSelected(presetSelector.getSelectedId()); };
    savePresetButton.onClick = [this] { onSavePresetClicked(); };
    deletePresetButton.onClick = [this] { onDeletePresetClicked(); };
    exportPresetButton.onClick = [this] { onExportPresetClicked(); };
    openFolderButton.onClick = [this] { onOpenFolderClicked(); };

    // ===== APVTS ATTACHMENTS =====
    attVoiceConfig = std::make_unique<ComboAtt>(audioProcessor.apvts, VOICE_CONFIG, voiceConfigCombo);
    attVoiceSpread = std::make_unique<SliderAtt>(audioProcessor.apvts, VOICE_SPREAD, voiceSpread.slider);

    attOsc1Shape = std::make_unique<ComboAtt>(audioProcessor.apvts, OSC1_SHAPE, osc1Shape);
    attOsc1Coarse = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC1_COARSE, osc1Coarse.slider);
    attOsc1Fine = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC1_FINE, osc1Fine.slider);
    attOsc1Amount = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC1_AMOUNT, osc1Amount.slider);

    attOsc2Shape = std::make_unique<ComboAtt>(audioProcessor.apvts, OSC2_SHAPE, osc2Shape);
    attOsc2Coarse = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC2_COARSE, osc2Coarse.slider);
    attOsc2Fine = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC2_FINE, osc2Fine.slider);
    attOsc2Amount = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC2_AMOUNT, osc2Amount.slider);

    attOsc3Shape = std::make_unique<ComboAtt>(audioProcessor.apvts, OSC3_SHAPE, osc3Shape);
    attOsc3Amount = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC3_AMOUNT, osc3Amount.slider);

    attMix = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC_MIX, mixKnob.slider);
    attPW = std::make_unique<SliderAtt>(audioProcessor.apvts, PULSE_WIDTH, pwKnob.slider);
    attFM = std::make_unique<SliderAtt>(audioProcessor.apvts, FM_AMOUNT, fmKnob.slider);
    attRM = std::make_unique<SliderAtt>(audioProcessor.apvts, RM_AMOUNT, rmKnob.slider);

    attFltType = std::make_unique<ComboAtt>(audioProcessor.apvts, FLT_TYPE, fltType);
    attFltModel = std::make_unique<ComboAtt>(audioProcessor.apvts, FLT_MODEL, fltModel);
    attCutoff = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_CUTOFF, cutoff.slider);
    attReso = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_RESO, resonance.slider);
    attFltEnvAmt = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_ENV_AMT, fltEnvAmt.slider);
    attFltKT = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_KEYTRACK, fltKT.slider);

    attFlt2Type = std::make_unique<ComboAtt>(audioProcessor.apvts, FLT2_TYPE, flt2Type);
    attFlt2Model = std::make_unique<ComboAtt>(audioProcessor.apvts, FLT2_MODEL, flt2Model);
    attCutoff2 = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT2_CUTOFF, cutoff2.slider);
    attReso2 = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT2_RESO, resonance2.slider);
    attFlt2EnvAmt = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT2_ENV_AMT, flt2EnvAmt.slider);
    attFlt2KT = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT2_KEYTRACK, flt2KT.slider);

    attFltRouting = std::make_unique<ComboAtt>(audioProcessor.apvts, FLT_ROUTING, fltRouting);
    attFltParallelMix = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_PARALLEL_MIX, fltParallelMix.slider);

    attAmpA = std::make_unique<SliderAtt>(audioProcessor.apvts, AMP_ATTACK, ampA.slider);
    attAmpD = std::make_unique<SliderAtt>(audioProcessor.apvts, AMP_DECAY, ampD.slider);
    attAmpS = std::make_unique<SliderAtt>(audioProcessor.apvts, AMP_SUSTAIN, ampS.slider);
    attAmpR = std::make_unique<SliderAtt>(audioProcessor.apvts, AMP_RELEASE, ampR.slider);

    attFltA = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_ATTACK, fltA.slider);
    attFltD = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_DECAY, fltD.slider);
    attFltS = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_SUSTAIN, fltS.slider);
    attFltR = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_RELEASE, fltR.slider);

    attLfo1Shape = std::make_unique<ComboAtt>(audioProcessor.apvts, LFO1_SHAPE, lfo1Shape);
    attLfo1Target = std::make_unique<ComboAtt>(audioProcessor.apvts, LFO1_TARGET, lfo1Target);
    attLfo1Freq = std::make_unique<SliderAtt>(audioProcessor.apvts, LFO1_FREQ, lfo1Freq.slider);
    attLfo1Amt = std::make_unique<SliderAtt>(audioProcessor.apvts, LFO1_AMOUNT, lfo1Amount.slider);
    attLfo1Delay = std::make_unique<SliderAtt>(audioProcessor.apvts, LFO1_DELAY, lfo1Delay.slider);
    attLfo1Sync = std::make_unique<ButtonAtt>(audioProcessor.apvts, LFO1_SYNC, lfo1Sync);
    attLfo1Reset = std::make_unique<ButtonAtt>(audioProcessor.apvts, LFO1_RESET, lfo1Reset);

    attLfo2Shape = std::make_unique<ComboAtt>(audioProcessor.apvts, LFO2_SHAPE, lfo2Shape);
    attLfo2Target = std::make_unique<ComboAtt>(audioProcessor.apvts, LFO2_TARGET, lfo2Target);
    attLfo2Freq = std::make_unique<SliderAtt>(audioProcessor.apvts, LFO2_FREQ, lfo2Freq.slider);
    attLfo2Amt = std::make_unique<SliderAtt>(audioProcessor.apvts, LFO2_AMOUNT, lfo2Amount.slider);
    attLfo2Delay = std::make_unique<SliderAtt>(audioProcessor.apvts, LFO2_DELAY, lfo2Delay.slider);
    attLfo2Sync = std::make_unique<ButtonAtt>(audioProcessor.apvts, LFO2_SYNC, lfo2Sync);
    attLfo2Reset = std::make_unique<ButtonAtt>(audioProcessor.apvts, LFO2_RESET, lfo2Reset);

    attDistOn = std::make_unique<ButtonAtt>(audioProcessor.apvts, DIST_ON, distOn);
    attDistDrive = std::make_unique<SliderAtt>(audioProcessor.apvts, DIST_DRIVE, distDrive.slider);
    attDistTone = std::make_unique<SliderAtt>(audioProcessor.apvts, DIST_TONE, distTone.slider);
    attDistType = std::make_unique<ComboAtt>(audioProcessor.apvts, DIST_TYPE, distType);

    attDualVoice = std::make_unique<SliderAtt>(audioProcessor.apvts, DUAL_VOICE, dualVoice.slider);
    attDualDetune = std::make_unique<SliderAtt>(audioProcessor.apvts, DUAL_DETUNE, dualDetune.slider);
    attWaspChar = std::make_unique<SliderAtt>(audioProcessor.apvts, WASP_CHAR, waspChar.slider);
    attVCOBinary = std::make_unique<SliderAtt>(audioProcessor.apvts, VCO_BINARY, vcoBinary.slider);
    attCmosFilter = std::make_unique<ButtonAtt>(audioProcessor.apvts, CMOS_FILTER, cmosFilter);

    attCVAmount = std::make_unique<SliderAtt>(audioProcessor.apvts, CV_AMOUNT, cvAmount.slider);
    attCVTarget = std::make_unique<ComboAtt>(audioProcessor.apvts, CV_TARGET, cvTarget);

    attModEnvAtk = std::make_unique<SliderAtt>(audioProcessor.apvts, MODENV_ATTACK, modEnvAtk.slider);
    attModEnvDec = std::make_unique<SliderAtt>(audioProcessor.apvts, MODENV_DECAY, modEnvDec.slider);
    attModEnvAmt = std::make_unique<SliderAtt>(audioProcessor.apvts, MODENV_AMOUNT, modEnvAmt.slider);
    attModEnvDest = std::make_unique<ComboAtt>(audioProcessor.apvts, MODENV_DEST, modEnvDest);

    attVelToAmp = std::make_unique<SliderAtt>(audioProcessor.apvts, VEL_TO_AMP, velToAmp.slider);
    attVelToFlt = std::make_unique<SliderAtt>(audioProcessor.apvts, VEL_TO_FILTER, velToFlt.slider);

    attDelayTime = std::make_unique<SliderAtt>(audioProcessor.apvts, DELAY_TIME_MS, delayTime.slider);
    attDelayFeedback = std::make_unique<SliderAtt>(audioProcessor.apvts, DELAY_FEEDBACK, delayFeedback.slider);
    attDelayMix = std::make_unique<SliderAtt>(audioProcessor.apvts, DELAY_MIX, delayMix.slider);

    attMasterVolume = std::make_unique<SliderAtt>(audioProcessor.apvts, MASTER_VOLUME, masterVolume.slider);

    attDxfmEnable = std::make_unique<ButtonAtt>(audioProcessor.apvts, DXFM_ENABLE, dxfmEnable);
    attDxfmBlend = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_BLEND, dxfmBlend.slider);
    attDxCarA = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_CAR_ATK, dxCarA.slider);
    attDxCarD = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_CAR_DEC, dxCarD.slider);
    attDxCarR = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_CAR_REL, dxCarR.slider);
    attDxWave = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_WAVE, dxWave.slider);
    attDxModI = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_MOD_INIT, dxModI.slider);
    attDxModD = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_MOD_DEC, dxModD.slider);
    attDxModS = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_MOD_SUS, dxModS.slider);
    attDxModR = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_MOD_REL, dxModR.slider);
    attDxModV = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_MOD_VEL, dxModV.slider);
    attDxCoarse = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_COARSE, dxCoarse.slider);
    attDxFine = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_FINE, dxFine.slider);
    attDxThru = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_MOD_THRU, dxThru.slider);
    attDxOctave = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_OCTAVE, dxOctave.slider);
    attDxTune = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_TUNE, dxTune.slider);

    attBpFilter1 = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_FILTER1, bpFilter1Btn);
    attBpFilter2 = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_FILTER2, bpFilter2Btn);
    attBpDelay = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_DELAY, bpDelayBtn);
    attBpDist = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_DIST, bpDistBtn);
    attBpLfo1 = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_LFO1, bpLfo1Btn);
    attBpLfo2 = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_LFO2, bpLfo2Btn);
    attBpModEnv = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_MODENV, bpModEnvBtn);
    attBpCv = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_CV, bpCvBtn);
    attBpDualV = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_DUALVOICE, bpDualVBtn);
    attBpWaspChar = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_WASPCHAR, bpWaspCharBtn);
    attBpVcoBin = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_VCOBIN, bpVcoBinBtn);

    assignSectionPalettes();
}

WASPAlphaAudioProcessorEditor::~WASPAlphaAudioProcessorEditor()
{
    presetSelector.setLookAndFeel(nullptr);
    savePresetButton.setLookAndFeel(nullptr);
    deletePresetButton.setLookAndFeel(nullptr);
    exportPresetButton.setLookAndFeel(nullptr);
    openFolderButton.setLookAndFeel(nullptr);

    osc1Shape.setLookAndFeel(nullptr);
    osc2Shape.setLookAndFeel(nullptr);
    osc3Shape.setLookAndFeel(nullptr);
    fltType.setLookAndFeel(nullptr);
    fltModel.setLookAndFeel(nullptr);
    flt2Type.setLookAndFeel(nullptr);
    flt2Model.setLookAndFeel(nullptr);
    fltRouting.setLookAndFeel(nullptr);
    lfo1Shape.setLookAndFeel(nullptr);
    lfo1Target.setLookAndFeel(nullptr);
    lfo1Sync.setLookAndFeel(nullptr);
    lfo1Reset.setLookAndFeel(nullptr);
    lfo2Shape.setLookAndFeel(nullptr);
    lfo2Target.setLookAndFeel(nullptr);
    lfo2Sync.setLookAndFeel(nullptr);
    lfo2Reset.setLookAndFeel(nullptr);
    distOn.setLookAndFeel(nullptr);
    distType.setLookAndFeel(nullptr);
    cmosFilter.setLookAndFeel(nullptr);
    cvTarget.setLookAndFeel(nullptr);
    modEnvDest.setLookAndFeel(nullptr);
    dxfmEnable.setLookAndFeel(nullptr);
    bpFilter1Btn.setLookAndFeel(nullptr);
    bpFilter2Btn.setLookAndFeel(nullptr);
    bpDelayBtn.setLookAndFeel(nullptr);
    bpDistBtn.setLookAndFeel(nullptr);
    bpLfo1Btn.setLookAndFeel(nullptr);
    bpLfo2Btn.setLookAndFeel(nullptr);
    bpModEnvBtn.setLookAndFeel(nullptr);
    bpCvBtn.setLookAndFeel(nullptr);
    bpDualVBtn.setLookAndFeel(nullptr);
    bpWaspCharBtn.setLookAndFeel(nullptr);
    bpVcoBinBtn.setLookAndFeel(nullptr);
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::setupCombo(juce::ComboBox& box, const juce::StringArray& items)
{
    box.setLookAndFeel(&laf);
    int id = 1;
    for (auto& item : items)
        box.addItem(item, id++);
    box.setSelectedId(1, juce::dontSendNotification);
}

//==============================================================================
float WASPAlphaAudioProcessorEditor::uiScale() const
{
    const float s = (float)getWidth() / (float)kReferenceW;
    return juce::jlimit(0.80f, 1.60f, s);
}

int WASPAlphaAudioProcessorEditor::scaled(int px) const
{
    return (int)std::round((float)px * uiScale());
}

//==============================================================================
int WASPAlphaAudioProcessorEditor::rowY(int index) const
{
    return (index >= 0 && index < kNumRows) ? mRowY[index] : 0;
}

int WASPAlphaAudioProcessorEditor::rowH(int index) const
{
    return (index >= 0 && index < kNumRows) ? mRowH[index] : 0;
}

//==============================================================================
int WASPAlphaAudioProcessorEditor::comboBandH() const
{
    return scaled(kComboH);
}

int WASPAlphaAudioProcessorEditor::knobBandH() const
{
    return scaled(kKnobPx) + scaled(kKnobLblH);
}

int WASPAlphaAudioProcessorEditor::comboBandY(int rowIdx) const
{
    const int y = rowY(rowIdx);
    const int hdrH = scaled(kSectHdrH);
    return y + hdrH + scaled(3);
}

int WASPAlphaAudioProcessorEditor::knobBandY(int rowIdx) const
{
    return comboBandY(rowIdx) + comboBandH() + scaled(4);
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::assignSectionPalettes()
{
    // Alternate 0/1/2 across adjacent sections so nothing repeats.
    secVoice.setPaletteIndex(2);
    secOsc.setPaletteIndex(0);
    secMix.setPaletteIndex(1);

    secFilter.setPaletteIndex(0);
    secFilter2.setPaletteIndex(2);
    secRouting.setPaletteIndex(1);

    secAmpEnv.setPaletteIndex(1);
    secFltEnv.setPaletteIndex(2);
    secModEnv.setPaletteIndex(0);
    secVelocity.setPaletteIndex(1);
    secFx.setPaletteIndex(2);

    secLfo1.setPaletteIndex(0);
    secLfo2.setPaletteIndex(1);
    secChar.setPaletteIndex(2);
    secCV.setPaletteIndex(0);
    secUnison.setPaletteIndex(1);
    secDelay.setPaletteIndex(2);

    secDx.setPaletteIndex(1);
    secOutput.setPaletteIndex(0);
    secCpu.setPaletteIndex(2);
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::paintBevelRing(juce::Graphics& g)
{
    auto r = getLocalBounds().toFloat();

    g.setColour(juce::Colour(WaspLookAndFeel::COL_CASE_OUTER));
    g.drawRect(r, 5.0f);

    g.setColour(juce::Colour(WaspLookAndFeel::COL_CASE_MID));
    g.drawRect(r.reduced(1.0f), 3.0f);

    g.setColour(juce::Colour(WaspLookAndFeel::COL_CASE_HILITE).withAlpha(0.85f));
    g.drawRect(r.reduced(3.0f), 1.0f);

    g.setColour(juce::Colours::black.withAlpha(0.55f));
    g.drawRect(r.reduced(4.5f), 1.0f);

    g.setColour(juce::Colour(WaspLookAndFeel::COL_WASP_AMBER).withAlpha(0.35f));
    g.drawRect(r.reduced(6.0f), 1.0f);
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(WaspLookAndFeel::COL_BODY_BG));
    g.setColour(juce::Colour(WaspLookAndFeel::COL_WASP_STRIPE).withAlpha(0.22f));
    for (int y = 0; y < getHeight(); y += 4)
        g.fillRect(0, y, getWidth(), 1);

    const int headerH = scaled(34);
    juce::Rectangle<int> header(0, 0, getWidth(), headerH);
    g.setColour(juce::Colour(0xff0f1114u));
    g.fillRect(header);

    juce::ColourGradient hdrGrad(
        juce::Colour(WaspLookAndFeel::COL_GRAD_ORANGE).withAlpha(0.20f), 0.0f, 0.0f,
        juce::Colour(WaspLookAndFeel::COL_GRAD_RED).withAlpha(0.25f), (float)getWidth(), 0.0f, false);
    g.setGradientFill(hdrGrad);
    g.fillRect(header);

    juce::ColourGradient accentGrad(
        juce::Colour(WaspLookAndFeel::COL_GRAD_ORANGE), 0.0f, (float)(headerH - 1),
        juce::Colour(WaspLookAndFeel::COL_GRAD_RED), (float)getWidth(), (float)(headerH - 1), false);
    g.setGradientFill(accentGrad);
    g.fillRect(0, headerH - 1, getWidth(), 2);

    {
        const int titleH = juce::jmax(11, scaled(18));
        const auto font = juce::Font(juce::FontOptions("Courier New", (float)titleH, juce::Font::bold));
        juce::Rectangle<int> nameArea(scaled(10), 0, scaled(240), headerH);
        juce::ColourGradient nameGrad(
            juce::Colour(WaspLookAndFeel::COL_HDR_TEXT_A), (float)nameArea.getX(), (float)(headerH / 2),
            juce::Colour(WaspLookAndFeel::COL_HDR_TEXT_B), (float)nameArea.getRight(), (float)(headerH / 2), false);
        g.setGradientFill(nameGrad);
        g.setFont(font);
        g.drawText("The Stinger", nameArea, juce::Justification::centredLeft, false);
    }

    g.setColour(juce::Colour(WaspLookAndFeel::COL_TEXT_SECONDARY));
    g.setFont(juce::FontOptions("Courier New", (float)juce::jmax(7, scaled(8)), juce::Font::plain));
    g.drawText("AlphaAudio  |  DronerrEdition",
        scaled(248), 0, scaled(180), headerH,
        juce::Justification::centredLeft, false);

    paintBevelRing(g);
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::resized()
{
    // ---- Header / preset bar ----
    const int headerH = scaled(34);
    const int barH = scaled(20);
    const int barY = (headerH - barH) / 2;

    const int saveW = scaled(42);
    const int deleteW = scaled(42);
    const int exportW = scaled(42);
    const int folderW = scaled(42);
    const int btnGap = scaled(3);
    const int comboW = scaled(200);
    const int rightPad = scaled(12);

    const int buttonsTotalW = saveW + deleteW + exportW + folderW + 3 * btnGap;
    const int comboX = getWidth() - rightPad - buttonsTotalW - comboW - scaled(6);

    presetSelector.setBounds(comboX, barY, comboW, barH);

    int bx = comboX + comboW + scaled(6);
    savePresetButton.setBounds(bx, barY, saveW, barH);     bx += saveW + btnGap;
    deletePresetButton.setBounds(bx, barY, deleteW, barH); bx += deleteW + btnGap;
    exportPresetButton.setBounds(bx, barY, exportW, barH); bx += exportW + btnGap;
    openFolderButton.setBounds(bx, barY, folderW, barH);

    // ---- Six content rows ----
    // Weights reflect how much content each row carries after the reshuffle.
    // R3 now holds 5 panels (Dist moved in), R4 now holds 6 (Delay moved in),
    // R6 holds 11 toggles in a 4×3 grid.
    const int pad = scaled(5);
    const int top = headerH + scaled(3);
    const int bottom = getHeight() - pad;

    const float weights[kNumRows] = {
        1.10f,  // R1 voice + osc + mix + vol
        0.92f,  // R2 filters + routing
        1.05f,  // R3 enves + velocity + distortion (5 panels)
        1.10f,  // R4 lfos + character + cv + unison + delay (6 panels)
        0.92f,  // R5 dx fm
        0.86f   // R6 cpu saver (4×3 toggle grid)
    };
    float tot = 0.0f;
    for (float w : weights) tot += w;

    const int gapsH = (kNumRows - 1) * pad;
    const int availH = bottom - top - gapsH;

    int y = top;
    for (int i = 0; i < kNumRows; ++i)
    {
        mRowY[i] = y;
        mRowH[i] = (int)std::round((float)availH * (weights[i] / tot));
        y += mRowH[i] + pad;
    }

    layoutRow1_VoiceOscMixVol();
    layoutRow2_FiltersAndRouting();
    layoutRow3_EnvsVelocityDist();
    layoutRow4_LfosCharCvUniDelay();
    layoutRow5_DxFm();
    layoutRow6_CpuSaver();
}

//==============================================================================
// ROW 1 — Voice Stack + Oscillators + Mix/Mod + Master Volume
//==============================================================================
void WASPAlphaAudioProcessorEditor::layoutRow1_VoiceOscMixVol()
{
    const int y = rowY(0);
    const int h = rowH(0);
    const int pad = scaled(5);
    const int gap = scaled(6);
    const int k = scaled(kKnobPx);
    const int cH = comboBandH();
    const int ipad = scaled(kInnerPad);

    const int knobH = knobBandH();
    const int comboY = comboBandY(0);
    const int knobY = knobBandY(0);

    // ----- Voice Stack (leftmost) -----
    const int voiceW = scaled(150);
    secVoice.setBounds(pad, y, voiceW, h);
    voiceConfigCombo.setBounds(pad + ipad, comboY, voiceW - 2 * ipad, cH);
    voiceSpread.setBounds(pad + ipad + (voiceW - 2 * ipad - k) / 2, knobY, k, knobH);

    // ----- Master Volume (rightmost) -----
    const int volW = k + 2 * ipad + scaled(10);
    const int volX = getWidth() - pad - volW;
    secOutput.setBounds(volX, y, volW, h);
    masterVolume.setBounds(volX + ipad + (volW - 2 * ipad - k) / 2, knobY, k, knobH);

    // ----- Mix/Mod (left of volume) -----
    const int mixW = 4 * (k + gap) + 2 * ipad;
    const int mixX = volX - pad - mixW;
    secMix.setBounds(mixX, y, mixW, h);
    mixKnob.setBounds(mixX + ipad, knobY, k, knobH);
    pwKnob.setBounds(mixX + ipad + (k + gap), knobY, k, knobH);
    fmKnob.setBounds(mixX + ipad + 2 * (k + gap), knobY, k, knobH);
    rmKnob.setBounds(mixX + ipad + 3 * (k + gap), knobY, k, knobH);

    // ----- Oscillators (middle) -----
    // Three groups, each 3 knobs wide. Osc 3 uses the first two slots of its
    // group so its shape combo and amount knob line up under Osc 1 / Osc 2.
    const int oscX = pad + voiceW + pad;
    const int oscW = mixX - pad - oscX;
    secOsc.setBounds(oscX, y, oscW, h);

    const int comboW = scaled(64);
    const int groupW = 3 * (k + gap);

    const int totalNeeded = groupW * 3;
    const int freeSpace = oscW - 2 * ipad - totalNeeded;
    const int extraPerSlot = juce::jmax(0, freeSpace / 4);

    const int gx1 = oscX + ipad + extraPerSlot;
    const int gx2 = gx1 + groupW + extraPerSlot;
    const int gx3 = gx2 + groupW + extraPerSlot;

    auto placeOscGroup = [&](int gx, juce::ComboBox& shape,
        WaspKnob* c1, WaspKnob* c2, WaspKnob* c3)
        {
            shape.setBounds(gx, comboY, comboW, cH);
            if (c1) c1->setBounds(gx, knobY, k, knobH);
            if (c2) c2->setBounds(gx + (k + gap), knobY, k, knobH);
            if (c3) c3->setBounds(gx + 2 * (k + gap), knobY, k, knobH);
        };

    placeOscGroup(gx1, osc1Shape, &osc1Coarse, &osc1Fine, &osc1Amount);
    placeOscGroup(gx2, osc2Shape, &osc2Coarse, &osc2Fine, &osc2Amount);
    placeOscGroup(gx3, osc3Shape, nullptr, nullptr, &osc3Amount);
}

//==============================================================================
// ROW 2 — Filter 1 + Filter 2 + Filter Routing
//==============================================================================
void WASPAlphaAudioProcessorEditor::layoutRow2_FiltersAndRouting()
{
    const int y = rowY(1);
    const int h = rowH(1);
    const int pad = scaled(5);
    const int gap = scaled(6);
    const int k = scaled(kKnobPx);
    const int cH = comboBandH();
    const int ipad = scaled(kInnerPad);

    const int knobH = knobBandH();
    const int comboY = comboBandY(1);
    const int knobY = knobBandY(1);

    const int routeW = scaled(150);

    const int availW = getWidth() - 2 * pad - routeW - pad;
    const int f1W = availW / 2;
    const int f2W = availW - f1W;

    auto placeFilter = [&](int x, int w, juce::ComboBox& type, juce::ComboBox& model,
        WaspKnob& cut, WaspKnob& res, WaspKnob& env, WaspKnob& kt)
        {
            const int typeW = scaled(66);
            const int modelW = scaled(70);
            type.setBounds(x + ipad, comboY, typeW, cH);
            model.setBounds(x + ipad + typeW + gap, comboY, modelW, cH);

            const int knobsX = x + ipad;
            cut.setBounds(knobsX, knobY, k, knobH);
            res.setBounds(knobsX + (k + gap), knobY, k, knobH);
            env.setBounds(knobsX + 2 * (k + gap), knobY, k, knobH);
            kt.setBounds(knobsX + 3 * (k + gap), knobY, k, knobH);
        };

    secFilter.setBounds(pad, y, f1W, h);
    placeFilter(pad, f1W, fltType, fltModel, cutoff, resonance, fltEnvAmt, fltKT);

    secFilter2.setBounds(pad + f1W + pad, y, f2W, h);
    placeFilter(pad + f1W + pad, f2W, flt2Type, flt2Model, cutoff2, resonance2, flt2EnvAmt, flt2KT);

    const int routeX = pad + f1W + pad + f2W + pad;
    secRouting.setBounds(routeX, y, routeW, h);
    fltRouting.setBounds(routeX + ipad, comboY, routeW - 2 * ipad, cH);
    fltParallelMix.setBounds(routeX + ipad + (routeW - 2 * ipad - k) / 2, knobY, k, knobH);
}

//==============================================================================
// ROW 3 — Amp Env + Filter Env + Mod Env + Velocity + Distortion
//==============================================================================
void WASPAlphaAudioProcessorEditor::layoutRow3_EnvsVelocityDist()
{
    const int y = rowY(2);
    const int h = rowH(2);
    const int pad = scaled(5);
    const int gap = scaled(6);
    const int k = scaled(kKnobPx);
    const int cH = comboBandH();
    const int ipad = scaled(kInnerPad);

    const int knobH = knobBandH();
    const int comboY = comboBandY(2);
    const int knobY = knobBandY(2);

    // Panel widths, all sized tightly to content.
    const int ampW = 4 * (k + gap) + 2 * ipad;
    const int fltW = ampW;
    const int modW = 3 * (k + gap) + 2 * ipad;
    const int velW = 2 * (k + gap) + 2 * ipad;
    const int distW = 2 * (k + gap) + scaled(60) + 2 * ipad;

    const int totalNeeded = ampW + fltW + modW + velW + distW;
    const int numGaps = 4;   // four inter-panel gaps for five panels
    const int freeSpace = getWidth() - 2 * pad - numGaps * pad - totalNeeded;
    const int extraPad = juce::jmax(0, freeSpace / numGaps);

    int x = pad;

    // Amp Env
    secAmpEnv.setBounds(x, y, ampW, h);
    ampA.setBounds(x + ipad, knobY, k, knobH);
    ampD.setBounds(x + ipad + (k + gap), knobY, k, knobH);
    ampS.setBounds(x + ipad + 2 * (k + gap), knobY, k, knobH);
    ampR.setBounds(x + ipad + 3 * (k + gap), knobY, k, knobH);
    x += ampW + pad + extraPad;

    // Filter Env
    secFltEnv.setBounds(x, y, fltW, h);
    fltA.setBounds(x + ipad, knobY, k, knobH);
    fltD.setBounds(x + ipad + (k + gap), knobY, k, knobH);
    fltS.setBounds(x + ipad + 2 * (k + gap), knobY, k, knobH);
    fltR.setBounds(x + ipad + 3 * (k + gap), knobY, k, knobH);
    x += fltW + pad + extraPad;

    // Mod Env — combo sits on the combo band, 3 knobs below
    secModEnv.setBounds(x, y, modW, h);
    modEnvDest.setBounds(x + ipad, comboY, modW - 2 * ipad, cH);
    modEnvAtk.setBounds(x + ipad, knobY, k, knobH);
    modEnvDec.setBounds(x + ipad + (k + gap), knobY, k, knobH);
    modEnvAmt.setBounds(x + ipad + 2 * (k + gap), knobY, k, knobH);
    x += modW + pad + extraPad;

    // Velocity
    secVelocity.setBounds(x, y, velW, h);
    velToAmp.setBounds(x + ipad, knobY, k, knobH);
    velToFlt.setBounds(x + ipad + (k + gap), knobY, k, knobH);
    x += velW + pad + extraPad;

    // Distortion — toggle + type combo on the combo band, 2 knobs below
    secFx.setBounds(x, y, distW, h);
    distOn.setBounds(x + ipad, comboY, scaled(46), cH);
    distType.setBounds(x + ipad + scaled(52), comboY, scaled(58), cH);
    distDrive.setBounds(x + ipad, knobY, k, knobH);
    distTone.setBounds(x + ipad + (k + gap), knobY, k, knobH);
}

//==============================================================================
// ROW 4 — LFO 1 + LFO 2 + Character + CV + Unison + Delay
//==============================================================================
void WASPAlphaAudioProcessorEditor::layoutRow4_LfosCharCvUniDelay()
{
    const int y = rowY(3);
    const int h = rowH(3);
    const int pad = scaled(5);
    const int gap = scaled(6);
    const int k = scaled(kKnobPx);
    const int cH = comboBandH();
    const int ipad = scaled(kInnerPad);

    const int knobH = knobBandH();
    const int comboY = comboBandY(3);
    const int knobY = knobBandY(3);

    // LFO panel: two shape/target combos on the combo band, then 3 knobs
    // plus a vertical stack of SYNC/RESET toggles.
    const int lfoTogW = scaled(52);
    const int lfoComboW = scaled(72);
    const int lfoW = 2 * lfoComboW + gap + 3 * (k + gap) + lfoTogW + 2 * ipad;

    auto placeLfo = [&](int x, juce::ComboBox& shape, juce::ComboBox& target,
        WaspKnob& freq, WaspKnob& amt, WaspKnob& delay,
        juce::ToggleButton& sync, juce::ToggleButton& reset)
        {
            shape.setBounds(x + ipad, comboY, lfoComboW, cH);
            target.setBounds(x + ipad + lfoComboW + gap, comboY, lfoComboW, cH);

            freq.setBounds(x + ipad, knobY, k, knobH);
            amt.setBounds(x + ipad + (k + gap), knobY, k, knobH);
            delay.setBounds(x + ipad + 2 * (k + gap), knobY, k, knobH);

            const int togX = x + ipad + 3 * (k + gap) + gap;
            sync.setBounds(togX, knobY, lfoTogW, cH);
            reset.setBounds(togX, knobY + cH + scaled(3), lfoTogW, cH);
        };

    int x = pad;

    // LFO 1
    secLfo1.setBounds(x, y, lfoW, h);
    placeLfo(x, lfo1Shape, lfo1Target, lfo1Freq, lfo1Amount, lfo1Delay, lfo1Sync, lfo1Reset);
    x += lfoW + pad;

    // LFO 2
    secLfo2.setBounds(x, y, lfoW, h);
    placeLfo(x, lfo2Shape, lfo2Target, lfo2Freq, lfo2Amount, lfo2Delay, lfo2Sync, lfo2Reset);
    x += lfoW + pad;

    // Character — CMOS toggle on the combo band, 3 knobs on the knob band.
    const int charW = 3 * (k + gap) + 2 * ipad;
    secChar.setBounds(x, y, charW, h);
    cmosFilter.setBounds(x + ipad, comboY, charW - 2 * ipad, cH);
    dualVoice.setBounds(x + ipad, knobY, k, knobH);
    waspChar.setBounds(x + ipad + (k + gap), knobY, k, knobH);
    vcoBinary.setBounds(x + ipad + 2 * (k + gap), knobY, k, knobH);
    x += charW + pad;

    // CV — combo on combo band, single knob centered below.
    const int cvW = k + 2 * ipad + scaled(20);
    secCV.setBounds(x, y, cvW, h);
    cvTarget.setBounds(x + ipad, comboY, cvW - 2 * ipad, cH);
    cvAmount.setBounds(x + ipad + (cvW - 2 * ipad - k) / 2, knobY, k, knobH);
    x += cvW + pad;

    // Unison — single knob, no combo.
    const int uniW = k + 2 * ipad + scaled(20);
    secUnison.setBounds(x, y, uniW, h);
    dualDetune.setBounds(x + ipad + (uniW - 2 * ipad - k) / 2, knobY, k, knobH);
    x += uniW + pad;

    // Delay — fills remaining width.
    const int delayW = getWidth() - x - pad;
    secDelay.setBounds(x, y, delayW, h);
    delayTime.setBounds(x + ipad, knobY, k, knobH);
    delayFeedback.setBounds(x + ipad + (k + gap), knobY, k, knobH);
    delayMix.setBounds(x + ipad + 2 * (k + gap), knobY, k, knobH);
}

//==============================================================================
// ROW 5 — DX FM
//==============================================================================
void WASPAlphaAudioProcessorEditor::layoutRow5_DxFm()
{
    const int y = rowY(4);
    const int h = rowH(4);
    const int pad = scaled(5);
    const int gap = scaled(6);
    const int k = scaled(kKnobPx);
    const int ipad = scaled(kInnerPad);

    const int knobH = knobBandH();
    const int knobY = knobBandY(4);

    secDx.setBounds(pad, y, getWidth() - 2 * pad, h);

    // Left block: enable toggle + blend knob.
    const int leftW = scaled(72);
    const int togH = comboBandH();
    dxfmEnable.setBounds(pad + ipad, comboBandY(4), leftW - 2, togH);
    dxfmBlend.setBounds(pad + ipad + (leftW - k) / 2, knobY, k, knobH);

    // Right block: 14 knobs evenly distributed in a single row.
    const int knobAreaX = pad + ipad + leftW + gap;
    const int knobAreaW = getWidth() - knobAreaX - pad - ipad;

    WaspKnob* knobs[14] = {
        &dxCarA, &dxCarD, &dxCarR, &dxWave,
        &dxModI, &dxModD, &dxModS, &dxModR, &dxModV,
        &dxCoarse, &dxFine, &dxThru, &dxOctave, &dxTune
    };

    const int slotW = knobAreaW / 14;
    for (int i = 0; i < 14; ++i)
    {
        const int slotCentre = knobAreaX + i * slotW + slotW / 2;
        knobs[i]->setBounds(slotCentre - k / 2, knobY, k, knobH);
    }
}

//==============================================================================
// ROW 6 — CPU SAVER (11 toggles in 4-column × 3-row grid, full width)
//==============================================================================
void WASPAlphaAudioProcessorEditor::layoutRow6_CpuSaver()
{
    const int y = rowY(5);
    const int h = rowH(5);
    const int pad = scaled(5);
    const int cH = comboBandH();
    const int ipad = scaled(kInnerPad);

    secCpu.setBounds(pad, y, getWidth() - 2 * pad, h);

    const int hdrH = scaled(kSectHdrH);
    const int innerX = pad + ipad;
    const int innerW = getWidth() - 2 * pad - 2 * ipad;

    // 11 toggles: 4 columns × 3 rows. Row 2 has 3 toggles, 1 slot empty.
    constexpr int cols = 4;
    constexpr int rows = 3;
    const int colGap = scaled(8);
    const int rowGap = scaled(4);
    const int colW = (innerW - (cols - 1) * colGap) / cols;

    // Compute toggle height from available panel space so the grid always
    // fits, at any window size.
    const int available = h - hdrH - scaled(8) - (rows - 1) * rowGap - scaled(4);
    const int toggleH = juce::jlimit(scaled(14), cH, available / rows);

    const int topY = y + hdrH + scaled(6);

    auto placeCell = [&](juce::ToggleButton& b, int col, int row)
        {
            b.setBounds(innerX + col * (colW + colGap),
                topY + row * (toggleH + rowGap),
                colW, toggleH);
        };

    // Row 0 — sources and filters
    placeCell(bpFilter1Btn, 0, 0);
    placeCell(bpFilter2Btn, 1, 0);
    placeCell(bpLfo1Btn, 2, 0);
    placeCell(bpLfo2Btn, 3, 0);

    // Row 1 — modulators and effects
    placeCell(bpModEnvBtn, 0, 1);
    placeCell(bpCvBtn, 1, 1);
    placeCell(bpDistBtn, 2, 1);
    placeCell(bpDelayBtn, 3, 1);

    // Row 2 — character flags (one slot left free for future toggles)
    placeCell(bpDualVBtn, 0, 2);
    placeCell(bpWaspCharBtn, 1, 2);
    placeCell(bpVcoBinBtn, 2, 2);
}

//==============================================================================
// Preset management
//==============================================================================
void WASPAlphaAudioProcessorEditor::refreshPresetList()
{
    updatingPresetSelector = true;
    presetSelector.clear(juce::dontSendNotification);

    auto& manager = audioProcessor.getPresetManager();
    const auto& all = manager.getAllPresets();

    for (size_t i = 0; i < all.size(); ++i)
    {
        const auto& info = all[i];
        juce::String display;
        if (!info.isFactory)
            display << juce::String::charToString((juce::juce_wchar)0x2022) << " ";
        display << info.name;
        if (info.category.isNotEmpty())
            display << "   [" << info.category << "]";
        presetSelector.addItem(display, (int)i + 1);
    }

    if (presetSelector.getNumItems() > 0)
        presetSelector.setSelectedId(1, juce::dontSendNotification);

    updatingPresetSelector = false;
}

void WASPAlphaAudioProcessorEditor::onPresetSelected(int comboItemId)
{
    if (comboItemId <= 0) return;
    const int managerIndex = comboItemId - 1;
    auto& manager = audioProcessor.getPresetManager();
    if (managerIndex >= 0 && managerIndex < manager.getNumPresets())
        manager.loadPreset(managerIndex);
}

void WASPAlphaAudioProcessorEditor::onSavePresetClicked()
{
    auto* window = new juce::AlertWindow("Save Preset", "Enter a name for the new preset:", juce::MessageBoxIconType::NoIcon);
    window->addTextEditor("name", "", "Name:");

    const int currentIdx = presetSelector.getSelectedId() - 1;
    if (currentIdx >= 0)
    {
        auto& manager = audioProcessor.getPresetManager();
        if (currentIdx < manager.getNumPresets())
        {
            const auto& info = manager.getPresetInfo(currentIdx);
            window->getTextEditor("name")->setText(info.name + " (copy)", juce::dontSendNotification);
            window->getTextEditor("name")->selectAll();
        }
    }

    window->addButton("Save", 1, juce::KeyPress(juce::KeyPress::returnKey));
    window->addButton("Cancel", 0, juce::KeyPress(juce::KeyPress::escapeKey));

    window->enterModalState(true, juce::ModalCallbackFunction::create([this, window](int result) {
        juce::String name = window->getTextEditorContents("name").trim();
        if (result == 0 || name.isEmpty()) return;
        auto& manager = audioProcessor.getPresetManager();
        manager.saveUserPreset(name, "", "", true);
        refreshPresetList();
        }), true);
}

void WASPAlphaAudioProcessorEditor::onDeletePresetClicked()
{
    const int currentIdx = presetSelector.getSelectedId() - 1;
    if (currentIdx < 0) return;
    auto& manager = audioProcessor.getPresetManager();
    const auto& info = manager.getPresetInfo(currentIdx);
    if (info.isFactory)
    {
        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon, "Cannot Delete", "Factory presets cannot be deleted.");
        return;
    }
    manager.deletePreset(currentIdx);
    refreshPresetList();
}

void WASPAlphaAudioProcessorEditor::onExportPresetClicked()
{
    juce::String suggestedName = "Preset";
    const int currentIdx = presetSelector.getSelectedId() - 1;
    if (currentIdx >= 0)
    {
        auto& manager = audioProcessor.getPresetManager();
        if (currentIdx < manager.getNumPresets())
            suggestedName = manager.getPresetInfo(currentIdx).name;
    }

    auto chooser = std::make_shared<juce::FileChooser>(
        "Export Preset As...",
        juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile(suggestedName + ".stinger"),
        "*.stinger");

    chooser->launchAsync(juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::warnAboutOverwriting,
        [this, chooser, suggestedName](const juce::FileChooser& fc) {
            auto chosen = fc.getResult();
            if (chosen == juce::File()) return;
            if (!chosen.hasFileExtension("stinger")) chosen = chosen.withFileExtension("stinger");
            audioProcessor.getPresetManager().exportPresetToFile(chosen, suggestedName, "", "");
        });
}

void WASPAlphaAudioProcessorEditor::onOpenFolderClicked()
{
    audioProcessor.getPresetManager().getUserPresetDirectory().revealToUser();
}