#include "RobotController.h"
#include <iostream>

RobotController::RobotController() : initialized(false) {}

RobotController::~RobotController() {
    if (initialized) {
        shutdown();
    }
}

//--------------------  Configuration Functions ------------------------

bool RobotController::init() {
    std::cout << "[RobotController] Initializing robot..." << std::endl;

    // Use InitEnd and ErrorMessage from CallBack.cpp
    if (Initialization(INIT_MODE_ONLINE,
                          ER4USB_SYSTEM_TYPE,
                          (CallBackFun)&InitEnd,
                          (CallBackFun)&ErrorMessage)) {
        initialized = true;
        return true;
    }
    return false;
}

void RobotController::shutdown() {
    std::cout << "[RobotController] Shutting down robot." << std::endl;
    CloseUSBC();
    initialized = false;
}

bool RobotController::isEmergency() {
    BOOL ok = IsEmergency();
    std::cout << "[RobotController] IsEmergency = " << (ok ? "YES" : "NO") << "\n";
    return ok == TRUE;
}

bool RobotController::isTeachMode() {
    BOOL ok = IsTeachMode();
    std::cout << "[RobotController] IsTeachMode = " << (ok ? "YES" : "NO") << "\n";
    return ok == TRUE;
}

bool RobotController::isOnlineOk() {
    BOOL ok = IsOnLineOk();
    std::cout << "[RobotController] IsOnLineOk = " << (ok ? "YES" : "NO") << "\n";
    return ok == TRUE;
}

bool RobotController::getConfig() {
    ConfigData cfg;
    BOOL ok = GetConfig(cfg);
    if (!ok) {
        std::cerr << "[RobotController] GetConfig failed\n";
        return false;
    }

    std::cout << "[RobotController] Configuration:\n";
    std::cout << "  Mode: " << cfg.m_sMode << "\n";
    std::cout << "  Controller Type: " << cfg.m_sContrType << "\n";
    std::cout << "  Number of axes: " << cfg.m_sNumOfAxes << "\n";
    std::cout << "  Gripper: " << cfg.m_sGripper 
              << " (Range: " << cfg.m_sGripperRange << " mm)\n";
    std::cout << "  Digital In: " << cfg.m_sNumDIn 
              << "  Digital Out: " << cfg.m_sNumDOut << "\n";
    std::cout << "  Analog In: " << cfg.m_sNumAIn 
              << "  Analog Out: " << cfg.m_sNumAOut << "\n";
    std::wcout << L"  Software Ver: " << cfg.m_szUSBC_SoftVer << L"\n";
    std::wcout << L"  DeviceID1: " << cfg.m_szDeviceID1 
               << L"  DeviceID2: " << cfg.m_szDeviceID2 << L"\n";

    std::cout << "  Axes per group: [" 
              << cfg.m_sAxes[0] << ", "
              << cfg.m_sAxes[1] << ", "
              << cfg.m_sAxes[2] << "]\n";

    std::cout << "  Points per group: [" 
              << cfg.m_sPoints[0] << ", "
              << cfg.m_sPoints[1] << ", "
              << cfg.m_sPoints[2] << "]\n";

    std::cout << "  Axis types: ";
    for (int i = 0; i < TOTAL_AXES; i++) {
        std::cout << cfg.m_sType[i] << " ";
    }
    std::cout << "\n";

    return true;
}

short RobotController::getMode()
{
    return GetMode();   // direct passthrough to DLL
}

//-------------------- End of Configuration Functions ------------------------

//--------------------------- Movement Functions ------------------------

bool RobotController::enterManual(short manualType) {
    return EnterManual(manualType) == TRUE;
}

bool RobotController::moveManual(UCHAR axis, long velocity) {
    return MoveManual(axis, velocity) == TRUE;
}

bool RobotController::closeManual() {
    return CloseManual() == TRUE;
}

bool RobotController::move(short mode,
                           const TCHAR* vectorName, short pointNumber,
                           const TCHAR* vectorNameB, short pointNumberB) {
#ifdef UNICODE
    char nameA[64], nameB[64];
    wcstombs(nameA, vectorName, 63);
    nameA[63] = 0;

    char* bPtr = nullptr;
    if (vectorNameB) {
        wcstombs(nameB, vectorNameB, 63);
        nameB[63] = 0;
        bPtr = nameB;
    }
#else
    const char* nameA = vectorName;
    const char* bPtr  = vectorNameB;
#endif

    BOOL ok = FALSE;
    if (mode == 0) { // joint
        ok = MoveJoint((char*)nameA, pointNumber, (char*)bPtr, pointNumberB);
    } else if (mode == 1) { // linear
        ok = MoveLinear((char*)nameA, pointNumber, (char*)bPtr, pointNumberB);
    } else {
        std::cerr << "[RobotController] Invalid move mode: " << mode << std::endl;
        return false;
    }

    if (!ok) {
        std::cerr << "[RobotController] Move "
                  << (mode == 0 ? "Joint" : "Linear")
                  << " failed\n";
        return false;
    }

    std::cout << "[RobotController] Move "
              << (mode == 0 ? "Joint" : "Linear")
              << " executed to point " << pointNumber
              << " in vector " << vectorName;
    if (vectorNameB)
        std::cout << " then " << vectorNameB << ":" << pointNumberB;
    std::cout << std::endl;

    return true;
}

bool RobotController::openGripper() {
    if (!initialized) return false;
    std::cout << "[RobotController] Opening gripper..." << std::endl;
    return OpenGripper();
}

bool RobotController::closeGripper() {
    if (!initialized) return false;
    std::cout << "[RobotController] Closing gripper..." << std::endl;
    return CloseGripper();
}

bool RobotController::stop(UCHAR groupOrAxis) {
    BOOL ok = Stop(groupOrAxis);
    if (!ok) {
        std::cerr << "[RobotController] Stop failed for group/axis " << (int)groupOrAxis << "\n";
        return false;
    }
    std::cout << "[RobotController] Stop command sent for group/axis " << (int)groupOrAxis << "\n";
    return true;
}

// --- Velocity motion ---
bool RobotController::velocity(UCHAR groupOrAxis, long vel) {
    BOOL ok = Velocity(groupOrAxis, vel);
    if (!ok) {
        std::cerr << "[RobotController] Velocity command failed for group/axis "
                  << (int)groupOrAxis << " vel=" << vel << "\n";
        return false;
    }
    std::cout << "[RobotController] Velocity command sent to group/axis "
              << (int)groupOrAxis << " vel=" << vel << "\n";
    return true;
}

bool RobotController::control(bool enable) {
    BOOL ok = Control('&', enable ? TRUE : FALSE);
    if (!ok) {
        std::cerr << "[RobotController] Control "
                  << (enable ? "ON" : "OFF")
                  << " failed\n";
        return false;
    }
    std::cout << "[RobotController] Control "
              << (enable ? "ON" : "OFF")
              << " succeeded\n";
    return true;
}

bool RobotController::watchControl() {
    return WatchControl((CallBackFun)AxisControl) == TRUE;
}

bool RobotController::closeWatchControl() {
    return CloseWatchControl() == TRUE;
}

bool RobotController::homeRobot() {
    if (!initialized) return false;
    std::cout << "[RobotController] Homing Robot axes..." << std::endl;
    return Home('A', (CallBackFun)&HomingNotif);
}

bool RobotController::homePeripherals() {
    if (!initialized) return false;
    std::cout << "[RobotController] Homing Pereferial axes..." << std::endl;
    return Home('B', (CallBackFun)&HomingNotif);
}

//---------------------- End of Movement Functions ---------------

//-------------------  Position Functions -----------------------

bool RobotController::defineVector(UCHAR group, const TCHAR* name, short dimension)
{
    if (!name || dimension <= 0) return false;
    return DefineVector(group, const_cast<TCHAR*>(name), dimension) == TRUE;
}

bool RobotController::here(const TCHAR* vectorName, short pointNumber, long pointType) {
    BOOL ok = Here((TCHAR*)vectorName, pointNumber, pointType);
    if (!ok) {
        std::cerr << "[RobotController] Here failed\n";
        return false;
    }
    std::cout << "[RobotController] Stored current position into point "
              << pointNumber << " of vector\n";
    return true;
}

bool RobotController::teach(const TCHAR* vectorName, short pointNumber,
                            long* coords, short dim, long pointType) {
    BOOL ok = Teach((TCHAR*)vectorName, pointNumber, coords, dim, pointType);
    if (!ok) {
        std::cerr << "[RobotController] Teach failed\n";
        return false;
    }
    std::cout << "[RobotController] Teach point " << pointNumber << " in vector\n";
    return true;
}

bool RobotController::getPointInfo(const TCHAR* vectorName, short pointNumber) {
    RobotData enc;
    RobotData joint;
    RobotData xyz;
    long type = 0;

    BOOL ok = GetPointInfo((TCHAR*)vectorName, pointNumber,
                           &enc, &joint, &xyz, &type);
    if (!ok) {
        std::cerr << "[RobotController] GetPointInfo failed\n";
        return false;
    }

    int dataSize = sizeof(RobotData) / sizeof(long);

    std::cout << "[RobotController] Point " << pointNumber << " info:\n";

    std::cout << "  Encoders: ";
    for (int i = 0; i < dataSize; ++i) {
        std::cout << enc[i] << (i < dataSize - 1 ? ", " : "");
    }
    std::cout << "\n";

    std::cout << "  Joints:   ";
    for (int i = 0; i < dataSize; ++i) {
        std::cout << joint[i] << (i < dataSize - 1 ? ", " : "");
    }
    std::cout << "\n";

    std::cout << "  XYZ:      ";
    for (int i = 0; i < dataSize; ++i) {
        std::cout << xyz[i] << (i < dataSize - 1 ? ", " : "");
    }
    std::cout << "\n";

    std::cout << "  PointType: " << type << "\n";
    return true;
}

bool RobotController::getCurrentPosition(long enc[TOTAL_AXES],
                                         long joint[TOTAL_AXES],
                                         long xyz[TOTAL_AXES])
{
    if (!enc || !joint || !xyz) return false;
    return GetCurrentPosition(reinterpret_cast<RobotData*>(enc),
                              reinterpret_cast<RobotData*>(joint),
                              reinterpret_cast<RobotData*>(xyz)) == TRUE;
}

//-------------------  End of Position Functions ----------------

//------------------- Monitoring command -----------------------------

bool RobotController::showXYZ() {
    BOOL ok = ShowXYZ((CallBackFun)&ViewWatchXYZ);
    if (!ok) {
        std::cerr << "[RobotController] ShowXYZ failed\n";
        return false;
    }
    std::cout << "[RobotController] Started streaming XYZ\n";
    return true;
}

bool RobotController::closeXYZ() {
    BOOL ok = CloseXYZ();
    if (!ok) {
        std::cerr << "[RobotController] CloseXYZ failed\n";
        return false;
    }
    std::cout << "[RobotController] Stopped streaming XYZ\n";
    return true;
}

bool RobotController::showTorque(UCHAR axis) {
    BOOL ok = ShowTorque(axis, (CallBackFun)&ViewShowTorque);
    if (!ok) {
        std::cerr << "[RobotController] ShowTorque failed for axis " 
                  << (int)axis << "\n";
        return false;
    }
    std::cout << "[RobotController] Started torque stream for axis " 
              << (int)axis << "\n";
    return true;
}

bool RobotController::closeTorque() {
    BOOL ok = CloseTorque();
    if (!ok) {
        std::cerr << "[RobotController] CloseTorque failed\n";
        return false;
    }
    std::cout << "[RobotController] Stopped torque stream\n";
    return true;
}

bool RobotController::watchMotion() {
    auto ret = WatchMotion(
        (CallBackFun)MotionEnd,
        (CallBackFun)MotionStart
    );

    if (ret == nullptr) {
        std::cerr << "[RobotController] WatchMotion failed\n";
        return false;
    }

    std::cout << "[RobotController] Watching motion events...\n";
    return true;
}

bool RobotController::closeWatchMotion() {
    auto prev = WatchMotion(NULL);
    if (prev == nullptr) {
        std::cout << "[RobotController] No previous handler to restore.\n";
    } else {
        std::cout << "[RobotController] WatchMotion stopped, restored previous handler.\n";
    }
    return true;
}

//------------------- End of Monitoring command ----------------------

//------------------- Input/Output command ---------------------



bool RobotController::watchDigitalInputs() {
    BOOL ok = WatchDigitalInp((CallBackFun)&ViewWatchDigitInputs);
    if (!ok) {
        std::cerr << "[RobotController] Failed to start watching digital inputs\n";
        return false;
    }
    std::cout << "[RobotController] Watching digital inputs...\n";
    return true;
}

bool RobotController::closeWatchDigitalInputs() {
    BOOL ok = CloseWatchDigitalInp();
    if (!ok) {
        std::cerr << "[RobotController] Failed to stop watching digital inputs\n";
        return false;
    }
    std::cout << "[RobotController] Digital input watch stopped\n";
    return true;
}

bool RobotController::getDigitalInputs(ULONG &statusBitmap) {
    BOOL ok = GetDigitalInputs(&statusBitmap);
    if (!ok) {
        std::cerr << "[RobotController] GetDigitalInputs failed\n";
        return false;
    }

    std::cout << "[RobotController] Digital Inputs bitmap = 0x"
              << std::hex << statusBitmap << std::dec << std::endl;

    return true;
}

// Set one digital output
bool RobotController::setDigitalOutput(short number, bool state) {
    BOOL ok = SetDigitalOutput(number, state ? TRUE : FALSE);
    if (!ok) {
        std::cerr << "[RobotController] Failed to set digital output " << number 
                  << " to " << (state ? "ON" : "OFF") << "\n";
        return false;
    }
    std::cout << "[RobotController] Digital output " << number 
              << " set to " << (state ? "ON" : "OFF") << "\n";
    return true;
}

// Get all outputs in a bitmap (bit i = state of output i)
bool RobotController::getDigitalOutputs(ULONG &bitmap) {
    BOOL ok = GetDigitalOutputs(&bitmap);
    if (!ok) {
        std::cerr << "[RobotController] Failed to read digital outputs bitmap\n";
        return false;
    }
    std::cout << "[RobotController] Outputs bitmap = 0x" 
              << std::hex << bitmap << std::dec << "\n";
    return true;
}

