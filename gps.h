/*********************************
 * GPS Module Interface
   *********************************/

// gps.h
#pragma once
#include <vector>
#include "Direction.h"
#include "Fragment.h"
//#include "GPSCenter.h"
//#include "GPSLeft.h"
//#include "GPSRight.h"

class GPS {
public:
    virtual void destroy(std::vector<Fragment>& satellites) {
        satellites.push_back(GPSCenter(this, Direction(90)));
        satellites.push_back(GPSLeft(this, Direction(0)));
        satellites.push_back(GPSRight(this, Direction(180)));
        satellites.push_back(Fragment(this, Direction(330)));
        satellites.push_back(Fragment(this, Direction(250)));
    }
    virtual ~GPS() = default;
};

class GPSRight : public GPS {
public:
    void destroy(std::vector<Fragment>& satellites) override {
        satellites.push_back(Fragment(this, Direction(115)));
        satellites.push_back(Fragment(this, Direction(325)));
    }
};
