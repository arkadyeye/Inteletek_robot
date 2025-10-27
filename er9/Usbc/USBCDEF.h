// File: USBCDEF.h                                 Date: 23-JUN-2003


#if !defined( _USBCDEF_H_INCLUDED_ )
#define _USBCDEF_H_INCLUDED_


#define   TOTAL_AXES 8
#define   TOTAL_DIGITAL_IO 32
#define   TOTAL_ANALOG_INP  4
#define   TOTAL_ANALOG_OUT  2

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
#define ER14_SYSTEM_TYPE    140
#define ER14USB_SYSTEM_TYPE 141

#define ASRS36USB_SYSTEM_TYPE       36 
#define ASRS2_36USB_SYSTEM_TYPE    236 


#define ER2USB_SYSTEM_NAME _T("ER-2u")
#define ER4USB_SYSTEM_NAME _T("ER-4u")
#define ER5P_SYSTEM_NAME    _T("ER-Vplus")
#define ER7_SYSTEM_NAME    _T("ER-7")
#define ER9_SYSTEM_NAME    _T("ER-9")
#define ER9USB_SYSTEM_NAME _T("ER-9u")
#define ER14_SYSTEM_NAME    _T("ER-14")

#define ASRS36USB_SYSTEM_NAME   _T("ASRS-36")
#define ASRS2_36USB_SYSTEM_NAME _T("ASRS-2*36")


#define NOC_TEXT    _T("NOC")
//---------------- Initialization status -----------------------------
#define INIT_STATUS_TRANSIT 0
#define INIT_STATUS_ONLINE  1
#define INIT_STATUS_SIMUL   2
#define INIT_STATUS_OFFLINE 3 

class ConfigData
{
public:
   short   m_sMode;
   short   m_sType[TOTAL_AXES];       // axis types
   TCHAR   m_szUSBC_SoftVer[24];
   short   m_sContrType;
   short   m_sAxes[3];               // axes setup according groups
   short   m_sPoints[3];             // size of points databases
   short   m_sNumOfAxes;             // number of axes
   short   m_sGripper;               // gripper
   short   m_sNumDIn; 			     // total number of inputs in the system
   short   m_sNumDOut;			     // total number of inputs in the system
   short   m_sNumAIn; 			     // total number of analog inputs in the system
   short   m_sNumAOut;			     // total number of analog inputs in the system
   short   m_sGripperRange;          // mm  
   TCHAR   m_szDeviceID1[ 16 ];      // Current peripheral ID string
   TCHAR   m_szDeviceID2[ 16 ];      // Current peripheral ID string

   ConfigData()
   {
      m_sMode =  INIT_MODE_DEFAULT;  
	  m_sNumOfAxes = 0;
   }
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