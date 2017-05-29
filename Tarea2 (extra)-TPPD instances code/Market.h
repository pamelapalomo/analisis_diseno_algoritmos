/*
 * Market.h
 *
 *  Created on: Feb 23, 2017
 *      Author: pamela
 */

#ifndef MARKET_H_
#define MARKET_H_

#include "Node.h"

struct offer{
	int stock;
	int price;
};

namespace std {

class Market:public Node {
private:
	map<int,offer> offer_market;
public:
	Market();
	Market(const Market &);
	virtual ~Market();

	void updateOffer(int, int);
	void clearOffer();
	bool isActive();

	void setOffer(int product_id, int quantity, int price){offer this_offer; this_offer.price=price; this_offer.stock=quantity;offer_market[product_id]=this_offer;}

	int getOffer(int product_id){map<int,offer>::iterator it=offer_market.find(product_id); if(it!=offer_market.end()) return it->second.stock; return 0;}
	int getPrice(int product_id){map<int,offer>::iterator it=offer_market.find(product_id); if(it!=offer_market.end()) return it->second.price; return 0;}
};

} /* namespace std */

#endif /* MARKET_H_ */
