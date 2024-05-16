/*
A simple demo for ICP algorithm
*/
#include <iostream>
#include <vector>
#include <numeric>
#include <sys/time.h>
#include "Eigen/Eigen"
#include "icp.h"
#include "data_io.h"
#include <random>
#include <fstream>


using namespace std;
using namespace Eigen;


#define noise_sigma 1e-4    // standard deviation error to be added
#define translation 1     // max translation of the test set
#define rotation 1        // max rotation (radians) of the test set

float my_random(void);
Matrix3d rotation_matrix(Vector3d axis, float theta);
void test_best_fit(void);
void test_icp(void);
void my_random_shuffle(MatrixXd &matrix);

void saveVectorToFile(const std::vector<std::vector<float>>& vec, const std::string& filename) {
    std::ofstream outFile;
    outFile.open(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    for (const auto& row : vec) {
        for (const auto& elem : row) {
            outFile << elem << " ";
        }
        outFile << std::endl;
    }

    outFile.close();
}


unsigned GetTickCount()
{
        struct timeval tv;
        if(gettimeofday(&tv, NULL) != 0)
                return 0;

        return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

std::vector<std::vector<float>> toVector(Eigen::MatrixXd& matrix)
{
    std::vector<std::vector<float>> result(matrix.rows(), std::vector<float>(matrix.cols()));
    for (int i = 0; i < matrix.rows(); i++)
    {
        for (int j = 0; j<matrix.row(i).size(); j++)
        {
            result[i][j] = matrix.row(i)[j];
        }
    }
    return result;
}

int main(int argc, char *argv[]){


    std::random_device rd;
    std::mt19937 gen(rd());

    std::string base_dir = "/home/ziyang/sdsl-lite/modelnet40/";
    std::string file_name = base_dir + "airplane_0001.txt";
    MatrixXd pcl_data = load_pcl(file_name);
    int num_point = pcl_data.rows();
    VectorXd row1 = pcl_data.row(1);

    std::vector<std::vector<float>> pcl_data_vec = toVector(pcl_data);

    std::vector<std::vector<float>> sample(6, vector<float>(pcl_data.row(0).size(), 0));
    for (int i = 0; i<sample.size(); i++){
        for(int j = 0; j< pcl_data.row(0).size(); j++)
        {
            sample[i][j] = int(pcl_data_vec[i][j]*100);
        }
    }

    saveVectorToFile(sample, "empty.txt");

    // for (int i = 0; i< pcl_data.rows(); i++){

    //     for(int j = 0; j<pcl_data.row(i).size(); j++){
    //         // 将矩阵中每个数都转化为整数
    //         pcl_data.row(i)[j]= pcl_data.row(i)[j]*100000;
    //     }
    // }

    // for (int i =0; i<row1.size(); i++)
    // {
    //     row1 = row1*100;
    // }
    // cout<<row1<<endl;

    return 0;
}



///////////////////////////
//  help function

// 0-1 float variables
float my_random(void){
    float tmp = rand()%100;
    return tmp/100;
}

void my_random_shuffle(MatrixXd &matrix){
    int row = matrix.rows();
    vector<Vector3d> temp;
    for(int jj=0; jj < row; jj++){
        temp.push_back(matrix.block<1,3>(jj,0));
    }
    random_shuffle(temp.begin(),temp.end());
    for(int jj=0; jj < row; jj++){
        matrix.block<1,3>(jj,0) = temp[jj].transpose();
        // cout << temp[jj].transpose() << endl;
        // cout << "row  " << row << endl;
    }
}


Matrix3d rotation_matrix(Vector3d axis, float theta){
    axis = axis / sqrt(axis.transpose()*axis);
    float a = cos(theta/2);
    Vector3d temp = -axis*sin(theta/2);
    float b,c,d;
    b = temp(0);
    c = temp(1);
    d = temp(2);
    Matrix3d R;
    R << a*a+b*b-c*c-d*d, 2*(b*c-a*d), 2*(b*d+a*c),
        2*(b*c+a*d), a*a+c*c-b*b-d*d, 2*(c*d-a*b),
        2*(b*d-a*c), 2*(c*d+a*b), a*a+d*d-b*b-c*c;

    return R;
}





