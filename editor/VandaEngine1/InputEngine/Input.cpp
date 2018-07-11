 /*Author   :   Dave Astle
 Date     :   11/22/2000

 Written for OpenGL Game Programming
 */
#include "stdafx.h"
#include "Input.h"


/*****************************************************************************
 CKeyboard::onstructor

 Initializes the DI device
*****************************************************************************/
CKeyboard::CKeyboard(LPDIRECTINPUT8 pDI, HWND hwnd)
{
  if (FAILED(pDI->CreateDevice(GUID_SysKeyboard, &m_pDIDev, NULL)))
  {
    // error processing
  }

  if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIKeyboard)))
  {
    // error processing
  }

  if (FAILED(m_pDIDev->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
  {
    // error processing
  }

  if (FAILED(m_pDIDev->Acquire()))
  {
    // error processing
  }

  //Clear();
} // end CKeyboard::onstructor


/*****************************************************************************
 CKeyboard::Destructor

 Releases the DI device
*****************************************************************************/
CKeyboard::~CKeyboard()
{
  if (m_pDIDev)
  {
    m_pDIDev->Unacquire();
    m_pDIDev->Release();
  }
} // end CKeyboard::Destructor


/*****************************************************************************
 CKeyboard::Update()

 Queries the current state of the keyboard and stores it in the member
 variables.
*****************************************************************************/
CBool CKeyboard::Update()
{
  if (FAILED(m_pDIDev->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
  {
    if (FAILED(m_pDIDev->Acquire()))
    {
      return false;
    }
    if (FAILED(m_pDIDev->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
    {
      return false;
    }
  }
  return true;
} // end CKeyboard::Update()


/*****************************************************************************
 CKeyboard::Acquire()

 Acquires the keyboard
*****************************************************************************/
CBool CKeyboard::Acquire()
{
  Clear();
  return (!FAILED(m_pDIDev->Acquire()));
} // end CKeyboard::Acquire()


/*****************************************************************************
 CKeyboard::Unacquire()

 Unacquires the keyboard
*****************************************************************************/
CBool CKeyboard::Unacquire()
{
  //Clear();
  return (!FAILED(m_pDIDev->Unacquire()));
} // end CKeyboard::Unacquire()



/*****************************************************************************
 CMouse::onstructor

 Initializes the DI device
*****************************************************************************/
CMouse::CMouse(LPDIRECTINPUT8 pDI, HWND hwnd, CBool isExclusive)
{
  if (FAILED(pDI->CreateDevice(GUID_SysMouse, &m_pDIDev, NULL)))
  {
    // error processing
  }

  if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIMouse)))
  {
    // error processing
  }

  DWORD flags;
  if (isExclusive)
    flags = DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
  else
    flags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;


  if (FAILED(m_pDIDev->SetCooperativeLevel(hwnd, flags)))
  {
    // error processing
  }

  if (FAILED(m_pDIDev->Acquire()))
  {
    // error processing
  }

  if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
  {
    // error processing
  }
} // end CMouse::onstructor


/*****************************************************************************
 CMouse::Destructor

 Releases the DI device
*****************************************************************************/
CMouse::~CMouse()
{
  if (m_pDIDev)
  {
    m_pDIDev->Unacquire();
    m_pDIDev->Release();
  }
} // end CMouse::Destructor


/*****************************************************************************
 CMouse::Update()

 Queries the current state of the mouse and stores it in the member
 variables.
*****************************************************************************/
CBool CMouse::Update()
{
  if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
  {
    if (FAILED(m_pDIDev->Acquire()))
    {
      return false;
    }
    if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
    {
      return false;
    }
  }

  return true;
} // end CMouse::Update()


/*****************************************************************************
 CMouse::Acquire()

 Acquires the mouse
*****************************************************************************/
CBool CMouse::Acquire()
{
  return (!FAILED(m_pDIDev->Acquire()));
} // end CMouse::Acquire


/*****************************************************************************
 CMouse::Unacquire()

 Unacquires the keyboard
*****************************************************************************/
CBool CMouse::Unacquire()
{
  return (!FAILED(m_pDIDev->Unacquire()));
} // end CMouse::Unacquire()


/*****************************************************************************
 CInputSystem::Initialize()

 Initializes the input system. isExclusive should be set to true for exclusive
 mouse access, false otherwise. Flags should be a combination of
 IS_USEKEYBOARD and/or IS_USEMOUSE.
*****************************************************************************/
CBool CInputSystem::Initialize(HWND hwnd, HINSTANCE appInstance, CBool isExclusive, DWORD flags)
{
  // create the DI object
  if (FAILED(DirectInput8Create(appInstance,
                               DIRECTINPUT_VERSION,
                               IID_IDirectInput8,
                               (CVoid **)&m_pDI,
                               NULL)))
    return false;

  if (flags & IS_USEKEYBOARD)
  {
    m_pKeyboard = new CKeyboard(m_pDI, hwnd);
    if (m_pKeyboard == NULL)
      return false;
  }
  if (flags & IS_USEMOUSE)
  {
    m_pMouse = new CMouse(m_pDI, hwnd, isExclusive);
    if (m_pMouse == NULL)
      return false;
  }

  return true;
} // end CInputSystem::Initialize()


/*****************************************************************************
 CInputSystem::Shutdown()

 Releases all objects and frees memory.
*****************************************************************************/
CBool CInputSystem::Shutdown()
{
  UnacquireAll(); 
  if (m_pKeyboard)
  {
    delete m_pKeyboard;
    m_pKeyboard = NULL;
  }

  if (m_pMouse)
  {
    delete m_pMouse;
    m_pMouse = NULL;
  }

  if( m_pDI )
  {
  if (FAILED(m_pDI->Release()))
    return false;
  }

  return true;
} // end CInputSystem::Shutdown()


/*****************************************************************************
 CInputSystem::Update()

 Queries the current state of all devices.
*****************************************************************************/
CBool CInputSystem::Update()
{
  if (m_pKeyboard)
    m_pKeyboard->Update();
  if (m_pMouse)
    m_pMouse->Update();

  return true;
} // end CInputSystem::Update()


/*****************************************************************************
 CInputSystem::AcquireAll()

 //Makes sure all input devices are acquired
*****************************************************************************/
CVoid CInputSystem::AcquireAll()
{
  if (m_pKeyboard)
    m_pKeyboard->Acquire();
  if (m_pMouse)
    m_pMouse->Acquire();
} // end CInputSystem::AcquireAll()


/*****************************************************************************
 CInputSystem::UnacquireAll()

 Unacquires all devices
*****************************************************************************/
CVoid CInputSystem::UnacquireAll()
{
  if (m_pKeyboard)
    m_pKeyboard->Unacquire();
  if (m_pMouse)
    m_pMouse->Unacquire();
} // end CInputSystem::UnacquireAll()

