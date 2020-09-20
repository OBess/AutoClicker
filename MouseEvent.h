#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

class MouseEvent{
public:
    int x;
    int y;
    int milliseconds;
    unsigned clicks;

    MouseEvent(int x, int y) :
        x{x}, y{y}, milliseconds{1}, clicks{1}{}
};

#endif // MOUSEEVENT_H

