/*
 * ScatterSearch.cpp
 *
 *  Created on: Mar 10, 2017
 *      Author: pamela
 */

#include "ScatterSearch.h"

namespace std {

ScatterSearch::ScatterSearch(char** input) {
	srand(time(NULL));

	problem_data=new Instance(input[1]);
	cout<<"Resolviendo "<<input[1]<<endl;

	initial_set_size=atoi(input[2]);

	reference_set_size=atoi(input[3]);
	str_ref_set_size=input[3];

	running_time=0;
}

ScatterSearch::~ScatterSearch() {
	// TODO Auto-generated destructor stub
}

void ScatterSearch::solve(){
	clock_t begin=clock();

	//Generate and improve the initial solutions
	set<Solution> initial_set;
	while(initial_set.size()<initial_set_size){
		Solution _solution=generateSolution();
		flip(&_solution);

		initial_set.insert(_solution);
	}


	//Create the reference set
	set<Solution>reference_set=generateReferenceSet(initial_set);
	initial_set.clear();

	//Iterate while the reference set is not improved
	bool improve_refset=true;
	while(improve_refset){
		set<Solution>::iterator it_best=reference_set.begin();
		Solution best=*it_best;
		if(best.getNumberOfSatisfiedClauses()==problem_data->getNumberOfClauses()) break;
		improve_refset=false;
		list<Solution> new_solutions;

		set<Solution>::iterator itw=reference_set.end();
		itw--;
		for(int i=0;i<reference_set_size/2;i++){
			//Combination of solutions
			Solution first=*it_best;
			Solution second=*itw;
			Solution combination=combine(first,second);

			//Improvement of solutions
			flip(&combination);
			new_solutions.push_back(combination);
			it_best++;
			itw--;
		}

		//Update the reference set
		for(list<Solution>::iterator it=new_solutions.begin();it!=new_solutions.end();it++){
			Solution _solution=*it;

			set<Solution>::iterator itb=reference_set.end();
			itb--;
			Solution worst=*itb;
			if(_solution.getNumberOfSatisfiedClauses()>worst.getNumberOfSatisfiedClauses()){

				//The solution could be part of the reference set
				reference_set.insert(_solution);
				if(reference_set.size()>reference_set_size){

					//The solution is unique in the reference set
					reference_set.erase(itb);
					improve_refset=true;
				}
			}
		}

		new_solutions.clear();
	}
	clock_t end=clock();
	running_time= float(end-begin)/float (CLOCKS_PER_SEC);

	//Write results
	set<Solution>::iterator it_best=reference_set.begin();
	reportResult(*it_best);

}

Solution ScatterSearch::generateSolution(){
	Solution _solution(problem_data);
	for (int i = 1; i <= problem_data->getNumberOfVariables(); i++) {
		if (rand() % 2 == 0)
			_solution.at(i) = true;
	}

	_solution.evaluate();

	return _solution;
}

void ScatterSearch::flip(Solution* _solution){
	int i=1;
	while(i<=problem_data->getNumberOfVariables()){
		int incrementSAT=_solution->evaluateChange(i);
		if(incrementSAT>0){
			if(_solution->at(i)) _solution->at(i)=false;
			else _solution->at(i)=true;
			_solution->setNumberOfSatisfiedClauses(_solution->getNumberOfSatisfiedClauses()+incrementSAT);
			i=1;
		}
		else i++;
	}
}

set<Solution> ScatterSearch::generateReferenceSet(set<Solution> _set){
	set<Solution> reference_set;

	//The half of the reference set includes the best evaluated solutions and the other half includes worst evaluated
	set<Solution>::iterator itb=_set.begin();
	set<Solution>::iterator itw=_set.end();
	itw--;
	for(int i=0;i<reference_set_size/2;i++){
		Solution b=*itb;
		Solution w=*itw;
		reference_set.insert(Solution(b));
		reference_set.insert(Solution(w));
		itb++;
		itw--;
	}

	return reference_set;
}

Solution ScatterSearch::combine(Solution first, Solution second){

	Solution combination(problem_data);
	for(int i=1;i<=problem_data->getNumberOfVariables();i++){
		if((first.at(i) && second.at(i)) || (((first.at(i) && !second.at(i)) || (!first.at(i) && second.at(i))) && rand()%2==0)) combination.at(i)=true;
	}
	combination.evaluate();

	return combination;
}

void ScatterSearch::reportResult(Solution best){
	string path("./Resultados/");
	path+=str_ref_set_size+"_"+problem_data->getName();

	ofstream odatas;
	odatas.open(path.c_str(),ofstream::out | ios::app);
	odatas<<best.getNumberOfSatisfiedClauses()<<"\t"<<running_time<<"\t";
	for(int i=1;i<=problem_data->getNumberOfVariables();i++){
		if(best[i]) odatas<<1<<" ";
		else odatas<<0<<" ";
	}
	odatas<<endl;

	odatas.close();
}

} /* namespace std */
