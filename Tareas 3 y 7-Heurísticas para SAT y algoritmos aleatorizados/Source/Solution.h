/*
 * Solution.h
 *
 *  Created on: Mar 10, 2017
 *      Author: pamela
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_

#include "Instance.h"

namespace std {

class Solution:public vector<bool> {
private:
	Instance* problem_data;
	int nsatisfied_clauses;
public:
	Solution(Instance*);
	Solution(const Solution &);
	virtual ~Solution();

	//Methods
	void evaluate();
	int evaluateChange(int);

	//Getters
	int getNumberOfSatisfiedClauses(){return nsatisfied_clauses;}

	//Setters
	void setNumberOfSatisfiedClauses(int nSAT){nsatisfied_clauses=nSAT;}

	bool operator<(const Solution)const ;
	void print();
};

} /* namespace std */

#endif /* SOLUTION_H_ */
