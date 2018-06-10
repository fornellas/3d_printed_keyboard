#ifndef _KEYMAP_H_
#define _KEYMAP_H_

#include "ScanKeys.h"

#define _VALUE_BITS 12
#define _VALUE_MASK 0x0FFF
#define _FN_MASK 0xF000

#define GET_KEY_FN(key) ((_FN_MASK & key) >> _VALUE_BITS)
#define GET_KEY_VALUE(key) (key & _VALUE_MASK)

// Keycodes for HID Keyboard/Keypad Page (0x07)
#define KEY_FN_KEYBOARD_PAGE 0
#define K(name)  ((HID_KEYBOARD_SC_ ## name) | (KEY_FN_KEYBOARD_PAGE << _VALUE_BITS))

// Keycodes for HID Generic Desktop Page (0x01)
#define KEY_FN_GENERIC_DESKTOP_PAGE 1
#define KGD(name)  ((HID_KEYBOARD_GENERIC_DESKTOP_SC_ ## name) | (KEY_FN_GENERIC_DESKTOP_PAGE << _VALUE_BITS))
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_POINTER_CP 0x01
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_MOUSE_CA 0x02
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_JOYSTICK_CA 0x04
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_GAME_PAD_CA 0x05
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_KEYBOARD_CA 0x06
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_KEYPAD_CA 0x07
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_MULTI_AXIS_CONTROLLER_CA 0x08
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_TABLET_PC_SYSTEM_CONTROLS_CA 0x09
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_X_DV 0x30
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_Y_DV 0x31
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_Z_DV 0x32
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_RX_DV 0x33
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_RY_DV 0x34
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_RZ_DV 0x35
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SLIDER_DV 0x36
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_DIAL_DV 0x37
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_WHEEL_DV 0x38
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_HAT_SWITCH_DV 0x39
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_COUNTED_BUFFER_CL 0x3A
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_BYTE_COUNT_DV 0x3B
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_MOTION_WAKEUP_OSC 0x3C
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_START_OOC 0x3D
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SELECT_OOC 0x3E
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_VX_DV 0x40
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_VY_DV 0x41
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_VZ_DV 0x42
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_VBRX_DV 0x43
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_VBRY_DV 0x44
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_VBRZ_DV 0x45
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_VNO_DV 0x46
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_FEATURE_NOTIFICATION_DV_DF 0x47
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_RESOLUTION_MULTIPLIER_DV 0x48
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_CONTROL_CA 0x80
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_POWER_DOWN_OSC 0x81
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_SLEEP_OSC 0x82
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_WAKE_UP_OSC 0x83
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_CONTEXT_MENU_OSC 0x84
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_MAIN_MENU_OSC 0x85
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_APP_MENU_OSC 0x86
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_MENU_HELP_OSC 0x87
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_MENU_EXIT_OSC 0x88
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_MENU_SELECT_OSC 0x89
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_MENU_RIGHT_RTC 0x8A
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_MENU_LEFT_RTC 0x8B
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_MENU_UP_RTC 0x8C
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_MENU_DOWN_RTC 0x8D
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_COLD_RESTART_OSC 0x8E
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_WARM_RESTART_OSC 0x8F
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_D_PAD_UP_OOC 0x90
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_D_PAD_DOWN_OOC 0x91
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_D_PAD_RIGHT_OOC 0x92
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_D_PAD_LEFT_OOC 0x93
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_DOCK_OSC 0xA0
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_UNDOCK_OSC 0xA1
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_SETUP_OSC 0xA2
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_BREAK_OSC 0xA3
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_DEBUGGER_BREAK_OSC 0xA4
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_APPLICATION_BREAK_OSC 0xA5
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_APPLICATION_DEBUGGER_BREAK_OSC 0xA6
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_SPEAKER_MUTE_OSC 0xA7
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_HIBERNATE_OSC 0xA8
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_DISPLAY_INVERT_OSC 0xB0
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_DISPLAY_INTERNAL_OSC 0xB1
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_DISPLAY_EXTERNAL_OSC 0xB2
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_DISPLAY_BOTH_OSC 0xB3
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_DISPLAY_DUAL_OSC 0xB4
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_DISPLAY_TOGGLE_INT_EXT_OSC 0xB5
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_DISPLAY_SWAP_PRIMARY_SECONDARY_OSC 0xB6
#define HID_KEYBOARD_GENERIC_DESKTOP_SC_SYSTEM_DISPLAY_LCD_AUTOSCALE_OSC 0xB7

// Keycodes for HID Consumer Page (0x01)
#define KEY_FN_CONSUMER_PAGE_PAGE 2
#define KC(name)  ((HID_KEYBOARD_CONSUMER_SC_ ## name) | (KEY_FN_CONSUMER_PAGE_PAGE << _VALUE_BITS))
#define HID_KEYBOARD_CONSUMER_SC_CONSUMER_CONTROL_CA 0x0001
#define HID_KEYBOARD_CONSUMER_SC_NUMERIC_KEY_PAD_NARY 0x0002
#define HID_KEYBOARD_CONSUMER_SC_PROGRAMMABLE_BUTTONS_NARY 0x0003
#define HID_KEYBOARD_CONSUMER_SC_MICROPHONE_CA 0x0004
#define HID_KEYBOARD_CONSUMER_SC_HEADPHONE_CA 0x0005
#define HID_KEYBOARD_CONSUMER_SC_GRAPHIC_EQUALIZER_CA 0x0006
#define HID_KEYBOARD_CONSUMER_SC_PLUS_10_OSC 0x0020
#define HID_KEYBOARD_CONSUMER_SC_PLUS_100_OSC 0x0021
#define HID_KEYBOARD_CONSUMER_SC_AM_PM_OSC 0x0022
#define HID_KEYBOARD_CONSUMER_SC_POWER_OOC 0x0030
#define HID_KEYBOARD_CONSUMER_SC_RESET_OSC 0x0031
#define HID_KEYBOARD_CONSUMER_SC_SLEEP_OSC 0x0032
#define HID_KEYBOARD_CONSUMER_SC_SLEEP_AFTER_OSC 0x0033
#define HID_KEYBOARD_CONSUMER_SC_SLEEP_MODE_RTC 0x0034
#define HID_KEYBOARD_CONSUMER_SC_ILLUMINATION_OOC 0x0035
#define HID_KEYBOARD_CONSUMER_SC_FUNCTION_BUTTONS_NARY 0x0036
#define HID_KEYBOARD_CONSUMER_SC_MENU_OOC 0x0040
#define HID_KEYBOARD_CONSUMER_SC_MENU_PICK_OSC 0x0041
#define HID_KEYBOARD_CONSUMER_SC_MENU_UP_OSC 0x0042
#define HID_KEYBOARD_CONSUMER_SC_MENU_DOWN_OSC 0x0043
#define HID_KEYBOARD_CONSUMER_SC_MENU_LEFT_OSC 0x0044
#define HID_KEYBOARD_CONSUMER_SC_MENU_RIGHT_OSC 0x0045
#define HID_KEYBOARD_CONSUMER_SC_MENU_ESCAPE_OSC 0x0046
#define HID_KEYBOARD_CONSUMER_SC_MENU_VALUE_INCREASE_OSC 0x0047
#define HID_KEYBOARD_CONSUMER_SC_MENU_VALUE_DECREASE_OSC 0x0048
#define HID_KEYBOARD_CONSUMER_SC_DATA_ON_SCREEN_OOC 0x0060
#define HID_KEYBOARD_CONSUMER_SC_CLOSED_CAPTION_OOC 0x0061
#define HID_KEYBOARD_CONSUMER_SC_CLOSED_CAPTION_SELECT_OSC 0x0062
#define HID_KEYBOARD_CONSUMER_SC_VCR_TV_OOC 0x0063
#define HID_KEYBOARD_CONSUMER_SC_BROADCAST_MODE_OSC 0x0064
#define HID_KEYBOARD_CONSUMER_SC_SNAPSHOT_OSC 0x0065
#define HID_KEYBOARD_CONSUMER_SC_STILL_OSC 0x0066
#define HID_KEYBOARD_CONSUMER_SC_SELECTION_NARY 0x0080
#define HID_KEYBOARD_CONSUMER_SC_ASSIGN_SELECTION_OSC 0x0081
#define HID_KEYBOARD_CONSUMER_SC_MODE_STEP_OSC 0x0082
#define HID_KEYBOARD_CONSUMER_SC_RECALL_LAST_OSC 0x0083
#define HID_KEYBOARD_CONSUMER_SC_ENTER_CHANNEL_OSC 0x0084
#define HID_KEYBOARD_CONSUMER_SC_ORDER_MOVIE_OSC 0x0085
#define HID_KEYBOARD_CONSUMER_SC_CHANNEL_LC 0x0086
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECTION_NARY 0x0087
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_COMPUTER_SEL 0x0088
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_TV_SEL 0x0089
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_WWW_SEL 0x008A
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_DVD_SEL 0x008B
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_TELEPHONE_SEL 0x008C
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_PROGRAM_GUIDE_SEL 0x008D
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_VIDEO_PHONE_SEL 0x008E
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_GAMES_SEL 0x008F
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_MESSAGES_SEL 0x0090
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_CD_SEL 0x0091
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_VCR_SEL 0x0092
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_TUNER_SEL 0x0093
#define HID_KEYBOARD_CONSUMER_SC_QUIT_OSC 0x0094
#define HID_KEYBOARD_CONSUMER_SC_HELP_OOC 0x0095
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_TAPE_SEL 0x0096
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_CABLE_SEL 0x0097
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_SATELLITE_SEL 0x0098
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_SECURITY_SEL 0x0099
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_HOME_SEL 0x009A
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_CALL_SEL 0x009B
#define HID_KEYBOARD_CONSUMER_SC_CHANNEL_INCREMENT_OSC 0x009C
#define HID_KEYBOARD_CONSUMER_SC_CHANNEL_DECREMENT_OSC 0x009D
#define HID_KEYBOARD_CONSUMER_SC_MEDIA_SELECT_SAP_SEL 0x009E
#define HID_KEYBOARD_CONSUMER_SC_VCR_PLUS_OSC 0x00A0
#define HID_KEYBOARD_CONSUMER_SC_ONCE_OSC 0x00A1
#define HID_KEYBOARD_CONSUMER_SC_DAILY_OSC 0x00A2
#define HID_KEYBOARD_CONSUMER_SC_WEEKLY_OSC 0x00A3
#define HID_KEYBOARD_CONSUMER_SC_MONTHLY_OSC 0x00A4
#define HID_KEYBOARD_CONSUMER_SC_PLAY_OOC 0x00B0
#define HID_KEYBOARD_CONSUMER_SC_PAUSE_OOC 0x00B1
#define HID_KEYBOARD_CONSUMER_SC_RECORD_OOC 0x00B2
#define HID_KEYBOARD_CONSUMER_SC_FAST_FORWARD_OOC 0x00B3
#define HID_KEYBOARD_CONSUMER_SC_REWIND_OOC 0x00B4
#define HID_KEYBOARD_CONSUMER_SC_SCAN_NEXT_TRACK_OSC 0x00B5
#define HID_KEYBOARD_CONSUMER_SC_SCAN_PREVIOUS_TRACK_OSC 0x00B6
#define HID_KEYBOARD_CONSUMER_SC_STOP_OSC 0x00B7
#define HID_KEYBOARD_CONSUMER_SC_EJECT_OSC 0x00B8
#define HID_KEYBOARD_CONSUMER_SC_RANDOM_PLAY_OOC 0x00B9
#define HID_KEYBOARD_CONSUMER_SC_SELECT_DISC_NARY 0x00BA
#define HID_KEYBOARD_CONSUMER_SC_ENTER_DISC_MC 0x00BB
#define HID_KEYBOARD_CONSUMER_SC_REPEAT_OSC 0x00BC
#define HID_KEYBOARD_CONSUMER_SC_TRACKING_LC 0x00BD
#define HID_KEYBOARD_CONSUMER_SC_TRACK_NORMAL_OSC 0x00BE
#define HID_KEYBOARD_CONSUMER_SC_SLOW_TRACKING_LC 0x00BF
#define HID_KEYBOARD_CONSUMER_SC_FRAME_FORWARD_RTC 0x00C0
#define HID_KEYBOARD_CONSUMER_SC_FRAME_BACK_RTC 0x00C1
#define HID_KEYBOARD_CONSUMER_SC_MARK_OSC 0x00C2
#define HID_KEYBOARD_CONSUMER_SC_CLEAR_MARK_OSC 0x00C3
#define HID_KEYBOARD_CONSUMER_SC_REPEAT_FROM_MARK_OOC 0x00C4
#define HID_KEYBOARD_CONSUMER_SC_RETURN_TO_MARK_OSC 0x00C5
#define HID_KEYBOARD_CONSUMER_SC_SEARCH_MARK_FORWARD_OSC 0x00C6
#define HID_KEYBOARD_CONSUMER_SC_SEARCH_MARK_BACKWARDS_OSC 0x00C7
#define HID_KEYBOARD_CONSUMER_SC_COUNTER_RESET_OSC 0x00C8
#define HID_KEYBOARD_CONSUMER_SC_SHOW_COUNTER_OSC 0x00C9
#define HID_KEYBOARD_CONSUMER_SC_TRACKING_INCREMENT_RTC 0x00CA
#define HID_KEYBOARD_CONSUMER_SC_TRACKING_DECREMENT_RTC 0x00CB
#define HID_KEYBOARD_CONSUMER_SC_STOP_EJECT_OSC 0x00CC
#define HID_KEYBOARD_CONSUMER_SC_PLAY_PAUSE_OSC 0x00CD
#define HID_KEYBOARD_CONSUMER_SC_PLAY_SKIP_OSC 0x00CE
#define HID_KEYBOARD_CONSUMER_SC_VOLUME_LC 0x00E0
#define HID_KEYBOARD_CONSUMER_SC_BALANCE_LC 0x00E1
#define HID_KEYBOARD_CONSUMER_SC_MUTE_OOC 0x00E2
#define HID_KEYBOARD_CONSUMER_SC_BASS_LC 0x00E3
#define HID_KEYBOARD_CONSUMER_SC_TREBLE_LC 0x00E4
#define HID_KEYBOARD_CONSUMER_SC_BASS_BOOST_OOC 0x00E5
#define HID_KEYBOARD_CONSUMER_SC_SURROUND_MODE_OSC 0x00E6
#define HID_KEYBOARD_CONSUMER_SC_LOUDNESS_OOC 0x00E7
#define HID_KEYBOARD_CONSUMER_SC_MPX_OOC 0x00E8
#define HID_KEYBOARD_CONSUMER_SC_VOLUME_INCREMENT_RTC 0x00E9
#define HID_KEYBOARD_CONSUMER_SC_VOLUME_DECREMENT_RTC 0x00EA
#define HID_KEYBOARD_CONSUMER_SC_SPEED_SELECT_OSC 0x00F0
#define HID_KEYBOARD_CONSUMER_SC_PLAYBACK_SPEED_NARY 0x00F1
#define HID_KEYBOARD_CONSUMER_SC_STANDARD_PLAY_SEL 0x00F2
#define HID_KEYBOARD_CONSUMER_SC_LONG_PLAY_SEL 0x00F3
#define HID_KEYBOARD_CONSUMER_SC_EXTENDED_PLAY_SEL 0x00F4
#define HID_KEYBOARD_CONSUMER_SC_SLOW_OSC 0x00F5
#define HID_KEYBOARD_CONSUMER_SC_FAN_ENABLE_OOC 0x0100
#define HID_KEYBOARD_CONSUMER_SC_FAN_SPEED_LC 0x0101
#define HID_KEYBOARD_CONSUMER_SC_LIGHT_ENABLE_OOC 0x0102
#define HID_KEYBOARD_CONSUMER_SC_LIGHT_ILLUMINATION_LEVEL_LC 0x0103
#define HID_KEYBOARD_CONSUMER_SC_CLIMATE_CONTROL_ENABLE_OOC 0x0104
#define HID_KEYBOARD_CONSUMER_SC_ROOM_TEMPERATURE_LC 0x0105
#define HID_KEYBOARD_CONSUMER_SC_SECURITY_ENABLE_OOC 0x0106
#define HID_KEYBOARD_CONSUMER_SC_FIRE_ALARM_OSC 0x0107
#define HID_KEYBOARD_CONSUMER_SC_POLICE_ALARM_OSC 0x0108
#define HID_KEYBOARD_CONSUMER_SC_PROXIMITY_LC 0x0109
#define HID_KEYBOARD_CONSUMER_SC_MOTION_OSC 0x010A
#define HID_KEYBOARD_CONSUMER_SC_DURESS_ALARM_OSC 0x010B
#define HID_KEYBOARD_CONSUMER_SC_HOLDUP_ALARM_OSC 0x010C
#define HID_KEYBOARD_CONSUMER_SC_MEDICAL_ALARM_OSC 0x010D
#define HID_KEYBOARD_CONSUMER_SC_BALANCE_RIGHT_RTC 0x0150
#define HID_KEYBOARD_CONSUMER_SC_BALANCE_LEFT_RTC 0x0151
#define HID_KEYBOARD_CONSUMER_SC_BASS_INCREMENT_RTC 0x0152
#define HID_KEYBOARD_CONSUMER_SC_BASS_DECREMENT_RTC 0x0153
#define HID_KEYBOARD_CONSUMER_SC_TREBLE_INCREMENT_RTC 0x0154
#define HID_KEYBOARD_CONSUMER_SC_TREBLE_DECREMENT_RTC 0x0155
#define HID_KEYBOARD_CONSUMER_SC_SPEAKER_SYSTEM_CL 0x0160
#define HID_KEYBOARD_CONSUMER_SC_CHANNEL_LEFT_CL 0x0161
#define HID_KEYBOARD_CONSUMER_SC_CHANNEL_RIGHT_CL 0x0162
#define HID_KEYBOARD_CONSUMER_SC_CHANNEL_CENTER_CL 0x0163
#define HID_KEYBOARD_CONSUMER_SC_CHANNEL_FRONT_CL 0x0164
#define HID_KEYBOARD_CONSUMER_SC_CHANNEL_CENTER_FRONT_CL 0x0165
#define HID_KEYBOARD_CONSUMER_SC_CHANNEL_SIDE_CL 0x0166
#define HID_KEYBOARD_CONSUMER_SC_CHANNEL_SURROUND_CL 0x0167
#define HID_KEYBOARD_CONSUMER_SC_CHANNEL_LOW_FREQUENCY_ENHANCEMENT_CL 0x0168
#define HID_KEYBOARD_CONSUMER_SC_CHANNEL_TOP_CL 0x0169
#define HID_KEYBOARD_CONSUMER_SC_CHANNEL_UNKNOWN_CL 0x016A
#define HID_KEYBOARD_CONSUMER_SC_SUB_CHANNEL_LC 0x0170
#define HID_KEYBOARD_CONSUMER_SC_SUB_CHANNEL_INCREMENT_OSC 0x0171
#define HID_KEYBOARD_CONSUMER_SC_SUB_CHANNEL_DECREMENT_OSC 0x0172
#define HID_KEYBOARD_CONSUMER_SC_ALTERNATE_AUDIO_INCREMENT_OSC 0x0173
#define HID_KEYBOARD_CONSUMER_SC_ALTERNATE_AUDIO_DECREMENT_OSC 0x0174
#define HID_KEYBOARD_CONSUMER_SC_APPLICATION_LAUNCH_BUTTONS_NARY 0x0180
#define HID_KEYBOARD_CONSUMER_SC_AL_LAUNCH_BUTTON_CONFIGURATION_TOOL_SEL 0x0181
#define HID_KEYBOARD_CONSUMER_SC_AL_PROGRAMMABLE_BUTTON_CONFIGURATION_SEL 0x0182
#define HID_KEYBOARD_CONSUMER_SC_AL_CONSUMER_CONTROL_CONFIGURATION_SEL 0x0183
#define HID_KEYBOARD_CONSUMER_SC_AL_WORD_PROCESSOR_SEL 0x0184
#define HID_KEYBOARD_CONSUMER_SC_AL_TEXT_EDITOR_SEL 0x0185
#define HID_KEYBOARD_CONSUMER_SC_AL_SPREADSHEET_SEL 0x0186
#define HID_KEYBOARD_CONSUMER_SC_AL_GRAPHICS_EDITOR_SEL 0x0187
#define HID_KEYBOARD_CONSUMER_SC_AL_PRESENTATION_APP_SEL 0x0188
#define HID_KEYBOARD_CONSUMER_SC_AL_DATABASE_APP_SEL 0x0189
#define HID_KEYBOARD_CONSUMER_SC_AL_EMAIL_READER_SEL 0x018A
#define HID_KEYBOARD_CONSUMER_SC_AL_NEWSREADER_SEL 0x018B
#define HID_KEYBOARD_CONSUMER_SC_AL_VOICEMAIL_SEL 0x018C
#define HID_KEYBOARD_CONSUMER_SC_AL_CONTACTS_ADDRESS_BOOK_SEL 0x018D
#define HID_KEYBOARD_CONSUMER_SC_AL_CALENDAR_SCHEDULE_SEL 0x018E
#define HID_KEYBOARD_CONSUMER_SC_AL_TASK_PROJECT_MANAGER_SEL 0x018F
#define HID_KEYBOARD_CONSUMER_SC_AL_LOG_JOURNAL_TIMECARD_SEL 0x0190
#define HID_KEYBOARD_CONSUMER_SC_AL_CHECKBOOK_FINANCE_SEL 0x0191
#define HID_KEYBOARD_CONSUMER_SC_AL_CALCULATOR_SEL 0x0192
#define HID_KEYBOARD_CONSUMER_SC_AL_A_V_CAPTURE_PLAYBACK_SEL 0x0193
#define HID_KEYBOARD_CONSUMER_SC_AL_LOCAL_MACHINE_BROWSER_SEL 0x0194
#define HID_KEYBOARD_CONSUMER_SC_AL_LAN_WAN_BROWSER_SEL 0x0195
#define HID_KEYBOARD_CONSUMER_SC_AL_INTERNET_BROWSER_SEL 0x0196
#define HID_KEYBOARD_CONSUMER_SC_AL_REMOTE_NETWORKING_ISP_CONNECT_SEL 0x0197
#define HID_KEYBOARD_CONSUMER_SC_AL_NETWORK_CONFERENCE_SEL 0x0198
#define HID_KEYBOARD_CONSUMER_SC_AL_NETWORK_CHAT_SEL 0x0199
#define HID_KEYBOARD_CONSUMER_SC_AL_TELEPHONY_DIALER_SEL 0x019A
#define HID_KEYBOARD_CONSUMER_SC_AL_LOGON_SEL 0x019B
#define HID_KEYBOARD_CONSUMER_SC_AL_LOGOFF_SEL 0x019C
#define HID_KEYBOARD_CONSUMER_SC_AL_LOGON_LOGOFF_SEL 0x019D
#define HID_KEYBOARD_CONSUMER_SC_AL_TERMINAL_LOCK_SCREENSAVER_SEL 0x019E
#define HID_KEYBOARD_CONSUMER_SC_AL_CONTROL_PANEL_SEL 0x019F
#define HID_KEYBOARD_CONSUMER_SC_AL_COMMAND_LINE_PROCESSOR_RUN_SEL 0x01A0
#define HID_KEYBOARD_CONSUMER_SC_AL_PROCESS_TASK_MANAGER_SEL 0x01A1
#define HID_KEYBOARD_CONSUMER_SC_AL_SELECT_TASK_APPLICATION_SEL 0x01A2
#define HID_KEYBOARD_CONSUMER_SC_AL_NEXT_TASK_APPLICATION_SEL 0x01A3
#define HID_KEYBOARD_CONSUMER_SC_AL_PREVIOUS_TASK_APPLICATION_SEL 0x01A4
#define HID_KEYBOARD_CONSUMER_SC_AL_PREEMPTIVE_HALT_TASK_APPLICATION_SEL 0x01A5
#define HID_KEYBOARD_CONSUMER_SC_AL_INTEGRATED_HELP_CENTER_SEL 0x01A6
#define HID_KEYBOARD_CONSUMER_SC_AL_DOCUMENTS_SEL 0x01A7
#define HID_KEYBOARD_CONSUMER_SC_AL_THESAURUS_SEL 0x01A8
#define HID_KEYBOARD_CONSUMER_SC_AL_DICTIONARY_SEL 0x01A9
#define HID_KEYBOARD_CONSUMER_SC_AL_DESKTOP_SEL 0x01AA
#define HID_KEYBOARD_CONSUMER_SC_AL_SPELL_CHECK_SEL 0x01AB
#define HID_KEYBOARD_CONSUMER_SC_AL_GRAMMAR_CHECK_SEL 0x01AC
#define HID_KEYBOARD_CONSUMER_SC_AL_WIRELESS_STATUS_SEL 0x01AD
#define HID_KEYBOARD_CONSUMER_SC_AL_KEYBOARD_LAYOUT_SEL 0x01AE
#define HID_KEYBOARD_CONSUMER_SC_AL_VIRUS_PROTECTION_SEL 0x01AF
#define HID_KEYBOARD_CONSUMER_SC_AL_ENCRYPTION_SEL 0x01B0
#define HID_KEYBOARD_CONSUMER_SC_AL_SCREEN_SAVER_SEL 0x01B1
#define HID_KEYBOARD_CONSUMER_SC_AL_ALARMS_SEL 0x01B2
#define HID_KEYBOARD_CONSUMER_SC_AL_CLOCK_SEL 0x01B3
#define HID_KEYBOARD_CONSUMER_SC_AL_FILE_BROWSER_SEL 0x01B4
#define HID_KEYBOARD_CONSUMER_SC_AL_POWER_STATUS_SEL 0x01B5
#define HID_KEYBOARD_CONSUMER_SC_AL_IMAGE_BROWSER_SEL 0x01B6
#define HID_KEYBOARD_CONSUMER_SC_AL_AUDIO_BROWSER_SEL 0x01B7
#define HID_KEYBOARD_CONSUMER_SC_AL_MOVIE_BROWSER_SEL 0x01B8
#define HID_KEYBOARD_CONSUMER_SC_AL_DIGITAL_RIGHTS_MANAGER_SEL 0x01B9
#define HID_KEYBOARD_CONSUMER_SC_AL_DIGITAL_WALLET_SEL 0x01BA
#define HID_KEYBOARD_CONSUMER_SC_AL_INSTANT_MESSAGING_SEL 0x01BC
#define HID_KEYBOARD_CONSUMER_SC_AL_OEM_FEATURES_TIPS_TUTORIAL_BROWSER_SEL 0x01BD
#define HID_KEYBOARD_CONSUMER_SC_AL_OEM_HELP_SEL 0x01BE
#define HID_KEYBOARD_CONSUMER_SC_AL_ONLINE_COMMUNITY_SEL 0x01BF
#define HID_KEYBOARD_CONSUMER_SC_AL_ENTERTAINMENT_CONTENT_BROWSER_SEL 0x01C0
#define HID_KEYBOARD_CONSUMER_SC_AL_ONLINE_SHOPPING_BROWSER_SEL 0x01C1
#define HID_KEYBOARD_CONSUMER_SC_AL_SMARTCARD_INFORMATION_HELP_SEL 0x01C2
#define HID_KEYBOARD_CONSUMER_SC_AL_MARKET_MONITOR_FINANCE_BROWSER_SEL 0x01C3
#define HID_KEYBOARD_CONSUMER_SC_AL_CUSTOMIZED_CORPORATE_NEWS_BROWSER_SEL 0x01C4
#define HID_KEYBOARD_CONSUMER_SC_AL_ONLINE_ACTIVITY_BROWSER_SEL 0x01C5
#define HID_KEYBOARD_CONSUMER_SC_AL_RESEARCH_SEARCH_BROWSER_SEL 0x01C6
#define HID_KEYBOARD_CONSUMER_SC_AL_AUDIO_PLAYER_SEL 0x01C7
#define HID_KEYBOARD_CONSUMER_SC_GENERIC_GUI_APPLICATION_CONTROLS_NARY 0x0200
#define HID_KEYBOARD_CONSUMER_SC_AC_NEW_SEL 0x0201
#define HID_KEYBOARD_CONSUMER_SC_AC_OPEN_SEL 0x0202
#define HID_KEYBOARD_CONSUMER_SC_AC_CLOSE_SEL 0x0203
#define HID_KEYBOARD_CONSUMER_SC_AC_EXIT_SEL 0x0204
#define HID_KEYBOARD_CONSUMER_SC_AC_MAXIMIZE_SEL 0x0205
#define HID_KEYBOARD_CONSUMER_SC_AC_MINIMIZE_SEL 0x0206
#define HID_KEYBOARD_CONSUMER_SC_AC_SAVE_SEL 0x0207
#define HID_KEYBOARD_CONSUMER_SC_AC_PRINT_SEL 0x0208
#define HID_KEYBOARD_CONSUMER_SC_AC_PROPERTIES_SEL 0x0209
#define HID_KEYBOARD_CONSUMER_SC_AC_UNDO_SEL 0x021A
#define HID_KEYBOARD_CONSUMER_SC_AC_COPY_SEL 0x021B
#define HID_KEYBOARD_CONSUMER_SC_AC_CUT_SEL 0x021C
#define HID_KEYBOARD_CONSUMER_SC_AC_PASTE_SEL 0x021D
#define HID_KEYBOARD_CONSUMER_SC_AC_SELECT_ALL_SEL 0x021E
#define HID_KEYBOARD_CONSUMER_SC_AC_FIND_SEL 0x021F
#define HID_KEYBOARD_CONSUMER_SC_AC_FIND_AND_REPLACE_SEL 0x0220
#define HID_KEYBOARD_CONSUMER_SC_AC_SEARCH_SEL 0x0221
#define HID_KEYBOARD_CONSUMER_SC_AC_GO_TO_SEL 0x0222
#define HID_KEYBOARD_CONSUMER_SC_AC_HOME_SEL 0x0223
#define HID_KEYBOARD_CONSUMER_SC_AC_BACK_SEL 0x0224
#define HID_KEYBOARD_CONSUMER_SC_AC_FORWARD_SEL 0x0225
#define HID_KEYBOARD_CONSUMER_SC_AC_STOP_SEL 0x0226
#define HID_KEYBOARD_CONSUMER_SC_AC_REFRESH_SEL 0x0227
#define HID_KEYBOARD_CONSUMER_SC_AC_PREVIOUS_LINK_SEL 0x0228
#define HID_KEYBOARD_CONSUMER_SC_AC_NEXT_LINK_SEL 0x0229
#define HID_KEYBOARD_CONSUMER_SC_AC_BOOKMARKS_SEL 0x022A
#define HID_KEYBOARD_CONSUMER_SC_AC_HISTORY_SEL 0x022B
#define HID_KEYBOARD_CONSUMER_SC_AC_SUBSCRIPTIONS_SEL 0x022C
#define HID_KEYBOARD_CONSUMER_SC_AC_ZOOM_IN_SEL 0x022D
#define HID_KEYBOARD_CONSUMER_SC_AC_ZOOM_OUT_SEL 0x022E
#define HID_KEYBOARD_CONSUMER_SC_AC_ZOOM_LC 0x022F
#define HID_KEYBOARD_CONSUMER_SC_AC_FULL_SCREEN_VIEW_SEL 0x0230
#define HID_KEYBOARD_CONSUMER_SC_AC_NORMAL_VIEW_SEL 0x0231
#define HID_KEYBOARD_CONSUMER_SC_AC_VIEW_TOGGLE_SEL 0x0232
#define HID_KEYBOARD_CONSUMER_SC_AC_SCROLL_UP_SEL 0x0233
#define HID_KEYBOARD_CONSUMER_SC_AC_SCROLL_DOWN_SEL 0x0234
#define HID_KEYBOARD_CONSUMER_SC_AC_SCROLL_LC 0x0235
#define HID_KEYBOARD_CONSUMER_SC_AC_PAN_LEFT_SEL 0x0236
#define HID_KEYBOARD_CONSUMER_SC_AC_PAN_RIGHT_SEL 0x0237
#define HID_KEYBOARD_CONSUMER_SC_AC_PAN_LC 0x0238
#define HID_KEYBOARD_CONSUMER_SC_AC_NEW_WINDOW_SEL 0x0239
#define HID_KEYBOARD_CONSUMER_SC_AC_TILE_HORIZONTALLY_SEL 0x023A
#define HID_KEYBOARD_CONSUMER_SC_AC_TILE_VERTICALLY_SEL 0x023B
#define HID_KEYBOARD_CONSUMER_SC_AC_FORMAT_SEL 0x023C
#define HID_KEYBOARD_CONSUMER_SC_AC_EDIT_SEL 0x023D
#define HID_KEYBOARD_CONSUMER_SC_AC_BOLD_SEL 0x023E
#define HID_KEYBOARD_CONSUMER_SC_AC_ITALICS_SEL 0x023F
#define HID_KEYBOARD_CONSUMER_SC_AC_UNDERLINE_SEL 0x0240
#define HID_KEYBOARD_CONSUMER_SC_AC_STRIKETHROUGH_SEL 0x0241
#define HID_KEYBOARD_CONSUMER_SC_AC_SUBSCRIPT_SEL 0x0242
#define HID_KEYBOARD_CONSUMER_SC_AC_SUPERSCRIPT_SEL 0x0243
#define HID_KEYBOARD_CONSUMER_SC_AC_ALL_CAPS_SEL 0x0244
#define HID_KEYBOARD_CONSUMER_SC_AC_ROTATE_SEL 0x0245
#define HID_KEYBOARD_CONSUMER_SC_AC_RESIZE_SEL 0x0246
#define HID_KEYBOARD_CONSUMER_SC_AC_FLIP_HORIZONTAL_SEL 0x0247
#define HID_KEYBOARD_CONSUMER_SC_AC_FLIP_VERTICAL_SEL 0x0248
#define HID_KEYBOARD_CONSUMER_SC_AC_MIRROR_HORIZONTAL_SEL 0x0249
#define HID_KEYBOARD_CONSUMER_SC_AC_MIRROR_VERTICAL_SEL 0x024A
#define HID_KEYBOARD_CONSUMER_SC_AC_FONT_SELECT_SEL 0x024B
#define HID_KEYBOARD_CONSUMER_SC_AC_FONT_COLOR_SEL 0x024C
#define HID_KEYBOARD_CONSUMER_SC_AC_FONT_SIZE_SEL 0x024D
#define HID_KEYBOARD_CONSUMER_SC_AC_JUSTIFY_LEFT_SEL 0x024E
#define HID_KEYBOARD_CONSUMER_SC_AC_JUSTIFY_CENTER_H SEL 0x024F
#define HID_KEYBOARD_CONSUMER_SC_AC_JUSTIFY_RIGHT_SEL 0x0250
#define HID_KEYBOARD_CONSUMER_SC_AC_JUSTIFY_BLOCK_H SEL 0x0251
#define HID_KEYBOARD_CONSUMER_SC_AC_JUSTIFY_TOP_SEL 0x0252
#define HID_KEYBOARD_CONSUMER_SC_AC_JUSTIFY_CENTER_V SEL 0x0253
#define HID_KEYBOARD_CONSUMER_SC_AC_JUSTIFY_BOTTOM_SEL 0x0254
#define HID_KEYBOARD_CONSUMER_SC_AC_JUSTIFY_BLOCK_V SEL 0x0255
#define HID_KEYBOARD_CONSUMER_SC_AC_INDENT_DECREASE_SEL 0x0256
#define HID_KEYBOARD_CONSUMER_SC_AC_INDENT_INCREASE_SEL 0x0257
#define HID_KEYBOARD_CONSUMER_SC_AC_NUMBERED_LIST_SEL 0x0258
#define HID_KEYBOARD_CONSUMER_SC_AC_RESTART_NUMBERING_SEL 0x0259
#define HID_KEYBOARD_CONSUMER_SC_AC_BULLETED_LIST_SEL 0x025A
#define HID_KEYBOARD_CONSUMER_SC_AC_PROMOTE_SEL 0x025B
#define HID_KEYBOARD_CONSUMER_SC_AC_DEMOTE_SEL 0x025C
#define HID_KEYBOARD_CONSUMER_SC_AC_YES_SEL 0x025D
#define HID_KEYBOARD_CONSUMER_SC_AC_NO_SEL 0x025E
#define HID_KEYBOARD_CONSUMER_SC_AC_CANCEL_SEL 0x025F
#define HID_KEYBOARD_CONSUMER_SC_AC_CATALOG_SEL 0x0260
#define HID_KEYBOARD_CONSUMER_SC_AC_BUY_CHECKOUT_SEL 0x0261
#define HID_KEYBOARD_CONSUMER_SC_AC_ADD_TO_CART_SEL 0x0262
#define HID_KEYBOARD_CONSUMER_SC_AC_EXPAND_SEL 0x0263
#define HID_KEYBOARD_CONSUMER_SC_AC_EXPAND_ALL_SEL 0x0264
#define HID_KEYBOARD_CONSUMER_SC_AC_COLLAPSE_SEL 0x0265
#define HID_KEYBOARD_CONSUMER_SC_AC_COLLAPSE_ALL_SEL 0x0266
#define HID_KEYBOARD_CONSUMER_SC_AC_PRINT_PREVIEW_SEL 0x0267
#define HID_KEYBOARD_CONSUMER_SC_AC_PASTE_SPECIAL_SEL 0x0268
#define HID_KEYBOARD_CONSUMER_SC_AC_INSERT_MODE_SEL 0x0269
#define HID_KEYBOARD_CONSUMER_SC_AC_DELETE_SEL 0x026A
#define HID_KEYBOARD_CONSUMER_SC_AC_LOCK_SEL 0x026B
#define HID_KEYBOARD_CONSUMER_SC_AC_UNLOCK_SEL 0x026C
#define HID_KEYBOARD_CONSUMER_SC_AC_PROTECT_SEL 0x026D
#define HID_KEYBOARD_CONSUMER_SC_AC_UNPROTECT_SEL 0x026E
#define HID_KEYBOARD_CONSUMER_SC_AC_ATTACH_COMMENT_SEL 0x026F
#define HID_KEYBOARD_CONSUMER_SC_AC_DELETE_COMMENT_SEL 0x0270
#define HID_KEYBOARD_CONSUMER_SC_AC_VIEW_COMMENT_SEL 0x0271
#define HID_KEYBOARD_CONSUMER_SC_AC_SELECT_WORD_SEL 0x0272
#define HID_KEYBOARD_CONSUMER_SC_AC_SELECT_SENTENCE_SEL 0x0273
#define HID_KEYBOARD_CONSUMER_SC_AC_SELECT_PARAGRAPH_SEL 0x0274
#define HID_KEYBOARD_CONSUMER_SC_AC_SELECT_COLUMN_SEL 0x0275
#define HID_KEYBOARD_CONSUMER_SC_AC_SELECT_ROW_SEL 0x0276
#define HID_KEYBOARD_CONSUMER_SC_AC_SELECT_TABLE_SEL 0x0277
#define HID_KEYBOARD_CONSUMER_SC_AC_SELECT_OBJECT_SEL 0x0278
#define HID_KEYBOARD_CONSUMER_SC_AC_REDO_REPEAT_SEL 0x0279
#define HID_KEYBOARD_CONSUMER_SC_AC_SORT_SEL 0x027A
#define HID_KEYBOARD_CONSUMER_SC_AC_SORT_ASCENDING_SEL 0x027B
#define HID_KEYBOARD_CONSUMER_SC_AC_SORT_DESCENDING_SEL 0x027C
#define HID_KEYBOARD_CONSUMER_SC_AC_FILTER_SEL 0x027D
#define HID_KEYBOARD_CONSUMER_SC_AC_SET_CLOCK_SEL 0x027E
#define HID_KEYBOARD_CONSUMER_SC_AC_VIEW_CLOCK_SEL 0x027F
#define HID_KEYBOARD_CONSUMER_SC_AC_SELECT_TIME_ZONE_SEL 0x0280
#define HID_KEYBOARD_CONSUMER_SC_AC_EDIT_TIME_ZONES_SEL 0x0281
#define HID_KEYBOARD_CONSUMER_SC_AC_SET_ALARM_SEL 0x0282
#define HID_KEYBOARD_CONSUMER_SC_AC_CLEAR_ALARM_SEL 0x0283
#define HID_KEYBOARD_CONSUMER_SC_AC_SNOOZE_ALARM_SEL 0x0284
#define HID_KEYBOARD_CONSUMER_SC_AC_RESET_ALARM_SEL 0x0285
#define HID_KEYBOARD_CONSUMER_SC_AC_SYNCHRONIZE_SEL 0x0286
#define HID_KEYBOARD_CONSUMER_SC_AC_SEND_RECEIVE_SEL 0x0287
#define HID_KEYBOARD_CONSUMER_SC_AC_SEND_TO_SEL 0x0288
#define HID_KEYBOARD_CONSUMER_SC_AC_REPLY_SEL 0x0289
#define HID_KEYBOARD_CONSUMER_SC_AC_REPLY_ALL_SEL 0x028A
#define HID_KEYBOARD_CONSUMER_SC_AC_FORWARD_MSG_SEL 0x028B
#define HID_KEYBOARD_CONSUMER_SC_AC_SEND_SEL 0x028C
#define HID_KEYBOARD_CONSUMER_SC_AC_ATTACH_FILE_SEL 0x028D
#define HID_KEYBOARD_CONSUMER_SC_AC_UPLOAD_SEL 0x028E
#define HID_KEYBOARD_CONSUMER_SC_AC_DOWNLOAD_SAVE_TARGET_AS_SEL 0x028F
#define HID_KEYBOARD_CONSUMER_SC_AC_SET_BORDERS_SEL 0x0290
#define HID_KEYBOARD_CONSUMER_SC_AC_INSERT_ROW_SEL 0x0291
#define HID_KEYBOARD_CONSUMER_SC_AC_INSERT_COLUMN_SEL 0x0292
#define HID_KEYBOARD_CONSUMER_SC_AC_INSERT_FILE_SEL 0x0293
#define HID_KEYBOARD_CONSUMER_SC_AC_INSERT_PICTURE_SEL 0x0294
#define HID_KEYBOARD_CONSUMER_SC_AC_INSERT_OBJECT_SEL 0x0295
#define HID_KEYBOARD_CONSUMER_SC_AC_INSERT_SYMBOL_SEL 0x0296
#define HID_KEYBOARD_CONSUMER_SC_AC_SAVE_AND_CLOSE_SEL 0x0297
#define HID_KEYBOARD_CONSUMER_SC_AC_RENAME_SEL 0x0298
#define HID_KEYBOARD_CONSUMER_SC_AC_MERGE_SEL 0x0299
#define HID_KEYBOARD_CONSUMER_SC_AC_SPLIT_SEL 0x029A
#define HID_KEYBOARD_CONSUMER_SC_AC_DISRIBUTE_HORIZONTALLY_SEL 0x029B

// Ignore key
#define KEY_FN_NONE 3
#define NONE (KEY_FN_NONE << _VALUE_BITS)
#define TODO(_) NONE
// Pass through to the next layer
#define KEY_FN_PASS 4
#define ____ (KEY_FN_PASS << _VALUE_BITS)
// Execute macro
#define KEY_FN_MACRO 5
#define MACRO(name) (name | (KEY_FN_MACRO << _VALUE_BITS))
// Change to
#define KEY_FN_LAYOUT 6
#define LAYOUT(name) (name | (KEY_FN_LAYOUT << _VALUE_BITS))
// Play key sequence
#define KEY_FN_SEQ 7
#define SEQ(name) (name | (KEY_FN_SEQ<<_VALUE_BITS))

enum keymap_macros {
  MACRO_FN,
  MACRO_KEYPAD,
  MACRO_COMMON_SHIFTED,
  MACRO_TOGGLE_SHIFTED_NUMBER_LAYER,
  MACRO_CUT,
  MACRO_COPY,
  MACRO_PASTE,
  MACRO_DESKTOP,
  MACRO_COUNT,
};

extern void (* const keymap_macros[MACRO_COUNT])(struct Key);

enum keymap_seq {
  SEQ_SHUFFLE,
  SEQ_00,
  SEQ_B_TAB,
  SEQ_COUNT,
};

extern const uint16_t *keymap_seqs[SEQ_COUNT];

enum layer_start_status {
  KEYMAP_START_ENABLED,
  KEYMAP_START_DISABLED,
  KEYMAP_START_LOAD,
};

enum keymap_layers {
  FN_LAYER,
  KEYPAD_LAYER,
  QWERTY_QWERTY_LAYER,
  QWERTY_DVORAK_LAYER,
  DVORAK_DVORAK_LAYER,
  DVORAK_QWERTY_LAYER,
  SHIFTED_NUMBER_LAYER,
  COMMON_LAYER,
  LAYER_COUNT,
};

extern const uint8_t keymap_layout_layers[];

#define LAYOUT_LAYERS_COUNT 4

extern const uint8_t layer_initial_state[LAYER_COUNT];

extern const uint16_t keymaps[LAYER_COUNT][SCAN_MATRIX_ROWS][SCAN_MATRIX_COLUMNS];

void Keymap_Init(void);

char * Keymap_Get_Layer_Keyboard_Name(uint8_t);
char * Keymap_Get_Layer_Computer_Name(uint8_t);

#endif
