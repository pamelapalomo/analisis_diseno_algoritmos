/*
 * Instance.h
 *
 *  Created on: Mar 10, 2017
 *      Author: pamela
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include "Header.h"

namespace std {

class Clause:public list<int>{};

class Instance {
private:
	int number_of_variables;
	int number_of_clauses;
	string name;
	Clause* clauses_list; //Stores the clauses
	set<int>* variable_clauses_set; //Stores the ids of the clauses containing each variable

public:
	Instance(string);
	virtual ~Instance();

	//Getters
	int getNumberOfVariables(){return number_of_variables;}
	int getNumberOfClauses(){return number_of_clauses;}
	list<int> getClause(int clause_id){return clauses_list[clause_id];}
	set<int> getClausesContainingVariable(int variable_id){return variable_clauses_set[variable_id];}
	string getName(){return name;}

	void print();
};

} /* namespace std */

#endif /* INSTANCE_H_ */
