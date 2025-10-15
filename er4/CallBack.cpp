// File: CallBack.cpp (console rewrite of Intelitek original)
// Date: 2025-09-25

#include <iostream>
#include <string>
#include <cstdio>
#include "CallBack.h"

#include "usbc/usbc.h"
#include "usbc/usbcdef.h"
#include "usbc/error.h"
#include "usbc/Extern.h"
//----------------------------------------------------
void MotionEnd(UCHAR *ucEndCode)
{
    if (!ucEndCode) return;
    UCHAR ucCode = *ucEndCode;

    switch (ucCode) {
        case 'A':
            std::cout << "[MotionEnd] End of Robot's motion" << std::endl;
            break;
        case 'B':
            std::cout << "[MotionEnd] End of Peripheral's motion" << std::endl;
            break;
        case 'G':
            std::cout << "[MotionEnd] End of the Gripper's motion" << std::endl;
            break;
        default:
            std::cout << "[MotionEnd] End of axis " << (int)ucCode << " motion" << std::endl;
            break;
    }
}

void MotionStart(CMotionStart *pCMotionStart) {
    if (!pCMotionStart) return;
    UCHAR ucCode = pCMotionStart->ucGroup;

    switch (ucCode) {
        case 'A':
            std::cout << "[MotionStart] Robot's motion started"
                      << " (Speed=" << pCMotionStart->dSpeed
                      << ", Time=" << pCMotionStart->dTime << ")\n";
            break;
        case 'B':
            std::cout << "[MotionStart] Peripheral's motion started"
                      << " (Speed=" << pCMotionStart->dSpeed
                      << ", Time=" << pCMotionStart->dTime << ")\n";
            break;
        case 'G':
            std::cout << "[MotionStart] Gripper's motion started"
                      << " (Speed=" << pCMotionStart->dSpeed
                      << ", Time=" << pCMotionStart->dTime << ")\n";
            break;
        default:
            std::cout << "[MotionStart] Axis " << static_cast<int>(ucCode)
                      << " motion started"
                      << " (Speed=" << pCMotionStart->dSpeed
                      << ", Time=" << pCMotionStart->dTime << ")\n";
            break;
    }
}


//-----------------------------------------------
void InitEnd(ConfigData *pTheConfigData)
{
    std::cout << "[InitEnd] Initialization finished" << std::endl;
    if (pTheConfigData) {
        std::cout << "  Mode: " << pTheConfigData->m_sMode
                  << "  Controller type: " << pTheConfigData->m_sContrType
                  << "  Axes: " << pTheConfigData->m_sNumOfAxes << std::endl;
    }
}

//--------------------------------------------------------------
void AxisControl(UINT *uiBitmap)
{
    if (!uiBitmap) return;
    UINT con = *uiBitmap;

    if (con != 255) {
        std::cout << "[AxisControl] Control OFF" << std::endl;
    } else {
        std::cout << "[AxisControl] Control ON" << std::endl;
    }
}

//--------------------------------------------------------------

// Called during homing sequence
void HomingNotif(UCHAR *ucNotifCode) {
    if (!ucNotifCode) return;

    UCHAR code = *ucNotifCode;
    switch (code) {
        case HOME_NOTIF_START:
            std::cout << "[HomingNotif] Homing started" << std::endl;
            break;
        case HOME_NOTIF_FINISH:
            std::cout << "[HomingNotif] Homing finished" << std::endl;
            break;
        default:
            std::cout << "[HomingNotif] Axis " << (int)code 
                      << " homing in progress" << std::endl;
            break;
    }
}

// Called whenever digital inputs change
void ViewWatchDigitInputs(DigitalIO *pDigitalIO) {
    if (!pDigitalIO) return;

    ULONG status = pDigitalIO->GetStatus();
    ULONG changes = pDigitalIO->GetChanges();

    std::cout << "[DigitalInputs] Status bitmap = 0x" 
              << std::hex << status 
              << "  Changes bitmap = 0x" 
              << std::hex << changes 
              << std::dec << std::endl;

    // Example: print which bits are ON
    for (int i = 0; i < 32; i++) {
        BOOL bitChanged, bitState;
        if (pDigitalIO->GetDigitalIOStatus(bitState, bitChanged, i)) {
            if (bitChanged) {
                std::cout << "  Input[" << i << "] = " << (bitState ? "ON" : "OFF") << std::endl;
            }
        }
    }
}

// Callback for ShowXYZ
void ViewWatchXYZ(RobotData TheXYZ) {
    if (!TheXYZ) {
        std::cerr << "[Callback: XYZ] Null data received\n";
        return;
    }

    // The array length depends on TOTAL_AXES (usually 6 for ER4U).
    std::cout << "[Callback: XYZ]";
    for (int i = 0; i < TOTAL_AXES; i++) {
        std::cout << " Axis" << i << "=" << TheXYZ[i];
    }
    std::cout << std::endl;
}


void ViewShowTorque(long* lTorque) {
    if (lTorque) {
        std::cout << "[Callback: Torque] value=" << *lTorque << std::endl;
    } else {
        std::cout << "[Callback: Torque] (null)" << std::endl;
    }
}


//--------------------------------------------------------------
void ErrorMessage(ErrorInfo *pTheErrorInfo)
{
    if (!pTheErrorInfo) {
        std::cerr << "[ErrorMessage] Null pointer!" << std::endl;
        return;
    }

    char szWork[512], szTemp[512];

    switch (pTheErrorInfo->lNumber)
    {
        case ERR_EMERG_ON:
            std::cerr << "[Error] Emergency ON" << std::endl;
            return;

        case ERR_EMERG_OFF:
            std::cerr << "[Error] Emergency OFF" << std::endl;
            return;

        case ERR_HOME_ABORTED:
            sprintf(szWork, "(%ld) Homing aborted by user", pTheErrorInfo->lNumber);
            break;

        case ERR_INVPAR:
            sprintf(szWork, "(%ld) Invalid parameter in file", pTheErrorInfo->lNumber);
            break;

        case ERR_NOT_RESPOND:
            sprintf(szWork, "(%ld) Controller is not responding", pTheErrorInfo->lNumber);
            std::cerr << szWork << std::endl;
            return;

        case ERR_TRCK:
            sprintf(szTemp,
                    "Position error too large or impact occurred (Axis %d)",
                    pTheErrorInfo->cAxis);
            sprintf(szWork, "(%ld) %s. Control is OFF", pTheErrorInfo->lNumber, szTemp);
            break;

        case ERR_COFF:
            sprintf(szWork, "(%ld) Control disabled", pTheErrorInfo->lNumber);
            break;

        case ERR_ROBOT_HM_ND:
            sprintf(szWork, "(%ld) Robot has not been homed", pTheErrorInfo->lNumber);
            break;

        case KIN_ALPHA:
            sprintf(szWork, "(%ld) Kinematics alpha error (outside workspace)", pTheErrorInfo->lNumber);
            break;

        case KIN_BETA:
            sprintf(szWork, "(%ld) Kinematics beta error (outside workspace)", pTheErrorInfo->lNumber);
            break;

        case ERR_XYZ_INV:
        case ERR_JNT_INV:
            sprintf(szWork, "(%ld) Position is not in workspace", pTheErrorInfo->lNumber);
            break;

        case ERR_ENC_INV:
            sprintf(szWork, "(%ld) Position not in encoder workspace", pTheErrorInfo->lNumber);
            break;

        case ERR_MOVP:
            sprintf(szWork, "(%ld) Motion already in progress", pTheErrorInfo->lNumber);
            break;

        case ERR_SPEED:
            sprintf(szWork, "(%ld) Excessive speed required", pTheErrorInfo->lNumber);
            break;

        case ERR_ACCL:
            sprintf(szWork, "(%ld) Excessive acceleration required", pTheErrorInfo->lNumber);
            break;

        case ERR_MDUR:
            sprintf(szWork, "(%ld) Invalid movement duration", pTheErrorInfo->lNumber);
            break;

        case ERR_TIME_PAR:
            sprintf(szWork, "(%ld) Invalid time parameter", pTheErrorInfo->lNumber);
            break;

        case ERR_VELO_PAR:
            sprintf(szWork, "(%ld) Invalid velocity parameter", pTheErrorInfo->lNumber);
            break;

        case ERR_A_PAR:
            sprintf(szWork, "(%ld) Invalid acceleration parameter", pTheErrorInfo->lNumber);
            break;

        case ERR_AA_PAR:
            sprintf(szWork, "(%ld) Invalid accel-increase parameter", pTheErrorInfo->lNumber);
            break;

        case ERR_SKIN:
            sprintf(szWork, "(%ld) Cannot execute specified path", pTheErrorInfo->lNumber);
            break;

        case ERR_GRP_INV:
            sprintf(szWork, "(%ld) Invalid group", pTheErrorInfo->lNumber);
            break;

        case KIN_CFG:
            sprintf(szWork, "(%ld) Kinematics configuration invalid", pTheErrorInfo->lNumber);
            break;

        case ERR_B_INV:
            sprintf(szWork, "(%ld) Position not in peripheral workspace", pTheErrorInfo->lNumber);
            break;

        case ERR_CCHANGE:
            sprintf(szWork, "(%ld) Axis 3 angle prevents movement", pTheErrorInfo->lNumber);
            break;

        case ERR_AXTYPE:
            sprintf(szTemp, "Invalid axis type (Axis %d)", pTheErrorInfo->cAxis);
            sprintf(szWork, "(%ld) %s", pTheErrorInfo->lNumber, szTemp);
            break;

        default:
            if (pTheErrorInfo->cAxis == 0) {
                sprintf(szWork, "(%ld) %s", pTheErrorInfo->lNumber, pTheErrorInfo->cOptional);
            } else {
                sprintf(szWork, "(%ld) Axis %d %s",
                        pTheErrorInfo->lNumber,
                        pTheErrorInfo->cAxis,
                        pTheErrorInfo->cOptional);
            }
            break;
    }

    std::cerr << szWork << std::endl;
}
