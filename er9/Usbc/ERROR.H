////////////////////////////////////////////////////////////////////////
//
//      Error.h
//
//	Definitions of error messages of the er_1 program
//	Here only the error numbers are defined the text of each
//	message is given ine Err.cpp
//
//	Date of creation: 27. June 1993
//
//	Author: Mirko B.    Modified by Shimon.  Date: 24-SEP-2001
//
//	Company: Eshed Robotec R&D
//
/////////////////////////////////////////////////////////////////////////
#if !defined( _ERROR_H_ )
#define _ERROR_H_

#define OK					0
#define KIN_OK    	   0
#define ERR_IO			   1	       //"FATAL: Invalid status of motion ecountered"
#define ERR_TR_SND	   2	       //"FATAL: Position error during or impact occured unable to reach PIC"
#define ERR_TCK_SND	   3	       //"FATAL: Unable to communicte with PIC"
#define ERR_REE		   4	       //"FATAL: Reentrance occured in the RTC driven procedure"
#define ERR_SKIN		   5	       //"FATAL: Singular point encountered or error in robot kinematics parameters"
#define ERR_MST		   6	       //"FATAL: Motion status invalid"
#define ERR_MEM         7			 //"Memory problems"

#define KIN_GEAR        10
#define KIN_CFG         11
#define KIN_CCFG        12

#define ERR_NOT_RESPOND         20			  // "Controller is not responding"
#define ERR_ADD		     30			  // "Invalid board address"
#define ERR_ADC         40			  // A/D conversion error

#define ERR_PNR         50           // "PIC not ready"
#define ERR_ESTK        51           // "The message doesn't come out of the stack"
#define ERR_FLL	      52 	        //"Full"
#define ERR_MBFF	      53
#define ERR_SLCT	      54
#define ERR_LRG	      55
#define ERR_IRST        56           // Invalid reset

#define ERR_SST         60           // "Unable to send string"

// Up to this error code are FATAL ERRORS *********************************
//-------------------------------------------------------------------------
#define ERR_FATAL		   200


#define ERR_TRCK		   201				//" Position error during the motion is grater then allowed or impact has occured"
#define ERR_THR		   202				//" Thermic overload
#define ERR_PWOFF       203           //" The PB is off "
#define ERR_EMERG_ON		   300				//" Emergency ON!!
#define ERR_EMERG_OFF		   301				//" Emergency OFF!!

// Up to this error code are ROBOT ERROS *********************************
//-------------------------------------------------------------------------
#define ERR_ROBOT		   500  //" Position error during the motion is grater then allowed or impact has occured"

#define ERR_PB			   511   //" Power Box error
#define ERR_PB_UNR  	   512
#define ERR_PB_OVR  	   513
#define ERR_PB_LEN  	   514
#define ERR_PB_NUM  	   515
#define ERR_PB_BFOVR    516
#define ERR_PB_OCURR    517


#define ERR_PF_NF       522           // "%s:(Path or file not found)"
#define ERR_TOO_F       523           // "(Too many open files)"
#define ERR_IN_ACC      524           // "(Invalid access code)"
#define ERR_CLOSE       525           // "Unable to close file"
#define ERR_PER_DEN     527           // "Permission denied"
#define ERR_BAD_FN      528           // "Bad file number"
#define ERR_PAR_WR      529           // "Error while writing parameters"
#define ERR_PAR_RE      530           // "Error while reading parameters"
#define ERR_UK_ERR      531	        //"%s : Unknown error option"
#define ERR_INVNM		   532	        // Invalid name
#define ERR_INVPAR	   533	        // Invalid parameter
#define ER_BK_LNL  	   534			  // Too long line
#define ERR_NO_OPEN     535			  // File not opened
#define ERR_NO_CLOSE    536			  // File not closed

#define ERR_INVP        550			 //  "Invalid points of the arc "
#define ERR_ROBT        551			 //  "Invalid robot type "

#define ERR_MOD          560         // "Invalid mode"
#define ERR_HT			 561	       //"Time for homing elapsed"
#define ERR_IC			 562	       //"Invalid or unreckognized command"
#define ERR_HNF		     563	       //"Home switch not found"
#define ERR_PL			 564	       //"Plus limit"
#define ERR_ML           565         //"Minus limit"
#define ERR_STCK	     566         // Stack Full
#define ERR_IMM          567			  // Immediate mode
#define ERR_NOT_CONNECT  568		 // Peripheral axis is not connected. Shimon
#define ERR_HOME_ABORTED 569		 // Homing aborted by user.

#define ERR_A_BIG       580         // "Axis number too big"
#define ERR_A_PAR	      581	       //"Invalid acceleration parameter"
#define ERR_AA_PAR      582	       //"Invalid parmeter of increase of acceleration"
#define ERR_VELO_PAR    583	       //"Invalid velocity"
#define ERR_STP	      584	       //"Unable to stop motion"
#define ERR_MDUR        586         // "Invalid motion duration"
#define ERR_VEL_Z	      587	       // "Zero velocity!"
#define ERR_MTYP	      588	       //"Invalid motion type option!"
#define ERR_CTYP	      589	       //"Invalid coordinate type option!"
#define ERR_IWM	      590	       //"Unable to initialize parameters while robot is moving!"

#define ERR_INDAT 	   600	 		 //"Invalid data"
#define ERR_TOO_FEW     601        //"Too few arguments"
#define ERR_GRP_NSP     602        //"Unsupported group"
#define ERR_AXNUM       603			 //"Invalid number of axes"

#define ERR_GRP_B	      604	       // "Invalid gripper and group B values"
#define ERR_INIT        605          // "INIT"
#define ERR_SEM_T       607          //"Invalid sample time"
#define ERR_STRT        608 	       //"RTC was not started!"

#define CMM_ERR_INVDESC	 701
#define CMM_ERR_INVOPT	 702
#define CMM_ERR_INVAX	 703
#define CMM_ERR_INVGRP	 704
#define CMM_ERR_INVIND	 705
#define CMM_ERR_INVNAM   706
#define CMM_ERR_LNGMSS   708
#define CMM_ERR_NOTIN    710
#define CMM_ERR_TIM		 711
#define CMM_ERR_MLON		 712
#define CMM_ERR_MFLL		 714
#define CMM_ERR_NRED		 715
#define CMM_ERR_UEXP		 716
#define CMM_ERR_UANS		 717
#define CMM_UNASS			 718
#define COMM_LOCK			 719
#define COMM_NOTTP		 721
#define CMM_UNKNOWN_SOURCE  750
#define CMM_ERR_INVCHN	 751
#define CMM_CTRL_UNKN    742

// Up to this error code are SYSTEM ERRORS *********************************
//-------------------------------------------------------------------------
#define ERR_SYSTEM	     900       //"Position error during the motion is grater then allowed or impact has occured"

#define ERR_MAN_HM_ND     901	       //"Home not done"
#define ERR_SINGU	      902	       //"Manual motion not allowed (singularity)"
#define ERR_COFF	      903			 // "Control disabled"
#define ERR_INCOO	      904	       // "Invalid coordinate type!"
#define ERR_INV         905	       // "Given point is not in the workspace of the robot"
#define ERR_ENC_INV     906	       // "Given point is not in the workspace of the encoders"
#define ERR_JNT_INV     907	       //"Given point is not in the workspace of the joints"
#define ERR_XYZ_INV     908	       //"Given point is not in the workspace of the Cartesian space"
#define ERR_TIME_PAR	   909	       //"Invalid time duration of the movement"
#define ERR_AXTYPE	   910			 // "Invalid axis tytpe"
#define ERR_MOVP	      911			 // "Motion in progress"
#define ERR_CCHANGE     912	       //"Configuration change"
#define ERR_SPEED       913         // "Speed"
#define ERR_ACCL        914         // "Acceleration"
#define ERR_SPC	      915	       //"Not enaugh space to store all points"
#define ERR_RCR		   916	       //"Recursion!"
#define ERR_ORG		   917	       //"Orign"
#define ERR_PDEF        918			 //"Point already defined"
#define ERR_PINV        919			 //"Invalid point"
#define ERR_LEN         920			 //len
#define ERR_VEC_BRK     921			 //Vector broken
#define ERR_VEC_GRP     922			 //Vectors of different groups not allwed
#define ERR_PNAM        923         //"Invalid point name"
#define ERR_GRP_INV     924         //"iNVALID GROUP"
#define ERR_UNASS       925			 //"Unassigned point"
#define ERR_NO_VEC      926         //"Not a vector type"
#define ERR_PICVER      927			 // Invalid version
#define ERR_VER         928	       // "Invalid version number"
#define ERR_PROC        929	       //"Procents must be between 0.0 and 1.0"
#define ERR_B_INV       930	       // "Given point is not in the workspace of the B"
#define ERR_C_INV       931	       //"Given point is not in the workspace of the C"
#define ERR_ION         932	       //"Invalid I/O number "
#define ERR_IOV         933 		    //"Invalid I/O value  "
#define ERR_IOD         934			 //"I/O not disabled"
#define ERR_MWRK        935			 //"The motion is out of the robot workspace"
#define ERR_IRQ         936			 //"Invalid IRQ number."  //  Shimon

#define ERR_ROBOT_HM_ND 937          // "Robot home not done"   //  Shimon
#define ERR_AXIS_HM_ND  938          // "Peripheral axis home not done" //  Shimon

#define ERR_UNASS_ROBOT   939			 //"Undefined robot position"   // Shimon
#define ERR_UNASS_PERIPH  940			 //"Undefined peripheral position" // Shimon

#define ERR_NOT_MAIL     941  // "(%d) Cannot make mailslot '%s'"  // Shimon
#define ERR_WRITE_MAIL   942  //"(%d) Cannot write mailslot '%s'"  // Shimon    New


// Welding
#define ERR_WRONG_POS_TYPE  943   // "Wrong type of position:  %d"
#define ERR_UNDEF_POS       944   // "Undefined position: %d"
#define ERR_CHAR_BASE_POS   945   // "No %d  Character: %c  Base position: %d"
#define ERR_CART_WORKSPACE  946   // "Position  %d  is not in the Cartesian workspace!"
#define ERR_REL_POS         947   // "Relative: X:%5.1f  Y:%5.1f  Z:%5.1f  P:%5.1f  R:%5.1f"
#define ERR_ABS_POS         948   // "Absolute: X:%5.1f  Y:%5.1f  Z:%5.1f  P:%5.1f  R:%5.1f"
#define ERR_CANNOT_WRITE_CHAR 949  // Robot cannot reach position required for writing character: %c   character # %d
#define ERR_CHAR_TEMPL_LIB     950  // Error in character template library./nContact your product dealer.

#define COMM_TEACH	   960
#define KIN_ZERO        961
#define KIN_BETA        962
#define KIN_ALPHA       963

#define TP_TEACH        970
#define TP_AUTO         971

#define ERR_PERIPH_CONFIG 973     // Peripherals positions are not suitable for peripherals configuration.
#define ERR_DELETE_POSIT  974     // Cannot delete position "N". It is the base position for relative position "M".

// Up to this error code are USER ERRORS *********************************
//-------------------------------------------------------------------------
#define ERR_USER	      1000	      


#define ERR_MAX         1500
#define MAXERR 		   3000

// For Desktop application only
#define DSK_ERRORS      CMM_CTRL_UNKN+500
#define DSK_CFG 		   DSK_ERRORS+1
#define DSK_CFG_ACCEPT  DSK_ERRORS+2
#define DSK_CFG_OPEN    DSK_ERRORS+3
#define DSK_CFG_NUM     DSK_ERRORS+4
#define DSK_MOVE		   DSK_ERRORS+5
#define DSK_POS_SPEC	   DSK_ERRORS+10
#define DSK_POSM_SPEC   DSK_ERRORS+11
#define DSK_POSTM_SPEC  DSK_ERRORS+12
#define DSK_POS_IND	   DSK_ERRORS+13
#define DSK_NOPEN		   DSK_ERRORS+14

///////////////////////////////////////////////////////////////////////////
// Text of the messages that are usually a fatal messages
//

// #define WxxC  				MAXERR+1   // Mirko

#define WPCC_NAME      MAXERR+1
#define WACLC_NAME     MAXERR+2
#define WER3C_NAME     MAXERR+3

#define wc_ERR          MAXERR+4
#define wc_MER				MAXERR+5
#define wc_OO           MAXERR+6
#define wc_TUN          MAXERR+7
#define wc_VER          MAXERR+8
#define wc_MEM          MAXERR+9
#define wc_TIM          MAXERR+10
#define wc_WPCC         MAXERR+11
#define wc_CHK          MAXERR+12
#define wc_ATA          MAXERR+13
#define wc_CHNOAP       MAXERR+14
#define wc_UOP          MAXERR+15
#define wc_NOSEL        MAXERR+16
#define wc_WxxC         MAXERR+17
#define wc_UNDEF        MAXERR+18

#define IDS_NOTCONNECT_FN_AXIS  MAXERR+119
#define IDS_INCORRECT_SELECT    MAXERR+120
#define IDS_CONV_FN_AXIS        MAXERR+121
#define IDS_SPEED_CNTR_CONV     MAXERR+122


#define TP_ERROR			MAXERR+500

#define  ERR_MAN_HM_ND_STR 		TP_ERROR+1
#define  ERR_SINGU_STR           TP_ERROR+2
#define  ERR_COFF_STR            TP_ERROR+3
#define  ERR_INCOO_STR           TP_ERROR+4
#define  ERR_INV_STR             TP_ERROR+5
#define  ERR_ENC_INV_STR         TP_ERROR+6
#define  ERR_JNT_INV_STR         TP_ERROR+7
#define  ERR_XYZ_INV_STR         TP_ERROR+8
#define  ERR_MWRK_STR            TP_ERROR+9
#define  ERR_B_INV_STR           TP_ERROR+10
#define  ERR_C_INV_STR           TP_ERROR+11
#define  ERR_AXTYPE_STR          TP_ERROR+12
#define  ERR_MOVP_STR            TP_ERROR+13
#define  ERR_CCHANGE_STR         TP_ERROR+14
#define  ERR_SPEED_STR           TP_ERROR+15
#define  ERR_ACCL_STR            TP_ERROR+16
#define  ERR_PINV_STR            TP_ERROR+17
#define  ERR_UNASS_STR           TP_ERROR+18
#define  ERR_NO_VEC_STR          TP_ERROR+19
#define  ERR_TRCK_STR            TP_ERROR+20
#define  ERR_THR_STR             TP_ERROR+21
#define  ERR_EMERG_STR           TP_ERROR+22
#define  KIN_ZERO_STR            TP_ERROR+23
#define  KIN_BETA_STR            TP_ERROR+24
#define  KIN_ALPHA_STR           TP_ERROR+25
#define  COMM_TEACH_STR          TP_ERROR+26
#define  TP_ERR_STR              TP_ERROR+27
#define  TP_FATAL_STR            TP_ERROR+28
#define  TP_SYSTEM_STR           TP_ERROR+29
#define  CMM_ERR_INVNAM_STR      TP_ERROR+30

#define DOSERROR						MAXERR+1000
#define ERROROR_EZERO    DOSERROR+0      /* Error 0                  */
#define ERROR_EINVFNC  DOSERROR+1      /* Invalid function number  */
#define ERROR_ENOFILE  DOSERROR+2      /* File not found,   No such file or directory*/
#define ERROR_ENOPATH  DOSERROR+3      /* Path not found           */
#define ERROR_EMFILE   DOSERROR+4      /* Too many open files      */
#define ERROR_EACCES   DOSERROR+5      /* Permission denied        */
#define ERROR_EBADF    DOSERROR+6      /* Bad file number          */
#define ERROR_ECONTR   DOSERROR+7      /* Memory blocks destroyed  */
#define ERROR_ENOMEM   DOSERROR+8      /* Not enough core          */
#define ERROR_EINVMEM  DOSERROR+9      /* Invalid memory block address */
#define ERROR_EINVENV  DOSERROR+10      /* Invalid environment      */
#define ERROR_EINVFMT  DOSERROR+11      /* Invalid format           */
#define ERROR_EINVACC  DOSERROR+12      /* Invalid access code      */
#define ERROR_EINVDAT  DOSERROR+13      /* Invalid data             */
#define ERROR_EINVDRV  DOSERROR+15      /* Invalid drive specified  No such device */
#define ERROR_ECURDIR  DOSERROR+16      /* Attempt to remove CurDir */
#define ERROR_ENOTSAM  DOSERROR+17      /* Not same device          */
#define ERROR_ENMFILE  DOSERROR+18      /* No more files            */
#define ERROR_EFAULT   DOSERROR+14      /* Unknown error            */
#define ERROR_EINVAL   DOSERROR+19      /* Invalid argument         */
#define ERROR_E2BIG    DOSERROR+20      /* Arg list too long        */
#define ERROR_ENOEXEC  DOSERROR+21      /* Exec format error        */
#define ERROR_EXDEV    DOSERROR+22      /* Cross-device link        */
#define ERROR_ENFILE   DOSERROR+23      /* Too many open files      */
#define ERROR_ECHILD   DOSERROR+24      /* No child process         */
#define ERROR_ENOTTY   DOSERROR+25      /* UNIX - not MSDOS         */
#define ERROR_ETXTBSY  DOSERROR+26      /* UNIX - not MSDOS         */
#define ERROR_EFBIG    DOSERROR+27      /* UNIX - not MSDOS         */
#define ERROR_ENOSPC   DOSERROR+28      /* No space left on device  */
#define ERROR_ESPIPE   DOSERROR+29      /* Illegal seek             */
#define ERROR_EROFS    DOSERROR+30      /* Read-only file system    */
#define ERROR_EMLINK   DOSERROR+31      /* UNIX - not MSDOS         */
#define ERROR_EPIPE    DOSERROR+32      /* Broken pipe              */
#define ERROR_EDOM     DOSERROR+33      /* Math argument            */
#define ERROR_ERANGE   DOSERROR+34      /* Result too large         */
#define ERROR_EEXIST   DOSERROR+35      /* File already exists      */
#define ERROR_EDEADLOCK DOSERROR+36    /* Locking violation        */
#define ERROR_EPERM   DOSERROR+37      /* Operation not permitted  */
#define ERROR_ESRCH   DOSERROR+38      /* UNIX - not MSDOS         */
#define ERROR_EINTR   DOSERROR+39      /* Interrupted function call */
#define ERROR_EIO     DOSERROR+40      /* Input/output error       */
#define ERROR_ENXIO   DOSERROR+41      /* No such device or address */
#define ERROR_EAGAIN  DOSERROR+42      /* Resource temporarily unavailable */
#define ERROR_ENOTBLK DOSERROR+43      /* UNIX - not MSDOS         */
#define ERROR_EBUSY   DOSERROR+44      /* Resource busy            */
#define ERROR_ENOTDIR DOSERROR+45      /* UNIX - not MSDOS         */
#define ERROR_EISDIR  DOSERROR+46      /* UNIX - not MSDOS         */
#define ERROR_EUCLEAN DOSERROR+47      /* UNIX - not MSDOS         */


/////////////////////////////////////////////////////////////////////////
// Offset for the network error strings
#define NET_ERROR_BASE (MAXERR+10000)

// Offset for the COMM_PORT_ERRORs.
#define COMM_PORT_ERROR_BASE (MAXERR+15000)

//   COMM_PORT_UNKNOWN  Unknown error.
#define COMM_PORT_UNKNOWN (COMM_PORT_ERROR_BASE+25)

//  IE_BADID The device identifier is invalid or unsupported.
#define COMM_PORT_IE_BADID	(COMM_PORT_ERROR_BASE+1)
// IE_BAUDRATE	 The device's baud rate is unsupported.
#define COMM_PORT_IE_BAUDRATE	(COMM_PORT_ERROR_BASE+12)
// IE_BYTESIZE	 The specified byte size is invalid.
#define COMM_PORT_IE_BYTESIZE	(COMM_PORT_ERROR_BASE+11)
// IE_DEFAULT	 The default parameters are in error.
#define COMM_PORT_IE_DEFAULT	 (COMM_PORT_ERROR_BASE+5)
//IE_HARDWARE	 The hardware is not available (is locked by another device).
#define COMM_PORT_IE_HARDWARE (COMM_PORT_ERROR_BASE+10)
// IE_MEMORY	 The function cannot allocate the queues.
#define COMM_PORT_IE_MEMORY  (COMM_PORT_ERROR_BASE+4)
// IE_NOPEN	    The device is not open.
#define COMM_PORT_IE_NOPEN	(COMM_PORT_ERROR_BASE+3)
// IE_OPEN	    The device is already open.
#define COMM_PORT_IE_OPEN	(COMM_PORT_ERROR_BASE+2)

#define COMM_PORT_LINESET_SECT     (COMM_PORT_ERROR_BASE+30)
#define COMM_PORT_PORT_ENTRY       (COMM_PORT_ERROR_BASE+31)
#define COMM_PORT_BAUD_ENTRY       (COMM_PORT_ERROR_BASE+32)
#define COMM_PORT_DATABITS_ENTRY   (COMM_PORT_ERROR_BASE+33)
#define COMM_PORT_STOPBITS_ENTRY   (COMM_PORT_ERROR_BASE+34)
#define COMM_PORT_PARITY_ENTRY     (COMM_PORT_ERROR_BASE+35)
#define COMM_PORT_XONXOFF_ENTRY    (COMM_PORT_ERROR_BASE+36)

#define COMM_PORT_UNEXPECTED_DATA   (COMM_PORT_ERROR_BASE+37)



#define ER3_ERROR_BASE (MAXERR+17000)
#define FATAL_INCORRECT_RESDLL        ER3_ERROR_BASE+1
#define ER3_INI_FILE_NAME             ER3_ERROR_BASE+2
#define ER3_PARAM_AXIS_SECT           ER3_ERROR_BASE+3
#define ER3_MAXSPEED_AXIS_ENTRY       ER3_ERROR_BASE+5
#define ER3_MOTORSTEPS_AXIS_ENTRY     ER3_ERROR_BASE+7
#define ER3_ACCELTIME_AXIS_ENTRY      ER3_ERROR_BASE+10
#define ER3_MANUALENCPLUS_AXIS_ENTRY  ER3_ERROR_BASE+12
#define ER3_MANUALENCMINUS_AXIS_ENTRY ER3_ERROR_BASE+15
#define ER3_ENCTORELEASE_AXIS_ENTRY ER3_ERROR_BASE+18

#define ER3_GRIPPER_CANNOT            ER3_ERROR_BASE+20
#define ER3_MOTOR_ERROR               ER3_ERROR_BASE+21
#define ER3_CONTR_NOT_RESPOND         ER3_ERROR_BASE+22

#endif