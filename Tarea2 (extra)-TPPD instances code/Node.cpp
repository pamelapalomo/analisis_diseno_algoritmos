/*
 * Node.cpp
 *
 *  Created on: Feb 23, 2017
 *      Author: pamela
 */

#include "Node.h"

namespace std {

static int id_generator=0;

Node::Node() {
	id=id_generator++;
	x_coordinate=rand()%1000;
	y_coordinate=rand()%1000;
	service_time=0;
}

Node::Node(const Node &other){
	id=other.id;
	x_coordinate=other.x_coordinate;
	y_coordinate=other.y_coordinate;
	service_time=other.service_time;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
