/*
 * Eclipse.h
 *
 *  Created on: Oct 11, 2017
 *      Author: Eric Gonzalez
 */

#ifndef SRC_ECLIPSE_H_
#define SRC_ECLIPSE_H_
#include <string>
#include <iostream>

using namespace std;

template<class T>
class ResizableArray;

class Eclipse {
friend std::ostream& operator<<(std::ostream& output, const Eclipse& e);
public:
	Eclipse();
	Eclipse(string e);
	Eclipse(string catNum, string canonPlate, string calenderYear, string calenderMonth, string calenderDay,
			string tdGreatestEclipse, string dt, string lunaNum, string sarosNum, string eclipseType, string gamma,
			string eclipseMag, string latitude, string longitude, string sunAlt, string azm, string width, string centralDur);
	virtual ~Eclipse();
	// Accessor methods
	string getColumnElement(int response) const;
	string getcsvDataLine();
	void print();
	string getCategorySection(int numCol, bool isPartial);
	Eclipse(const Eclipse &source);
	bool operator < (const Eclipse& e);
	bool operator > (const Eclipse& e);
	bool operator >= (const Eclipse& e);
	bool operator <= (const Eclipse& e);
	Eclipse operator= (const Eclipse& source);
private:
	string line;
	string csvDataLine;
	string eclipseInfo[18];


	string catNum;
	string canonPlate;
	string calenderYear;
	string calenderMonth;
	string calenderDay;
	string tdGreatestEclipse;
	string dt;
	string lunaNum;
	string sarosNum;
	string eclipseType;
	string gamma;
	string elcipseMag;
	string latitude;
	string longitude;
	string sunAlt;
	string azm;
	string width;
	string centralDur;
};
#endif /* SRC_ECLIPSE_H_ */
