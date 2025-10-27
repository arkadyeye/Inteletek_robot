// Simplified CallBack.h for console-based robot server
/*
#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include <windows.h>

#include "usbc/usbc.h"
#include "usbc/usbcdef.h"
#include "usbc/error.h"
#include "usbc/Extern.h"

#include <string>
#include <iostream>

class DigitalIO {
    ULONG m_ulStatusBitmap;
    ULONG m_ulChangeBitmap;
public:
    DigitalIO() : m_ulStatusBitmap(0), m_ulChangeBitmap(0) {}
    void ClearStatusBitmap() { m_ulStatusBitmap = 0; }
    void ClearChangeBitmap() { m_ulChangeBitmap = 0; }
    void SetStatusBitmap(ULONG ul) { m_ulStatusBitmap = ul; }
    void SetChangeBitmap(ULONG ul) { m_ulChangeBitmap = ul; }
    ULONG GetStatus() const { return m_ulStatusBitmap; }
    ULONG GetChanges() const { return m_ulChangeBitmap; }

    BOOL SetDigitalIOStatus(BOOL bStatus, BOOL bIsChanged, int iNumber);
    BOOL GetDigitalIOStatus(BOOL &bStatus, BOOL &bIsChanged, int iNumber);
};

struct CMotionStart {
    UCHAR ucGroup;
    double dSpeed;
    double dTime;
};


// Callbacks
void InitEnd(ConfigData *pConfigData);
void ErrorMessage(ErrorInfo *pErrorInfo);
void AxisControl(UINT *uiBitmap);
void MotionEnd(UCHAR *ucEndCode);
void MotionStart(CMotionStart *pStart);
void HomingNotif(UCHAR *ucNotifCode);
void ViewWatchJoint(RobotData TheJoint);
void ChangeConfigDone(ConfigData *pMyConfigData);
void ViewShowTorque(long *lTorque);
void ViewWatchDigitInputs(DigitalIO *pDigitalIO);

#endif

*/

// File: CallBack.h                   Date: 03-SEP-2002

#if !defined( _CALLBACK_H_ )
#define _CALLBACK_H_

#include <windows.h>

#include "usbb/usbc.h"
#include "usbb/usbcdef.h"
#include "usbb/error.h"
#include "usbb/Extern.h"

#include <string>
#include <iostream>

class DigitalIO
{
private: 
	ULONG m_ulStatusBitmap;
	ULONG m_ulChangeBitmap;

public:
	DigitalIO( ) { m_ulStatusBitmap = m_ulChangeBitmap = 0; };
	void ClearStatusBitmap( ){ m_ulStatusBitmap = 0; };
    void ClearChangeBitmap( ){ m_ulChangeBitmap = 0; }; 
	void SetStatusBitmap( ULONG ulStatusBitmap ){ m_ulStatusBitmap = ulStatusBitmap; };
    void SetChangeBitmap( ULONG ulChangeBitmap ){ m_ulChangeBitmap = ulChangeBitmap; }; 
	ULONG GetStatus( ){ return m_ulStatusBitmap; };
    ULONG GetChanges( ){ return m_ulChangeBitmap; }; 

	// iNumber 0...31
	BOOL SetDigitalIOStatus ( BOOL bStatus, BOOL bIsChanged, int iNumber )
	{
		if( iNumber < 0 || iNumber > 31 )
			return FALSE;
		ULONG ulWorkMask, ulBitMask =  1 << iNumber;
		if( bStatus )
		{
			ulWorkMask = ulBitMask;
			m_ulStatusBitmap |= ulWorkMask;
		}
		else
		{
			ulWorkMask = ~ulBitMask;
			m_ulStatusBitmap &= ulWorkMask;
		}		
		if( bIsChanged )
		{
			ulWorkMask = ulBitMask;
			m_ulChangeBitmap |= ulWorkMask;
		}
		else
		{
			ulWorkMask = ~ulBitMask;
			m_ulChangeBitmap &= ulWorkMask;
		}
        return TRUE;
	}// end of BOOL SetDigitalIOStatus ( BOOL bStatus, BOOL bIsChanged, int iNumber )

	// iNumber 0...31
	BOOL GetDigitalIOStatus ( BOOL &bStatus, BOOL &bIsChanged, int iNumber )
	{
		BOOL bStat, bChange;
		if( iNumber < 0 || iNumber > 31 )
			return FALSE;
        ULONG ulBitMask =  1 << iNumber;
		bChange = ( m_ulChangeBitmap & ulBitMask ) ? TRUE : FALSE;
		bStat = ( m_ulStatusBitmap & ulBitMask ) ? TRUE : FALSE;      
		bIsChanged = bChange;
		bStatus = bStat;	
		return TRUE;
	}// end of BOOL GetDigitalIOStatus ( BOOL bIsChanged, int iNumber )
};// end of class DigitalIO

class  CMotionStart
{
public:
    UCHAR ucGroup;
	double dSpeed;    
    double dTime;     
};// end of class  CMotionStart

void InitEnd(ConfigData *pTheConfigData);       // see Initialization function in USBC.H file
void ErrorMessage(ErrorInfo *pTheErrorInfo);    // see Initialization function in USBC.H file 
void AxisControl(UINT * uiBitmap);              // see WatchControl function in USBC.H file

// ucEndCode:
// 'A' - group A
// 'B' - group B
// 'G' - gripper
//  0...7 Axis
void MotionEnd(UCHAR *ucEndCode);                 // see WatchMotion function in USBC.H file
void MotionStart( CMotionStart *pCMotionStart );  // see WatchMotion function in USBC.H file

#define HOME_NOTIF_START  0xff
#define HOME_NOTIF_FINISH 0x40
//  ucNotifCode
//  HOME_NOTIF_START
//  1...8 Start Homing Axis 
//  HOME_NOTIF_FINISH
void HomingNotif( UCHAR * ucNotifCode );   // see Home function in USBC.H file


void ViewWatchJoint(RobotData TheJoint);        // see WatchJoint function in USBC.H file
void ViewWatchXYZ(RobotData TheJoint);        // 



void ChangeConfigDone(ConfigData *pMyConfigData);  // see ChangeConfig function in USBC.H file

// set *lTorque  value  ( -244 0  +244 ) for specified axis in ShowTorque function.
void ViewShowTorque( long *lTorque );          // see ShowTorque function in USBC.H file

void ViewWatchDigitInputs(DigitalIO *pDigitalIO);  // see WatchDigitalInp function in USBC.H file  

#endif
