#ifndef MENU_H

#define MENU_H

#define NOMINMAX
#include <windows.h>
#include "NxBounds3.h"

HMENU createMyMenu(void);
bool  processMenu(HWND hwnd,unsigned int cmd,NxBounds3 &b);
void  saveMenuState(void);

#endif
