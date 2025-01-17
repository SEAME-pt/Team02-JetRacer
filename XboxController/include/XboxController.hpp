
#pragma once

#include <linux/joystick.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include "zenoh.hxx"

#define JS_EVENT_BUTTON 0x01 /* button pressed/released */
#define JS_EVENT_AXIS 0x02   /* joystick moved */
#define JS_EVENT_INIT 0x80   /* initial state of device */

enum Button
{
    BUTTON_A           = 0,
    BUTTON_B           = 1,
    BUTTON_BACK        = 2,
    BUTTON_X           = 3,
    BUTTON_Y           = 4,
    BUTTON_UNKNOWN     = 5,
    BUTTON_LB          = 6,
    BUTTON_RB          = 7,
    BUTTON_L2          = 8,
    BUTTON_R2          = 9,
    BUTTON_SELECT      = 10,
    BUTTON_START       = 11,
    BUTTON_HOME        = 12,
    BUTTON_LEFT_STICK  = 13,
    BUTTON_RIGHT_STICK = 14
};

enum Axis
{
    AXIS_RIGHT_STICK = 0,
    AXIS_LEFT_STICK  = 1,
};

struct axis_state
{
    int x = 0;
    int y = 0;
};

struct LightsInfo {
  bool rightBlinker;
  bool leftBlinker;
  bool lowBeam;
  bool highBeam;
  bool frontFogLight;
  bool rearFogLight;
  bool hazardLight;
  bool parkingLight;
};

using namespace zenoh;

class XboxController
{
  private:
    int js;
    Session m_session;
    Publisher m_pubThrottle;
    Publisher m_pubDirection;
    Publisher m_pubLights;
    LightsInfo lightsInfo;

  public:
    std::vector<struct axis_state*> axes;
    struct js_event event;

    XboxController();
    ~XboxController();
    int readEvent(void);
    int getButtonCount(void);
    int getAxisCount(void);
    int getAxisState(void);
    void run();
};