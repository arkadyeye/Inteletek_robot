#include <windows.h>
#include <tchar.h>
#include <vector>
#include "RobotController.h"
#include <iostream>

int main() {
    RobotController robot;
    bool running = true;

    while (running) {
        std::cout << "\n--- Robot CLI Menu ---\n";

        std::cout << "1. Initialize robot\n";
        //exit moved to the last (default) case

        std::cout << "2. Check Emergency Status\n";
        std::cout << "3. Check Teach Mode\n";
        std::cout << "4. Check Online OK\n";

        std::cout << "5. Get Configuration\n";
        std::cout << "6. Get Mode\n";

        std::cout << "7. Enter Manual Mode\n";
        std::cout << "8. Move Manual Axis\n";
        std::cout << "9. Close Manual Mode\n";

        std::cout << "10. Move to a taught point\n";
        std::cout << "11. Open gripper\n";
        std::cout << "12. Close gripper\n";
        std::cout << "13. Stop motion\n";

        //failed to use this api
        std::cout << "14. Move with velocity\n";

        std::cout << "15. Control ON/OFF\n";
        std::cout << "16. Watch control\n";
        std::cout << "17. Stop watching control\n";

        std::cout << "18. Home Robot\n";
        std::cout << "19. Home Peripherals\n";

        std::cout << "20. Define Vector\n";
        std::cout << "21. Here (store current position)\n";
        std::cout << "22. Teach point (manual values)\n";

        std::cout << "23. Get Point Info\n";
        std::cout << "24. Get Current Position\n";

        std::cout << "25. Start ShowXYZ\n";
        std::cout << "26. Stop ShowXYZ\n";
        std::cout << "27. Start ShowTorque (per axis)\n";
        std::cout << "28. Stop ShowTorque\n";
        
        //i've failed to use this api
        std::cout << "29. Watch Motion\n";
        std::cout << "30. Stop Watching Motion\n";

        std::cout << "31. Watch Digital Inputs\n";
        std::cout << "32. Stop Watching Digital Inputs\n";
        std::cout << "33. Get Digital Inputs\n";

        std::cout << "34. Set Digital Output\n";
        std::cout << "35. Get Digital Output\n";
      
        std::cout << "0. Exit\n";
        
        std::cout << "Select option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {

//--------------------  Configuration Functions ------------------------
        case 1:
            if (!robot.init()) {
                std::cerr << "[CLI] Initialization failed!" << std::endl;
            } else {
                std::cout << "[CLI] Robot initialized successfully." << std::endl;
            }
            break;

        
        case 2: {
            if (robot.isEmergency())
                std::cout << "[CLI] Emergency is ACTIVE!\n";
            else
                std::cout << "[CLI] Emergency is NOT active.\n";
            break;
        }

        case 3: {
            if (robot.isTeachMode())
                std::cout << "[CLI] Teach mode is ON\n";
            else
                std::cout << "[CLI] Teach mode is OFF\n";
            break;
        }

        case 4: {
            if (robot.isOnlineOk())
                std::cout << "[CLI] Robot is ONLINE\n";
            else
                std::cout << "[CLI] Robot is OFFLINE\n";
            break;
        }

        case 5: {
            if (!robot.getConfig()) {
                std::cerr << "[CLI] Failed to get configuration\n";
            }
            break;
        }

        case 6: {
            short mode = robot.getMode();
            std::cout << "[CLI] Mode = " << mode << "\n";
            break;
        }

//-------------------- End of Configuration Functions ------------------------

//--------------------------- Movement Functions ------------------------

        case 7: {
            short type;
            std::cout << "Enter manual type (0=joint, maybe 1=linear): ";
            std::cin >> type;
            if (robot.enterManual(type)) 
                std::cout << "[CLI] Entered manual mode type " << type << "\n";
            else 
                std::cerr << "[CLI] Failed to enter manual mode\n";
            break;
        }
       
        case 8: {
            int axis;
            long vel;
            std::cout << "Axis (0...7): ";
            std::cin >> axis;
            std::cout << "Velocity (+/-): ";
            std::cin >> vel;
            if (robot.moveManual((UCHAR)axis, vel))
                std::cout << "[CLI] Moving axis " << axis << " with velocity " << vel << "\n";
            else
                std::cerr << "[CLI] Failed to move axis\n";
            break;
        }

        case 9:
            if (robot.closeManual()) std::cout << "[CLI] Closed manual mode\n";
            else std::cerr << "[CLI] Failed to close manual mode\n";
            break;

        case 10: { // Move
            short mode;
            short p1, p2;
            char both;

            std::cout << "Mode (0=Joint, 1=Linear): ";
            std::cin >> mode;

            std::cout << "Point A: ";
            std::cin >> p1;

            std::cout << "Use both SCORA/SCORB vectors? (y/n): ";
            std::cin >> both;

            if (both == 'y' || both == 'Y') {
                // Move both robot arm (SCORA) and peripherals (SCORB)
                if (!robot.move(mode, _T("SCORA"), p1, nullptr, 0)) {
                    std::cerr << "[CLI] Move failed for SCORA\n";
                } else {
                    std::cout << "[CLI] Move executed for SCORA, point " << p1 << "\n";
                }

                if (!robot.move(mode, _T("SCORB"), p1, nullptr, 0)) {
                    std::cerr << "[CLI] Move failed for SCORB\n";
                } else {
                    std::cout << "[CLI] Move executed for SCORB, point " << p1 << "\n";
                }
            } else {
                // Single vector move
                std::string v1, v2;
                std::cout << "Vector A: "; std::cin >> v1;
                std::cout << "Vector B (or empty): "; std::cin >> v2;

                std::cout << "Point A: "; std::cin >> p1;
                if (!v2.empty()) {
                    std::cout << "Point B: "; std::cin >> p2;
                } else {
                    p2 = 0;
                }

                TCHAR tNameA[64], tNameB[64];
            #ifdef UNICODE
                mbstowcs(tNameA, v1.c_str(), 63); tNameA[63] = 0;
                TCHAR* tB = nullptr;
                if (!v2.empty()) {
                    mbstowcs(tNameB, v2.c_str(), 63); tNameB[63] = 0;
                    tB = tNameB;
                }
            #else
                strncpy(tNameA, v1.c_str(), 63); tNameA[63] = 0;
                TCHAR* tB = v2.empty() ? nullptr : tNameB;
                if (tB) strncpy(tNameB, v2.c_str(), 63);
            #endif

                if (!robot.move(mode, tNameA, p1, tB, p2)) {
                    std::cerr << "[CLI] Move failed!\n";
                } else {
                    std::cout << "[CLI] Move executed\n";
                }
            }
            break;
        }

        case 11:
            if (!robot.openGripper()) {
                std::cerr << "[CLI] Open gripper failed!" << std::endl;
            } else {
                std::cout << "[CLI] Gripper opening command sent." << std::endl;
            }
            break;

        case 12:
            if (!robot.closeGripper()) {
                std::cerr << "[CLI] Close gripper failed!" << std::endl;
            } else {
                std::cout << "[CLI] Gripper closing command sent." << std::endl;
            }
            break;

        case 13: {
            char group;
            if (robot.stop('&'))
                std::cout << "[CLI] Stop sent.\n";
            else
                std::cerr << "[CLI] Stop failed.\n";
            break;
        }

        case 14: {
            char group;
            long vel;
            std::cout << "Enter group/axis (A, B, G or 0-7): ";
            std::cin >> group;
            std::cout << "Enter velocity: ";
            std::cin >> vel;
            if (robot.velocity((UCHAR)group, vel))
                std::cout << "[CLI] Velocity command sent.\n";
            else
                std::cerr << "[CLI] Velocity command failed.\n";
            break;
        }

        case 15: {
            int flag;
            std::cout << "Control (1=ON, 0=OFF): ";
            std::cin >> flag;
            if (robot.control(flag == 1))
                std::cout << "[CLI] Control " << (flag ? "ON" : "OFF") << "\n";
            else
                std::cerr << "[CLI] Control operation failed\n";
            break;
        }

        case 16:
            if (robot.watchControl()) std::cout << "[CLI] Watching control changes...\n";
            else std::cerr << "[CLI] Failed to start watchControl\n";
            break;

        case 17:
            if (robot.closeWatchControl()) std::cout << "[CLI] Closed control watch.\n";
            else std::cerr << "[CLI] Failed to close control watch\n";
            break;

        case 18:
            if (!robot.homeRobot()) {
                std::cerr << "[CLI] Homing Robot failed!" << std::endl;
            } else {
                std::cout << "[CLI] Homing Robot command sent." << std::endl;
            }
            break;

        case 19:
            if (!robot.homePeripherals()) {
                std::cerr << "[CLI] Homing Pereferials failed!" << std::endl;
            } else {
                std::cout << "[CLI] Homing Pereferials command sent." << std::endl;
            }
            break;

//---------------------- End of Movement Functions ---------------

//-------------------  Position Functions -----------------------

        case 20: { // Define Vector(s)
            short dim;
            std::cout << "Dimension (e.g. 1000): ";
            std::cin >> dim;

            // Ask if user wants both vectors
            char both;
            std::cout << "Define both SCORA (arm) and SCORB (peripherals)? (y/n): ";
            std::cin >> both;

            if (both == 'y' || both == 'Y') {
                if (robot.defineVector('A', _T("SCORA"), dim) &&
                    robot.defineVector('B', _T("SCORB"), dim)) {
                    std::cout << "[CLI] SCORA and SCORB vectors defined with dim=" << dim << "\n";
                } else {
                    std::cerr << "[CLI] Failed to define SCORA/SCORB\n";
                }
            } else {
                char groupChar;
                std::string name;
                std::cout << "Group (char, e.g. A, B, C): ";
                std::cin >> groupChar;
                std::cout << "Vector name: ";
                std::cin >> name;

                TCHAR tName[64];
            #ifdef UNICODE
                mbstowcs(tName, name.c_str(), 63);
            #else
                strncpy(tName, name.c_str(), 63);
            #endif
                tName[63] = 0;

                if (robot.defineVector((UCHAR)groupChar, tName, dim))
                    std::cout << "[CLI] Vector " << name << " defined in group " << groupChar
                            << " with dim=" << dim << "\n";
                else
                    std::cerr << "[CLI] Failed to define vector\n";
            }
            break;
        }

        case 21: { // Here (store current position)
            short point;
            char both;
            std::cout << "Point number: ";
            std::cin >> point;
            std::cout << "Store in both SCORA (arm) and SCORB (peripherals)? (y/n): ";
            std::cin >> both;

            if (both == 'y' || both == 'Y') {
                if (robot.here(_T("SCORA"), point, ABS_JOINT) &&
                    robot.here(_T("SCORB"), point, ABS_JOINT)) {
                    std::cout << "[CLI] Position stored into SCORA and SCORB, point " 
                            << point << "\n";
                } else {
                    std::cerr << "[CLI] Failed to store position in SCORA/SCORB\n";
                }
            } else {
                std::string name;
                std::cout << "Vector name: ";
                std::cin >> name;

                TCHAR tName[64];
            #ifdef UNICODE
                mbstowcs(tName, name.c_str(), 63);
            #else
                strncpy(tName, name.c_str(), 63);
            #endif
                tName[63] = 0;

                if (robot.here(tName, point, ABS_JOINT)) {
                    std::cout << "[CLI] Position stored into " << name 
                            << ", point " << point << "\n";
                } else {
                    std::cerr << "[CLI] Failed to store position with Here\n";
                }
            }
            break;
        }

        case 22: {
            std::string name;
            short point;
            int dim;
            std::cout << "Vector name: ";
            std::cin >> name;
            std::cout << "Point number: ";
            std::cin >> point;
            std::cout << "How many coordinates (e.g., 5): ";
            std::cin >> dim;

            std::vector<long> coords(dim);
            for (int i = 0; i < dim; i++) {
                std::cout << "Coord[" << i << "]: ";
                std::cin >> coords[i];
            }

            TCHAR tName[64];
        #ifdef UNICODE
            mbstowcs(tName, name.c_str(), 63);
        #else
            strncpy(tName, name.c_str(), 63);
        #endif
            tName[63] = 0;

            long pointType = ABS_XYZ_A; // default type from USBC.h

            if (robot.teach(tName, point, coords.data(), (short)dim, pointType)) {
                std::cout << "[CLI] Point " << point
                        << " taught into vector " << name << "\n";
            } else {
                std::cerr << "[CLI] Failed to teach point\n";
            }
            break;
        }

        
        case 23: {
            std::string name;
            short point;
            std::cout << "Vector name: ";
            std::cin >> name;
            std::cout << "Point number: ";
            std::cin >> point;

            TCHAR tName[64];
        #ifdef UNICODE
            mbstowcs(tName, name.c_str(), 63);
        #else
            strncpy(tName, name.c_str(), 63);
        #endif
            tName[63] = 0;

            if (!robot.getPointInfo(tName, point)) {
                std::cerr << "[CLI] GetPointInfo failed!\n";
            } else {
                std::cout << "[CLI] GetPointInfo completed.\n";
            }
            break;
        }


        case 24: {
            long enc[TOTAL_AXES], jnt[TOTAL_AXES], xyz[TOTAL_AXES];
            if (robot.getCurrentPosition(enc, jnt, xyz)) {
                std::cout << "[CLI] Current Position:\n";
                for (int i = 0; i < TOTAL_AXES; i++) {
                    std::cout << "  Axis " << i
                              << " enc=" << enc[i]
                              << " jnt=" << jnt[i]
                              << " xyz=" << xyz[i] << "\n";
                }
            } else {
                std::cerr << "[CLI] Failed to get current position\n";
            }
            break;
        }

//-------------------  End of Position Functions ----------------

//------------------- Monitoring command -----------------------------

        case 25:
            robot.showXYZ();
            break;
        case 26:
            robot.closeXYZ();
            break;

        case 27: {
            int axis;
            std::cout << "Axis (0..7): ";
            std::cin >> axis;
            if (robot.showTorque((UCHAR)axis))
                std::cout << "[CLI] Torque streaming started for axis " << axis << "\n";
            else
                std::cerr << "[CLI] Failed to start torque stream\n";
            break;
        }
        case 28:
            if (robot.closeTorque())
                std::cout << "[CLI] Torque streaming stopped\n";
            else
                std::cerr << "[CLI] Failed to stop torque stream\n";
            break;

        case 29:
            if (robot.watchMotion())
                std::cout << "[CLI] Started watching motion events\n";
            else
                std::cerr << "[CLI] Failed to start motion watch\n";
            break;

        case 30:
            if (robot.closeWatchMotion())
                std::cout << "[CLI] Stopped watching motion events\n";
            else
                std::cerr << "[CLI] Failed to stop motion watch\n";
            break;


//------------------- End of Monitoring command ----------------------

//------------------- Input/Output command ---------------------

        case 31:
            if (robot.watchDigitalInputs()) 
                std::cout << "[CLI] Watching digital inputs.\n";
            else 
                std::cerr << "[CLI] Failed to watch digital inputs.\n";
            break;

        case 32:
            if (robot.closeWatchDigitalInputs()) 
                std::cout << "[CLI] Stopped digital inputs watch.\n";
            else 
                std::cerr << "[CLI] Failed to stop digital inputs watch.\n";
            break;

        case 33: {
            ULONG inputs = 0;
            if (robot.getDigitalInputs(inputs)) {
                std::cout << "[CLI] Digital inputs bitmap: 0x"
                        << std::hex << inputs << std::dec << "\n";

                // Optional: print bit by bit
                for (int i = 0; i < 32; i++) {
                    bool state = (inputs & (1 << i)) != 0;
                    std::cout << "  Input[" << i << "] = " << (state ? "ON" : "OFF") << "\n";
                }
            } else {
                std::cerr << "[CLI] Failed to read digital inputs\n";
            }
            break;
        }

        case 34: {
            short num;
            int val;
            std::cout << "Output number (0..31): ";
            std::cin >> num;
            std::cout << "State (1=ON, 0=OFF): ";
            std::cin >> val;
            if (robot.setDigitalOutput(num, val != 0))
                std::cout << "[CLI] Digital output " << num 
                          << " set to " << (val ? "ON" : "OFF") << "\n";
            else
                std::cerr << "[CLI] Failed to set output\n";
            break;
        }

        case 35: {
            ULONG bitmap;
            if (robot.getDigitalOutputs(bitmap)) {
                std::cout << "[CLI] Outputs bitmap: 0x" 
                          << std::hex << bitmap << std::dec << "\n";
                for (int i = 0; i < 32; i++) {
                    bool state = (bitmap & (1UL << i)) != 0;
                    std::cout << "  Output " << i << " = " 
                              << (state ? "ON" : "OFF") << "\n";
                }
            }
            break;
        }

        case 0:
            running = false;
            break;

        default:
            std::cerr << "Invalid option, try again." << std::endl;
        }
    }

    robot.shutdown();
    return 0;
}

