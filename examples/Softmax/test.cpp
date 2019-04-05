#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include "utils.h"
#include "model.h"
using namespace std;

Softmax load_model(std::string fname) {
    Softmax lr_model;
    lr_model.load(fname);
    return lr_model;
}

MatrixXd load_data(int num, int feature_num) {
    MatrixXd feature_matrix = MatrixXd::Zero(num, feature_num);
    for (int row = 0; row < feature_matrix.rows(); row++) {
        feature_matrix(row, 0) = 1; // [1, v1, v2]， 1 为bias
        feature_matrix(row, 1) = rand() % 6 - 3;
        feature_matrix(row, 2) = rand() % 15;
    }
    return feature_matrix;
}

void save_result(std::string fname, MatrixXd feature_matrix, MatrixXd &result) {
    ofstream out(fname.c_str(), ios::out);
    for (int i = 0; i < result.rows(); i++) {
        for(int j = 1; j < feature_matrix.cols(); j++){
            out << std::setprecision(16) << feature_matrix(i, j) << "\t";
        }
        out << std::setprecision(16) << result(i, 0) << "\t" << result(i, 1) << std::endl;
    }
}

MatrixXd predict(Softmax &model, MatrixXd &feature_matrix){
    MatrixXd result = model.predict(feature_matrix);
    MatrixXd predict = MatrixXd::Zero(result.rows(), 2);
    
    for(int i = 0; i < result.rows(); i++){
        MatrixXd::Index  max_index;
        double max_val = result.row(i).maxCoeff(&max_index);
        predict(i, 0) = max_index;
        predict(i, 1) = max_val;
    }
    return predict;
}

int main(int argc, char *argv[]) {
    std::cout << "---------- 1.load model ------------" << std::endl;
    Softmax lr_model = load_model("softmax_weights");

    std::cout << "---------- 2.load data ------------" << std::endl;
    MatrixXd  feature_matrix = load_data(100, lr_model.weights().rows());

    std::cout << "---------- 3.get prediction ------------" << std::endl;
    MatrixXd result_classes = predict(lr_model, feature_matrix);

    std::cout << "---------- 4.save prediction ------------" << std::endl;
    save_result("result", feature_matrix, result_classes);
}
