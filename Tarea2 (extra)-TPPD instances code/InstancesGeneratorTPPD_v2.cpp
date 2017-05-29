//============================================================================
// Name        : InstancesGeneratorTPPD_v2.cpp
// Author      : Pamela Jocelyn Palomo Martinez. Graduate Program in Systems Engineering. Universidad Autonoma de Nuevo Leon
// Version     : 2
// Description : Instances generator for the TPPD
//============================================================================

#include "Instance.h"
using namespace std;

int main(int argc, char** argv) {

	Instance problem_data_c(atoi(argv[1]), atoi(argv[2]));

	//Capacitated instance and repairs are required
	cout<<"Instancia 1"<<endl;
	Instance problem_data_c_r(problem_data_c);
	problem_data_c_r.generateServiceTimesCustomers("r");
	problem_data_c_r.exportToFile();

	//Capacitated instance and repairs are not required
	cout<<"Instancia 2"<<endl;
	Instance problem_data_c_nr(problem_data_c);
	problem_data_c_nr.generateServiceTimesCustomers("nr");
	problem_data_c_nr.exportToFile();

	//Non capacitated instance and repairs are required
	cout<<"Instancia 3"<<endl;
	Instance problem_data_nc_r(problem_data_c_r);
	problem_data_nc_r.transformationToNonCapacitated();
	problem_data_nc_r.exportToFile();

	//Non capacitated instance and repairs are not required
	cout<<"Instancia 4"<<endl;
	Instance problem_data_nc_nr(problem_data_c_nr);
	problem_data_nc_nr.transformationToNonCapacitated();
	problem_data_nc_nr.exportToFile();

	return 0;
}
