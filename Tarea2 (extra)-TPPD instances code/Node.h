/*
 * Node.h
 *
 *  Created on: Feb 23, 2017
 *      Author: pamela
 */

#ifndef NODE_H_
#define NODE_H_

#include "Header.h"

namespace std {


class Node {
private:
	int id;
	int x_coordinate;
	int y_coordinate;
	int service_time;
public:
	Node();
	Node(const Node &);
	virtual ~Node();

	int getXCoordinate(){return x_coordinate;}
	int getYCoordinate(){return y_coordinate;}
	int getID(){return id;}
	int getServiceTime(){return service_time;}

	void setServiceTime(int s){service_time=s;}
};

} /* namespace std */

#endif /* NODE_H_ */
