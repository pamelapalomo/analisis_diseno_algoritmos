/*
 * Instance.h
 *
 *  Created on: Feb 23, 2017
 *      Author: pamela
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include "Customer.h"
#include "Market.h"

namespace std {

class Instance {
private:
	int number_of_nodes;
	int number_of_customers;
	int number_of_markets;
	int number_of_products;
	int* initial_stock;
	Node* depot;
	Customer** customer_set;
	Market** market_set;
	list<int> cheap_products;
	list<int> medium_products;
	list<int> expensive_products;
	int average_traveling_time;
	string demand_level;
	string service_to_customers;
	string capacitated;
public:
	Instance(int, int);
	Instance(const Instance &);
	virtual ~Instance();

	void generateNumberOfMarketsCustomers();
	void generateNodesCoordinates();
	void generateProductCategories();
	void generateDemand();
	int obtainProductCategory(int);
	void generateServiceTimesMarkets();
	pair<int,int> obtainCoordinatesNode(int);
	void generateMarketsOffer();
	void generateCustomersDemand();
	void generateServiceTimesCustomers(string);
	void transformationToNonCapacitated();
	bool inactiveCustomers();
	bool inactiveMarkets();
	void exportToFile();
	string intToString(int);
	void generateStock();
	bool inactiveProducts();
};


} /* namespace std */

#endif /* INSTANCE_H_ */
