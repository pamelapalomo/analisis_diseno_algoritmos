/*
 * Instance.cpp
 *
 *  Created on: Mar 10, 2017
 *      Author: pamela
 */

#include "Instance.h"

namespace std {

Instance::Instance(string input) {
	name=input;
	string path("./Instancias/");
	path+=input;

	ifstream data;
	data.open(path.c_str());


	//Read problem data
	string dummy_str;
	data>>dummy_str>>number_of_variables>>number_of_clauses;

	clauses_list=new Clause[number_of_clauses];
	variable_clauses_set=new set<int>[number_of_variables+1];

	//Read clauses
	int clause_id=0;
	for(int i=0;i<number_of_clauses;i++){
		if(data.eof()) break;

		//Read variables of each clause
		Clause _clause;
		while(true){
			int variable;
			data>>variable;
			if(variable!=0) _clause.push_back(variable);
			else break;
		}

		clauses_list[clause_id]=_clause;

		for(Clause::iterator it=_clause.begin();it!=_clause.end();it++){
			int variable_id=*it;
			if(variable_id<0) variable_id=0-variable_id;
			variable_clauses_set[variable_id].insert(clause_id);
		}
		clause_id++;
	}

	data.close();
}

Instance::~Instance() {
	delete clauses_list;
	delete variable_clauses_set;
}

void Instance::print(){
	cout<<"Instance: "<<name<<endl;
	cout<<"Number of variables: "<<number_of_variables<<endl;
	cout<<"Number of clauses: "<<number_of_clauses<<endl;

	for(int i=0;i<number_of_clauses;i++){
		cout<<"Clause "<<i<<": ";
		for(Clause::iterator it=clauses_list[i].begin();it!=clauses_list[i].end();it++){
			cout<<*it<<"\t";
		}
		cout<<endl;
	}
	cout<<endl<<"Clauses containing: "<<endl;
	for(int i=1;i<=number_of_variables;i++){
		cout<<"Variable "<<i<<":\n";
		for(set<int>::iterator it=variable_clauses_set[i].begin();it!=variable_clauses_set[i].end();it++){
			cout<<*it<<"\t";
		}
		cout<<endl;
	}
}
} /* namespace std */

