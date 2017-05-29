/*
 * Solution.cpp
 *
 *  Created on: Mar 10, 2017
 *      Author: pamela
 */

#include "Solution.h"

namespace std {

Solution::Solution(Instance* pd) {
	problem_data=pd;
	nsatisfied_clauses=0;
	for(int i=0;i<=problem_data->getNumberOfVariables();i++) this->push_back(false);
}

Solution::Solution(const Solution &other){
	problem_data=other.problem_data;
	nsatisfied_clauses=other.nsatisfied_clauses;
	for(int i=0;i<=problem_data->getNumberOfVariables();i++) this->push_back(other.at(i));
}

Solution::~Solution() {
	// TODO Auto-generated destructor stub
}

void Solution::evaluate(){
	nsatisfied_clauses=0;
	for(int i=0;i<problem_data->getNumberOfClauses();i++){
		list<int> _clause=problem_data->getClause(i);

		for(Clause::iterator it=_clause.begin();it!=_clause.end();it++){
			if((*it>0 && this->at(abs(*it))) || (*it<0 && !this->at(abs(*it)))){
				nsatisfied_clauses++;
				break;
			}
		}
	}
}

int Solution::evaluateChange(int variable_id){
	int incrementSAT=0;
	set<int> clauses_containingv=problem_data->getClausesContainingVariable(variable_id);

	for(set<int>::iterator it=clauses_containingv.begin();it!=clauses_containingv.end();it++){
		list<int> _clause=problem_data->getClause(*it);
		bool SAT=false;
		bool SAT_after_change=false;
		for(Clause::iterator itc=_clause.begin();itc!=_clause.end();itc++){
			if((*itc>0 && this->at(abs(*itc))) || (*itc<0 && !this->at(abs(*itc)))){
				SAT=true;
				if(abs(*itc)!=variable_id) SAT_after_change=true;
			}
			else if(abs(*itc)==variable_id) SAT_after_change=true;

			if(SAT && SAT_after_change) break;
		}

		if(SAT && !SAT_after_change) incrementSAT--;
		if(!SAT && SAT_after_change) incrementSAT++;
	}

	return incrementSAT;
}

bool Solution::operator <(const Solution other) const{
	if(this->nsatisfied_clauses<other.nsatisfied_clauses) return false;
	if(this->nsatisfied_clauses>other.nsatisfied_clauses) return true;
	for(int i=1;i<=problem_data->getNumberOfVariables();i++){
		if(!this->at(i) && other.at(i)) return true;
		if(this->at(i) && !other.at(i)) return false;
	}

	return false;
}

void Solution::print(){
	cout<<nsatisfied_clauses<<": ";
	for(int i=1;i<=problem_data->getNumberOfVariables();i++){
		if(this->at(i)) cout<<"1 ";
		else cout<<"0 ";
	}
	cout<<endl;
}

} /* namespace std */
