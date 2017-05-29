/*
 * Market.cpp
 *
 *  Created on: Feb 23, 2017
 *      Author: pamela
 */

#include "Market.h"

namespace std {

Market::Market():Node() {

}

Market::Market(const Market &other):Node(other){
	offer_market=other.offer_market;
}

Market::~Market() {
	// TODO Auto-generated destructor stub
}

void Market::updateOffer(int product_id, int quantity){
	map<int,offer>::iterator it=offer_market.find(product_id);
	it->second.stock=quantity;
}

void Market::clearOffer(){
	offer_market.clear();
}

bool Market::isActive(){
	return (offer_market.size()>0);
}


} /* namespace std */
