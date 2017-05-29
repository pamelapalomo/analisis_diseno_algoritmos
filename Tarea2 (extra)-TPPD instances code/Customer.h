/*
 * Customer.h
 *
 *  Created on: Feb 23, 2017
 *      Author: pamela
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include "Node.h"

namespace std {

class Customer:public Node {
private:
	map<int,int> demand; //product id, quantity;
public:
	Customer();
	Customer(const Customer &);
	virtual ~Customer();

	void clearDemand();
	bool isActive();

	void setDemand(int product_id, int quantity){demand[product_id]=quantity;}

	int getDemand(int product_id){map<int,int>::iterator it=demand.find(product_id); if(it!=demand.end()) return it->second; return 0;}
};

} /* namespace std */

#endif /* CUSTOMER_H_ */
