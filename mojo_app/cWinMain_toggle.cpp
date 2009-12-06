/***********************************************************************************************************************
/*
/*    cWinMain_toggle.cpp / mojo_app
/*   
/*    Copyright 2009 Robert Sacks.  See end of file for more info.
/*
/**********************************************************************************************************************/

#include "stdafx.h"


//======================================================================================================================
// PROTOTYPES
//======================================================================================================================

void             toggle_sub ( bool * pbSetting, const wchar_t * pSettingName, 
                              const wchar_t * pMenuTxtOn, const wchar_t * pMenuTxtOff,
							  const wchar_t * pToolbarTxtOn, const wchar_t * pToolbarTxtOff,
                              int iCtrlID );

//======================================================================================================================
//  CODE
//======================================================================================================================


//----------------------------------------------------------------------------------------------------------------------
//  TOGGLE BROADCAST
//----------------------------------------------------------------------------------------------------------------------
void cWinMain :: toggle_broadcast ()
{
	toggle_sub ( &g_Settings.bBroadcastIsOn,
                 L"bBroadcastIsOn",
                 L"Turn broadcast off",
				 L"Turn broadcast on",
				 L"Broadcast is on",
				 L"Broadcast is off",
				 ID_TOGGLE_BROADCAST );
}

//----------------------------------------------------------------------------------------------------------------------
//  TOGGLE HOTKEYS
//----------------------------------------------------------------------------------------------------------------------
void cWinMain :: toggle_hotkeys ()
{
	g_Settings.bHotkeysAreOn = true;

	toggle_sub ( &g_Settings.bHotkeysAreOn,
                 L"bHotkeysAreOn",
                 L"Turn hotkeys off",
				 L"Turn hotkeys on",
				 L"Hotkeys are on",
				 L"Hotkeys are off",
				 ID_TOGGLE_HOTKEYS );
}

//----------------------------------------------------------------------------------------------------------------------
//  TOGGLE MOUSEOVER
//----------------------------------------------------------------------------------------------------------------------
void cWinMain :: toggle_mouseover ()
{
	toggle_sub ( &g_Settings.bMouseoverIsOn,
                 L"bMouseoverIsOn",
                 L"Turn mouseover off",
				 L"Turn mouseover on",
				 L"Mouseover is on",
				 L"Mouseover is off",
				 ID_TOGGLE_MOUSEOVER );
}
                              

//----------------------------------------------------------------------------------------------------------------------
//  TOGGLE SUB
//----------------------------------------------------------------------------------------------------------------------
void cWinMain :: toggle_sub ( bool * pbSetting, const wchar_t * pSettingName, 
                              const wchar_t * pMenuTxtOn, const wchar_t * pMenuTxtOff,
							  const wchar_t * pToolbarTxtOn, const wchar_t * pToolbarTxtOff,
                              int iCtrlID )

{
	pToolbarTxtOff, pToolbarTxtOn, pMenuTxtOff, pMenuTxtOn;

	*pbSetting = *pbSetting ? false : true;
	mojo::set ( pSettingName, *pbSetting );

	const wchar_t * pMenuTxt = *pbSetting ? pMenuTxtOn : pMenuTxtOff;

#if 0 // TOOLBAR STUFF HAS BEEN REPLACED BY DLG MODE STRIP

	TBBUTTONINFO tbbi;
	tbbi.cbSize = sizeof ( tbbi );
	tbbi.dwMask = TBIF_IMAGE | TBIF_STATE | TBIF_TEXT;

	if ( *pbSetting )
	{
		tbbi.fsState = TBSTATE_ENABLED | TBSTATE_CHECKED;
		pMenuTxt     = (wchar_t*) pMenuTxtOn;
		tbbi.pszText = (wchar_t*) pToolbarTxtOn;
		tbbi.iImage  = 1;
	}

	else
	{
		tbbi.fsState = TBSTATE_ENABLED;
		pMenuTxt     = (wchar_t*) pMenuTxtOff;
		tbbi.pszText = (wchar_t*) pToolbarTxtOff;
		tbbi.iImage  = 0;
	}

	SendMessage ( g_WinMain.toolbar(), TB_SETBUTTONINFO, iCtrlID, (LPARAM) &tbbi );

#endif

	set_menu_item_text ( g_hwnd, iCtrlID, pMenuTxt );

	DlgModeStrip.redraw_buttons();
	InvalidateRect ( g_hwnd, NULL, TRUE );
	UpdateWindow ( g_hwnd );

	mojo::set ( pSettingName, *pbSetting );
	// set_tray_icon ();
}


//----------------------------------------------------------------------------------------------------------------------
//  TOGGLE BROADCAST
//----------------------------------------------------------------------------------------------------------------------
#if 0
void cWinMain :: toggle_broadcast ()
{
	g_Settings.bBroadcastIsOn = g_Settings.bBroadcastIsOn ? false : true;
	mojo::set ( L"bBroadcastIsOn", g_Settings.bBroadcastIsOn );

	wchar_t * pMenuTxt;

	TBBUTTONINFO tbbi;
	tbbi.cbSize = sizeof ( tbbi );
	tbbi.dwMask = TBIF_IMAGE | TBIF_STATE | TBIF_TEXT;

	if ( g_Settings.bBroadcastIsOn )
	{
		tbbi.fsState = TBSTATE_ENABLED | TBSTATE_CHECKED;
		pMenuTxt = L"Turn broadcast off";
		tbbi.pszText = L"Broadcast is on";
		tbbi.iImage = 1;
	}

	else
	{
		tbbi.fsState = TBSTATE_ENABLED;
		pMenuTxt = L"Turn broadcast on";
		tbbi.pszText = L"Broadcast is off";
		tbbi.iImage = 0;
	}

	SendMessage ( hwndToolbar, TB_SETBUTTONINFO, ID_TOGGLE_BROADCAST, (LPARAM) &tbbi );

	set_menu_item_text ( g_hwnd, ID_TOGGLE_BROADCAST, pMenuTxt );

	InvalidateRect ( g_hwnd, NULL, TRUE );
	UpdateWindow ( g_hwnd );
	// set_tray_icon ();
}
#endif


/***********************************************************************************************************************
/*
/*    This file is part of Mojo.  For more information, see http://mojoware.org.
/*
/*    You may redistribute and/or modify Mojo under the terms of the GNU General Public License, version 3, as
/*    published by the Free Software Foundation.  You should have received a copy of the license with mojo.  If you
/*    did not, go to http://www.gnu.org.
/* 
/*    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
/*    NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
/*    IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
/*    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
/*    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
/*    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
/*    EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
/*
/***********************************************************************************************************************/
