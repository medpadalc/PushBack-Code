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

    void run(GoalType goal);
    void iterate(GoalType goal);
    void stop();
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

namespace midGoalDescore {
    void extend();
    void retract();
    void toggle();
}

};
