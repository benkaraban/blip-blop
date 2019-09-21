#pragma once

namespace SDL {
class Surface;
}

// FIXME: That ontology is pretty bad. Find something better.
enum MenuType : int {
    Main,
    Start,
    Options,
    Exit,
    Keys_1,
    Keys_2,
    Game_1,
    Game_2
};

class AbstractMenu {
   public:
    virtual void Draw(SDL::Surface* surf) const = 0;
    virtual int ProcessEvent() = 0;
};
