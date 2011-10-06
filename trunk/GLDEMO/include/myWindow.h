#pragma once

#include <glutwindow.h>

class myWindow : public cwc::glutWindow
{
public:
	myWindow();

	virtual void OnRender(void);
	virtual void OnIdle();

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit();

	virtual void OnResize(int w, int h);
	virtual void OnClose(void);
	virtual void OnMouseDown(int button, int x, int y);
	virtual void OnMouseUp(int button, int x, int y);
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y);

	virtual void OnKeyDown(int nKey, char cAscii);

	virtual void OnKeyUp(int nKey, char cAscii);
};