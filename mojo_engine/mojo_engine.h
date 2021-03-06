/***********************************************************************************************************************
/*
/*    mojo_engine.h / mojo_engine
/*
/*    This file declares the DLL's exported interface.   Include this file in any program
/*    that uses this DLL.
/*
/*    Your program can use any function on this page.
/*
/*    Your program can also use any MOJO_ENGINE_API class in the included header files.
/*
/*    Copyright 2009 Robert Sacks.  See end of file for more info.
/*
/**********************************************************************************************************************/

#pragma once

#ifndef MOJO_ENGINE_API
#ifdef MOJO_DLL_EXPORTS
#define MOJO_ENGINE_API __declspec(dllexport)
#else
#define MOJO_ENGINE_API __declspec(dllimport)
#endif
#endif

//======================================================================================================================
//  OTHER HEADER FILES
//======================================================================================================================

#include "tStr.h"
#include "tPt.h"
#include "regex.h"
#include "tRect.h"
#include "cVersion.h"
#include "tList.h"
#include "tList2.h"
#include "tArray.h"
#include "tCircBuf.h"
#include "cLog.h"
#include "cScrib.h"
#include "cScribPack.h"
#include "cScribMgr.h"
#include "cException.h"
#include "cInputEvent.h"
#include "cKeyboard.h"
#include "utility.h"
#include "cMemo.h"
#include "cAdLibMemo.h"
#include "cSettingsBase.h"
#include "set.h"
#include "cDisplay.h"
#include "cMach.h"
#include "cMachlist.h"
#include "cTarget.h"
#include "cArrayTarget.h"
#include "directories.h"
#include "cFile.h"
#include "cTrigger.h"


namespace mojo
{
//======================================================================================================================
//  DATA
//======================================================================================================================

const UINT uWM_INPUT_EVENT_READY             = WM_APP + 0xBFFF - 0;
const UINT uWM_MEMO_READY                    = WM_APP + 0xBFFF - 1;
const UINT uWM_MACHLIST_CHANGED              = WM_APP + 0xBFFF - 2;
const UINT uWM_TARGETS_CHANGED               = WM_APP + 0xBFFF - 3;
const UINT uWM_HIDE_OR_SHOW_CURSOR           = WM_APP + 0xBFFF - 4;
const UINT uWM_KEY_EVENT_OCCURRED            = WM_APP + 0xBFFF - 5;
const UINT uWM_MOJO_OFF_ON                   = WM_APP + 0xBFFF - 6;
const UINT uWM_WINDOW_BROADCAST_OFF_ON       = WM_APP + 0xBFFF - 7;
const UINT uWM_COMPUTER_BROADCAST_OFF_ON     = WM_APP + 0xBFFF - 8;
const UINT uWM_MOUSEOVER_OFF_ON              = WM_APP + 0xBFFF - 9;
const UINT uWM_HOTKEYS_OFF_ON                = WM_APP + 0xBFFF - 10;
const UINT uWM_HIDE_SHOW_MOJO                = WM_APP + 0xBFFF - 11;
// const UINT uWM_BRING_MOUSEOVER_CURSOR_HOME   = WM_APP + 0xBFFF - 10;

namespace nConnectionStatus
{
	enum eConnectionStatus { none=0, server=1, client=2, both=3 };
}


//======================================================================================================================
//  PROTOTYPES
//======================================================================================================================

MOJO_ENGINE_API void test					();	

MOJO_ENGINE_API void get_engine_version   ( cVersion * pRetVersion );
MOJO_ENGINE_API bool load_engine_settings	( const wchar_t * pAppDataDirectory );
MOJO_ENGINE_API bool initialize_engine 	( HINSTANCE hAppInstance, 
										  HWND hwndAppMessageLoop,
										  const wchar_t * pAppTitle,
										  const wchar_t * apScribs [],
										  const wchar_t * pScribPathname [],
	                                      const wchar_t * pAppDataDirectory, 
										  const cVersion * pVersionRequiredByApp );
MOJO_ENGINE_API void shut_down_engine 	         ();
MOJO_ENGINE_API bool get_input_event 		     ( mojo::cInputEvent * pRetInputEvent );
MOJO_ENGINE_API void put_memo				     ( mojo::cMemo::_eSeverity e, const wchar_t * pKey, ... );
MOJO_ENGINE_API void put_memo 			         ( mojo::cMemo * pMemo );
MOJO_ENGINE_API void put_ad_lib_memo		     ( mojo::cMemo::_eSeverity e, const wchar_t * pHeadFormatString, const wchar_t * pBodyFormatString=NULL, ... );
MOJO_ENGINE_API bool get_memo				     ( mojo::cMemo * pRetMemo );

MOJO_ENGINE_API int load_scribs                  ( const wchar_t * apScribs [],  bool bReplace );
MOJO_ENGINE_API int load_scribs                  ( const wchar_t * pPathname,	bool bReplace );
MOJO_ENGINE_API bool get_ip_addresses            ( mojo::cArrayU * pRet );
MOJO_ENGINE_API void ip_dword_to_cStrW           ( cStrW * pRet, DWORD dw );
MOJO_ENGINE_API DWORD ip_pw_to_dword		     ( const wchar_t * );
MOJO_ENGINE_API void  get_machlist		         ( mojo::cMachlist * pRet );
MOJO_ENGINE_API bool  get_mach                   ( mojo::cMach * pRet, DWORD dwHandle );
MOJO_ENGINE_API mojo::nConnectionStatus::eConnectionStatus 
				get_connection_status 	         ( DWORD dwMachHandle );
MOJO_ENGINE_API void get_targets                 ( mojo::cArrayTarget * pRet );
MOJO_ENGINE_API void get_local_targets           ( mojo::cArrayTarget * pRet );
MOJO_ENGINE_API void set_mouseover_layout        ( mojo::cMachlist * pMachlist );
MOJO_ENGINE_API void get_key_state_as_trigger    ( mojo::cTrigger * pRet );
MOJO_ENGINE_API void register_for_key_events     ( /* mojo::tCircBuf<WORD> * pBuf, */ HWND hNotifyMe );
MOJO_ENGINE_API void unregister_for_key_events   ( HWND hNotifyMe );
MOJO_ENGINE_API void start_swallowing_key_events ( HWND hwndSwallow );
MOJO_ENGINE_API void stop_swallowing_key_events  ();
MOJO_ENGINE_API void set_launch_target           ( mojo::cTarget * p ); // adds it if necessary
MOJO_ENGINE_API void remove_launch_target        ( DWORD dwID ); // adds it if necessary
MOJO_ENGINE_API bool set_predefined_hotkey       ( const wchar_t * pName, mojo::cTrigger * pTrigger );
MOJO_ENGINE_API bool clear_predefined_hotkey     ( const wchar_t * pName );
MOJO_ENGINE_API void set_active_window_tracking  ( bool b );
MOJO_ENGINE_API void set_active_window_tracking_z_order  ( bool b );
MOJO_ENGINE_API void set_active_window_tracking_delay ( int );
} // namespace

/***********************************************************************************************************************
/*
/*    This file is part of Mojo.  For more information, see http://mojoware.org.
/*
/*    You may redistribute and/or modify Mojo under the terms of the GNU General Public License, 
/*    version 3, as published by the Free Software Foundation.  You should have received a copy of the 
/*    license with mojo.  If you did not, go to http://www.gnu.org.
/*     
/*    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
/*    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
/*    PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
/*    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
/*    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
/*    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
/*    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
/*    EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
/*
/***********************************************************************************************************************/