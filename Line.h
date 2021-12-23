#pragma once

class Line
{
private:
	int nowX; 
	int nowY; 
	int beforeX;
	int beforeY;
public:
	Line(int x, int y);
	void changePos(int x, int y);
	int  getNowX();
	int  getNowY();
	int  getBeforeX();
	int  getBeforeY();
};