#include "XboxController.hpp"

XboxController::XboxController()
{
    const char* device = "/dev/input/js0";
    js                 = open(device, O_RDONLY);

    if (js == -1)
        throw std::exception();

    int numAxes = this->getAxisCount();
    for (int i = 0; i < numAxes; i++)
    {
        struct axis_state* axis = new struct axis_state();
        axes.push_back(axis);
    }

    auto config = zenoh::Config::create_default();
    session_    = std::make_shared<zenoh::Session>(
        zenoh::Session::open(std::move(config)));

    publisher_ = std::make_unique<ControllerPublisher>(session_);

    std::cout << "Remote controller created!" << std::endl;
}

XboxController::XboxController(const std::string& configFile)
{
    const char* device = "/dev/input/js0";
    js                 = open(device, O_RDONLY);

    if (js == -1)
        throw std::exception();

    int numAxes = this->getAxisCount();
    for (int i = 0; i < numAxes; i++)
    {
        struct axis_state* axis = new struct axis_state();
        axes.push_back(axis);
    }

    auto config = zenoh::Config::from_file(configFile);
    session_    = std::make_shared<zenoh::Session>(
        zenoh::Session::open(std::move(config)));

    publisher_ = std::make_unique<ControllerPublisher>(session_);

    std::cout << "Remote controller created!" << std::endl;
}

XboxController::~XboxController()
{
    for (unsigned int i = 0; i < axes.size(); i++)
    {
        delete axes[i];
    }

    close(js);
}
int XboxController::readEvent(void)
{
    int bytes;

    bytes = read(js, &event, sizeof(event));

    if (bytes == sizeof(event))
        return 0;

    return -1;
}

int XboxController::getButtonCount(void)
{
    int buttons;
    if (ioctl(js, JSIOCGBUTTONS, &buttons) == -1)
        return 0;

    return buttons;
}

int XboxController::getAxisCount(void)
{
    int axes;
    if (ioctl(js, JSIOCGAXES, &axes) == -1)
        return 0;

    return axes;
}

int XboxController::getAxisState(void)
{
    int axis = event.number / 2;

    if (axis < 3)
    {
        if (event.number % 2 == 0)
            axes[axis]->x = event.value;
        else
            axes[axis]->y = event.value;
    }
    return axis;
}

void XboxController::run()
{
    size_t axis;
    size_t button;

    while (this->readEvent() == 0)
    {
        switch (this->event.type)
        {
            case JS_EVENT_BUTTON:
            {
                button = this->event.number;
                if (this->event.value == 1)
                {
                    switch (button)
                    {
                        case BUTTON_RB:
                        {
                            publisher_->publishDirectionIndicatorRight(true);
                            std::cout << "RightBlinker" << std::endl;
                            break;
                        }
                        case BUTTON_LB:
                        {
                            publisher_->publishDirectionIndicatorLeft(true);
                            std::cout << "LeftBlinker" << std::endl;
                            break;
                        }
                        case BUTTON_A:
                        {
                            publisher_->publishBeamLow(true);
                            std::cout << "lowBeam" << std::endl;
                            break;
                        }
                        case BUTTON_B:
                        {
                            publisher_->publishBeamHigh(true);
                            std::cout << "highBeam" << std::endl;
                            break;
                        }
                        case BUTTON_X:
                        {
                            publisher_->publishFogRear(true);
                            std::cout << "rearFogLight" << std::endl;
                            break;
                        }
                        case BUTTON_Y:
                        {
                            publisher_->publishFogFront(true);
                            std::cout << "frontFogLight" << std::endl;
                            break;
                        }
                        case BUTTON_L2:
                        {
                            publisher_->publishHazard(true);
                            std::cout << "hazardLight" << std::endl;
                            break;
                        }
                        case BUTTON_R2:
                        {
                            publisher_->publishParking(true);
                            std::cout << "parkingLight" << std::endl;
                            break;
                        }

                        default:
                            break;
                    }
                }
                break;
            }
            case JS_EVENT_AXIS:
            {
                axis = this->getAxisState();
                switch (axis)
                {
                    case (AXIS_LEFT_STICK):
                    {
                        float speed = -this->axes[axis]->y * 100 / 32767;
                        if (speed < -5)
                        {
                            publisher_->publishCurrentGear(-1);
                        }
                        else if (speed > 5)
                        {
                            publisher_->publishCurrentGear(1);
                        }
                        else
                        {
                            publisher_->publishCurrentGear(0);
                        }
                        publisher_->publishSpeed(speed);
                        std::cout << "Speed" << std::endl;
                        break;
                    }
                    case (AXIS_RIGHT_STICK):
                    {
                        float direction = 90 + this->axes[axis]->x * 90 / 32767;
                        publisher_->publishSteering(direction);
                        std::cout << "Direction" << std::endl;
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            default:
                break;
                // if ((gear[0] >> 1) == 1 || (gear[0] >> 3) == 1)
                // {
                //     gear[0] = 0;
                //     ;
                //     gear[0] ^= (1 << 2);
                //     this->m_pubGear.put(gear);
                // }
        }
        fflush(stdout);
    }
}