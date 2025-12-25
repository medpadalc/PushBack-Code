#pragma once

#include "pros/motor_group.hpp"
#include "pros/optical.hpp"
#include "pros/adi.hpp"
#include <memory>
#include <utility>

namespace subsystems {

namespace intake {
    enum class GoalType {
        LOW_GOAL,
        MEDIUM_GOAL,
        HOLD_BALLS,
        LONG_GOAL,
        NONE
    };

    enum class AllianceColor {
        RED,
        BLUE,
        DISABLED
    };

    void run(GoalType goal);
    void iterate(GoalType goal);
    void stop();
    std::string getAllianceColorAsString();
    void setAllianceColor(AllianceColor color);
    void toggleAllianceColor();
    void disableColorSort();
}

namespace hood {
    void open();
    void close();
    void toggle();
}

namespace matchload {
    void extend();
    void retract();
    void toggle();
}

namespace wing {
    void extend();
    void retract();
    void toggle();
}

};
