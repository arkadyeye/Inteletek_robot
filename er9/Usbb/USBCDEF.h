// File: USBCDEF.H               Date: 11-JAN-2009


#if !defined( _USBCDEF_H_INCLUDED_ )
#define _USBCDEF_H_INCLUDED_

#include <tchar.h>

#define   TOTAL_AXES 8
#define   TOTAL_DIGITAL_IO 32
#define   TOTAL_ANALOG_INP  4
#define   TOTAL_ANALOG_OUT  2
#define   DEVICE_ID_LENGTH 16


typedef long RobotData[ TOTAL_AXES ];

// Initialization mode constant 
#define INIT_MODE_DEFAULT  0  // Set mode from INI file. ( Last used )
#define INIT_MODE_ONLINE   1  // Force online mode
#define INIT_MODE_SIMULAT  2  // Force simulation mode
#define INIT_MODE_OFFLINE  3  // Force offline mode ( None Go... motion commands )

//   Motion constants
#define MANUAL_TYPE_ENC      0
#define MANUAL_TYPE_XYZ      1

#define MOTION_STATUS_DONT_MOVE     0
#define MOTION_STATUS_MOVE          1
#define MOTION_STATUS_ENDLESS_MOVE  2
#define MOTION_STATUS_CONTROL_OFF   3


////////////////////////////////////////////////////////////////////
// From Controller B:
////////////////////////////////////////////////////////////////////
	 /************************
	 * REFERENCE POINT TYPES *
	 ************************/
#define  ABS_XYZ_A           -32766
#define  ABS_XYZ_B           -32765
#define  REL_XYZ_CRNT        -32767
#define  REL_XYZ_PNT(x)      ((x<0?1:0) && (x>-32765?1:0))
#define  XYZ_REFER(x)       ((x<0?1:0))
#define  ABS_JOINT          0
#define  REL_JOINT_CRNT      32767
#define  REL_JOINT_PNT(x)    ((x>0?1:0) && (x<32767?1:0))
#define  JOINT_REFER(x)     ((x>=0?1:0))
#define  RELATIVE_REFER(x)  ((x!=ABS_JOINT) && (x!=ABS_XYZ_A) && (x!=ABS_XYZ_B))
#define  ABS_REFER(x)       ((x==ABS_JOINT) || (x==ABS_XYZ_A) || (x==ABS_XYZ_B))
#define  ABS_XYZ(x)   		 ((x==ABS_XYZ_A) || (x==ABS_XYZ_B))
#define  REL_CRNT(x)			 ((x==REL_XYZ_CRNT) ||(x==REL_JOINT_CRNT))


// IO  constants
#define ALL_IO 32767

// Axis types ( bitmap )
#define AX_ROTAT    0x0000
#define AX_LINEAR   0x0001
#define AX_GRIPPER  0x0002
#define AX_ENDLESS  0x0004

#define ROBOT_GROUP  _T('A')
#define PERIPH_GROUP _T('B')
#define AXES_GROUP   _T('C')

// Controller types
#define  USB_CONTR_TYPE   10
#define  USBB_CONTR_TYPE  11
#define  ACL_A_CONTR_TYPE 20
#define  ACL_B_CONTR_TYPE 30

// System types
#define DEFAULT_SYSTEM_TYPE     0
#define ARBITRARY_SYSTEM_TYPE   1
#define ER2USB_SYSTEM_TYPE  21
#define ER4USB_SYSTEM_TYPE  41
#define ER5P_SYSTEM_TYPE    55
#define ER7_SYSTEM_TYPE     70
#define ER9_SYSTEM_TYPE     90
#define ER9USB_SYSTEM_TYPE  91        
#define ER9USBB_SYSTEM_TYPE 92  
#define ER14_SYSTEM_TYPE    140
#define ER14USBB_SYSTEM_TYPE 141

#define ASRS36USB_SYSTEM_TYPE       36 
#define ASRS2_36USB_SYSTEM_TYPE    236 

// Gripper Types
#define MISSING_GRIPPER_TYPE   0
#define PNEUMATIC_GRIPPER_TYPE 1
#define SERVO_GRIPPER_TYPE     2

#define NUMBER_DEGREE_FREEDOM_ER9  5
#define NUMBER_DEGREE_FREEDOM_ER14  4


#define ER2USB_SYSTEM_NAME _T("ER-2u")
#define ER4USB_SYSTEM_NAME _T("ER-4u")
#define ER5P_SYSTEM_NAME    _T("ER-Vplus")
#define ER7_SYSTEM_NAME    _T("ER-7")
#define ER9_SYSTEM_NAME    _T("ER-9")
#define ER9USB_SYSTEM_NAME _T("ER-9u")
#define ER9USBB_SYSTEM_NAME _T("ER-9ub")
#define ER14_SYSTEM_NAME    _T("ER-14")
#define ER14USBB_SYSTEM_NAME _T("ER-14ub")

#define ASRS36USB_SYSTEM_NAME   _T("ASRS-36")
#define ASRS2_36USB_SYSTEM_NAME _T("ASRS-2*36")


#define NOC_TEXT    _T("NOC")
//---------------- Initialization status -----------------------------
#define INIT_STATUS_TRANSIT 0
#define INIT_STATUS_ONLINE  1
#define INIT_STATUS_SIMUL   2
#define INIT_STATUS_OFFLINE 3 

class HardwareSetupData
{
    public:
    short   m_sSystemType;
    short   m_sGripperType;
    short   m_sPneuGripDigOutputNumber; // pneumatic gripper digital output number
    short   m_sOutStateClosedGripper;   // output state for closed gripper
    short   m_sGripDuration;            // 1/10 second
	short   m_sWarnDigOutputNumber;     // warning light digital output number
    TCHAR   m_szDeviceID[ TOTAL_AXES + 1 ][ DEVICE_ID_LENGTH ];  // current peripherals ID string for axes 0...7

	HardwareSetupData()
	{
      m_sSystemType = m_sGripperType = m_sPneuGripDigOutputNumber = m_sOutStateClosedGripper = m_sGripDuration = m_sWarnDigOutputNumber = 0;
      for( int i = 0; i < TOTAL_AXES; i++ )
	  {
		   for( int j = 0; j < DEVICE_ID_LENGTH; j++ )
		   {
               m_szDeviceID[i][j] = 0;
		   }// end of for( int j = 0; j < DEVICE_ID_LENGTH; j++ )
	  }// end if for( int i = 0; i < TOTAL_AXES; i++ )
	}// end of HardwareSetupData()

};// end of class HardwareSetupData

class ConfigData
{
public:
   short   m_sMode;
   short   m_sType[TOTAL_AXES];      // axis types
   TCHAR   m_szUSBC_SoftVer[24];
   short   m_sSystemType;
   short   m_sAxes[3];               // axes setup according groups
   short   m_sPoints[3];             // size of points databases
   short   m_sNumOfAxes;             // number of axes
   short   m_sGripperAxisNumber;     // gripper axis number
   short   m_sNumDIn; 			     // total number of inputs in the system
   short   m_sNumDOut;			     // total number of inputs in the system
   short   m_sNumAIn; 			     // total number of analog inputs in the system
   short   m_sNumAOut;			     // total number of analog inputs in the system
   short   m_sGripperRange;          // mm  
   short   m_sGripperType;           // MISSING_GRIPPER_TYPE or PNEUMATIC_GRIPPER_TYPE or SERVO_GRIPPER_TYPE
   short   m_sPneuGripDigOutputNumber;  // pneumatic gripper output number
   short   m_sOutStateClosedGripper; // output state for closed gripper
   short   m_sGripDuration;          // 1/10 second
   short   m_sWarnDigOutputNumber;   // warning light digital output number
   short   m_sHomingSeq[ TOTAL_AXES ];
   TCHAR   m_szDeviceID[ TOTAL_AXES + 1 ][ DEVICE_ID_LENGTH ];  // current peripherals ID string for axes 0...7
   
   ConfigData()
   {
      m_sMode =  INIT_MODE_DEFAULT;  
	  m_sNumOfAxes = 0;
      for( int i = 0; i < TOTAL_AXES; i++ )
	  {
		   m_sHomingSeq[i] = 0;
		   for( int j = 0; j < DEVICE_ID_LENGTH; j++ )
		   {
               m_szDeviceID[i][j] = 0;
		   }// end of for( int j = 0; j < DEVICE_ID_LENGTH; j++ )
	  }// end if for( int i = 0; i < TOTAL_AXES; i++ )
   }// end of ConfigData()

   const ConfigData& operator=(HardwareSetupData& ref)
   {
	   m_sSystemType = ref.m_sSystemType;
	   m_sGripperType = ref.m_sGripperType;
	   m_sPneuGripDigOutputNumber = ref.m_sPneuGripDigOutputNumber;
       m_sOutStateClosedGripper = ref.m_sOutStateClosedGripper;
	   m_sGripDuration = ref.m_sGripDuration;
	   m_sWarnDigOutputNumber = ref.m_sWarnDigOutputNumber;
	   for( int i = 0; i < TOTAL_AXES; i++ )
	   { 
		   for( int j = 0; j < DEVICE_ID_LENGTH; j++ )
		   {
               m_szDeviceID[i][j] = ref.m_szDeviceID[i][j];
		   }// end of for( int j = 0; j < DEVICE_ID_LENGTH; j++ )
	   }// end if for( int i = 0; i < TOTAL_AXES; i++ )

       short sNoDegOfFree = (m_sSystemType == ER9USBB_SYSTEM_TYPE) ? NUMBER_DEGREE_FREEDOM_ER9 : NUMBER_DEGREE_FREEDOM_ER14;
       m_sGripperAxisNumber = ((m_sGripperType == PNEUMATIC_GRIPPER_TYPE || m_sGripperType == MISSING_GRIPPER_TYPE) ? 0 : sNoDegOfFree + 1);
       m_sAxes[0] = sNoDegOfFree + ((m_sGripperAxisNumber > 0)?1:0);
       m_sAxes[2] = 0;
	   m_sAxes[1] = m_sNumOfAxes - m_sAxes[0];
       return *this;
   };// end ofConfigData& operator=(const HardwareSetupData& ref)


    HardwareSetupData GetHardwareSetupData()
	{
	   HardwareSetupData TheSetupData;

	   TheSetupData.m_sSystemType = m_sSystemType;
	   TheSetupData.m_sGripperType = m_sGripperType;
	   TheSetupData.m_sPneuGripDigOutputNumber = m_sPneuGripDigOutputNumber;
       TheSetupData.m_sOutStateClosedGripper = m_sOutStateClosedGripper;
	   TheSetupData.m_sGripDuration = m_sGripDuration;
	   TheSetupData.m_sWarnDigOutputNumber = m_sWarnDigOutputNumber;


       short sNumDegFree, sGripperAxis, sGroupB;
       GetAxesConfig( m_sSystemType, m_sGripperType, sNumDegFree,
						                              sGripperAxis, sGroupB );

	   short sNumPerih = m_sNumOfAxes - sGroupB + 1;
	   int iPeriphCounter = 0, iDeviceIDLength;

	   for( int i = 0; i < TOTAL_AXES; i++ )
	   {
		   iDeviceIDLength = 0;
		   for( int j = 0; j < DEVICE_ID_LENGTH; j++ )
		   {
               TheSetupData.m_szDeviceID[i][j] = m_szDeviceID[i][j];
			   if( m_szDeviceID[i][j] == _T('\0') )
				   break;
			   iDeviceIDLength++;
		   }// end of for( int j = 0; j < DEVICE_ID_LENGTH; j++ )
		   if( iDeviceIDLength > 0)
				iPeriphCounter++;
	   }// end if for( int i = 0; i < TOTAL_AXES; i++ )
	   if( iPeriphCounter < sNumPerih )
	   {
		   _tcscpy( TheSetupData.m_szDeviceID[ iPeriphCounter ], NOC_TEXT );
	   }// end of if( iPeriphCounter < sNumPerih )

	   return TheSetupData;
	}// end of HardwareSetupData GetHardwareSetupData()

    void GetAxesConfig( short sSystemType, short sGripperType, short &sNumDegFree,
						 short &sGripperAxis, short &sGroupB )
	{
		if ( sGripperType == PNEUMATIC_GRIPPER_TYPE || sGripperType == MISSING_GRIPPER_TYPE )
		{
			sGripperAxis = 0;
			if( sSystemType == ER9USBB_SYSTEM_TYPE )
			{
				sNumDegFree = NUMBER_DEGREE_FREEDOM_ER9;
				sGroupB = 6;
			}
			else if( sSystemType == ER14USBB_SYSTEM_TYPE )
			{
				sNumDegFree = NUMBER_DEGREE_FREEDOM_ER14; 
				sGroupB = 5;
			}
		}
		else if ( sGripperType == SERVO_GRIPPER_TYPE )
		{
			if( sSystemType == ER9USBB_SYSTEM_TYPE )
			{
				sNumDegFree = NUMBER_DEGREE_FREEDOM_ER9;
				sGripperAxis = 6;
				sGroupB = 7;
			}
			else if( sSystemType == ER14USBB_SYSTEM_TYPE )
			{
				sNumDegFree = NUMBER_DEGREE_FREEDOM_ER14; 
				sGripperAxis = 5;
				sGroupB = 6;
			}
		}
	}// end of short GetAxesConfig( short sSystemType, short sGripperType,
};// end of class ConfigData


#define MAX_WRITE_CHARS		40
#define MAX_WRITE_CHAR_POS	30
class WriteStruct
{
	public:
	char cChar;
	char szSourcePosFileName[ 257 ];
	int iQuantPosits;
	int iSourcePosit[ MAX_WRITE_CHAR_POS ];
	int iNewProgPosit[ MAX_WRITE_CHAR_POS ];
	int operator == ( const WriteStruct &rWriteStruct ) const
	{
		return ( cChar == rWriteStruct.cChar );
	}
};
#endif