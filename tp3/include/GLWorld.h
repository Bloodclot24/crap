#ifndef _GLWORLD_H_
#define _GLWORLD_H_

class GLWorld
{
    public:
    virtual void initialize();
    virtual void handleDisplay();
    virtual void handleReshape(int width, int height);
    virtual void handleKeyboard(unsigned char key, int x, int y);
    virtual void handleMouseClick(int button, int state, int x, int y);
    virtual void handleMouseMotion(int x, int y);
    virtual void timerCallback(int value);

    GLWorld();
    virtual ~GLWorld();
};

#endif /* _GLWORLD_H_ */
