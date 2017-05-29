/*
 * Customer.cpp
 *
 *  Created on: Feb 23, 2017
 *      Author: pamela
 */

#include "Customer.h"

namespace std {

Customer::Customer():Node() {

}

Customer::Customer(const Customer &other):Node(other){
	demand=other.demand;
}
Customer::~Customer() {
	// TODO Auto-generated destructor stub
}

void Customer::clearDemand(){
	demand.clear();
}

bool Customer::isActive(){
	return (demand.size()>0);
}

} /* namespace std */
