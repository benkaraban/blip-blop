#pragma once

/* Okay, first, don't hate me. I know, the name sucks; get over it.
 * I know, the concept sucks, but the game handles time in a way that is either
 * bad or unfamiliar to me.
 *
 * So, what is UpdateRegulator, and how is it to be used?
 * In order to have a constant game speed, the games I know would typically
 * have a main loop like this:
 *   start = time();
 *   while (!quit) {
 *      Draw();
 *      elapsed = start - time();
 *      start = time();
 *      Update(elapsed);
 *   }
 * and the update function would perform Euler integration with this varying
 * time step.
 *
 * HOWEVER Blip&Blop doesn't work like this. Instead of having an update step
 * that acts differently based on the time step, it has a fixed time step
 * update rules that's called many time.
 *
 * Say your computer is super fast, and very little time happened since last
 * frame: you won't perform an update step. Say the last frame was long to
 * compute: you will perform more than one update before drawing again (drawing
 * is by far the slow part anyway). It's fine. It's just weird that the
 * solution for a too long frame is adding more compute... that will take time.
 * Today's computers can handle an update step in a blink of an eye, but still.
 *
 * So the regulator is here for that. It tells you how many update steps to
 * take.
 */

#include "moving_average.h"

class UpdateRegulator {
   public:
    UpdateRegulator(int delay_goal = 11, int margin = 1, int hist_size = 50)
        : last_frames_spare_time_(hist_size),
          dtime_(0),
          delay_goal_(delay_goal),
          margin_(margin) {}

    /**
     * @brief notify that you're starting a new frame.
     *
     * @return how many update steps to perform.
     */
    int Step() {
        int since_last = RegisterFrameTime();
        dtime_ += since_last;
        int mean_FST = last_frames_spare_time_.average();

        frame_time_.Reset();

        if (-margin_ <= mean_FST && mean_FST <= margin_) {
            // game is running exactly as planned, make 1 update
            dtime_ = 0;
            return 1;
        } else {
            // game is not running exactly as planned (slower or faster), so we
            // use the accumulated time to count how many updates are needed
            int cnt = 0;
            while (dtime_ > delay_goal_) {
                ++cnt;
                dtime_ -= delay_goal_;
            }
            return cnt;
        }
    }

    /**
     * @brief Call when you want to restart counting the time taken for that
     * current frame.
     */
    void Skip() {
        frame_time_.Reset();
    }

   private:
    int RegisterFrameTime() {
        int since_last = frame_time_.elapsed();
        // adjust for oddities
        if (since_last <= 0) {
            last_frames_spare_time_.Add(0);
        } else if (since_last >= 500) {
            last_frames_spare_time_.Add(0);
        } else {
            last_frames_spare_time_.Add(since_last - delay_goal_);
        }
        return since_last;
    }

    MovingAverage<int> last_frames_spare_time_;
    Chrono frame_time_;
    int dtime_;
    int delay_goal_;
    int margin_;
};
