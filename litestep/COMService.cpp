//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// This is a part of the Litestep Shell source code.
//
// Copyright (C) 1998 (e)
// Copyright (C) 1997-2015  LiteStep Development Team
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <functional>
#include "COMService.h"
#include "../utility/common.h"
#include "../utility/shlobjw.h"
#include "IDesktopWallpaper.h"
#include "COMFactory.h"
#include "../utility/debug.hpp"
#include "../lsapi/lsapi.h"


//
// COMService
//
COMService::COMService()
{
}


//
// ~COMService
//
COMService::~COMService()
{
}


//
// ThreadProc
// Protects COM objects from actions of modules (CoUninitialize...)
//
void COMService::ThreadProc()
{
    m_dwThreadID = GetCurrentThreadId();

#if defined(_DEBUG)
    DbgSetCurrentThreadName("LS COM Service");
#endif

    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    // C2CF3110-460E-4fc1-B9D0-8A1C0C9CC4BD
    const GUID CLSID_DesktopWallpaper = { 0xC2CF3110, 0x460E, 0x4FC1,
        { 0xB9, 0xD0, 0x8A, 0x1C, 0x0C, 0x9C, 0xC4, 0xBD } };

    DWORD dwFactoryCookie;
    CoRegisterClassObject(CLSID_DesktopWallpaper, m_pFactory,
        CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &dwFactoryCookie);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CoRevokeClassObject(dwFactoryCookie);

    CoUninitialize();
}


//
// IService::Start
//
HRESULT COMService::Start()
{
    m_pFactory = new COMFactory();
    LSAPISetCOMFactory((IClassFactory*)m_pFactory);
    m_COMThread = std::thread(std::bind(&COMService::ThreadProc, this));
    return S_OK;
}


//
// IService::Start
//
HRESULT COMService::Stop()
{
    // Switch to this if we ever drop XP support, using m_dwThreadID leads to a possible race condition
    //PostThreadMessage(GetThreadId(m_COMThread.native_handle()), WM_QUIT, 0, 0);
    PostThreadMessage(m_dwThreadID, WM_QUIT, 0, 0);
    m_COMThread.join();

    LSAPISetCOMFactory(nullptr);
    m_pFactory->Release();

    return S_OK;
}


//
// IService::Start
//
HRESULT COMService::Recycle()
{
    return S_OK;
}
