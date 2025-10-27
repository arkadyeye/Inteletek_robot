#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H

#include <windows.h>
#include "usbb/usbc.h"
#include "usbb/usbcdef.h"
#include "CallBack.h"

class RobotController {
public:
    RobotController();
    ~RobotController();

//--------------------  Configuration Functions ------------------------
    bool init();       // Initialization
    void shutdown();   // CloseUSBC

    bool isEmergency();
    bool isTeachMode();
    bool isOnlineOk();

    bool getConfig();
    short getMode();

//-------------------- End of Configuration Functions ------------------------

//--------------------------- Movement Functions ------------------------
    // --- Manual movement ---
    bool enterManual(short manualType);   // e.g., 0 = joint mode, 1 = xyz mode
    bool moveManual(UCHAR axis, long velocity);
    bool closeManual();

    // mode: 0 = MoveJoint, 1 = MoveLinear
    bool move(short mode,
              const TCHAR* vectorName, short pointNumber,
              const TCHAR* vectorNameB = nullptr, short pointNumberB = 0);

    bool openGripper();
    bool closeGripper();
  
    bool stop(UCHAR groupOrAxis);

    bool velocity(UCHAR groupOrAxis, long vel);

    bool control(bool enable);  // true = ON, false = OFF
    bool watchControl();
    bool closeWatchControl();

    //here we should add home perepherials
    bool homeRobot();    // Home robot only
    bool homePeripherals(); // Home axis 7,8

//---------------------- End of Movement Functions ---------------

//-------------------  Position Functions -----------------------

    bool defineVector(UCHAR group, const TCHAR* name, short dimension);

    bool here(const TCHAR* vectorName, short pointNumber, long pointType);
    bool teach(const TCHAR* vectorName, short pointNumber,
            long* coords, short dim, long pointType);

    bool getPointInfo(const TCHAR* vectorName, short pointNumber);

    // Fills the three arrays (size = TOTAL_AXES) with encoder, joint and XYZ data.
    bool getCurrentPosition(long enc[TOTAL_AXES],
                            long joint[TOTAL_AXES],
                            long xyz[TOTAL_AXES]);

//-------------------  End of Position Functions ----------------

//------------------- Monitoring command -----------------------------

    bool showXYZ();
    bool closeXYZ();

    bool showTorque(UCHAR axis);
    bool closeTorque();

    bool watchMotion();
    bool closeWatchMotion();

//------------------- End of Monitoring command ----------------------

//------------------- Input/Output command ---------------------

    // Digital Inputs
    bool watchDigitalInputs();
    bool closeWatchDigitalInputs();

    // Digital Outputs
    bool setDigitalOutput(short number, bool state);
    bool getDigitalOutputs(ULONG &bitmap);
    bool getDigitalInputs(ULONG &statusBitmap);

private:
    bool initialized;
};

#endif

