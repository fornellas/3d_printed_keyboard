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
 *  Main source file for the Keyboard demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "Keyboard.h"
#include "KeyboardReport.h"
#include "Keymap.h"
#include "LayerState.h"
#include "Sequence.h"

/** Buffer to hold the previously generated Keyboard HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Keyboard_HID_Interface =
  {
    .Config =
      {
        .InterfaceNumber              = INTERFACE_ID_Keyboard,
        .ReportINEndpoint             =
          {
            .Address              = KEYBOARD_EPADDR,
            .Size                 = KEYBOARD_EPSIZE,
            .Banks                = 1,
          },
        .PrevReportINBuffer           = PrevKeyboardHIDReportBuffer,
        .PrevReportINBufferSize       = sizeof(PrevKeyboardHIDReportBuffer),
      },
  };


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
  SetupHardware();

  GlobalInterruptEnable();

  for (;;)
  {
    HID_Device_USBTask(&Keyboard_HID_Interface);
    USB_USBTask();
    Display_Update();
    Device_RemoteWakeup();
  }
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware()
{
#if (ARCH == ARCH_AVR8)
  /* Disable watchdog if enabled by bootloader/fuses */
  MCUSR &= ~(1 << WDRF);
  wdt_disable();

  /* Disable clock division */
  clock_prescale_set(clock_div_1);
#elif (ARCH == ARCH_XMEGA)
  /* Start the PLL to multiply the 2MHz RC oscillator to 32MHz and switch the CPU core to run from it */
  XMEGACLK_StartPLL(CLOCK_SRC_INT_RC2MHZ, 2000000, F_CPU);
  XMEGACLK_SetCPUClockSource(CLOCK_SRC_PLL);

  /* Start the 32MHz internal RC oscillator and start the DFLL to increase it to 48MHz using the USB SOF as a reference */
  XMEGACLK_StartInternalOscillator(CLOCK_SRC_INT_RC32MHZ);
  XMEGACLK_StartDFLL(CLOCK_SRC_INT_RC32MHZ, DFLL_REF_INT_USBSOF, F_USB);

  PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
#endif

  /* Hardware Initialization */
  SPI_Init(SPI_MODE_MASTER);
  Display_Init();
  ScanKeys_Init();
  Keymap_Init();
  LayerState_Init();
  Sequence_Init();
  USB_Init();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
  // TODO Display: USB Enumerating
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
  // TODO Display: USB Not Ready
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
  bool ConfigSuccess = true;

  ConfigSuccess &= HID_Device_ConfigureEndpoints(&Keyboard_HID_Interface);

  USB_Device_EnableSOFEvents();

  // TODO Display:
  // if(ConfigSuccess) {
  //   // TODO Display: USB Ready
  // } else {
  //   // TODO Display: USB Error
  // }
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
  HID_Device_ProcessControlRequest(&Keyboard_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
  HID_Device_MillisecondElapsed(&Keyboard_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
  USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;

  ScanKeys_Read(&KeyboardReport_ScanKeys_Callback, (void *)KeyboardReport);

  Sequence_Play(KeyboardReport);

  *ReportSize = sizeof(USB_KeyboardReport_Data_t);
  return false;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
  Display_Set_LEDReport(*(uint8_t*)ReportData);
}

void Device_RemoteWakeup_ScanKeys_Callback(struct Key key, void *data)
{
  uint8_t *send_remote_wakeup = (uint8_t *)data;

  if(key.state)
    *send_remote_wakeup = 1;
}

void Device_RemoteWakeup(void)
{
  uint8_t send_remote_wakeup = 0;

  if(DEVICE_STATE_Suspended==USB_DeviceState)
    if(USB_Device_RemoteWakeupEnabled) {
      ScanKeys_Read(&KeyboardReport_ScanKeys_Callback, (void *)&send_remote_wakeup);
      if(send_remote_wakeup)
        USB_Device_SendRemoteWakeup();
    }
}
