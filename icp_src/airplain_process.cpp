#include <iostream>
#include <vector>
#include <numeric>
#include <sys/time.h>
#include "Eigen/Eigen"
#include "icp.h"
#include "data_io.h"
#include <random>
// #include <sdsl/k2_treap.hpp>
// #include <sdsl/bit_vectors.hpp>
#include <complex>
#include <string>
#include <tuple>
#include <vector>


using namespace std;
using namespace Eigen;
using namespace sdsl;

int main(int argc, char *argv[]){

    std::random_device rd;
    std::mt19937 gen(rd());

    std::string filename = "airplane_0001.txt";
    MatrixXd pcl_data = load_pcl(file_name);
    int num_point = pcl_data.rows();
    std::cout<<num_point<<std::endl;

}



