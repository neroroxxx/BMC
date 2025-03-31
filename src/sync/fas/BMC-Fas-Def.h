/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Wrapper to control/read from Fractal Audio Devices
*/

#ifndef BMC_FAS_DEF_H
#define BMC_FAS_DEF_H

// Fractal Compatible Device IDs


#define BMC_FAS_DEVICE_ID_AXE_FX_II        	 0x03
#define BMC_FAS_DEVICE_ID_AXE_FX_II_XL     	 0x06
#define BMC_FAS_DEVICE_ID_AXE_FX_II_XL_PLUS	 0x07
#define BMC_FAS_DEVICE_ID_AX8              	 0x08
#define BMC_FAS_DEVICE_ID_AXE_FX_III       	 0x10
#define BMC_FAS_DEVICE_ID_FM3              	 0x11
#define BMC_FAS_DEVICE_ID_FM9              	 0x12


// *******************************************************
// *******************************************************
// *******************************************************
// *
// *               AXE FX 3, FM3 & FM9
// *
// *******************************************************
// *******************************************************
// *******************************************************


#define BMC_FAS_MAX_PRESET_NAME      33

#if defined(BMC_USE_FAS3)
  // sysex function id
  #define BMC_FAS3_FUNC_ID_BYPASS           0x0A
  #define BMC_FAS3_FUNC_ID_CHANNEL          0x0B
  #define BMC_FAS3_FUNC_ID_SCENE            0x0C
  #define BMC_FAS3_FUNC_ID_PRESET_NAME      0x0D
  #define BMC_FAS3_FUNC_ID_SCENE_NAME       0x0E
  #define BMC_FAS3_FUNC_ID_LOOPER           0x0F
  #define BMC_FAS3_FUNC_ID_TEMPO            0x10 // same as tap
  #define BMC_FAS3_FUNC_ID_TAP              0x10 // same as push data tempo
  #define BMC_FAS3_FUNC_ID_TUNER            0x11 // same as push data tuner
  #define BMC_FAS3_FUNC_ID_BLOCKS           0x13
  #define BMC_FAS3_FUNC_ID_SET_TEMPO        0x14

  // looper bit positions
  // #define BMC_FAS3_LOOPER_CMD_RECORD 	 0
  // #define BMC_FAS3_LOOPER_CMD_PLAY   	 1
  // #define BMC_FAS3_LOOPER_CMD_DUB   	 2
  // #define BMC_FAS3_LOOPER_CMD_UNDO   	 2
  // #define BMC_FAS3_LOOPER_CMD_ONCE   	 3
  // #define BMC_FAS3_LOOPER_CMD_REVERSE	 4
  // #define BMC_FAS3_LOOPER_CMD_HALF   	 5

  // other
  #define BMC_FAS3_MAX_SCENE_NAME    	 17

  // block id
  #define BMC_FAS_BLOCK_IN_1         	 37
  #define BMC_FAS_BLOCK_IN_2         	 38
  #define BMC_FAS_BLOCK_IN_3         	 39
  #define BMC_FAS_BLOCK_IN_4         	 40
  #define BMC_FAS_BLOCK_IN_5         	 41
  #define BMC_FAS_BLOCK_OUT_1        	 42
  #define BMC_FAS_BLOCK_OUT_2        	 43
  #define BMC_FAS_BLOCK_OUT_3        	 44
  #define BMC_FAS_BLOCK_OUT_4        	 45
  #define BMC_FAS_BLOCK_CMP_1        	 46
  #define BMC_FAS_BLOCK_CMP_2        	 47
  #define BMC_FAS_BLOCK_CMP_3        	 48
  #define BMC_FAS_BLOCK_CMP_4        	 49
  #define BMC_FAS_BLOCK_GEQ_1        	 50
  #define BMC_FAS_BLOCK_GEQ_2        	 51
  #define BMC_FAS_BLOCK_GEQ_3        	 52
  #define BMC_FAS_BLOCK_GEQ_4        	 53
  #define BMC_FAS_BLOCK_PEQ_1        	 54
  #define BMC_FAS_BLOCK_PEQ_2        	 55
  #define BMC_FAS_BLOCK_PEQ_3        	 56
  #define BMC_FAS_BLOCK_PEQ_4        	 57
  #define BMC_FAS_BLOCK_AMP_1        	 58
  #define BMC_FAS_BLOCK_AMP_2        	 59
  #define BMC_FAS_BLOCK_CAB_1        	 62
  #define BMC_FAS_BLOCK_CAB_2        	 63
  #define BMC_FAS_BLOCK_REV_1        	 66
  #define BMC_FAS_BLOCK_REV_2        	 67
  #define BMC_FAS_BLOCK_DLY_1        	 70
  #define BMC_FAS_BLOCK_DLY_2        	 71
  #define BMC_FAS_BLOCK_DLY_3        	 72
  #define BMC_FAS_BLOCK_DLY_4        	 73
  #define BMC_FAS_BLOCK_MTD_1        	 74
  #define BMC_FAS_BLOCK_MTD_2        	 75
  #define BMC_FAS_BLOCK_CHO_1        	 78
  #define BMC_FAS_BLOCK_CHO_2        	 79
  #define BMC_FAS_BLOCK_FLG_1        	 82
  #define BMC_FAS_BLOCK_FLG_2        	 83
  #define BMC_FAS_BLOCK_ROT_1        	 86
  #define BMC_FAS_BLOCK_ROT_2        	 87
  #define BMC_FAS_BLOCK_PHA_1        	 90
  #define BMC_FAS_BLOCK_PHA_2        	 91
  #define BMC_FAS_BLOCK_WAH_1        	 94
  #define BMC_FAS_BLOCK_WAH_2        	 95
  #define BMC_FAS_BLOCK_FOR_1        	 98
  #define BMC_FAS_BLOCK_FOR_2        	 99
  #define BMC_FAS_BLOCK_VOL_1        	 102
  #define BMC_FAS_BLOCK_VOL_2        	 103
  #define BMC_FAS_BLOCK_VOL_3        	 104
  #define BMC_FAS_BLOCK_VOL_4        	 105
  #define BMC_FAS_BLOCK_TRM_1        	 106
  #define BMC_FAS_BLOCK_TRM_2        	 107
  #define BMC_FAS_BLOCK_PIT_1        	 110
  #define BMC_FAS_BLOCK_PIT_2        	 111
  #define BMC_FAS_BLOCK_FIL_1        	 114
  #define BMC_FAS_BLOCK_FIL_2        	 115
  #define BMC_FAS_BLOCK_FIL_3        	 116
  #define BMC_FAS_BLOCK_FIL_4        	 117
  #define BMC_FAS_BLOCK_DRV_1        	 118
  #define BMC_FAS_BLOCK_DRV_2        	 119
  #define BMC_FAS_BLOCK_DRV_3        	 120
  #define BMC_FAS_BLOCK_DRV_4        	 121
  #define BMC_FAS_BLOCK_ENH_1        	 122
  #define BMC_FAS_BLOCK_ENH_2        	 123
  #define BMC_FAS_BLOCK_SYN_1        	 130
  #define BMC_FAS_BLOCK_SYN_2        	 131
  #define BMC_FAS_BLOCK_VOC_1        	 134
  #define BMC_FAS_BLOCK_MGT_1        	 138
  #define BMC_FAS_BLOCK_MGT_2        	 139
  #define BMC_FAS_BLOCK_XVR_1        	 142
  #define BMC_FAS_BLOCK_XVR_2        	 143
  #define BMC_FAS_BLOCK_GTE_1        	 146
  #define BMC_FAS_BLOCK_GTE_2        	 147
  #define BMC_FAS_BLOCK_GTE_3        	 148
  #define BMC_FAS_BLOCK_GTE_4        	 149
  #define BMC_FAS_BLOCK_RNG_1        	 150
  #define BMC_FAS_BLOCK_MBC_1        	 154
  #define BMC_FAS_BLOCK_MBC_2        	 155
  #define BMC_FAS_BLOCK_TTD_1        	 158
  #define BMC_FAS_BLOCK_TTD_2        	 159
  #define BMC_FAS_BLOCK_RES_1        	 162
  #define BMC_FAS_BLOCK_RES_2        	 163
  #define BMC_FAS_BLOCK_LPR_1        	 166
  #define BMC_FAS_BLOCK_TMA_1        	 170
  #define BMC_FAS_BLOCK_PLX_1        	 178
  #define BMC_FAS_BLOCK_PLX_2        	 179
  #define BMC_FAS_BLOCK_SND_1        	 182
  #define BMC_FAS_BLOCK_SND_2        	 183
  #define BMC_FAS_BLOCK_RTN_1        	 186
  #define BMC_FAS_BLOCK_RTN_2        	 187
  #define BMC_FAS_BLOCK_IRP_1        	 195
  #define BMC_FAS_BLOCK_IRP_2        	 196
#endif




// typedef enum EFFECT_ID_ {
//   ID_CONTROL = 2,
//   ID_TUNER = 35,
//   ID_IRCAPTURE,
//   ID_INPUT1,
//   ID_INPUT2,
//   ID_INPUT3,
//   ID_INPUT4,
//   ID_INPUT5, // USB Input
//   ID_OUTPUT1,
//   ID_OUTPUT2,
//   ID_OUTPUT3,
//   ID_OUTPUT4,
//   ID_COMP1,
//   ID_COMP2,
//   ID_COMP3,
//   ID_COMP4,
//   ID_GRAPHEQ1,
//   ID_GRAPHEQ2,
//   ID_GRAPHEQ3,
//   ID_GRAPHEQ4,
//   ID_PARAEQ1,
//   ID_PARAEQ2,
//   ID_PARAEQ3,
//   ID_PARAEQ4,
//   ID_DISTORT1,
//   ID_DISTORT2,
//   ID_DISTORT3,
//   ID_DISTORT4,
//   ID_CAB1,
//   ID_CAB2,
//   ID_CAB3,
//   ID_CAB4,
//   ID_REVERB1,
//   ID_REVERB2,
//   ID_REVERB3,
//   ID_REVERB4,
//   ID_DELAY1,
//   ID_DELAY2,
//   ID_DELAY3,
//   ID_DELAY4,
//   ID_MULTITAP1,
//   ID_MULTITAP2,
//   ID_MULTITAP3,
//   ID_MULTITAP4,
//   ID_CHORUS1,
//   ID_CHORUS2,
//   ID_CHORUS3,
//   ID_CHORUS4,
//   ID_FLANGER1,
//   ID_FLANGER2,
//   ID_FLANGER3,
//   ID_FLANGER4,
//   ID_ROTARY1,
//   ID_ROTARY2,
//   ID_ROTARY3,
//   ID_ROTARY4,
//   ID_PHASER1,
//   ID_PHASER2,
//   ID_PHASER3,
//   ID_PHASER4,
//   ID_WAH1,
//   ID_WAH2,
//   ID_WAH3,
//   ID_WAH4,
//   ID_FORMANT1,
//   ID_FORMANT2,
//   ID_FORMANT3,
//   ID_FORMANT4,
//   ID_VOLUME1,
//   ID_VOLUME2,
//   ID_VOLUME3,
//   ID_VOLUME4,
//   ID_TREMOLO1,
//   ID_TREMOLO2,
//   ID_TREMOLO3,
//   ID_TREMOLO4,
//   ID_PITCH1,
//   ID_PITCH2,
//   ID_PITCH3,
//   ID_PITCH4,
//   ID_FILTER1,
//   ID_FILTER2,
//   ID_FILTER3,
//   ID_FILTER4,
//   ID_FUZZ1,
//   ID_FUZZ2,
//   ID_FUZZ3,
//   ID_FUZZ4,
//   ID_ENHANCER1,
//   ID_ENHANCER2,
//   ID_ENHANCER3,
//   ID_ENHANCER4,
//   ID_MIXER1,
//   ID_MIXER2,
//   ID_MIXER3,
//   ID_MIXER4,
//   ID_SYNTH1,
//   ID_SYNTH2,
//   ID_SYNTH3,
//   ID_SYNTH4,
//   ID_VOCODER1,
//   ID_VOCODER2,
//   ID_VOCODER3,
//   ID_VOCODER4,
//   ID_MEGATAP1,
//   ID_MEGATAP2,
//   ID_MEGATAP3,
//   ID_MEGATAP4,
//   ID_CROSSOVER1,
//   ID_CROSSOVER2,
//   ID_CROSSOVER3,
//   ID_CROSSOVER4,
//   ID_GATE1,
//   ID_GATE2,
//   ID_GATE3,
//   ID_GATE4,
//   ID_RINGMOD1,
//   ID_RINGMOD2,
//   ID_RINGMOD3,
//   ID_RINGMOD4,
//   ID_MULTICOMP1,
//   ID_MULTICOMP2,
//   ID_MULTICOMP3,
//   ID_MULTICOMP4,
//   ID_TENTAP1,
//   ID_TENTAP2,
//   ID_TENTAP3,
//   ID_TENTAP4,
//   ID_RESONATOR1,
//   ID_RESONATOR2,
//   ID_RESONATOR3,
//   ID_RESONATOR4,
//   ID_LOOPER1,
//   ID_LOOPER2,
//   ID_LOOPER3,
//   ID_LOOPER4,
//   ID_TONEMATCH1,
//   ID_TONEMATCH2,
//   ID_TONEMATCH3,
//   ID_TONEMATCH4,
//   ID_RTA1,
//   ID_RTA2,
//   ID_RTA3,
//   ID_RTA4,
//   ID_PLEX1,
//   ID_PLEX2,
//   ID_PLEX3,
//   ID_PLEX4,
//   ID_FBSEND1,
//   ID_FBSEND2,
//   ID_FBSEND3,
//   ID_FBSEND4,
//   ID_FBRETURN1,
//   ID_FBRETURN2,
//   ID_FBRETURN3,
//   ID_FBRETURN4,
//   ID_MIDIBLOCK,
//   ID_MULTIPLEXER1,
//   ID_MULTIPLEXER2,
//   ID_MULTIPLEXER3,
//   ID_MULTIPLEXER4,
//   ID_IRPLAYER1,
//   ID_IRPLAYER2,
//   ID_IRPLAYER3,
//   ID_IRPLAYER4,
//   ID_FOOTCONTROLLER,
//   ID_PRESET_FC
// } EFFECT_ID;




// *******************************************************
// *******************************************************
// *******************************************************
// *
// *               AXE FX 2 & AX8 Data
// *
// *******************************************************
// *******************************************************
// *******************************************************

#if !defined(BMC_USE_FAS3)
// Fractal Block IDs
  #define BMC_FAS_BLOCK_CPR        	 100
  #define BMC_FAS_BLOCK_CPR_1      	 100
  #define BMC_FAS_BLOCK_CPR_2      	 101
  #define BMC_FAS_BLOCK_GEQ        	 102
  #define BMC_FAS_BLOCK_GEQ_1      	 102
  #define BMC_FAS_BLOCK_GEQ_2      	 103
  #define BMC_FAS_BLOCK_PEQ        	 104
  #define BMC_FAS_BLOCK_PEQ_1      	 104
  #define BMC_FAS_BLOCK_PEQ_2      	 105
  #define BMC_FAS_BLOCK_AMP        	 106
  #define BMC_FAS_BLOCK_AMP_1      	 106
  #define BMC_FAS_BLOCK_AMP_2      	 107
  #define BMC_FAS_BLOCK_CAB        	 108
  #define BMC_FAS_BLOCK_CAB_1      	 108
  #define BMC_FAS_BLOCK_CAB_2      	 109
  #define BMC_FAS_BLOCK_REV        	 110
  #define BMC_FAS_BLOCK_REV_1      	 110
  #define BMC_FAS_BLOCK_REV_2      	 111
  #define BMC_FAS_BLOCK_DLY        	 112
  #define BMC_FAS_BLOCK_DLY_1      	 112
  #define BMC_FAS_BLOCK_DLY_2      	 113
  #define BMC_FAS_BLOCK_MTD        	 114
  #define BMC_FAS_BLOCK_MTD_1      	 114
  #define BMC_FAS_BLOCK_MTD_2      	 115
  #define BMC_FAS_BLOCK_CHO        	 116
  #define BMC_FAS_BLOCK_CHO_1      	 116
  #define BMC_FAS_BLOCK_CHO_2      	 117
  #define BMC_FAS_BLOCK_FLG        	 118
  #define BMC_FAS_BLOCK_FLG_1      	 118
  #define BMC_FAS_BLOCK_FLG_2      	 119
  #define BMC_FAS_BLOCK_ROT        	 120
  #define BMC_FAS_BLOCK_ROT_1      	 120
  #define BMC_FAS_BLOCK_ROT_2      	 121
  #define BMC_FAS_BLOCK_PHA        	 122
  #define BMC_FAS_BLOCK_PHA_1      	 122
  #define BMC_FAS_BLOCK_PHA_2      	 123
  #define BMC_FAS_BLOCK_WAH        	 124
  #define BMC_FAS_BLOCK_WAH_1      	 124
  #define BMC_FAS_BLOCK_WAH_2      	 125
  #define BMC_FAS_BLOCK_FRM        	 126
  #define BMC_FAS_BLOCK_FRM_1      	 126
  #define BMC_FAS_BLOCK_VOL        	 127
  #define BMC_FAS_BLOCK_VOL_1      	 127
  #define BMC_FAS_BLOCK_TRM        	 128
  #define BMC_FAS_BLOCK_TRM_1      	 128
  #define BMC_FAS_BLOCK_TRM_2      	 129
  #define BMC_FAS_BLOCK_PIT        	 130
  #define BMC_FAS_BLOCK_PIT_1      	 130
  #define BMC_FAS_BLOCK_FIL        	 131
  #define BMC_FAS_BLOCK_FIL_1      	 131
  #define BMC_FAS_BLOCK_FIL_2      	 132
  #define BMC_FAS_BLOCK_DRV        	 133
  #define BMC_FAS_BLOCK_DRV_1      	 133
  #define BMC_FAS_BLOCK_DRV_2      	 134
  #define BMC_FAS_BLOCK_ENH        	 135
  #define BMC_FAS_BLOCK_ENH_1      	 135
  #define BMC_FAS_BLOCK_FXL        	 136
  #define BMC_FAS_BLOCK_FXL_1      	 136
  #define BMC_FAS_BLOCK_MIX        	 137
  #define BMC_FAS_BLOCK_MIX_1      	 137
  #define BMC_FAS_BLOCK_MIX_2      	 138
  #define BMC_FAS_BLOCK_ING        	 139
  #define BMC_FAS_BLOCK_ING_1      	 139
  #define BMC_FAS_BLOCK_OUT        	 140
  #define BMC_FAS_BLOCK_OUT_1      	 140
  #define BMC_FAS_BLOCK_CTR        	 141
  #define BMC_FAS_BLOCK_CTR_1      	 141
  #define BMC_FAS_BLOCK_SND        	 142
  #define BMC_FAS_BLOCK_SND_1      	 142
  #define BMC_FAS_BLOCK_RTN        	 143
  #define BMC_FAS_BLOCK_RTN_1      	 143
  #define BMC_FAS_BLOCK_SYN        	 144
  #define BMC_FAS_BLOCK_SYN_1      	 144
  #define BMC_FAS_BLOCK_SYN_2      	 145
  #define BMC_FAS_BLOCK_VOC        	 146
  #define BMC_FAS_BLOCK_VOC_1      	 146
  #define BMC_FAS_BLOCK_MGT        	 147
  #define BMC_FAS_BLOCK_MGT_1      	 147
  #define BMC_FAS_BLOCK_XVR        	 148
  #define BMC_FAS_BLOCK_XVR_1      	 148
  #define BMC_FAS_BLOCK_XVR_2      	 149
  #define BMC_FAS_BLOCK_GTE        	 150
  #define BMC_FAS_BLOCK_GTE_1      	 150
  #define BMC_FAS_BLOCK_GTE_2      	 151
  #define BMC_FAS_BLOCK_RNG        	 152
  #define BMC_FAS_BLOCK_RNG_1      	 152
  #define BMC_FAS_BLOCK_PIT_2      	 153
  #define BMC_FAS_BLOCK_MBC        	 154
  #define BMC_FAS_BLOCK_MBC_1      	 154
  #define BMC_FAS_BLOCK_MBC_2      	 155
  #define BMC_FAS_BLOCK_QCH        	 156
  #define BMC_FAS_BLOCK_QCH_1      	 156
  #define BMC_FAS_BLOCK_QCH_2      	 157
  #define BMC_FAS_BLOCK_RES        	 158
  #define BMC_FAS_BLOCK_RES_1      	 158
  #define BMC_FAS_BLOCK_RES_2      	 159
  #define BMC_FAS_BLOCK_GEQ_3      	 160
  #define BMC_FAS_BLOCK_GEQ_4      	 161
  #define BMC_FAS_BLOCK_PEQ_3      	 162
  #define BMC_FAS_BLOCK_PEQ_4      	 163
  #define BMC_FAS_BLOCK_FIL_3      	 164
  #define BMC_FAS_BLOCK_FIL_4      	 165
  #define BMC_FAS_BLOCK_VOL_2      	 166
  #define BMC_FAS_BLOCK_VOL_3      	 167
  #define BMC_FAS_BLOCK_VOL_4      	 168
  #define BMC_FAS_BLOCK_LPR        	 169
  #define BMC_FAS_BLOCK_LPR_1      	 169
  #define BMC_FAS_BLOCK_TMA        	 170
  #define BMC_FAS_BLOCK_TMA_1      	 170



#ifndef BMC_FAS_CC_TAP_TEMPO
	#define BMC_FAS_CC_TAP_TEMPO 14
#endif
#ifndef BMC_FAS_CC_TUNER
	#define BMC_FAS_CC_TUNER 15
#endif
#ifndef BMC_FAS_CC_SCENE
	#define BMC_FAS_CC_SCENE 34
#endif
#ifndef BMC_FAS_CC_METRONOME
	#define BMC_FAS_CC_METRONOME 122
#endif
#ifndef BMC_FAS_CC_SCENE_INC
	#define BMC_FAS_CC_SCENE_INC 123
#endif
#ifndef BMC_FAS_CC_SCENE_DEC
	#define BMC_FAS_CC_SCENE_DEC 124
#endif
#ifndef BMC_FAS_CC_LOOPER_RECORD
	#define BMC_FAS_CC_LOOPER_RECORD 28
#endif
#ifndef BMC_FAS_CC_LOOPER_PLAY
	#define BMC_FAS_CC_LOOPER_PLAY 29
#endif
#ifndef BMC_FAS_CC_LOOPER_ONCE
	#define BMC_FAS_CC_LOOPER_ONCE 30
#endif
#ifndef BMC_FAS_CC_LOOPER_DUB
	#define BMC_FAS_CC_LOOPER_DUB 31
#endif
#ifndef BMC_FAS_CC_LOOPER_REVERSE
	#define BMC_FAS_CC_LOOPER_REVERSE 32
#endif
#ifndef BMC_FAS_CC_LOOPER_BYPASS
	#define BMC_FAS_CC_LOOPER_BYPASS 33
#endif
#ifndef BMC_FAS_CC_LOOPER_HALF
	#define BMC_FAS_CC_LOOPER_HALF 120
#endif
#ifndef BMC_FAS_CC_LOOPER_UNDO
	#define BMC_FAS_CC_LOOPER_UNDO 121
#endif

// BLOCK PARAMETERS

// ***********************
// *** BLOCK SETUP (SETUP) ***
// ***********************
#define BMC_FAS_PARAM_SETUP_EQ_31 15 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ_63 16 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ_125 17 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ_250 18 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ_500 19 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ_1K 20 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ_2K 21 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ_4K 22 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ_8K 23 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ_16K 24 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_GAIN_OUT1 25 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ2_31 26 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ2_63 27 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ2_125 28 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ2_250 29 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ2_500 30 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ2_1K 31 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ2_2K 32 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ2_4K 33 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ2_8K 34 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_EQ2_16K 35 // range 0 to 65534
#define BMC_FAS_PARAM_SETUP_GAIN_OUT2 36 // range 0 to 65534
// range 0 to 16, values: 0="NONE", 1="SINGLE PRST/BANK", 2="STICKY PRST/BANK", 3="STICKY PRST +/-", 4="SINGLE SCENE", 5="STICKY SCENE", 6="PRESET UP", 7="PRESET DN", 8="TEMPO TAP", 9="TUNER", 10="SINGLE X/Y", 11="STICKY X/Y", 12="LOOPER CONTROL", 13="BANK UP", 14="BANK DOWN", 15="SCENE 1/2 TOGGLE", 16="EXIT"
#define BMC_FAS_PARAM_SETUP_F1_TAP 46
// range 0 to 16, values: 0="NONE", 1="SINGLE PRST/BANK", 2="STICKY PRST/BANK", 3="STICKY PRST +/-", 4="SINGLE SCENE", 5="STICKY SCENE", 6="PRESET UP", 7="PRESET DN", 8="null", 9="TUNER", 10="SINGLE X/Y", 11="STICKY X/Y", 12="LOOPER CONTROL", 13="BANK UP", 14="BANK DOWN", 15="SCENE 1/2 TOGGLE", 16="EXIT"
#define BMC_FAS_PARAM_SETUP_F1_HOLD 47
// range 0 to 16, values: 0="NONE", 1="null", 2="null", 3="null", 4="SINGLE SCENE", 5="STICKY SCENE", 6="PRESET UP", 7="PRESET DN", 8="TEMPO TAP", 9="TUNER", 10="SINGLE X/Y", 11="STICKY X/Y", 12="LOOPER CONTROL", 13="BANK UP", 14="BANK DOWN", 15="SCENE 1/2 TOGGLE", 16="EXIT"
#define BMC_FAS_PARAM_SETUP_F2_TAP 48
// range 0 to 16, values: 0="NONE", 1="null", 2="null", 3="null", 4="SINGLE SCENE", 5="STICKY SCENE", 6="PRESET UP", 7="PRESET DN", 8="null", 9="TUNER", 10="SINGLE X/Y", 11="STICKY X/Y", 12="LOOPER CONTROL", 13="BANK UP", 14="BANK DOWN", 15="SCENE 1/2 TOGGLE", 16="EXIT"
#define BMC_FAS_PARAM_SETUP_F2_HOLD 49
// range 0 to 16, values: 0="NONE", 1="null", 2="null", 3="null", 4="SINGLE SCENE", 5="STICKY SCENE", 6="PRESET UP", 7="PRESET DN", 8="TEMPO TAP", 9="TUNER", 10="SINGLE X/Y", 11="STICKY X/Y", 12="LOOPER CONTROL", 13="BANK UP", 14="BANK DOWN", 15="SCENE 1/2 TOGGLE", 16="EXIT"
#define BMC_FAS_PARAM_SETUP_F3_TAP 50
// range 0 to 16, values: 0="NONE", 1="null", 2="null", 3="null", 4="SINGLE SCENE", 5="STICKY SCENE", 6="PRESET UP", 7="PRESET DN", 8="null", 9="TUNER", 10="SINGLE X/Y", 11="STICKY X/Y", 12="LOOPER CONTROL", 13="BANK UP", 14="BANK DOWN", 15="SCENE 1/2 TOGGLE", 16="EXIT"
#define BMC_FAS_PARAM_SETUP_F3_HOLD 51


// ***********************
// *** BLOCK Compressor (CPR) ***
// ***********************
#define BMC_FAS_PARAM_CPR_TRESHOLD 0 // range 0 to 65534
#define BMC_FAS_PARAM_CPR_RATIO 1 // range 0 to 65534
#define BMC_FAS_PARAM_CPR_ATTACK 2 // range 0 to 65534
#define BMC_FAS_PARAM_CPR_RELEASE 3 // range 0 to 65534
#define BMC_FAS_PARAM_CPR_LEVEL 4 // range 0 to 65534
// range 0 to 3, values: 0="HARD", 1="SOFT", 2="SOFTER", 3="SOFTEST"
#define BMC_FAS_PARAM_CPR_KNEE 5
#define BMC_FAS_PARAM_CPR_MAKEUP_SW 6 // range 0 to 1
// range 0 to 3, values: 0="RMS", 1="PEAK", 2="RMS+PEAK", 3="FAST RMS"
#define BMC_FAS_PARAM_CPR_DETECT 7
#define BMC_FAS_PARAM_CPR_FILTER 8 // range 0 to 65534
// range 0 to 8, values: 0="BLOCK L+R", 1="ROW 1", 2="ROW 2", 3="ROW 3", 4="ROW 4", 5="INPUT 1", 6="INPUT 2", 7="BLOCK L", 8="BLOCK R"
#define BMC_FAS_PARAM_CPR_SIDECHAIN 10
#define BMC_FAS_PARAM_CPR_MIX 11 // range 0 to 65534
// range 0 to 5, values: 0="STUDIO COMP", 1="PEDAL COMP 1", 2="PEDAL COMP 2", 3="DYNAMICS", 4="OPTICAL 1", 5="OPTICAL 2"
#define BMC_FAS_PARAM_CPR_EFFECT_TYPE 12
#define BMC_FAS_PARAM_CPR_COMP 13 // range 0 to 65534
// range 0 to 2, values: 0="THRU", 1="MUTE FX OUT", 2="MUTE OUT"
#define BMC_FAS_PARAM_CPR_BYPASS_MODE 14
#define BMC_FAS_PARAM_CPR_LOOK_AHEAD 15 // range 0 to 65534
#define BMC_FAS_PARAM_CPR_AUTO_SW 16 // range 0 to 1
#define BMC_FAS_PARAM_CPR_EMPHASIS 17 // range 0 to 65534
#define BMC_FAS_PARAM_CPR_DYNAMICS 18 // range 0 to 65534
// range 0 to 1, values: 0="INSTRUMENT", 1="LINE"
#define BMC_FAS_PARAM_CPR_INPUT_LEVEL 19


// ***********************
// *** BLOCK Graphic EQ (GEQ) ***
// ***********************
#define BMC_FAS_PARAM_GEQ_31 0 // range 0 to 65534
#define BMC_FAS_PARAM_GEQ_63 1 // range 0 to 65534
#define BMC_FAS_PARAM_GEQ_125 2 // range 0 to 65534
#define BMC_FAS_PARAM_GEQ_250 3 // range 0 to 65534
#define BMC_FAS_PARAM_GEQ_500 4 // range 0 to 65534
#define BMC_FAS_PARAM_GEQ_1K 5 // range 0 to 65534
#define BMC_FAS_PARAM_GEQ_2K 6 // range 0 to 65534
#define BMC_FAS_PARAM_GEQ_4K 7 // range 0 to 65534
#define BMC_FAS_PARAM_GEQ_8K 8 // range 0 to 65534
#define BMC_FAS_PARAM_GEQ_16K 9 // range 0 to 65534
#define BMC_FAS_PARAM_GEQ_LEVEL 11 // range 0 to 65534
#define BMC_FAS_PARAM_GEQ_BALANCE 12 // range 0 to 65534
// range 0 to 1, values: 0="THRU", 1="MUTE"
#define BMC_FAS_PARAM_GEQ_BYPASS_MODE 13
// range 0 to 11, values: 0="10 BAND CONST Q", 1="8 BAND CONST Q", 2="7 BAND CONST Q", 3="5 BAND CONST Q", 4="10 BAND VAR Q", 5="8 BAND VAR Q", 6="7 BAND VAR Q", 7="5 BAND VAR Q", 8="5 BAND PASSIVE", 9="4 BAND PASSIVE", 10="3 BAND PASSIVE", 11="3 BAND CONSOLE"
#define BMC_FAS_PARAM_GEQ_EFFECT_TYPE 15
#define BMC_FAS_PARAM_GEQ_MASTER_Q 16 // range 0 to 65534


// ***********************
// *** BLOCK Parametric EQ (PEQ) ***
// ***********************
#define BMC_FAS_PARAM_PEQ_FREQ_1 0 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_FREQ_2 1 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_FREQ_3 2 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_FREQ_4 3 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_FREQ_5 4 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_Q_1 5 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_Q_2 6 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_Q_3 7 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_Q_4 8 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_Q_5 9 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_GAIN_1 10 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_GAIN_2 11 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_GAIN_3 12 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_GAIN_4 13 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_GAIN_5 14 // range 0 to 65534
// range 0 to 3, values: 0="SHELVING", 1="PEAKING", 2="BLOCKING", 3="SHELVING2"
#define BMC_FAS_PARAM_PEQ_FREQ_TYPE_1 15
// range 0 to 3, values: 0="SHELVING", 1="PEAKING", 2="BLOCKING", 3="SHELVING2"
#define BMC_FAS_PARAM_PEQ_FREQ_TYPE_5 16
// range 0 to 2, values: 0="PEAKING", 1="SHELVING", 2="SHELVING2"
#define BMC_FAS_PARAM_PEQ_FREQ_TYPE_2 17
// range 0 to 2, values: 0="PEAKING", 1="SHELVING", 2="SHELVING2"
#define BMC_FAS_PARAM_PEQ_FREQ_TYPE_4 18
#define BMC_FAS_PARAM_PEQ_LEVEL 19 // range 0 to 65534
#define BMC_FAS_PARAM_PEQ_BALANCE 20 // range 0 to 65534
// range 0 to 1, values: 0="THRU", 1="MUTE"
#define BMC_FAS_PARAM_PEQ_BYPASS_MODE 21


// ***********************
// *** BLOCK Amp (AMP) ***
// ***********************
// range 0 to 258, values: 0="59 BASSGUY", 1="65 BASSGUY NRML", 2="VIBRATO VERB", 3="DELUXE VERB VIB", 4="DOUBLE VERB VIB", 5="JR BLUES", 6="CLASS-A 15W TB", 7="CLASS-A 30W", 8="CLASS-A 30W TB", 9="BRIT JM45", 10="PLEXI 50W NRML", 11="PLEXI 50W HI 1", 12="1987X NORMAL", 13="1987X TREBLE", 14="BRIT 800", 15="BRIT SUPER", 16="HIPOWER NORMAL", 17="HIPOWER BRILLNT", 18="USA CLEAN", 19="USA PRE CLEAN", 20="USA RHYTHM", 21="USA IIC+", 22="USA IIC+ BRIGHT", 23="USA LEAD", 24="USA LEAD BRT", 25="RECTO2 ORG VNTG", 26="RECTO2 ORG MDRN", 27="RECTO2 RED VNTG", 28="RECTO2 RED MDRN", 29="EURO BLUE", 30="EURO RED", 31="SHIVER CLEAN", 32="SHIVER LEAD", 33="EURO UBER", 34="SOLO 99 CLEAN", 35="SOLO 100 RHY", 36="SOLO 100 LEAD", 37="FRIEDMAN BE V1", 38="FRIEDMAN HBE V1", 39="PVH 6160 BLOCK", 40="MR Z MZ-38", 41="CA3+ RHY", 42="CA3+ LEAD", 43="WRECKER ROCKET", 44="CORNCOB M50", 45="CA OD-2", 46="FRYETTE D60 L", 47="FRYETTE D60 M", 48="BRIT BROWN", 49="CITRUS RV50", 50="JAZZ 120", 51="ENERGYBALL", 52="ODS-100 CLEAN", 53="ODS-100 HRM", 54="FAS RHYTHM", 55="FAS LEAD 1", 56="FAS LEAD 2", 57="FAS MODERN", 58="DAS METALL", 59="BRIT PRE", 60="BUTTERY", 61="BOUTIQUE 1", 62="BOUTIQUE 2", 63="CAMERON CCV 1A", 64="CAMERON CCV 2A", 65="SV BASS", 66="TUBE PRE", 67="FAS BROWN", 68="BIG HAIR", 69="SOLO 99 LEAD", 70="SUPERTWEED", 71="TX STAR LEAD", 72="FAS WRECK", 73="BRIT JVM OD1 OR", 74="BRIT JVM OD2 OR", 75="FAS 6160", 76="CALI LEGGY", 77="USA LEAD +", 78="USA LEAD BRT +", 79="PRINCE TONE", 80="BLANKNSHP LEEDS", 81="5153 100W GREEN", 82="5153 100W BLUE", 83="5153 100W RED", 84="SOLO 88 RHYTHM", 85="DIV/13 CJ", 86="HERBIE CH2-", 87="HERBIE CH2+", 88="HERBIE CH3", 89="DIRTY SHIRLEY 1", 90="DIZZY V4 BLUE 2", 91="DIZZY V4 BLUE 3", 92="DIZZY V4 BLUE 4", 93="SUHR BADGER 18", 94="SUHR BADGER 30", 95="PRINCE TONE NR", 96="SUPREMO TREM", 97="ATOMICA LOW", 98="ATOMICA HIGH", 99="DELUXE TWEED", 100="SPAWN ROD OD2-1", 101="SPAWN ROD OD2-2", 102="SPAWN ROD OD2-3", 103="BRIT SILVER", 104="SPAWN NITROUS 2", 105="FAS CRUNCH", 106="TWO STONE J35 1", 107="FOX ODS", 108="HOT KITTY", 109="BAND-COMMANDER", 110="SUPER VERB VIB", 111="VIBRA-KING", 112="GIBTONE SCOUT", 113="PVH 6160+ LD", 114="SOLO 100 CLEAN", 115="USA PRE LD2 GRN", 116="USA PRE LD2 YLW", 117="CA3+ CLEAN", 118="FOX ODS DEEP", 119="BRIT JVM OD1 GN", 120="BRIT JVM OD2 GN", 121="VIBRATO LUX", 122="BRIT 800 MOD", 123="NUCLEAR-TONE", 124="BLUDOJAI CLEAN", 125="BLUDOJAI LD PAB", 126="PLEXI 100W HIGH", 127="PLEXI 100W NRML", 128="RUBY ROCKET", 129="AC-20 EF86 B", 130="PRINCE TONE REV", 131="COMET CONCOURSE", 132="FAS MODERN II", 133="CA TRIPTIK MDRN", 134="CA TRIPTIK CLSC", 135="CA TRIPTIK CLN", 136="THORDENDAL VINT", 137="THORDENDAL MDRN", 138="ODS-100 HRM MID", 139="EURO BLUE MDRN", 140="EURO RED MDRN", 141="PLEXI 50W JUMP", 142="AC-20 EF86 T", 143="COMET 60", 144="HIPOWER JUMPED", 145="PLEXI 100W JUMP", 146="BRIT JM45 JUMP", 147="1987X JUMP", 148="RECTO1 ORG VNTG", 149="RECTO1 RED", 150="ODS-100 FORD 1", 151="BOGFISH STRATO", 152="BOGFISH BROWN", 153="5F1 TWEED", 154="WRECKER EXPRESS", 155="TWO STONE J35 2", 156="ODS-100 FORD 2", 157="MR Z MZ-8", 158="CAR ROAMER", 159="USA SUB BLUES", 160="WRECKER LVRPOOL", 161="CITRUS TERRIER", 162="CITRUS A30 CLN", 163="CITRUS A30 DRTY", 164="DIV/13 FT37 LO", 165="DIV/13 FT37 HI", 166="MATCHBOX D-30", 167="FAS CLASS-A", 168="USA BASS 400 1", 169="USA BASS 400 2", 170="CITRUS BASS 200", 171="FAS BASS", 172="TREMOLO LUX", 173="FAS BROOTALZ", 174="RECTO1 ORG MDRN", 175="ANGLE SEVERE 1", 176="ANGLE SEVERE 2", 177="USA PRE LD2 RED", 178="USA PRE LD1 RED", 179="TX STAR CLEAN", 180="AC-20 12AX7 T", 181="VIBRATO VERB AA", 182="VIBRATO VERB AB", 183="CA TUCANA LEAD", 184="JR BLUES FAT", 185="SOLO 88 LEAD", 186="BRIT AFS100 1", 187="BRIT AFS100 2", 188="CLASS-A 30W HOT", 189="DIZZY V4 SLVR 2", 190="DIZZY V4 SLVR 3", 191="DIZZY V4 SLVR 4", 192="1959SLP NORMAL", 193="1959SLP TREBLE", 194="1959SLP JUMP", 195="FAS MODERN III", 196="ODS-100 FORD MD", 197="MR Z HWY 66", 198="6G4 SUPER", 199="6G12 CONCERT", 200="65 BASSGUY BASS", 201="VIBRA-KING FAT", 202="SPAWN ROD OD1-1", 203="SPAWN ROD OD1-2", 204="SPAWN ROD OD1-3", 205="CA TUCANA CLN", 206="BRIT JVM OD1 RD", 207="BRIT JVM OD2 RD", 208="CAMERON CCV 1B", 209="CAMERON CCV 2B", 210="CAMERON CCV 2C", 211="CAMERON CCV 2D", 212="FRIEDMAN SM BOX", 213="5153 50W BLUE", 214="DIV/13 CJ BOOST", 215="USA IIC+ DEEP", 216="USA IIC+ BRT/DP", 217="5F8 TWEED", 218="DOUBLE VERB SF", 219="VIBRATO VERB CS", 220="JMPRE-1 OD1", 221="JMPRE-1 OD2", 222="JMPRE-1 OD1 BS", 223="JMPRE-1 OD2 BS", 224="DELUXE VERB NRM", 225="DOUBLE VERB NRM", 226="SUPER VERB NRM", 227="BLUDOJAI LD 2", 228="PLEXI 50W 6550", 229="FAS HOT ROD", 230="PVH 6160+ RHY B", 231="PVH 6160+ RHY", 232="SOLO 88 CLEAN", 233="CLASS-A 30W BRT", 234="PLEXI 50W HI 2", 235="SPAWN NITROUS 1", 236="RUBY ROCKET BRT", 237="AC-20 12AX7 B", 238="PLEXI 100W 1970", 239="JS410 LEAD OR", 240="JS410 LEAD RD", 241="JS410 CRUNCH OR", 242="JS410 CRUNCH RD", 243="FRIEDMAN BE V2", 244="FRIEDMAN HBE V2", 245="DWEEZIL'S B-MAN", 246="FRIEDMAN BE", 247="FRIEDMAN HBE", 248="USA IIC++", 249="LEGATO 100", 250="CAPT HOOK 2B", 251="CAPT HOOK 3B", 252="CAPT HOOK 2A", 253="CAPT HOOK 3A", 254="CAPT HOOK 1A", 255="CAPT HOOK 1B", 256="DIRTY SHIRLEY 2", 257="BRIT 800 #34", 258="5F1 TWEED EC"
#define BMC_FAS_PARAM_AMP_EFFECT_TYPE 0
#define BMC_FAS_PARAM_AMP_INPUT_DRIVE 1 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_BASS 2 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_MIDDLE 3 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_TREBLE 4 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_MASTER_VOLUME 5 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_PREAMP_LOW_CUT 6 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_HIGH_CUT_FREQ 7 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_TONE_FREQ 8 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_XFORMER_GRIND 9 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_BRIGHT_CAP 10 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_XFORMER_LOW_FREQ 12 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_XFORMER_HI_FREQ 13 // range 0 to 65534
// range 0 to 3, values: 0="PRE", 1="POST", 2="MID", 3="END"
#define BMC_FAS_PARAM_AMP_TONE_LOCATION 14
// range 0 to 2, values: 0="LEFT", 1="RIGHT", 2="SUM L+R"
#define BMC_FAS_PARAM_AMP_INPUT_SELECT 15
#define BMC_FAS_PARAM_AMP_DEPTH 16 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_SUPPLY_SAG 19 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_PRESENCE 20 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_LEVEL 21 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_BALANCE 22 // range 0 to 65534
// range 0 to 2, values: 0="LEFT", 1="RIGHT", 2="SUM L+R"
#define BMC_FAS_PARAM_AMP_BYPASS_MODE 23
#define BMC_FAS_PARAM_AMP_NEG_FEEDBACK 24 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_PRESENCE_FREQ 25 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_LOW_RES_FREQ 26 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_LOW_RES 27 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_DEPTH_FREQ 29 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_MV_CAP 31 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_HARMONICS 33 // range 0 to 65534
// range 0 to 107, values: 0="ACTIVE", 1="DEFAULT", 2="BROWNFACE", 3="BLACKFACE", 4="BASSGUY", 5="TOP BOOST", 6="PLEXI", 7="BOUTIQUE", 8="HI POWER", 9="USA NORMAL", 10="USA FAT", 11="RECTO1 ORG", 12="RECTO1 RED", 13="SKYLINE", 14="GERMAN", 15="JR BLUES", 16="WRECKER 1", 17="NEUTRAL", 18="CA3+SE", 19="FREYER D60", 20="MR Z 38 SR", 21="EURO UBER", 22="PVH 6160", 23="SOLO 100", 24="CORNCOB", 25="XTC", 26="CAROLANN", 27="CITRUS", 28="BRIT JM45", 29="USA RHY", 30="RECTO2 ORG", 31="RECTO2 RED", 32="SHIVER CLN", 33="CAMERON", 34="BRIT JVM 0D1", 35="BRIT JVM 0D2", 36="5153 GREEN", 37="5153 BLUE", 38="5153 RED", 39="BRIT SUPER", 40="DIV13 CJ", 41="BADGER 18", 42="ATOMICA", 43="SPAWN", 44="BADGER 30", 45="BRIT SILVER", 46="SUPER VERB", 47="HOT KITTY", 48="VIBRATO-KING", 49="GIBTONE SCOUT", 50="CA3+SE CLEAN", 51="BF FIXED MID", 52="GERMAN V4", 53="VIBRATO-LUX", 54="DIRTY SHIRLEY", 55="PLEXI 100W", 56="RUBY ROCKET BRT", 57="CONCOURSE", 58="TRIPTIK LD", 59="TRIPTIK CLN", 60="JAZZ 120", 61="BOGFISH", 62="WRECKER 2", 63="SKYLINE DEEP", 64="USA SUB BLUES", 65="WRECKER LVRPOOL", 66="CITRUS A30 CLN", 67="CITRUS A30 DRT", 68="CAR ROAMER", 69="USA BASS", 70="CITRUS BASS", 71="STUDIO", 72="BRIT 800", 73="RECTO1 ORG MDRN", 74="ANGLE SEVERE 1", 75="ANGLE SEVERE 2", 76="USA PRE LD1 RED", 77="RECTO ORG BRT", 78="RECTO RED BRT", 79="VIBROVERB AA", 80="PVH 6160 II LD", 81="RUMBLE HRM", 82="MR Z HWY 66", 83="SUPER 6G4", 84="65 BASSMAN BASS", 85="FREIDMAN", 86="BAND-COMMANDER", 87="USA PRE CLEAN", 88="TUCANA CLEAN", 89="FRIEDMAN SM BOX", 90="TX STAR", 91="USA IIC+", 92="THORDENDAL", 93="SOLO 99", 94="BLUDOJAI", 95="HERBIE", 96="PVH 6160 II RHY", 97="SOLO 88 CLEAN", 98="JS410", 99="JS410 MIDSHIFT", 100="RUBY ROCKET", 101="USA IIC++", 102="LEGATO 100", 103="HOOK EDGE", 104="HOOK NO EDGE", 105="HOOK CLEAN 1", 106="HOOK CLEAN 2", 107="SOLO 88"
#define BMC_FAS_PARAM_AMP_TONE_STACK 34
#define BMC_FAS_PARAM_AMP_B_PLUS_TIME_CONST 35 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_TUBE_GRID_BIAS 36 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_BRIGHT_SWITCH_SW 39 // range 0 to 1
#define BMC_FAS_PARAM_AMP_BOOST_SW 40 // range 0 to 1
#define BMC_FAS_PARAM_AMP_LOW_RES_Q 41 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_PREAMP_BIAS 42 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_HI_FREQ 43 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_HI_RESONANCE 44 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_CUT_SW 45 // range 0 to 1
#define BMC_FAS_PARAM_AMP_XFORMER_DRIVE 46 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_INPUT_TRIM 47 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_PREAMP_HARDNESS 48 // range 0 to 65534
// range 0 to 2, values: 0="PRE-PI", 1="POST-PI", 2="PRE-TRIODE"
#define BMC_FAS_PARAM_AMP_MV_LOCATION 49
#define BMC_FAS_PARAM_AMP_SPEAKER_DRIVE 50 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_XFORMER_MATCH 51 // range 0 to 65534
// range 0 to 2, values: 0="OFF", 1="AUTH", 2="IDEAL"
#define BMC_FAS_PARAM_AMP_SAT_SWITCH 54
#define BMC_FAS_PARAM_AMP_GEQ_BAND_1 55 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_GEQ_BAND_2 56 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_GEQ_BAND_3 57 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_GEQ_BAND_4 58 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_GEQ_BAND_5 59 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_GEQ_BAND_6 60 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_GEQ_BAND_7 61 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_GEQ_BAND_8 62 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_BIAS_EXCURSION 63 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_TRIODE_2_PLATE_FREQ 66 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_TRIODE_1_PLATE_FREQ 67 // range 0 to 65534
// range 0 to 11, values: 0="IDEAL TETRODE", 1="IDEAL PENTODE", 2="EL34/6CA7", 3="EL84/6BQ5", 4="6L6/5881", 5="6V6", 6="KT66", 7="KT88", 8="6550", 9="6973", 10="6AQ5", 11="300B"
#define BMC_FAS_PARAM_AMP_PWR_AMP_TUBE 68
// range 0 to 8, values: 0="12AX7A SYL", 1="ECC83", 2="7025", 3="12AX7A JJ", 4="ECC803S", 5="EF86", 6="12AX7A RCA", 7="12AX7A", 8="12AX7B"
#define BMC_FAS_PARAM_AMP_PREAMP_TUBES 69
#define BMC_FAS_PARAM_AMP_OUT_COMP_CLARITY 70 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_CHARACTER_Q 71 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_CHARACTER_FREQ 72 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_CHARACTER_AMT 73 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_OVERDRIVE 74 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_OUT_COMP_AMOUNT 75 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_OUT_COMP_THRESHOLD 76 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_MASTER_TRIM 77 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_FAT_SW 78 // range 0 to 1
#define BMC_FAS_PARAM_AMP_DEFINITION 79 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_PREAMP_CF_COMPRESS 80 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_PREAMP_CF_TIME 81 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_DYNAMIC_PRESENCE 84 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_DYNAMIC_DEPTH 85 // range 0 to 65534
// range 0 to 1, values: 0="AC", 1="DC"
#define BMC_FAS_PARAM_AMP_POWER_TYPE 86
#define BMC_FAS_PARAM_AMP_AC_LINE_FREQ 87 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_PWR_AMP_HARDNESS 88 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_PREAMP_CF_RATIO 91 // range 0 to 65534
// range 0 to 9, values: 0="8 BAND VAR Q", 1="7 BAND VAR Q", 2="5 BAND (MARK)", 3="8 BAND CONST Q", 4="7 BAND CONST Q", 5="5 BAND CONST Q", 6="5 BAND PASSIVE", 7="4 BAND PASSIVE", 8="3 BAND PASSIVE", 9="3 BAND CONSOLE"
#define BMC_FAS_PARAM_AMP_EQ_TYPE 92
#define BMC_FAS_PARAM_AMP_CATHODE_RESIST 93 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_PREAMP_SAG_SW 96 // range 0 to 1
#define BMC_FAS_PARAM_AMP_BRIGHT 97 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_PWR_AMP_BIAS 98 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_PREAMP_DYNAMICS 99 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_HI_FREQ_SLOPE 100 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_VARIAC 101 // range 0 to 65534
// range 0 to 2, values: 0="SHELVING", 1="PEAKING", 2="DYNAMIC"
#define BMC_FAS_PARAM_AMP_CHAR_TYPE 102
#define BMC_FAS_PARAM_AMP_PRESENCE_SHIFT_SW 104 // range 0 to 1
#define BMC_FAS_PARAM_AMP_SATURATION_DRIVE 105 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_CRUNCH 106 // range 0 to 65534
// range 0 to 1, values: 0="OUTPUT", 1="FEEDBACK"
#define BMC_FAS_PARAM_AMP_OUT_COMP_TYPE 109
// range 0 to 1, values: 0="POST P.A.", 1="PRE P.A."
#define BMC_FAS_PARAM_AMP_EQ_LOCATION 110
// range 0 to 1, values: 0="AUTHENTIC", 1="IDEAL"
#define BMC_FAS_PARAM_AMP_CF_COMP_TYPE 111
#define BMC_FAS_PARAM_AMP_PREAMP_CF_HARDNESS 113 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_PI_BIAS_SHIFT 114 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_SPEAKER_COMP 115 // range 0 to 65534
#define BMC_FAS_PARAM_AMP_MOTOR_TIME_CONST 116 // range 0 to 65534


// ***********************
// *** BLOCK Cab (CAB) ***
// ***********************
// range 0 to -1, values:
#define BMC_FAS_PARAM_CAB_CAB 0
#define BMC_FAS_PARAM_CAB_PROX_EFFECT_SW 1 // range 0 to 1
// range 0 to -1, values:
#define BMC_FAS_PARAM_CAB_CAB_R 2
#define BMC_FAS_PARAM_CAB_PROX_EFFECT_R_SW 3 // range 0 to 1
#define BMC_FAS_PARAM_CAB_LINK_SW 4 // range 0 to 1
#define BMC_FAS_PARAM_CAB_LEVEL_L 5 // range 0 to 65534
#define BMC_FAS_PARAM_CAB_LEVEL_R 6 // range 0 to 65534
#define BMC_FAS_PARAM_CAB_PAN_L 7 // range 0 to 65534
#define BMC_FAS_PARAM_CAB_PAN_R 8 // range 0 to 65534
#define BMC_FAS_PARAM_CAB_LEVEL 9 // range 0 to 65534
#define BMC_FAS_PARAM_CAB_BALANCE 10 // range 0 to 65534
// range 0 to 1, values: 0="THRU", 1="MUTE"
#define BMC_FAS_PARAM_CAB_BYPASS_MODE 11
// range 0 to 3, values: 0="HI-/ULTRA-RES", 1="NORMAL RES", 2="STEREO", 3="STEREO ULTRARES"
#define BMC_FAS_PARAM_CAB_EFFECT_TYPE 12
#define BMC_FAS_PARAM_CAB_LOW_CUT 19 // range 0 to 65534
#define BMC_FAS_PARAM_CAB_HIGH_CUT 20 // range 0 to 65534
#define BMC_FAS_PARAM_CAB_PROXIMITY 22 // range 0 to 65534
#define BMC_FAS_PARAM_CAB_DELAY 26 // range 0 to 65534
#define BMC_FAS_PARAM_CAB_DELAY_R 27 // range 0 to 65534
#define BMC_FAS_PARAM_CAB_PROXIMITY_R 28 // range 0 to 65534
#define BMC_FAS_PARAM_CAB_PROX_FREQ 29 // range 0 to 65534
// range 0 to 3, values: 0="STEREO", 1="LEFT", 2="RIGHT", 3="SUM L+R"
#define BMC_FAS_PARAM_CAB_INPUT_SELECT 30
// range 0 to 1, values: 0="6 dB/OCT", 1="12 dB/OCT"
#define BMC_FAS_PARAM_CAB_FILTER_SLOPE 37


// **************************
// *** BLOCK Reverb (REV) ***
// **************************
// range 0 to 42, values: 0="SMALL ROOM", 1="MEDIUM ROOM", 2="LARGE ROOM", 3="SMALL HALL", 4="MEDIUM HALL", 5="LARGE HALL", 6="SMALL CHAMBER", 7="MEDIUM CHAMBER", 8="LARGE CHAMBER", 9="SMALL PLATE", 10="MEDIUM PLATE", 11="LARGE PLATE", 12="SMALL CATHEDRAL", 13="MED. CATHEDRAL", 14="LARGE CATHEDRAL", 15="SMALL SPRING", 16="MEDIUM SPRING", 17="LARGE SPRING", 18="CAVERN", 19="STONE QUARRY", 20="STUDIO", 21="AMBIENCE", 22="CONCERT HALL", 23="LARGE DEEP HALL", 24="REC STUDIO C", 25="NORTH CHURCH", 26="SOUTH CHURCH", 27="LONDON PLATE", 28="SUN PLATE", 29="HUGE ROOM", 30="DRUM ROOM", 31="HALLWAY", 32="TUNNEL", 33="DEEP CHAMBER", 34="LG WOODEN ROOM", 35="GYMNASIUM", 36="ASYLUM HALL", 37="DEEP SPACE", 38="REC STUDIO A", 39="LG TILED ROOM", 40="VOCAL PLATE", 41="WIDE HALL", 42="RICH HALL"
#define BMC_FAS_PARAM_REV_EFFECT_TYPE 0
#define BMC_FAS_PARAM_REV_TIME 1 // range 0 to 65534
#define BMC_FAS_PARAM_REV_HIGH_CUT 2 // range 0 to 65534
#define BMC_FAS_PARAM_REV_HF_TIME 3 // range 0 to 65534
#define BMC_FAS_PARAM_REV_WALL_DIFFUSION 4 // range 0 to 65534
#define BMC_FAS_PARAM_REV_SIZE 5 // range 0 to 65534
#define BMC_FAS_PARAM_REV_EARLY_LEVEL 7 // range 0 to 65534
#define BMC_FAS_PARAM_REV_LATE_LEVEL 8 // range 0 to 65534
#define BMC_FAS_PARAM_REV_PREDELAY 9 // range 0 to 65534
#define BMC_FAS_PARAM_REV_LOW_CUT 10 // range 0 to 65534
#define BMC_FAS_PARAM_REV_MOD_DEPTH 11 // range 0 to 65534
#define BMC_FAS_PARAM_REV_MOD_RATE 12 // range 0 to 65534
#define BMC_FAS_PARAM_REV_MIX 13 // range 0 to 65534
#define BMC_FAS_PARAM_REV_LEVEL 14 // range 0 to 65534
#define BMC_FAS_PARAM_REV_BALANCE 15 // range 0 to 65534
// range 0 to 4, values: 0="THRU", 1="MUTE FX OUT", 2="MUTE OUT", 3="MUTE FX IN", 4="MUTE IN"
#define BMC_FAS_PARAM_REV_BYPASS_MODE 16
#define BMC_FAS_PARAM_REV_GLOBAL_SW 17 // range 0 to 1
#define BMC_FAS_PARAM_REV_INPUT_GAIN 18 // range 0 to 65534
#define BMC_FAS_PARAM_REV_ECHO_DENSITY 19 // range 0 to 65534
#define BMC_FAS_PARAM_REV_LATE_DIFFUSION 20 // range 0 to 65534
#define BMC_FAS_PARAM_REV_LATE_DIFF_TIME 21 // range 0 to 65534
#define BMC_FAS_PARAM_REV_SPRING_NUMBER 23 // range 0 to 65534
#define BMC_FAS_PARAM_REV_SPRING_TONE 24 // range 0 to 65534
#define BMC_FAS_PARAM_REV_MIC_SPACING 25 // range 0 to 65534
#define BMC_FAS_PARAM_REV_FREQ_1 26 // range 0 to 65534
#define BMC_FAS_PARAM_REV_FREQ_2 27 // range 0 to 65534
#define BMC_FAS_PARAM_REV_Q_1 28 // range 0 to 65534
#define BMC_FAS_PARAM_REV_Q_2 29 // range 0 to 65534
#define BMC_FAS_PARAM_REV_GAIN_1 30 // range 0 to 65534
#define BMC_FAS_PARAM_REV_GAIN_2 31 // range 0 to 65534
#define BMC_FAS_PARAM_REV_SPRING_DRIVE 32 // range 0 to 65534
#define BMC_FAS_PARAM_REV_LF_TIME 33 // range 0 to 65534
#define BMC_FAS_PARAM_REV_LF_CROSSOVER 34 // range 0 to 65534
#define BMC_FAS_PARAM_REV_STEREO_WIDTH 35 // range 0 to 65534
#define BMC_FAS_PARAM_REV_ATTEN 36 // range 0 to 65534
#define BMC_FAS_PARAM_REV_THRESHOLD 37 // range 0 to 65534
#define BMC_FAS_PARAM_REV_RELEASE_TIME 38 // range 0 to 65534
#define BMC_FAS_PARAM_REV_EARLY_DIFFUSION 39 // range 0 to 65534
#define BMC_FAS_PARAM_REV_EARLY_DIFF_TIME 40 // range 0 to 65534
#define BMC_FAS_PARAM_REV_EARLY_DECAY 41 // range 0 to 65534
// range 0 to 1, values: 0="NORMAL", 1="HIGH"
#define BMC_FAS_PARAM_REV_QUALITY 43
#define BMC_FAS_PARAM_REV_HOLD_SW 44 // range 0 to 1


// ***********************
// *** BLOCK Delay (DLY) ***
// ***********************
// range 0 to 17, values: 0="DIGITAL MONO", 1="DIGITAL STEREO", 2="ANALOG MONO", 3="ANALOG STEREO", 4="MONO TAPE", 5="STEREO TAPE", 6="PING-PONG", 7="DUAL DELAY", 8="REVERSE DELAY", 9="SWEEP DELAY", 10="DUCKING DELAY", 11="VINTAGE DIGITAL", 12="2290 W/ MOD", 13="AMBIENT STEREO", 14="DELUXE MIND GUY", 15="MONO BBD", 16="STEREO BBD", 17="LO-FI TAPE"
#define BMC_FAS_PARAM_DLY_EFFECT_TYPE 0
// range 0 to 6, values: 0="MONO", 1="STEREO", 2="PING-PONG", 3="DUAL", 4="REVERSE", 5="SWEEP", 6="TAPE"
#define BMC_FAS_PARAM_DLY_CONFIG 1
#define BMC_FAS_PARAM_DLY_TIME 2 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_RATIO 3 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_FEEDBACK 4 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_FEEDBACK_R 6 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_ECHO_PAN 7 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_SPREAD 8 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_DLY_TEMPO 9
#define BMC_FAS_PARAM_DLY_LOW_CUT 10 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_HIGH_CUT 11 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_LFO1_RATE 12 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_LFO2_RATE 13 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_LFO1_DEPTH 14 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_LFO2_DEPTH 15 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_DRIVE 16 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_MIX 17 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_LEVEL 18 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_BALANCE 19 // range 0 to 65534
// range 0 to 4, values: 0="THRU", 1="MUTE FX OUT", 2="MUTE OUT", 3="MUTE FX IN", 4="MUTE IN"
#define BMC_FAS_PARAM_DLY_BYPASS_MODE 20
#define BMC_FAS_PARAM_DLY_GLOBAL_SW 21 // range 0 to 1
#define BMC_FAS_PARAM_DLY_INPUT_GAIN 23 // range 0 to 65534
// range 0 to 8, values: 0="SINE", 1="TRIANGLE", 2="SQUARE", 3="SAW UP", 4="SAW DOWN", 5="RANDOM", 6="LOG", 7="EXP", 8="TRAPEZOID"
#define BMC_FAS_PARAM_DLY_LFO1_TYPE 24
// range 0 to 8, values: 0="SINE", 1="TRIANGLE", 2="SQUARE", 3="SAW UP", 4="SAW DOWN", 5="RANDOM", 6="LOG", 7="EXP", 8="TRAPEZOID"
#define BMC_FAS_PARAM_DLY_LFO2_TYPE 25
#define BMC_FAS_PARAM_DLY_TIME_R 26 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_REPEAT_HOLD_SW 27 // range 0 to 1
#define BMC_FAS_PARAM_DLY_MASTER_FEEDBACK 28 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_DLY_TEMPO_R 29
#define BMC_FAS_PARAM_DLY_FEEDBACK_L_R 30 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_FEEDBACK_R_L 31 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_LEVEL_1 32 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_LEVEL_2 33 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_PAN_1 34 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_PAN_2 35 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_LFO1_PHASE 36 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_LFO2_PHASE 37 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_X_FADE_TIME 38 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_RUN_SW 39 // range 0 to 1
#define BMC_FAS_PARAM_DLY_TRIGGER_RESTART_SW 40 // range 0 to 1
// range 0 to 4, values: 0="6 dB/OCT", 1="12 dB/OCT", 2="24 dB/OCT", 3="36 dB/OCT", 4="48 dB/OCT"
#define BMC_FAS_PARAM_DLY_FILTER_SLOPE 41
#define BMC_FAS_PARAM_DLY_DUCK_ATTN 42 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_DUCK_THRES 43 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_DUCK_RELEASE 44 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_DIFFUSION 45 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_DIFF_TIME 46 // range 0 to 65534
// range 0 to 3, values: 0="NONE", 1="RIGHT", 2="LEFT", 3="BOTH"
#define BMC_FAS_PARAM_DLY_PHASE_REVERSE 47
// range 0 to 2, values: 0="BOTH", 1="LEFT", 2="RIGHT"
#define BMC_FAS_PARAM_DLY_LFO1_TARGET 48
// range 0 to 2, values: 0="BOTH", 1="LEFT", 2="RIGHT"
#define BMC_FAS_PARAM_DLY_LFO2_TARGET 49
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_DLY_LFO1_TEMPO 50
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_DLY_LFO2_TEMPO 51
#define BMC_FAS_PARAM_DLY_SWEEP_RATE 52 // range 0 to 65534
// range 0 to 8, values: 0="SINE", 1="TRIANGLE", 2="SQUARE", 3="SAW UP", 4="SAW DOWN", 5="RANDOM", 6="LOG", 7="EXP", 8="TRAPEZOID"
#define BMC_FAS_PARAM_DLY_SWEEP_TYPE 53
#define BMC_FAS_PARAM_DLY_SWEEP_PHASE 54 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_DLY_SWEEP_TEMPO 55
#define BMC_FAS_PARAM_DLY_START_FREQ 56 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_STOP_FREQ 57 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_RESONANCE 58 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_Q 59 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_BIT_REDUCTION 60 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_FREQ_1 61 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_FREQ_2 62 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_Q_1 63 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_Q_2 64 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_GAIN_1 65 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_GAIN_2 66 // range 0 to 65534
// range 0 to 1, values: 0="LOW", 1="HIGH"
#define BMC_FAS_PARAM_DLY_LFO1_DEPTH_RANGE 67
#define BMC_FAS_PARAM_DLY_MOTOR_SPEED 68 // range 0 to 65534
#define BMC_FAS_PARAM_DLY_RIGHT_POST_DELAY 69 // range 0 to 65534


// ***********************
// *** BLOCK Multi Delay (MTD) ***
// ***********************
#define BMC_FAS_PARAM_MTD_TIME_1 0 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TIME_2 1 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TIME_3 2 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TIME_4 3 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_MTD_TEMPO_1 4
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_MTD_TEMPO_2 5
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_MTD_TEMPO_3 6
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_MTD_TEMPO_4 7
#define BMC_FAS_PARAM_MTD_LEVEL_1 8 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LEVEL_2 9 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LEVEL_3 10 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LEVEL_4 11 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_FEEDBACK_1 12 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_FEEDBACK_2 13 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_FEEDBACK_3 14 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_FEEDBACK_4 15 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_PAN_1 16 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_PAN_2 17 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_PAN_3 18 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_PAN_4 19 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LFO1_RATE 20 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LFO2_RATE 21 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LFO3_RATE 22 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LFO4_RATE 23 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_MTD_LFO1_TEMPO 24
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_MTD_LFO2_TEMPO 25
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_MTD_LFO3_TEMPO 26
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_MTD_LFO4_TEMPO 27
#define BMC_FAS_PARAM_MTD_MIX 28 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LEVEL 29 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_BALANCE 30 // range 0 to 65534
// range 0 to 4, values: 0="THRU", 1="MUTE FX OUT", 2="MUTE OUT", 3="MUTE FX IN", 4="MUTE IN"
#define BMC_FAS_PARAM_MTD_BYPASS_MODE 31
#define BMC_FAS_PARAM_MTD_GLOBAL_MIX_SW 32 // range 0 to 1
#define BMC_FAS_PARAM_MTD_INPUT_GAIN 33 // range 0 to 65534
// range 0 to 9, values: 0="QUAD-TAP", 1="PLEX DELAY", 2="PLEX DETUNE", 3="PLEX SHIFT", 4="BAND DELAY", 5="QUAD-SERIES", 6="TEN-TAP DLY", 7="RHYTHM TAP", 8="DIFFUSOR", 9="QUAD TAPE DLY"
#define BMC_FAS_PARAM_MTD_EFFECT_TYPE 35
#define BMC_FAS_PARAM_MTD_DECAY_TIME 36 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_DIFFUSION 37 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_INPUT_DIFF 38 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_DIFF_TIME 39 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_DUCKER_THRES 40 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_CROSSFADE 41 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_MASTER_TIME 42 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_MASTER_LEVEL 43 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_MASTER_PAN 44 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_MASTER_FREQ 45 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_MASTER_Q 46 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_MASTER_FEEDBACK 47 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_MASTER_PITCH 48 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_MASTER_DETUNE 49 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_DETUNE_1 50 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_DETUNE_2 51 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_DETUNE_3 52 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_DETUNE_4 53 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_SHIFT_1 54 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_SHIFT_2 55 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_SHIFT_3 56 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_SHIFT_4 57 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_FREQ_1 58 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_FREQ_2 59 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_FREQ_3 60 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_FREQ_4 61 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_Q_1 62 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_Q_2 63 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_Q_3 64 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_Q_4 65 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_MASTER_RATE 66 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_DUCKER_ATTEN 67 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_MASTER_DEPTH 68 // range 0 to 65534
// range 0 to 1, values: 0="FORWARD", 1="REVERSE"
#define BMC_FAS_PARAM_MTD_DIRECTION 69
#define BMC_FAS_PARAM_MTD_TAPE_SPEED 70 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LFO1_DEPTH 71 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LFO2_DEPTH 72 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LFO3_DEPTH 73 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LFO4_DEPTH 74 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LFO1_MASTER_SW 75 // range 0 to 1
// range 0 to 3, values: 0="1", 1="2", 2="3", 3="4"
#define BMC_FAS_PARAM_MTD_FB_SEND 76
// range 0 to 3, values: 0="1", 1="2", 2="3", 3="4"
#define BMC_FAS_PARAM_MTD_FB_RETURN 77
// range 0 to 1, values: 0="MONO", 1="STEREO"
#define BMC_FAS_PARAM_MTD_MONO_STEREO 78
#define BMC_FAS_PARAM_MTD_DELAY_TIME 79 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_MTD_QUANTIZE 81
#define BMC_FAS_PARAM_MTD_DECAY 82 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_NUMBER_OF_TAPS 84 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_SHUFFLE 85 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_MTD_DELAY_TEMPO 86
#define BMC_FAS_PARAM_MTD_SPREAD 87 // range 0 to 65534
// range 0 to 5, values: 0="CONSTANT", 1="INCREASING", 2="DECREASING", 3="UP / DOWN", 4="DOWN / UP", 5="SINE"
#define BMC_FAS_PARAM_MTD_PAN_SHAPE 88
#define BMC_FAS_PARAM_MTD_PAN_ALPHA 89 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_LOW_CUT 90 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_HIGH_CUT 91 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_RATIO 92 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_FEEDBACK 93 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_1_TIME 94 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_2_TIME 95 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_3_TIME 96 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_4_TIME 97 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_5_TIME 98 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_6_TIME 99 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_7_TIME 100 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_8_TIME 101 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_9_TIME 102 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_10_TIME 103 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_1_LEVEL 104 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_2_LEVEL 105 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_3_LEVEL 106 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_4_LEVEL 107 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_5_LEVEL 108 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_6_LEVEL 109 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_7_LEVEL 110 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_8_LEVEL 111 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_9_LEVEL 112 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_TAP_10_LEVEL 113 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_DUCKER_RELEASE 116 // range 0 to 65534
#define BMC_FAS_PARAM_MTD_DRIVE 117 // range 0 to 65534


// ***********************
// *** BLOCK Chorus (CHO) ***
// ***********************
// range 0 to 12, values: 0="DIGITAL MONO", 1="DIGITAL STEREO", 2="ANALOG MONO", 3="ANALOG STEREO", 4="JAPAN CE-2", 5="WARM STEREO", 6="80'S STYLE", 7="TRIANGLE CHORUS", 8="8-VOICE STEREO", 9="VINTAGE TAPE", 10="DIMENSION 1", 11="DIMENSION 2", 12="4-VOICE ANALOG"
#define BMC_FAS_PARAM_CHO_EFFECT_TYPE 0
#define BMC_FAS_PARAM_CHO_VOICES 1 // range 0 to 65534
#define BMC_FAS_PARAM_CHO_RATE 2 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_CHO_TEMPO 3
#define BMC_FAS_PARAM_CHO_DEPTH 4 // range 0 to 65534
#define BMC_FAS_PARAM_CHO_HIGH_CUT 5 // range 0 to 65534
#define BMC_FAS_PARAM_CHO_DELAY_TIME 6 // range 0 to 65534
#define BMC_FAS_PARAM_CHO_LFO_PHASE 7 // range 0 to 65534
// range 0 to 8, values: 0="SINE", 1="TRIANGLE", 2="SQUARE", 3="SAW UP", 4="SAW DOWN", 5="RANDOM", 6="LOG", 7="EXP", 8="TRAPEZOID"
#define BMC_FAS_PARAM_CHO_LFO_TYPE 8
// range 0 to 2, values: 0="OFF", 1="LOW", 2="HIGH"
#define BMC_FAS_PARAM_CHO_AUTO_DEPTH 9
#define BMC_FAS_PARAM_CHO_MIX 10 // range 0 to 65534
#define BMC_FAS_PARAM_CHO_LEVEL 11 // range 0 to 65534
#define BMC_FAS_PARAM_CHO_BALANCE 12 // range 0 to 65534
// range 0 to 2, values: 0="THRU", 1="MUTE FX OUT", 2="MUTE OUT"
#define BMC_FAS_PARAM_CHO_BYPASS_MODE 13
#define BMC_FAS_PARAM_CHO_GLOBAL_SW 14 // range 0 to 1
// range 0 to 3, values: 0="NONE", 1="RIGHT", 2="LEFT", 3="BOTH"
#define BMC_FAS_PARAM_CHO_PHASE_REVERSE 16
#define BMC_FAS_PARAM_CHO_WIDTH 17 // range 0 to 65534
#define BMC_FAS_PARAM_CHO_LFO_2_RATE 18 // range 0 to 65534
#define BMC_FAS_PARAM_CHO_LFO_2_DEPTH 19 // range 0 to 65534
#define BMC_FAS_PARAM_CHO_DRIVE 20 // range 0 to 65534
#define BMC_FAS_PARAM_CHO_LOW_CUT 21 // range 0 to 65534
#define BMC_FAS_PARAM_CHO_SPREAD 22 // range 0 to 65534
// range 0 to 3, values: 0="OFF", 1="LOW", 2="MED", 3="HIGH"
#define BMC_FAS_PARAM_CHO_DIMENSION 23


// ***********************
// *** BLOCK Flanger (FLG) ***
// ***********************
// range 0 to 7, values: 0="DIGITAL MONO", 1="DIGITAL STEREO", 2="ANALOG MONO", 3="ANALOG STEREO", 4="THRU-ZERO", 5="STEREO JET", 6="ZERO FLANGER", 7="POP FLANGER"
#define BMC_FAS_PARAM_FLG_EFFECT_TYPE 0
#define BMC_FAS_PARAM_FLG_RATE 1 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_FLG_TEMPO 2
#define BMC_FAS_PARAM_FLG_DEPTH 3 // range 0 to 65534
#define BMC_FAS_PARAM_FLG_FEEDBACK 4 // range 0 to 65534
#define BMC_FAS_PARAM_FLG_DELAY_TIME 5 // range 0 to 65534
#define BMC_FAS_PARAM_FLG_DRY_DELAY_SHIFT 6 // range 0 to 65534
#define BMC_FAS_PARAM_FLG_LFO_PHASE 7 // range 0 to 65534
// range 0 to 8, values: 0="SINE", 1="TRIANGLE", 2="SQUARE", 3="SAW UP", 4="SAW DOWN", 5="RANDOM", 6="LOG", 7="EXP", 8="TRAPEZOID"
#define BMC_FAS_PARAM_FLG_LFO_TYPE 8
#define BMC_FAS_PARAM_FLG_LFO_HIGHCUT 9 // range 0 to 65534
// range 0 to 3, values: 0="OFF", 1="LOW", 2="MED", 3="HIGH"
#define BMC_FAS_PARAM_FLG_AUTO_DEPTH 10
#define BMC_FAS_PARAM_FLG_MIX 11 // range 0 to 65534
#define BMC_FAS_PARAM_FLG_LEVEL 12 // range 0 to 65534
#define BMC_FAS_PARAM_FLG_BALANCE 13 // range 0 to 65534
// range 0 to 2, values: 0="THRU", 1="MUTE FX OUT", 2="MUTE OUT"
#define BMC_FAS_PARAM_FLG_BYPASS_MODE 14
#define BMC_FAS_PARAM_FLG_GLOBAL_SW 15 // range 0 to 1
// range 0 to 3, values: 0="NONE", 1="RIGHT", 2="LEFT", 3="BOTH"
#define BMC_FAS_PARAM_FLG_PHASE_REVERSE 17
#define BMC_FAS_PARAM_FLG_THRU_ZERO_SW 18 // range 0 to 1
#define BMC_FAS_PARAM_FLG_HIGH_CUT 19 // range 0 to 65534
#define BMC_FAS_PARAM_FLG_DRIVE 20 // range 0 to 65534
#define BMC_FAS_PARAM_FLG_LOW_CUT 21 // range 0 to 65534
#define BMC_FAS_PARAM_FLG_SPREAD 22 // range 0 to 65534


// ***********************
// *** BLOCK Rotary Speaker (ROT) ***
// ***********************
#define BMC_FAS_PARAM_ROT_RATE 0 // range 0 to 65534
#define BMC_FAS_PARAM_ROT_LOW_DEPTH 1 // range 0 to 65534
#define BMC_FAS_PARAM_ROT_HI_DEPTH 2 // range 0 to 65534
#define BMC_FAS_PARAM_ROT_HI_LEVEL 3 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_ROT_TEMPO 4
#define BMC_FAS_PARAM_ROT_MIX 5 // range 0 to 65534
#define BMC_FAS_PARAM_ROT_LEVEL 6 // range 0 to 65534
#define BMC_FAS_PARAM_ROT_BALANCE 7 // range 0 to 65534
// range 0 to 2, values: 0="THRU", 1="MUTE FX OUT", 2="MUTE OUT"
#define BMC_FAS_PARAM_ROT_BYPASS_MODE 8
#define BMC_FAS_PARAM_ROT_ROTOR_LENGTH 10 // range 0 to 65534
#define BMC_FAS_PARAM_ROT_MIC_SPACING 12 // range 0 to 65534
#define BMC_FAS_PARAM_ROT_LOW_RATE_MULT 13 // range 0 to 65534
#define BMC_FAS_PARAM_ROT_LOW_TIME_CONST 14 // range 0 to 65534
#define BMC_FAS_PARAM_ROT_HI_TIME_CONST 15 // range 0 to 65534
#define BMC_FAS_PARAM_ROT_STEREO_SPREAD 16 // range 0 to 65534
#define BMC_FAS_PARAM_ROT_DRIVE 17 // range 0 to 65534
#define BMC_FAS_PARAM_ROT_MIC_DISTANCE 18 // range 0 to 65534


// ***********************
// *** BLOCK Phaser (PHA) ***
// ***********************
// range 0 to 7, values: 0="DIGITAL MONO", 1="DIGITAL STEREO", 2="SCRIPT 45", 3="SCRIPT 90", 4="BLOCK 90", 5="CLASSIC VIBE", 6="STEREO 8-STAGE", 7="BARBERPOLE"
#define BMC_FAS_PARAM_PHA_EFFECT_TYPE 0
// range 0 to 5, values: 0="2", 1="4", 2="6", 3="8", 4="10", 5="12"
#define BMC_FAS_PARAM_PHA_ORDER 1
#define BMC_FAS_PARAM_PHA_RATE 2 // range 0 to 65534
// range 0 to 8, values: 0="SINE", 1="TRIANGLE", 2="SQUARE", 3="SAW UP", 4="SAW DOWN", 5="RANDOM", 6="LOG", 7="EXP", 8="TRAPEZOID"
#define BMC_FAS_PARAM_PHA_LFO_TYPE 3
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_PHA_TEMPO 4
#define BMC_FAS_PARAM_PHA_DEPTH 5 // range 0 to 65534
#define BMC_FAS_PARAM_PHA_FEEDBACK 6 // range 0 to 65534
#define BMC_FAS_PARAM_PHA_FREQ_START 7 // range 0 to 65534
#define BMC_FAS_PARAM_PHA_FREQ_SPAN 8 // range 0 to 65534
#define BMC_FAS_PARAM_PHA_LFO_PHASE 9 // range 0 to 65534
#define BMC_FAS_PARAM_PHA_BULB_BIAS 10 // range 0 to 65534
#define BMC_FAS_PARAM_PHA_MIX 11 // range 0 to 65534
#define BMC_FAS_PARAM_PHA_LEVEL 12 // range 0 to 65534
#define BMC_FAS_PARAM_PHA_BALANCE 13 // range 0 to 65534
// range 0 to 2, values: 0="THRU", 1="MUTE FX OUT", 2="MUTE OUT"
#define BMC_FAS_PARAM_PHA_BYPASS_MODE 14
#define BMC_FAS_PARAM_PHA_GLOBAL_SW 15 // range 0 to 1
// range 0 to 2, values: 0="NORMAL", 1="VIBE", 2="BARBERPOLE"
#define BMC_FAS_PARAM_PHA_MODE 17
#define BMC_FAS_PARAM_PHA_FEEDBACK_TAP_SW 18 // range 0 to 1
#define BMC_FAS_PARAM_PHA_TONE 19 // range 0 to 65534
// range 0 to 1, values: 0="UP", 1="DOWN"
#define BMC_FAS_PARAM_PHA_DIRECTION 20
#define BMC_FAS_PARAM_PHA_FILTER_Q 21 // range 0 to 65534
// range 0 to 4, values: 0="OFF", 1="0 DEG", 2="90 DEG", 3="180 DEG", 4="270 DEG"
#define BMC_FAS_PARAM_PHA_LFO_BYPASS_RESET 22


// ***********************
// *** BLOCK Wah (WAH) ***
// ***********************
// range 0 to 7, values: 0="FAS STANDARD", 1="CLYDE", 2="CRY BABE", 3="VX846", 4="COLOR-TONE", 5="FUNK", 6="MORTAL", 7="VX845"
#define BMC_FAS_PARAM_WAH_EFFECT_TYPE 0
#define BMC_FAS_PARAM_WAH_FREQ_MIN 1 // range 0 to 65534
#define BMC_FAS_PARAM_WAH_FREQ_MAX 2 // range 0 to 65534
#define BMC_FAS_PARAM_WAH_RESONANCE 3 // range 0 to 65534
#define BMC_FAS_PARAM_WAH_TRACKING 4 // range 0 to 65534
#define BMC_FAS_PARAM_WAH_CONTROL 5 // range 0 to 65534
#define BMC_FAS_PARAM_WAH_LEVEL 6 // range 0 to 65534
#define BMC_FAS_PARAM_WAH_BALANCE 7 // range 0 to 65534
// range 0 to 1, values: 0="THRU", 1="MUTE"
#define BMC_FAS_PARAM_WAH_BYPASS_MODE 8
#define BMC_FAS_PARAM_WAH_FAT 9 // range 0 to 65534
#define BMC_FAS_PARAM_WAH_DRIVE 10 // range 0 to 65534
// range 0 to 5, values: 0="LINEAR", 1="LOG 30A", 2="LOG 20A", 3="LOG 15A", 4="LOG 10A", 5="LOG 5A"
#define BMC_FAS_PARAM_WAH_TAPER 11
#define BMC_FAS_PARAM_WAH_COIL_BIAS 13 // range 0 to 65534
#define BMC_FAS_PARAM_WAH_LOW_CUT_FREQ 14 // range 0 to 65534


// ***********************
// *** BLOCK Formant (FRM) ***
// ***********************
// range 0 to 9, values: 0="AAA", 1="EEE", 2="III", 3="OHH", 4="OOO", 5="EHH", 6="AHH", 7="AWW", 8="UHH", 9="ERR"
#define BMC_FAS_PARAM_FRM_START 0
// range 0 to 9, values: 0="AAA", 1="EEE", 2="III", 3="OHH", 4="OOO", 5="EHH", 6="AHH", 7="AWW", 8="UHH", 9="ERR"
#define BMC_FAS_PARAM_FRM_MID 1
// range 0 to 9, values: 0="AAA", 1="EEE", 2="III", 3="OHH", 4="OOO", 5="EHH", 6="AHH", 7="AWW", 8="UHH", 9="ERR"
#define BMC_FAS_PARAM_FRM_END 2
#define BMC_FAS_PARAM_FRM_RESONANCE 3 // range 0 to 65534
#define BMC_FAS_PARAM_FRM_CONTROL 4 // range 0 to 65534
#define BMC_FAS_PARAM_FRM_MIX 5 // range 0 to 65534
#define BMC_FAS_PARAM_FRM_LEVEL 6 // range 0 to 65534
#define BMC_FAS_PARAM_FRM_BALANCE 7 // range 0 to 65534
// range 0 to 2, values: 0="THRU", 1="MUTE FX OUT", 2="MUTE OUT"
#define BMC_FAS_PARAM_FRM_BYPASS_MODE 8
#define BMC_FAS_PARAM_FRM_GLOBAL_SW 9 // range 0 to 1


// ***********************
// *** BLOCK Volume/Pan (VOL) ***
// ***********************
#define BMC_FAS_PARAM_VOL_VOLUME 0 // range 0 to 65534
#define BMC_FAS_PARAM_VOL_BALANCE 1 // range 0 to 65534
// range 0 to 5, values: 0="LINEAR", 1="LOG 30A", 2="LOG 20A", 3="LOG 15A", 4="LOG 10A", 5="LOG 5A"
#define BMC_FAS_PARAM_VOL_VOLUME_TAPER 2
#define BMC_FAS_PARAM_VOL_PAN_LEFT 4 // range 0 to 65534
#define BMC_FAS_PARAM_VOL_PAN_RIGHT 5 // range 0 to 65534
#define BMC_FAS_PARAM_VOL_LEVEL 6 // range 0 to 65534
// range 0 to 1, values: 0="THRU", 1="MUTE"
#define BMC_FAS_PARAM_VOL_BYPASS_MODE 7
// range 0 to 2, values: 0="STEREO", 1="LEFT ONLY", 2="RIGHT ONLY"
#define BMC_FAS_PARAM_VOL_INPUT_SELECT 8


// ***********************
// *** BLOCK Tremolo/Panner (TRM) ***
// ***********************
// range 0 to 1, values: 0="TREMOLO", 1="PANNER"
#define BMC_FAS_PARAM_TRM_EFFECT_TYPE 0
// range 0 to 8, values: 0="SINE", 1="TRIANGLE", 2="SQUARE", 3="SAW UP", 4="SAW DOWN", 5="RANDOM", 6="LOG", 7="EXP", 8="TRAPEZOID"
#define BMC_FAS_PARAM_TRM_LFO_TYPE 1
#define BMC_FAS_PARAM_TRM_RATE 2 // range 0 to 65534
#define BMC_FAS_PARAM_TRM_DEPTH 3 // range 0 to 65534
#define BMC_FAS_PARAM_TRM_DUTY 4 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_TRM_TEMPO 5
#define BMC_FAS_PARAM_TRM_LEVEL 7 // range 0 to 65534
#define BMC_FAS_PARAM_TRM_BALANCE 8 // range 0 to 65534
// range 0 to 1, values: 0="THRU", 1="MUTE"
#define BMC_FAS_PARAM_TRM_BYPASS_MODE 9
#define BMC_FAS_PARAM_TRM_LFO_PHASE 11 // range 0 to 65534
#define BMC_FAS_PARAM_TRM_WIDTH 12 // range 0 to 65534
#define BMC_FAS_PARAM_TRM_PAN_CENTER 13 // range 0 to 65534
#define BMC_FAS_PARAM_TRM_START_PHASE 15 // range 0 to 65534


// ***********************
// *** BLOCK Pitch (PIT) ***
// ***********************
// range 0 to 8, values: 0="DETUNE", 1="FIXED HARM", 2="INTEL HARM", 3="CL. WHAMMY", 4="OCTAVE DIV", 5="CRYSTALS", 6="AD. WHAMMY", 7="ARPEGGIATOR", 8="CUST. SHIFT"
#define BMC_FAS_PARAM_PIT_EFFECT_TYPE 0
// range 0 to 5, values: 0="UP 1 OCT", 1="DOWN 1 OCT", 2="UP 2 OCT", 3="DOWN 2 OCT", 4="UP|DN 1 OCT", 5="UP|DN 2 OCT"
#define BMC_FAS_PARAM_PIT_MODE 1
#define BMC_FAS_PARAM_PIT_MASTER_PITCH 2 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_CONTROL 3 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_1_HARMONY 4 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_2_HARMONY 5 // range 0 to 65534
// range 0 to 11, values: 0="A ", 1="Bb", 2="B ", 3="C ", 4="Db", 5="D ", 6="Eb", 7="E ", 8="F ", 9="Gb", 10="G ", 11="Ab"
#define BMC_FAS_PARAM_PIT_KEY 6
// range 0 to 17, values: 0="IONIAN MAJ", 1="DORIAN", 2="PHRYGIAN", 3="LYDIAN", 4="MIXOLYDIAN", 5="AEOLIAN MIN", 6="LOCRIAN", 7="MEL. MINOR", 8="HARM. MINOR", 9="DIMINISHED", 10="WHOLE TONE", 11="DOM. SEVEN", 12="DIM. WHOLE", 13="PENTA. MAJ", 14="PENTA. MIN", 15="BLUES", 16="CHROMATIC", 17="CUSTOM"
#define BMC_FAS_PARAM_PIT_SCALE 7
// range 0 to 1, values: 0="SMOOTH", 1="STEPPED"
#define BMC_FAS_PARAM_PIT_TRACK_MODE 8
#define BMC_FAS_PARAM_PIT_VOICE_1_DETUNE 9 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_2_DETUNE 10 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_1_SHIFT 11 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_2_SHIFT 12 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_1_LEVEL 13 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_2_LEVEL 14 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_1_PAN 15 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_2_PAN 16 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_1_DELAY 17 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_2_DELAY 18 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_1_FEEDBACK 19 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_2_FEEDBACK 20 // range 0 to 65534
// range 0 to 2, values: 0="OFF", 1="POLY", 2="MONO"
#define BMC_FAS_PARAM_PIT_PITCH_TRACK 21
#define BMC_FAS_PARAM_PIT_TRACK_ADJUST 22 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_MIX 23 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_LEVEL 24 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_BALANCE 25 // range 0 to 65534
// range 0 to 4, values: 0="THRU", 1="MUTE FX OUT", 2="MUTE OUT", 3="MUTE FX IN", 4="MUTE IN"
#define BMC_FAS_PARAM_PIT_BYPASS_MODE 26
#define BMC_FAS_PARAM_PIT_GLOBAL_SW 27 // range 0 to 1
#define BMC_FAS_PARAM_PIT_INPUT_GAIN 28 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_CROSSFADE 30 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_1_SPLICE 31 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_2_SPLICE 32 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_PIT_VOICE_1_TEMPO 33
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_PIT_VOICE_2_TEMPO 34
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_PIT_SPLC1_TEMPO 35
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_PIT_SPLC2_TEMPO 36
// range 0 to 2, values: 0="DUAL", 1="BOTH", 2="PING-PONG"
#define BMC_FAS_PARAM_PIT_FEEDBACK_TYPE 37
#define BMC_FAS_PARAM_PIT_REVERSE_SW 38 // range 0 to 1
#define BMC_FAS_PARAM_PIT_HI_CUT 39 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_GLIDE_TIME 40 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_MASTER_DELAY 41 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_MASTER_FEEDBACK 42 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_MASTER_PAN 43 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_MASTER_LEVEL 44 // range 0 to 65534
// range 0 to 8, values: 0="0", 1="1", 2="2", 3="3", 4="4", 5="5", 6="6", 7="7", 8="8"
#define BMC_FAS_PARAM_PIT_NOTES 45
#define BMC_FAS_PARAM_PIT_VOICE_1_SCALE 53 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_2_SCALE 54 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGES 55 // range 0 to 65534
// range 0 to 31, values: 0="0", 1="1", 2="2", 3="3", 4="4", 5="5", 6="6", 7="7", 8="8", 9="9", 10="10", 11="11", 12="12", 13="13", 14="14", 15="15", 16="16", 17="17", 18="18", 19="19", 20="20", 21="21", 22="22", 23="23", 24="24", 25="25", 26="26", 27="27", 28="28", 29="29", 30="30", 31="Infinite"
#define BMC_FAS_PARAM_PIT_REPEATS 56
#define BMC_FAS_PARAM_PIT_RUN_SW 57 // range 0 to 1
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_PIT_TEMPO 58
#define BMC_FAS_PARAM_PIT_STAGE_1_SHIFT 59 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_2_SHIFT 60 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_3_SHIFT 61 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_4_SHIFT 62 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_5_SHIFT 63 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_6_SHIFT 64 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_7_SHIFT 65 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_8_SHIFT 66 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_9_SHIFT 67 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_10_SHIFT 68 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_11_SHIFT 69 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_12_SHIFT 70 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_13_SHIFT 71 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_14_SHIFT 72 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_15_SHIFT 73 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_STAGE_16_SHIFT 74 // range 0 to 65534
// range 0 to 5, values: 0="CONSTANT", 1="INCREASING", 2="DECREASING", 3="UP / DOWN", 4="DOWN / UP", 5="SINE"
#define BMC_FAS_PARAM_PIT_AMPLITUBE_SHAPE 75
#define BMC_FAS_PARAM_PIT_AMPLITUBE_ALPHA 76 // range 0 to 65534
// range 0 to 5, values: 0="CONSTANT", 1="INCREASING", 2="DECREASING", 3="UP / DOWN", 4="DOWN / UP", 5="SINE"
#define BMC_FAS_PARAM_PIT_PAN_SHAPE 77
#define BMC_FAS_PARAM_PIT_PAN_ALPHA 78 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_1_DELAY_2 79 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_VOICE_2_DELAY_2 80 // range 0 to 65534
// range 0 to 1, values: 0="GLOBAL", 1="LOCAL"
#define BMC_FAS_PARAM_PIT_PITCH_SOURCE 81
// range 0 to 1, values: 0="MONO", 1="STEREO"
#define BMC_FAS_PARAM_PIT_INPUT_MODE 82
#define BMC_FAS_PARAM_PIT_LEARN_SW 83 // range 0 to 1
#define BMC_FAS_PARAM_PIT_LOW_CUT 84 // range 0 to 65534
#define BMC_FAS_PARAM_PIT_ECONOMY_SW 85 // range 0 to 1


// ***********************
// *** BLOCK Filter (FIL) ***
// ***********************
// range 0 to 11, values: 0="NULL", 1="LOWPASS", 2="BANDPASS", 3="HIGHPASS", 4="LOWSHELF", 5="HIGHSHLF", 6="PEAKING", 7="NOTCH", 8="TILT EQ", 9="LOWSHELF2", 10="HIGHSHLF2", 11="PEAKING2"
#define BMC_FAS_PARAM_FIL_EFFECT_TYPE 0
#define BMC_FAS_PARAM_FIL_FREQUENCY 1 // range 0 to 65534
#define BMC_FAS_PARAM_FIL_Q 2 // range 0 to 65534
#define BMC_FAS_PARAM_FIL_GAIN 3 // range 0 to 65534
#define BMC_FAS_PARAM_FIL_LEVEL 4 // range 0 to 65534
#define BMC_FAS_PARAM_FIL_BALANCE 5 // range 0 to 65534
// range 0 to 1, values: 0="THRU", 1="MUTE"
#define BMC_FAS_PARAM_FIL_BYPASS_MODE 6
// range 0 to 1, values: 0="2nd", 1="4th"
#define BMC_FAS_PARAM_FIL_ORDER 7
#define BMC_FAS_PARAM_FIL_PAN_LEFT 9 // range 0 to 65534
#define BMC_FAS_PARAM_FIL_PAN_RIGHT 10 // range 0 to 65534
// range 0 to 3, values: 0="NONE", 1="RIGHT", 2="LEFT", 3="BOTH"
#define BMC_FAS_PARAM_FIL_INVERT 11
#define BMC_FAS_PARAM_FIL_LOW_CUT 12 // range 0 to 65534
#define BMC_FAS_PARAM_FIL_HI_CUT 13 // range 0 to 65534


// ***********************
// *** BLOCK Drive (DRV) ***
// ***********************
// range 0 to 35, values: 0="RAT DIST", 1="PI FUZZ", 2="TUBE DRV 3-KNOB", 3="SUPER OD", 4="TREBLE BOOST", 5="MID BOOST", 6="T808 OD", 7="FAT RAT", 8="T808 MOD", 9="OCTAVE DIST", 10="PLUS DIST", 11="HARD FUZZ", 12="FET BOOST", 13="TAPE DIST", 14="FULL OD", 15="BLUES OD", 16="SHRED DIST", 17="M-ZONE DIST", 18="BENDER FUZZ", 19="BB PRE", 20="MASTER FUZZ", 21="FACE FUZZ", 22="BIT CRUSHER", 23="ETERNAL LOVE", 24="ESOTERIC ACB", 25="ESOTERIC RCB", 26="ZEN MASTER", 27="TUBE DRV 4-KNOB", 28="FAS LED-DRIVE", 29="SDD PREAMP", 30="FET PREAMP", 31="RUCKUS", 32="MICRO BOOST", 33="FAS BOOST", 34="TIMOTHY", 35="SHIMMER DRIVE"
#define BMC_FAS_PARAM_DRV_EFFECT_TYPE 0
#define BMC_FAS_PARAM_DRV_GAIN 1 // range 0 to 65534
#define BMC_FAS_PARAM_DRV_TONE 2 // range 0 to 65534
#define BMC_FAS_PARAM_DRV_VOLUME 3 // range 0 to 65534
#define BMC_FAS_PARAM_DRV_MIX 4 // range 0 to 65534
// range 0 to 1, values: 0="THRU", 1="MUTE"
#define BMC_FAS_PARAM_DRV_BYPASS_MODE 5
#define BMC_FAS_PARAM_DRV_SLEW_LIMIT 6 // range 0 to 65534
#define BMC_FAS_PARAM_DRV_LO_CUT 8 // range 0 to 65534
#define BMC_FAS_PARAM_DRV_HI_CUT 9 // range 0 to 65534
// range 0 to 12, values: 0="LV TUBE", 1="HARD", 2="SOFT", 3="GERMANIUM", 4="FW RECT", 5="HV TUBE", 6="SILICON", 7="4558/DIODE", 8="LED", 9="FET", 10="OP-AMP", 11="VARIABLE", 12="NULL"
#define BMC_FAS_PARAM_DRV_CLIP_TYPE 10
#define BMC_FAS_PARAM_DRV_BIAS 11 // range 0 to 65534
#define BMC_FAS_PARAM_DRV_BASS 12 // range 0 to 65534
#define BMC_FAS_PARAM_DRV_MIDDLE 13 // range 0 to 65534
#define BMC_FAS_PARAM_DRV_MID_FREQ 14 // range 0 to 65534
#define BMC_FAS_PARAM_DRV_TREBLE 15 // range 0 to 65534
#define BMC_FAS_PARAM_DRV_BIT_REDUCE 16 // range 0 to 65534
// range 0 to 2, values: 0="L+R", 1="LEFT", 2="RIGHT"
#define BMC_FAS_PARAM_DRV_INPUT 17
#define BMC_FAS_PARAM_DRV_BALANCE 18 // range 0 to 65534
#define BMC_FAS_PARAM_DRV_SAMPLE_RATE 19 // range 0 to 65534


// ***********************
// *** BLOCK Enhancer (ENH) ***
// ***********************
#define BMC_FAS_PARAM_ENH_WIDTH 0 // range 0 to 65534
#define BMC_FAS_PARAM_ENH_DEPTH 1 // range 0 to 65534
#define BMC_FAS_PARAM_ENH_LOW_CUT 2 // range 0 to 65534
#define BMC_FAS_PARAM_ENH_HIGH_CUT 3 // range 0 to 65534
#define BMC_FAS_PARAM_ENH_LEVEL 4 // range 0 to 65534
// range 0 to 1, values: 0="MODERN", 1="CLASSIC"
#define BMC_FAS_PARAM_ENH_EFFECT_TYPE 6
// range 0 to 3, values: 0="NONE", 1="RIGHT", 2="LEFT", 3="BOTH"
#define BMC_FAS_PARAM_ENH_INVERT 7
#define BMC_FAS_PARAM_ENH_PAN_LEFT 8 // range 0 to 65534
#define BMC_FAS_PARAM_ENH_PAN_RIGHT 9 // range 0 to 65534
#define BMC_FAS_PARAM_ENH_BALANCE 10 // range 0 to 65534


// ***********************
// *** BLOCK FX Loop (FXL) ***
// ***********************
#define BMC_FAS_PARAM_FXL_LEVEL_1 0 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_LEVEL_2 1 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_LEVEL_3 2 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_LEVEL_4 3 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_PAN_1 4 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_PAN_2 5 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_PAN_3 6 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_PAN_4 7 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_SCENE_1 8 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_SCENE_2 9 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_SCENE_3 10 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_SCENE_4 11 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_SCENE_5 12 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_SCENE_6 13 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_SCENE_7 14 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_SCENE_8 15 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_LEVEL 16 // range 0 to 65534
#define BMC_FAS_PARAM_FXL_BALANCE 17 // range 0 to 65534
// range 0 to 1, values: 0="THRU", 1="MUTE"
#define BMC_FAS_PARAM_FXL_BYPASS_MODE 18


// ***********************
// *** BLOCK Input Noise Gate (INPUT) ***
// ***********************
#define BMC_FAS_PARAM_INPUT_THRESHOLD 0 // range 0 to 65534
#define BMC_FAS_PARAM_INPUT_RATIO 1 // range 0 to 65534
#define BMC_FAS_PARAM_INPUT_RELEASE 2 // range 0 to 65534
#define BMC_FAS_PARAM_INPUT_ATTACK 3 // range 0 to 65534
#define BMC_FAS_PARAM_INPUT_LEVEL 4 // range 0 to 65534
// range 0 to 1, values: 0="CLASSIC", 1="INTELLIGENT"
#define BMC_FAS_PARAM_INPUT_EFFECT_TYPE 6


// ***********************
// *** BLOCK Output (OUTPUT) ***
// ***********************
#define BMC_FAS_PARAM_OUTPUT_LEVEL_1 0 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_LEVEL_2 1 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_LEVEL_3 2 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_LEVEL_4 3 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_BALANCE_1 4 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_BALANCE_2 5 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_BALANCE_3 6 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_BALANCE_4 7 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_SCENE_1_MAIN 8 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_SCENE_2_MAIN 9 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_SCENE_3_MAIN 10 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_SCENE_4_MAIN 11 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_SCENE_5_MAIN 12 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_SCENE_6_MAIN 13 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_SCENE_7_MAIN 14 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_SCENE_8_MAIN 15 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_LEVEL 16 // range 0 to 65534
#define BMC_FAS_PARAM_OUTPUT_PAN 17 // range 0 to 65534
// range 0 to 1, values: 0="THRU", 1="MUTE"
#define BMC_FAS_PARAM_OUTPUT_BYPASS_MODE 18


// ***********************
// *** BLOCK Controllers (CONTROLLERS) ***
// ***********************
// range 0 to 8, values: 0="SINE", 1="TRIANGLE", 2="SQUARE", 3="SAW UP", 4="SAW DOWN", 5="RANDOM", 6="LOG", 7="EXP", 8="TRAPEZOID"
#define BMC_FAS_PARAM_CONTROLLERS_LFO1_TYPE_RUN 0
#define BMC_FAS_PARAM_CONTROLLERS_LFO1_RATE 1 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_LFO1_DEPTH 2 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_LFO1_DUTY 3 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_LFO1_OUTPUT_B_PHASE 4 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_CONTROLLERS_LFO1_TEMPO 5
// range 0 to 8, values: 0="SINE", 1="TRIANGLE", 2="SQUARE", 3="SAW UP", 4="SAW DOWN", 5="RANDOM", 6="LOG", 7="EXP", 8="TRAPEZOID"
#define BMC_FAS_PARAM_CONTROLLERS_LFO2_TYPE_RUN 6
#define BMC_FAS_PARAM_CONTROLLERS_LFO2_RATE 7 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_LFO2_DEPTH 8 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_LFO2_DUTY 9 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_LFO2_OUTPUT_B_PHASE 10 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_CONTROLLERS_LFO2_TEMPO 11
// range 0 to 2, values: 0="ONCE", 1="LOOP", 2="SUST"
#define BMC_FAS_PARAM_CONTROLLERS_ADSR1_MODE 12
#define BMC_FAS_PARAM_CONTROLLERS_ADSR1_RETRIG_SW 13 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_ADSR1_ATTACK 14 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ADSR1_DECAY 15 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ADSR1_SUSTAIN 16 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ADSR1_LEVEL 17 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ADSR1_RELEASE 18 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ADSR1_THRESHOLD 19 // range 0 to 65534
// range 0 to 2, values: 0="ONCE", 1="LOOP", 2="SUST"
#define BMC_FAS_PARAM_CONTROLLERS_ADSR2_MODE 20
#define BMC_FAS_PARAM_CONTROLLERS_ADSR2_RETRIG_SW 21 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_ADSR2_ATTACK 22 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ADSR2_DECAY 23 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ADSR2_SUSTAIN 24 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ADSR2_LEVEL 25 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ADSR2_RELEASE 26 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ADSR2_THRESHOLD 27 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ENV_ATTACK 28 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ENV_RELEASE 29 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ENV_THRESHOLD 30 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_ENV_GAIN 31 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_TAP_TEMPO 32 // range 0 to 65534
// range 0 to 1, values: 0="PRESET", 1="GLOBAL"
#define BMC_FAS_PARAM_CONTROLLERS_TEMPO_SETTING 33
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_RATE 34 // range 0 to 65534
// range 0 to 78, values: 0="NONE", 1="1/64 TRIP", 2="1/64", 3="1/64 DOT", 4="1/32 TRIP", 5="1/32", 6="1/32 DOT", 7="1/16 TRIP", 8="1/16", 9="1/16 DOT", 10="1/8 TRIP", 11="1/8", 12="1/8 DOT", 13="1/4 TRIP", 14="1/4", 15="1/4 DOT", 16="1/2 TRIP", 17="1/2", 18="1/2 DOT", 19="1 TRIP", 20="1", 21="1 DOT", 22="2", 23="3", 24="4", 25="4/3", 26="5/4", 27="5/64", 28="7/64", 29="9/64", 30="10/64 (5/32)", 31="11/64", 32="13/64", 33="14/64 (7/32)", 34="15/64", 35="17/64", 36="18/64 (9/32)", 37="19/64", 38="20/64 (5/16)", 39="21/64", 40="22/64 (11/32)", 41="23/64", 42="25/64", 43="26/64 (13/32)", 44="27/64", 45="28/64 (7/16)", 46="29/64", 47="30/64 (15/32)", 48="31/64", 49="33/64", 50="34/64 (17/32)", 51="35/64", 52="36/64 (9/16)", 53="37/64", 54="38/64 (19/32)", 55="39/64", 56="40/64 (5/8)", 57="41/64", 58="42/64 (21/32)", 59="43/64", 60="44/64 (11/16)", 61="45/64", 62="46/64 (23/32)", 63="47/64", 64="49/64", 65="50/64 (25/32)", 66="51/64", 67="52/64 (13/16)", 68="53/64", 69="54/64 (27/32)", 70="55/64", 71="56/64 (7/8)", 72="57/64", 73="58/64 (29/32)", 74="59/64", 75="60/64 (15/16)", 76="61/64", 77="62/64 (31/32)", 78="63/64"
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_TEMPO 35
// range 0 to 32, values: 0="0", 1="1", 2="2", 3="3", 4="4", 5="5", 6="6", 7="7", 8="8", 9="9", 10="10", 11="11", 12="12", 13="13", 14="14", 15="15", 16="16", 17="17", 18="18", 19="19", 20="20", 21="21", 22="22", 23="23", 24="24", 25="25", 26="26", 27="27", 28="28", 29="29", 30="30", 31="31", 32="32"
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_STAGES 36
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_1 37 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_2 38 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_3 39 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_4 40 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_5 41 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_6 42 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_7 43 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_8 44 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_9 45 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_10 46 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_11 47 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_12 48 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_13 49 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_14 50 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_15 51 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_16 52 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_RUN_SW 54 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_17 55 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_18 56 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_19 57 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_20 58 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_21 59 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_22 60 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_23 61 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_24 62 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_25 63 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_26 64 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_27 65 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_28 66 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_29 67 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_30 68 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_31 69 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_SEQ_32 70 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR1_SCENE_1 74 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR1_SCENE_2 75 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR1_SCENE_3 76 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR1_SCENE_4 77 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR1_SCENE_5 78 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR1_SCENE_6 79 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR1_SCENE_7 80 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR1_SCENE_8 81 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR2_SCENE_1 82 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR2_SCENE_2 83 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR2_SCENE_3 84 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR2_SCENE_4 85 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR2_SCENE_5 86 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR2_SCENE_6 87 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR2_SCENE_7 88 // range 0 to 65534
#define BMC_FAS_PARAM_CONTROLLERS_CTR2_SCENE_8 89 // range 0 to 65534
// range 0 to 32, values: 0="", 1="OFF", 2="2", 3="3", 4="4", 5="5", 6="6", 7="7", 8="8", 9="9", 10="10", 11="11", 12="12", 13="13", 14="14", 15="15", 16="16", 17="17", 18="18", 19="19", 20="20", 21="21", 22="22", 23="23", 24="24", 25="25", 26="26", 27="27", 28="28", 29="29", 30="30", 31="31", 32="32"
#define BMC_FAS_PARAM_CONTROLLERS_LFO1_QUANTIZE 90
// range 0 to 32, values: 0="", 1="OFF", 2="2", 3="3", 4="4", 5="5", 6="6", 7="7", 8="8", 9="9", 10="10", 11="11", 12="12", 13="13", 14="14", 15="15", 16="16", 17="17", 18="18", 19="19", 20="20", 21="21", 22="22", 23="23", 24="24", 25="25", 26="26", 27="27", 28="28", 29="29", 30="30", 31="31", 32="32"
#define BMC_FAS_PARAM_CONTROLLERS_LFO2_QUANTIZE 91
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW1_SCENE_1_SW 92 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW1_SCENE_2_SW 93 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW1_SCENE_3_SW 94 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW1_SCENE_4_SW 95 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW1_SCENE_5_SW 96 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW1_SCENE_6_SW 97 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW1_SCENE_7_SW 98 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW1_SCENE_8_SW 99 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW2_SCENE_1_SW 100 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW2_SCENE_2_SW 101 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW2_SCENE_3_SW 102 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW2_SCENE_4_SW 103 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW2_SCENE_5_SW 104 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW2_SCENE_6_SW 105 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW2_SCENE_7_SW 106 // range 0 to 1
#define BMC_FAS_PARAM_CONTROLLERS_CTR_SW2_SCENE_8_SW 107 // range 0 to 1


// ***********************
// *** BLOCK Synth (SYN) ***
// ***********************
// range 0 to 7, values: 0="SINE", 1="TRIANGLE", 2="SQUARE", 3="SAWTOOTH", 4="RANDOM", 5="WHT NOISE", 6="PINK NOISE", 7="OFF"
#define BMC_FAS_PARAM_SYN_TYPE_1 0
#define BMC_FAS_PARAM_SYN_FREQUENCY_1 1 // range 0 to 65534
// range 0 to 3, values: 0="OFF", 1="ENV ONLY", 2="PITCH+ENV", 3="QUANTIZE"
#define BMC_FAS_PARAM_SYN_TRACK_1 2
#define BMC_FAS_PARAM_SYN_SHIFT_1 3 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_TUNE_1 4 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_DUTY_1 5 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_VOICE_LEVEL_1 6 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_VOICE_PAN_1 7 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_ATTACK_1 8 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_FILTER_1 9 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_Q_1 10 // range 0 to 65534
// range 0 to 7, values: 0="SINE", 1="TRIANGLE", 2="SQUARE", 3="SAWTOOTH", 4="RANDOM", 5="WHT NOISE", 6="PINK NOISE", 7="OFF"
#define BMC_FAS_PARAM_SYN_TYPE_2 11
#define BMC_FAS_PARAM_SYN_FREQUENCY_2 12 // range 0 to 65534
// range 0 to 3, values: 0="OFF", 1="ENV ONLY", 2="PITCH+ENV", 3="QUANTIZE"
#define BMC_FAS_PARAM_SYN_TRACK_2 13
#define BMC_FAS_PARAM_SYN_SHIFT_2 14 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_TUNE_2 15 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_DUTY_2 16 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_VOICE_LEVEL_2 17 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_VOICE_PAN_2 18 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_ATTACK_2 19 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_FILTER_2 20 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_Q_2 21 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_MIX 23 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_LEVEL 24 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_BALANCE 25 // range 0 to 65534
// range 0 to 2, values: 0="THRU", 1="MUTE FX OUT", 2="MUTE OUT"
#define BMC_FAS_PARAM_SYN_BYPASS_MODE 26
#define BMC_FAS_PARAM_SYN_GLOBAL_MIX_SW 27 // range 0 to 1
// range 0 to 7, values: 0="SINE", 1="TRIANGLE", 2="SQUARE", 3="SAWTOOTH", 4="RANDOM", 5="WHT NOISE", 6="PINK NOISE", 7="OFF"
#define BMC_FAS_PARAM_SYN_TYPE_3 29
#define BMC_FAS_PARAM_SYN_FREQUENCY_3 30 // range 0 to 65534
// range 0 to 3, values: 0="OFF", 1="ENV ONLY", 2="PITCH+ENV", 3="QUANTIZE"
#define BMC_FAS_PARAM_SYN_TRACK_3 31
#define BMC_FAS_PARAM_SYN_SHIFT_3 32 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_TUNE_3 33 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_DUTY_3 34 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_VOICE_LEVEL_3 35 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_VOICE_PAN_3 36 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_ATTACK_3 37 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_FILTER_3 38 // range 0 to 65534
#define BMC_FAS_PARAM_SYN_Q_3 39 // range 0 to 65534


// ***********************
// *** BLOCK Gate Expander (GTE) ***
// ***********************
#define BMC_FAS_PARAM_GTE_THRESHOLD 0 // range 0 to 65534
#define BMC_FAS_PARAM_GTE_ATTACK 1 // range 0 to 65534
#define BMC_FAS_PARAM_GTE_HOLD 2 // range 0 to 65534
#define BMC_FAS_PARAM_GTE_RELEASE 3 // range 0 to 65534
#define BMC_FAS_PARAM_GTE_RATIO 4 // range 0 to 65534
// range 0 to 6, values: 0="BLOCK L+R", 1="ROW 1", 2="ROW 2", 3="ROW 3", 4="ROW 4", 5="INPUT 1", 6="INPUT 2"
#define BMC_FAS_PARAM_GTE_SIDECHAIN_SELECT 5
#define BMC_FAS_PARAM_GTE_LOW_CUT 6 // range 0 to 65534
#define BMC_FAS_PARAM_GTE_HIGH_CUT 7 // range 0 to 65534
#define BMC_FAS_PARAM_GTE_LEVEL 9 // range 0 to 65534
#define BMC_FAS_PARAM_GTE_BALANCE 10 // range 0 to 65534
// range 0 to 1, values: 0="THRU", 1="MUTE"
#define BMC_FAS_PARAM_GTE_BYPASS_MODE 11


// ***********************
// *** BLOCK Ring Modulator (RNG) ***
// ***********************
#define BMC_FAS_PARAM_RNG_FREQUENCY 0 // range 0 to 65534
#define BMC_FAS_PARAM_RNG_F_MULTIPLIER 1 // range 0 to 65534
#define BMC_FAS_PARAM_RNG_TRACK_SW 2 // range 0 to 1
#define BMC_FAS_PARAM_RNG_HIGH_CUT 3 // range 0 to 65534
#define BMC_FAS_PARAM_RNG_MIX 4 // range 0 to 65534
#define BMC_FAS_PARAM_RNG_LEVEL 5 // range 0 to 65534
#define BMC_FAS_PARAM_RNG_BALANCE 6 // range 0 to 65534
// range 0 to 2, values: 0="THRU", 1="MUTE FX OUT", 2="MUTE OUT"
#define BMC_FAS_PARAM_RNG_BYPASS_MODE 7
#define BMC_FAS_PARAM_RNG_GLOBAL_MIX_SW 8 // range 0 to 1


// ***********************
// *** BLOCK Looper (LPR) ***
// ***********************
#define BMC_FAS_PARAM_LPR_MIX 0 // range 0 to 65534
#define BMC_FAS_PARAM_LPR_LEVEL 1 // range 0 to 65534
#define BMC_FAS_PARAM_LPR_BALANCE 2 // range 0 to 65534
// range 0 to 2, values: 0="THRU", 1="MUTE FX OUT", 2="MUTE OUT"
#define BMC_FAS_PARAM_LPR_BYPASS_MODE 3
#define BMC_FAS_PARAM_LPR_DUB_MIX 5 // range 0 to 65534
#define BMC_FAS_PARAM_LPR_THRESHOLD_SW 6 // range 0 to 1
#define BMC_FAS_PARAM_LPR_THRES_LEVEL 7 // range 0 to 65534
// range 0 to 3, values: 0="MONO", 1="STEREO", 2="MONO UNDO", 3="STEREO UNDO"
#define BMC_FAS_PARAM_LPR_MODE 8
// range 0 to 3, values: 0="OFF", 1="QUARTER", 2="EIGTH", 3="SIXTEENTH"
#define BMC_FAS_PARAM_LPR_QUANTIZE 9
#define BMC_FAS_PARAM_LPR_TRIM_STOP 10 // range 0 to 65534
#define BMC_FAS_PARAM_LPR_TRIM_START 11 // range 0 to 65534
#define BMC_FAS_PARAM_LPR_IMMEDIATE_PLAY_SW 12 // range 0 to 1
#define BMC_FAS_PARAM_LPR_RECORD_BEATS 13 // range 0 to 65534


#endif

#endif
