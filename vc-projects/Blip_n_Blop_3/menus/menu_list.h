#pragma once

#include <string>
#include <vector>

#include "../graphics.h"

class MenuList {
   public:
    void Draw(SDL::Surface* surf) const;

    void MoveUp() {
        focused_ -= 1;
        if (focused_ < 0) {
            focused_ = items_.size() - 1;
        }
    }

    void MoveDown() {
        focused_ += 1;
        if (focused_ >= items_.size()) {
            focused_ = 0;
        }
    }

    int focused() const { return focused_; }

    void AddEntry(const std::string& entry) { items_.push_back(entry); }
    void ChangeEntry(int idx, const std::string& entry) { items_[idx] = entry; }

    int size() const { return items_.size(); }

   private:
    int ComputeWidth() const;
    void ShadeTextBox(SDL::Surface* surf) const;

    std::vector<std::string> items_;
    int focused_ = 0;
};
