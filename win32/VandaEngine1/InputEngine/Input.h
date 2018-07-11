 /*Author   :   Dave Astle
 Date     :   11/22/2000

 Written for OpenGL Game Programming

************HOW TO USE INPUT SYSTEM**************


Files:
..\InputEngine\Input.h
..\InputEngine\InpuSystem.cpp

Usage:
1)Include the header file: 
   #include "InputEngine\Input.h"

2)Declare an InputSystem object:
   CInputSystem g_Input;

3)In your initialization function write the following code:
   g_Input.CAcquireAll();
   g_Input.CInitialize( hwnd, g_Instance, true, IS_USEKEYBOARD | IS_USEMOUSE );

   Comment:hwnd is a handle to the window. g_Instance is the application instance. 
   To use the keyboard, use from the IS_USEKEYBOARD symbolic constant.
   To use the mouse device, use from the IS_USEMOUSE symbolic constant.

4)In your Rendering function, update it:
   g_Input.CUpdate();

5)To use Keyboard:
5.1)To check for a "keydown" write the following code:
   g_Input.CKeyDown( * );
Where * is one of the following constants:
DIK_ESCAPE
DIK_F1 to DIK_F12 for function keys
DIK_LEFT  DIK_RIGHT  DIK_UP  DIK_DOWN for arraw keys
DIK_A to DIK_Z for alphabets

5.2)To check for a "keyup" write the following code:
  g_Input.CKeyUp( * );

6)To check for mouse movements:
    CInt dx, dy;
    g_Input.CGetMouseMovement(dx, dy);
	And then use from dx and dy values in your code.

7) In your release function, write the following code:
	g_Input.CUnacquireAll();
	g_Input.CShutdown();

***********************************************/

#pragma once

#define DIRECTINPUT_VERSION 0x0800
/********************************* Includes *********************************/

#include <dinput.h>

/********************************* Constants ********************************/
#define IS_USEKEYBOARD  1
#define IS_USEMOUSE     2

#pragma comment( lib, "dInput8.lib" )
#pragma comment( lib, "dxguid.lib" )

class CKeyboard
{
public:
  CKeyboard(LPDIRECTINPUT8 pDI, HWND hwnd);
  ~CKeyboard();

  CBool KeyDown(CInt key) { return (m_keys[key] & 0x80 ) ? true : false; }
  CBool KeyUp(CInt key) { return (m_keys[key] & 0x80) ? false : true; }

  CBool Update();

  CVoid Clear() { memset( m_keys,0, 256 * sizeof(unsigned char)); }

  CBool Acquire();
  CBool Unacquire();

private:
  LPDIRECTINPUTDEVICE8 m_pDIDev;
  unsigned char m_keys[256];
};


class CMouse
{
public:
  CMouse(LPDIRECTINPUT8 pDI, HWND hwnd, CBool isExclusive = true);
  ~CMouse();

  CBool ButtonDown(CInt button) { return (m_state.rgbButtons[button] & 0x80) ? true : false; }
  CBool ButtonUp(CInt button) { return (m_state.rgbButtons[button] & 0x80) ? false : true; }
  CInt GetWheelMovement() { return m_state.lZ; }
  CVoid GetMovement(CInt &dx, CInt &dy) { dx = m_state.lX; dy = m_state.lY; }

  CBool Update();

  CBool Acquire();
  CBool Unacquire();

private:
  LPDIRECTINPUTDEVICE8  m_pDIDev;
  DIMOUSESTATE          m_state;
};


class CInputSystem
{
public:
  CBool Initialize(HWND hwnd, HINSTANCE appInstance, CBool isExclusive, DWORD flags = 0);
  CBool Shutdown();

  CVoid AcquireAll();
  CVoid UnacquireAll();

  CKeyboard  *GetKeyboard() { return m_pKeyboard; }
  CMouse     *GetMouse()    { return m_pMouse; }

  CBool Update();

  CBool KeyDown(CInt key) { return (m_pKeyboard && m_pKeyboard->KeyDown(key)); }
  CBool KeyUp(CInt key) { return (m_pKeyboard && m_pKeyboard->KeyUp(key)); }

  CBool ButtonDown(CInt button) { return (m_pMouse && m_pMouse->ButtonDown(button)); }
  CBool ButtonUp(CInt button) { return (m_pMouse && m_pMouse->ButtonUp(button)); }
  CVoid GetMouseMovement(CInt &dx, CInt &dy) { if (m_pMouse) m_pMouse->GetMovement(dx, dy); }
  CInt GetMouseWheelMovement() { return (m_pMouse) ? m_pMouse->GetWheelMovement() : 0; }

private:
  CKeyboard  *m_pKeyboard;
  CMouse     *m_pMouse;
  
  LPDIRECTINPUT8 m_pDI;
};
