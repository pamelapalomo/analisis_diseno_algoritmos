/*
 * Instance.cpp
 *
 *  Created on: Feb 23, 2017
 *      Author: pamela
 */

#include "Instance.h"

namespace std {

Instance::Instance(int nnodes, int nproducts) {
	srand(time(NULL));

	number_of_nodes=nnodes;
	number_of_products=nproducts;
	//Generate stock
	generateStock();

	//Determine the proportion of markets and customers
	generateNumberOfMarketsCustomers();

	//Generate nodes coordinates
	generateNodesCoordinates();

	//Generate markets service time
	generateServiceTimesMarkets();

	//Generate different categories of products
	generateProductCategories();

	//Generate offer
	generateMarketsOffer();

	//Generate demand
	generateDemand();

	capacitated="c";
}

Instance::Instance(const Instance &other){
	number_of_nodes=other.number_of_nodes;
	number_of_customers=other.number_of_customers;
	number_of_markets=other.number_of_markets;
	number_of_products=other.number_of_products;

	depot=new Node(*other.depot);

	customer_set=new Customer*[number_of_customers];
	for(int i=0;i<number_of_customers;i++) customer_set[i]=new Customer(*other.customer_set[i]);

	market_set=new Market*[number_of_markets];
	for(int i=0;i<number_of_markets;i++) market_set[i]=new Market(*other.market_set[i]);

	initial_stock=new int[number_of_products];
	for(int i=0;i<number_of_products;i++) initial_stock[i]=other.initial_stock[i];

	average_traveling_time=other.average_traveling_time;
	demand_level=other.demand_level;
	service_to_customers=other.service_to_customers;
	capacitated=other.capacitated;
}

Instance::~Instance() {
	delete depot;

	for(int i=0;i<number_of_markets;i++){
		delete market_set[i];
	}
	delete market_set;

	for(int i=0;i<number_of_customers;i++){
		delete customer_set[i];
	}
	delete customer_set;
}

void Instance::generateNumberOfMarketsCustomers(){
	int random_int=rand()%3;
	switch(random_int){
	case 0:{
		number_of_customers=int(round(0.1*(number_of_nodes-1)));
		break;
	}
	case 1:{
		number_of_customers=int(round(0.5*(number_of_nodes-1)));
		break;
	}
	case 2:{
		number_of_customers=int(round(0.9*(number_of_nodes-1)));
		break;
	}
	}
	number_of_markets=number_of_nodes-number_of_customers-1;
}

void Instance::generateNodesCoordinates(){
	depot=new Node();

	market_set=new Market*[number_of_markets];
	for(int i=0;i<number_of_markets;i++){
		market_set[i]=new Market();
	}

	customer_set=new Customer*[number_of_customers];
	for(int i=0;i<number_of_customers;i++){
		customer_set[i]=new Customer();
	}
}

void Instance::generateProductCategories(){
	for(int i=0;i<number_of_products;i++){
		int random_int=rand()%3;
		switch(random_int){
		case 0:{
			cheap_products.push_back(i);
			break;
		}
		case 1:{
			medium_products.push_back(i);
			break;
		}
		case 2:{
			expensive_products.push_back(i);
			break;
		}
		}
	}
}

void Instance::generateDemand(){

	//Determine the demand level
	int random_int=rand()%3;
	float proportion_demand_offer=0;
	if(random_int==0){
		demand_level="l";
		proportion_demand_offer=0.1;
	}
	else if(random_int==1){
		demand_level="m";
		proportion_demand_offer=0.5;
	}
	else{
		demand_level="h";
		proportion_demand_offer=0.9;
	}

	while(inactiveCustomers()){

		for(int i=0;i<number_of_customers;i++) customer_set[i]->clearDemand();

		for(int i=0;i<number_of_products;i++){
			//Determine the total offer
			int total_offer_product=0;
			for(int j=0;j<number_of_markets;j++) total_offer_product+=market_set[j]->getOffer(i);

			//Select the number of customers that require this product
			int ncustomers_product=rand()%(min(total_offer_product,number_of_customers))+1;

			//Determine the required quantities
			int sum=0;
			int customers_demand[ncustomers_product];
			for(int j=0;j<ncustomers_product;j++){
				customers_demand[j]=rand()%10+1;
				sum+=customers_demand[j];
			}

			for(int j=0;j<ncustomers_product;j++) customers_demand[j]=int (round(float (customers_demand[j]*total_offer_product*proportion_demand_offer)/float (sum)));

			//Select the set of customers that require this product
			set<int> customers_product_set;
			while(customers_product_set.size()<ncustomers_product){
				int random_customer=rand()%number_of_customers;
				customers_product_set.insert(random_customer);
			}

			//Set the demands
			int aux=0;
			for(set<int>::iterator it=customers_product_set.begin();it!=customers_product_set.end();it++){
				customer_set[*it]->setDemand(i,customers_demand[aux]);
				aux++;
			}

		}
	}
}

int Instance::obtainProductCategory(int product_id){
	list<int>::iterator it=find(cheap_products.begin(),cheap_products.end(),product_id);
	if(it!=cheap_products.end()) return 0;

	it=find(medium_products.begin(),medium_products.end(),product_id);
	if(it!=medium_products.end()) return 1;

	return 2;
}

void Instance::generateServiceTimesMarkets(){
	float average=0;
	for(int i=0;i<number_of_nodes;i++){
		for(int j=0;j<i;j++){
			pair<int,int> coordinates_i=obtainCoordinatesNode(i);
			pair<int,int> coordinates_j=obtainCoordinatesNode(j);
			average+=(2.0*(sqrt(pow(coordinates_i.first-coordinates_j.first,2)+pow(coordinates_i.second-coordinates_j.second,2))))/float (number_of_nodes*(number_of_nodes-1)/2.0);
		}
	}
	average_traveling_time=int (round(average));

	for(int i=0;i<number_of_markets;i++){
		market_set[i]->setServiceTime(rand()%average_traveling_time+1);
	}
}

pair<int,int> Instance::obtainCoordinatesNode(int node_id){
	if(node_id==0) return pair<int,int>(depot->getXCoordinate(),depot->getYCoordinate());
	if(node_id<=number_of_markets) return pair<int,int>(market_set[node_id-1]->getXCoordinate(),market_set[node_id-1]->getYCoordinate());
	return pair<int,int>(customer_set[node_id-1-number_of_markets]->getXCoordinate(),customer_set[node_id-1-number_of_markets]->getYCoordinate());
}

void Instance::generateMarketsOffer(){

	while(inactiveMarkets() || inactiveProducts()){

		for(int i=0;i<number_of_markets;i++){
			market_set[i]->clearOffer();

			unsigned int random_nproducts=rand()%number_of_products+1;

			set<int>offer_products;
			while(offer_products.size()<random_nproducts){
				int random_product=rand()%number_of_products;
				offer_products.insert(random_product);
			}

			for(set<int>::iterator it=offer_products.begin();it!=offer_products.end();it++){
				int category=obtainProductCategory(*it);
				switch(category){
				case 0:{
					//cheap product
					market_set[i]->setOffer(*it,rand()%5+11,rand()%200+1);
					break;
				}
				case 1:{
					//Medium product
					market_set[i]->setOffer(*it,rand()%5+6,rand()%200+201);
					break;
				}
				case 2:{
					//Expensive product
					market_set[i]->setOffer(*it,rand()%5+1,rand()%100+401);
					break;
				}
				}
			}
		}
	}
}

void Instance::generateServiceTimesCustomers(string type){
	string repair_str("r");

	if(repair_str.compare(type)==0){
		//Repairs are required (high service times)
		service_to_customers=repair_str;
		for(int i=0;i<number_of_customers;i++) customer_set[i]->setServiceTime(rand()%average_traveling_time+average_traveling_time);
	}
	else{
		//Repairs are not required (low service times)
		service_to_customers="nr";
		for(int i=0;i<number_of_customers;i++) customer_set[i]->setServiceTime(rand()%average_traveling_time);
	}
}

void Instance::transformationToNonCapacitated(){
	capacitated="nc";

	for(int i=0;i<number_of_products;i++){
		int total_demand=0;
		for(int j=0;j<number_of_customers;j++) total_demand+=customer_set[j]->getDemand(i);

		for(int j=0;j<number_of_markets;j++){
			if(market_set[j]->getOffer(i)>0) market_set[j]->updateOffer(i,total_demand);
		}
	}
}

bool Instance::inactiveCustomers(){
	//Determines whether there is an inactive customer or not

	for(int i=0;i<number_of_customers;i++){
		if(!customer_set[i]->isActive()) return true;
	}
	return false;
}

bool Instance::inactiveMarkets(){
	//Determines whether there is an inactive market or not

	for(int i=0;i<number_of_markets;i++){
		if(!market_set[i]->isActive()) return true;
	}
	return false;
}

void Instance::exportToFile(){
	string file_name;
	if(capacitated.compare("c")==0){
		if(service_to_customers.compare("r")==0) file_name="Class 1";
		else file_name="Class 2";
	}
	else{
		if(service_to_customers.compare("r")==0) file_name="Class 3";
		else file_name="Class 4";
	}

	file_name+="/TPPD_"+intToString(number_of_nodes)+"_"+intToString(number_of_markets)+"_"+intToString(number_of_customers)+"_"+intToString(number_of_products)+"_"+capacitated+"_"+service_to_customers+"_"+demand_level+".txt";

	ofstream output(file_name.c_str());

	output<<number_of_nodes<<" "<<number_of_markets<<" "<<number_of_customers<<" "<<number_of_products<<"\n\n";

	output<<depot->getID()<<" "<<depot->getXCoordinate()<<" "<<depot->getYCoordinate()<<" "<<depot->getServiceTime()<<"\n";

	for(int i=0;i<number_of_markets;i++) output<<market_set[i]->getID()<<" "<<market_set[i]->getXCoordinate()<<" "<<market_set[i]->getYCoordinate()<<" "<<market_set[i]->getServiceTime()<<"\n";

	for(int i=0;i<number_of_customers;i++) output<<customer_set[i]->getID()<<" "<<customer_set[i]->getXCoordinate()<<" "<<customer_set[i]->getYCoordinate()<<" "<<customer_set[i]->getServiceTime()<<"\n";
	output<<"\n";
	for(int i=0;i<number_of_products;i++) output<<initial_stock[i]<<" ";
	output<<"\n\n";

	for(int i=0;i<number_of_products;i++){
		for(int j=0;j<number_of_markets;j++){
			output<<market_set[j]->getOffer(i)<<" ";
		}
		output<<"\n";
	}

	output<<"\n";

	for(int i=0;i<number_of_products;i++){
		for(int j=0;j<number_of_markets;j++) output<<market_set[j]->getPrice(i)<<" ";
		output<<"\n";
	}
	output<<"\n";

	for(int i=0;i<number_of_products;i++){
		for(int j=0;j<number_of_customers;j++) output<<customer_set[j]->getDemand(i)<<" ";
		output<<"\n";
	}
}

string Instance::intToString(int number){
	string result;
	ostringstream convert;
	convert << number;
	result = convert.str();

	return result;
}

void Instance::generateStock(){

	initial_stock=new int[number_of_products];
	for(int i=0;i<number_of_products;i++) initial_stock[i]=0;

	int random_nproducts=rand()%number_of_products+1;
	int nproducts=0;

	while(nproducts<random_nproducts){
		int random_id=rand()%number_of_products;
		if(initial_stock[random_id]==0){
			int category=obtainProductCategory(random_id);
				switch(category){
				case 0:{
					//cheap product
					initial_stock[random_id]=rand()%5+11;
					break;
				}
				case 1:{
					//Medium product
					initial_stock[random_id]=rand()%5+6;
					break;
				}
				case 2:{
					//Expensive product
					initial_stock[random_id]=rand()%5+1;
					break;
				}
				}
			nproducts++;
		}
	}
}

bool Instance::inactiveProducts(){
	for(int i=0;i<number_of_products;i++){
		int total_offer=0;
		for(int j=0;j<number_of_markets;j++) total_offer+=market_set[j]->getOffer(i);
		if(total_offer==0) return true;
	}
	return false;
}
} /* namespace std */
