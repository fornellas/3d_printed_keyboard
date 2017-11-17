#ifndef _GENERATE_KEYBOARD_REPORT_H_
#define _GENERATE_KEYBOARD_REPORT_H_

#include "ScanKeys.h"

void GenerateKeyboardReport_Init(void);
void GenerateKeyboardReport(struct Key key, void *data);

#endif
