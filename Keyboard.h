/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for Keyboard.c.
 */

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

  /* Includes: */
    #include <avr/wdt.h>
    #include <avr/power.h>

    #include "Descriptors.h"
    #include "Display.h"
    #include "ScanKeys.h"

    #include <LUFA/Drivers/USB/USB.h>

    #define MAX_KEYS 6

    /* Type Defines: */
    /** Type define for HID report. This report contains the bits to match the usages defined
      *  in the HID report of the device.
      */
    typedef struct
    {
      uint8_t Modifier; /**< Keyboard modifier byte, indicating pressed modifier keys (a combination of
                         *   \c HID_KEYBOARD_MODIFER_* masks).
                         */
      uint8_t Reserved; /**< Reserved for OEM use, always set to 0. */
      uint8_t KeyboardKeyPad[MAX_KEYS]; // Keyboard/Keypad Page (0x07)
      uint8_t GenericDesktop[MAX_KEYS]; // Generic Desktop Page (0x01)
      uint16_t Consumer[MAX_KEYS]; // Consumer Page (0x0C)
    } ATTR_PACKED USB_ExtendedKeyboardReport_Data_t;

  /* Function Prototypes: */
    void SetupHardware(void);

    void EVENT_USB_Device_Connect(void);
    void EVENT_USB_Device_Disconnect(void);
    void EVENT_USB_Device_ConfigurationChanged(void);
    void EVENT_USB_Device_ControlRequest(void);
    void EVENT_USB_Device_StartOfFrame(void);

    bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                             uint8_t* const ReportID,
                                             const uint8_t ReportType,
                                             void* ReportData,
                                             uint16_t* const ReportSize);
    void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                              const uint8_t ReportID,
                                              const uint8_t ReportType,
                                              const void* ReportData,
                                              const uint16_t ReportSize);
    void Device_RemoteWakeup(void);

#endif
