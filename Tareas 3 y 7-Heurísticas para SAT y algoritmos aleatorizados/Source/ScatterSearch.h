/*
 * ScatterSearch.h
 *
 *  Created on: Mar 10, 2017
 *      Author: pamela
 */

#ifndef SCATTERSEARCH_H_
#define SCATTERSEARCH_H_

#include "Solution.h"

namespace std {


class ScatterSearch {
private:
	Instance* problem_data;
	int initial_set_size;
	int reference_set_size;
	string str_ref_set_size;
	float running_time;
public:
	ScatterSearch(char**);
	virtual ~ScatterSearch();

	void solve();
	Solution generateSolution();
	void flip(Solution*);
	set<Solution> generateReferenceSet(set<Solution>);
	Solution combine(Solution, Solution);
	void reportResult(Solution);
};

} /* namespace std */

#endif /* SCATTERSEARCH_H_ */
