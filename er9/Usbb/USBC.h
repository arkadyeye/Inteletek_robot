// File: USBC.h                    Date: 13-JAN-2009
//
#if !defined(AFX_USBC_H__105D681E_3ED1_42FF_A947_79256D1786C9__INCLUDED_)
#define AFX_USBC_H__105D681E_3ED1_42FF_A947_79256D1786C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#ifndef __AFXWIN_H__
//	#error include 'stdafx.h' before including this file for PCH
//#endif

#include "resource.h"		// main symbols

#include "USBCDEF.h"

#ifdef USBC_EXPORTS
     #define USBC_API __declspec(dllexport)
#else
     #define USBC_API __declspec(dllimport)
#endif

#include "list"

using namespace std;

//#ifdef __cplusplus
//extern "C" {
//#endif

// {2DD76384-6A26-4740-AD8A-61EBEA262324}
#define USB_DEV_GUID \
{ 0x2dd76384, 0x6a26, 0x4740, { 0xad, 0x8a, 0x61, 0xeb, 0xea, 0x26, 0x23, 0x24 } };

typedef void (*CallBackFun)( void *);

typedef list<WriteStruct>WriteTextArray;

USBC_API BOOL BuildPositForWrite( short sScale, WriteTextArray *pWriteArray,
						                TCHAR *szVectorName, short sDimension );

//--------------------  Configuration Functions ------------------------
USBC_API BOOL Initialization( short sMode, HardwareSetupData SetupData,
								CallBackFun fnInitEnd = NULL,
									 CallBackFun fnErrMessage = NULL );      // New


USBC_API BOOL Initialization( short sMode, short sSystemType = DEFAULT_SYSTEM_TYPE,
					CallBackFun fnInitEnd = NULL,
			   CallBackFun fnErrMessage = NULL );                      


USBC_API BOOL Initialization( short sMode, CallBackFun fnInitEnd,   // InitEnd callback
			   CallBackFun fnErrMessage );  
USBC_API void CloseUSBC();

USBC_API BOOL SetParameterFolder( TCHAR * szFolderName );
USBC_API BOOL GetParameterFolder( TCHAR * szFolderName );

// ucAxis 0 - Robot, 1...8 - axes
USBC_API BOOL SetParameter( TCHAR * szName, UCHAR ucAxis, double dValue );

USBC_API BOOL GetVersion( ULONG * pulVersion );

USBC_API BOOL IsEmergency( );
USBC_API BOOL IsTeachMode( );
USBC_API BOOL IsOnLineOk( );

USBC_API BOOL GetConfig( ConfigData &Config ); 
USBC_API BOOL SetConfig( ConfigData Config, CallBackFun fnConfigAvail ); 

// USBC_API BOOL ChangeConfig(	TCHAR * szDeviceID1, TCHAR * szDeviceID2, CallBackFun fnConfigAvail);


// sDeviceNo: 1,2...
USBC_API BOOL EnumPeriph( short sDeviceNo, short sSystemType, TCHAR *szDeviceID );

USBC_API BOOL SetJawMetric( short sValue );    // mm
USBC_API BOOL SetGripperType( short sGripType,
                short sOutNum, BOOL bOutState, short sDelay ); // ConfigAvailable callback
USBC_API BOOL GetUSBDeviceNumber( int *iDevice );
USBC_API void USBDeviceArrival();
USBC_API void USBDeviceRemoved();
USBC_API void USBDeviceQueryRemove();
USBC_API short GetMode();
USBC_API BOOL MyPumpMessages();
USBC_API BOOL WaitUSBCCommunication();
//-------------------- End of Configuration Functions ------------------------

//--------------------------- Movement Functions ------------------------
// fnMotionEnd == NULL then stop watch. Return prev callback funct.
USBC_API CallBackFun WatchMotion( CallBackFun fnMotionEnd,
								           CallBackFun fnMotionStart = NULL ); 
USBC_API BOOL EnterManual( short sManualType );
USBC_API BOOL MoveManual( UCHAR ucAxis, long lVelocity );
USBC_API BOOL CloseManual();
USBC_API BOOL Time( UCHAR ucGroup, long lTime  ); // millisec
USBC_API BOOL Speed( UCHAR ucGroup, long lSpeed ); // percent
USBC_API BOOL SpeedLin( UCHAR ucGroup, long lSpeedLin ); // mm/sec

USBC_API BOOL MoveTorque( long *plTorqueArray, short sTorqueArrayDim );

USBC_API BOOL MoveTorque( UCHAR ucAxis, long lTorque = 0 );

USBC_API BOOL MoveJoint( char *szVectorName, short sPointNumber,           
						              char *szVectorNameB = NULL, short sPointNumberB = 0 );

USBC_API BOOL MoveLinear( char *szVectorName, short sPointNumber,            
						 char *szVectorNameB = NULL, short sPointNumberB = 0);

USBC_API BOOL MoveCircularVect( char *szVectorName,                          
	           short sThroughPointNumber, short sTargetPointNumber,
			   char *szVectorNameB = NULL, short sPointNumberB = 0 );

USBC_API BOOL OpenGripper();
USBC_API BOOL CloseGripper();

USBC_API BOOL Stop( UCHAR ucGroup );  // ucGroup: & for all axes

USBC_API BOOL Velocity( UCHAR ucAxis, short sPercent );

USBC_API BOOL JawPerc( short sPercent );
USBC_API BOOL JawMetric( short sValue );    // mm
USBC_API BOOL GetJaw( short *psPerc, short *psMetricValue );

USBC_API BOOL Control( UCHAR ucGroupAxis, BOOL bIsOn );  // ucGroupAxis: & for all axes
USBC_API BOOL WatchControl( CallBackFun fnWatchControl ); 
USBC_API BOOL CloseWatchControl();

USBC_API BOOL GetMotionStatus( UCHAR ucGroup, BOOL *pbIsMove );  // A, B or or 1...7 for axis

USBC_API BOOL WatchHoming( CallBackFun fnHomingNotif );              
USBC_API BOOL Home( UCHAR ucGroupAxis, CallBackFun fnHomingNotif );   // 'A' for Robot, or 6...7 for peripherals
USBC_API BOOL SetHome( UCHAR ucGroupAxis );   // A, B, C or 0...7  or & for all
USBC_API BOOL GetHomingFlag( UCHAR &ucBitmap );

// ucAxisNum - 0...7
// lHomeSwitch: -1 - no search, 0 - search for 0 polarity, 1 - search for 1 polarity;
// lIndexPulse: -1 - no search, 0 - search for 0 polarity.
USBC_API BOOL SearchHomeSwitchAndIndexPulse( short ax, long lVelocity, long &lFoundHomeEncoder, long &lFoundIndexEncoder, long lHomeSwitch, long lIndexPulse, BOOL bIsUnited );

// ucAxisNum - 0...7
// lHomeSwitch: -1 - no search, 0 - search for 0 polarity, 1 - search for 1 polarity;
// lIndexPulse: -1 - no search, 0 - search for 0 polarity.
// USBC_API BOOL HomeTech( short ax, long &lFoundHomeEncoder, long &lFoundIndexEncoder, BOOL bIsUnited );

USBC_API BOOL SetToolOffset( int iX, int iY, int iZ );

USBC_API BOOL GetTPInfo( UCHAR &code, TCHAR *szText );

USBC_API BOOL WatchJoint( CallBackFun fnWatchJoint ); 
USBC_API BOOL CloseWatchJoint();

USBC_API BOOL SetJoint( RobotData *pJointData );
USBC_API BOOL Impact( RobotData *pJointData );

//---------------------- End of Movement Functions ---------------

//-------------------  Position Functions -----------------------
USBC_API BOOL GetPointsPeriphID( TCHAR * szDeviceID1, TCHAR * szDeviceID2, TCHAR *szFileName = NULL ); // Obsolete
USBC_API BOOL GetPointsPeriphID( TCHAR szDeviceIDarray[] [DEVICE_ID_LENGTH], int &iNumberPeriph, TCHAR *szFileName = NULL );

USBC_API void ClearPointsAttributes();

USBC_API BOOL AddPoints( TCHAR *szFileName );
USBC_API BOOL SavePoints( TCHAR *szFileName );

USBC_API BOOL DefineVector( UCHAR ucGroup,
				              TCHAR *szVectorName, short sDimension );

USBC_API BOOL RenameVector( TCHAR *szOldName, TCHAR *szNewName );

// if( sPointNumber = -1 ) then Delete all Vector
USBC_API BOOL DeletePoint( TCHAR *szVectorName, short sPointNumber = -1 );

USBC_API BOOL Here( TCHAR *szVectorName, short sPointNumber, long lPointType = ABS_JOINT );

USBC_API BOOL Teach( TCHAR *szVectorName, short sPointNumber,
              long *plCoorArray, short sCoorArrayDim = 5, long lPointType = ABS_XYZ_A );

USBC_API BOOL SetEncoders( TCHAR *szVectorName, short sPointNumber,
              long *plCoorArray, short sCoorArrayDim, long lPointType );

USBC_API BOOL SetJoints( TCHAR *szVectorName, short sPointNumber,
						  long *plCoorArray, short sCoorArrayDim, long lPointType );

USBC_API BOOL IsPointExist( TCHAR *szVectorName, short sPointNumber );

USBC_API BOOL IsTheBasePosition( TCHAR *szVectorName, short sPointNumber, BOOL &bIsTheBasePosition, short &sRelPointNumber );

USBC_API BOOL GetNextPoint( TCHAR *szVectorName, short sCurPointNumber,
						   short *psNextPointNumber );

USBC_API BOOL GetPointInfo( TCHAR *szVectorName, short sPointNumber,
    RobotData *pEncData,
	RobotData *pJointData,
	RobotData *pXYZData,
	long *lPointType );


USBC_API BOOL AttachPosit( UCHAR ucGroup, TCHAR *szVectorName ); 

USBC_API BOOL GetCurrentPosition( RobotData *pEnc, RobotData *pJoint, RobotData *pXYZ );

//-------------------  End of Position Functions ----------------

//------------------- Monitoring command -----------------------------
 
USBC_API BOOL ShowEnco( CallBackFun fnViewEnco );
USBC_API BOOL CloseEnco();

USBC_API BOOL ShowXYZ( CallBackFun fnViewXYZ );
USBC_API BOOL CloseXYZ();

USBC_API BOOL ShowJoint( CallBackFun fnViewJoint );
USBC_API BOOL CloseJoint();

USBC_API BOOL ShowPositErr( CallBackFun fnPositErr );
USBC_API BOOL ClosePositErr();

USBC_API BOOL ShowHomeSwitches( CallBackFun fnHomeSwitches );
USBC_API BOOL CloseHomeSwitches();

USBC_API BOOL ShowIndexPulses( CallBackFun fnHomeSwitches );
USBC_API BOOL CloseIndexPulses();


USBC_API BOOL ShowTorque( UCHAR ucAxis, CallBackFun fnTorque );
USBC_API BOOL CloseTorque();

//------------------- End of Monitoring command ----------------------

//------------------- Input/Output command ---------------------

USBC_API BOOL WatchDigitalInp( CallBackFun fnWatchDigitalInp ); 
USBC_API BOOL CloseWatchDigitalInp();

USBC_API BOOL WatchDigitalOut( CallBackFun fnWatchDigitalOut ); 
USBC_API BOOL CloseWatchDigitalOut();

USBC_API BOOL GetDigitalInputs( ULONG *plStatusBitmap );
USBC_API BOOL GetDigitalOutputs( ULONG *plStatusBitmap );

USBC_API BOOL SetDigitalOutput(short sIONumber, BOOL bIsOn, BOOL bIsImmediate = TRUE );

USBC_API BOOL ForceStatusDigitalInput(short sIONumber, BOOL bIsOn);
USBC_API BOOL ForceDigitalInput(short sIONumber, BOOL bIsOn);
USBC_API BOOL GetForceStatusDigitalInput( ULONG *plStatusBitmap );

USBC_API BOOL SetDigitalInputInterruptAvailability(short sIONumber, BOOL bIsEnable);
USBC_API BOOL DigitalInputInterruptMotionStopover(short sIONumber, BOOL bIsInputChangeStatus);

USBC_API BOOL WatchAnalogInp( CallBackFun fnWatchAnalogInp ); 
USBC_API BOOL CloseWatchAnalogInp();

USBC_API BOOL WatchAnalogOut( CallBackFun fnWatchAnalogOut ); 
USBC_API BOOL CloseWatchAnalogOut();

USBC_API BOOL GetAnalogInput( short sIONumber, ULONG *ulValue );

USBC_API BOOL ForceStatusAnalogInput(short sIONumber, BOOL bIsOn);
USBC_API BOOL ForceAnalogInput(short sIONumber, ULONG ulValue );
USBC_API BOOL GetForceStatusAnalogInput( ULONG *plStatusBitmap );

USBC_API BOOL SetAnalogOutput( short sIONumber, ULONG ulValue );

USBC_API BOOL SimulClearDigIO( BOOL bIsDigInp = TRUE, BOOL bIsDigOut = TRUE );

//------------------- End of Input/Output command ----------------------

//#ifdef __cplusplus
 //};
//#endif



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBC_H__105D681E_3ED1_42FF_A947_79256D1786C9__INCLUDED_)
