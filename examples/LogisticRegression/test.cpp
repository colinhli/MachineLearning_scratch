#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include "utils.h"
#include "model.h"
using namespace std;

LogisticRegression load_model(std::string fname) {
    LogisticRegression lr_model;
    lr_model.load(fname);
    return lr_model;
}

void load_data(std::string fname, MatrixXd &feature_matrix) {
    auto data = load_data_double(fname, "\t");
    int feature_num = data[0].size() + 1;
    feature_matrix.resize(data.size(), feature_num);
    for (int row = 0; row < data.size(); row++) {
        auto row_data = data[row];
        feature_matrix(row, 0) = 1; // [1, v1, v2]， 1 为bias
        for (int col = 0; col < row_data.size(); col++) {
            feature_matrix(row, col + 1) = row_data[col];
        }
    }
}

void save_result(std::string fname, MatrixXd &result) {
    ofstream out(fname.c_str(), ios::out);
    for (int i = 0; i < result.rows(); i++) {
        out << std::setprecision(16)  << result(i, 0) << "\n";
    }
}

MatrixXd predict(LogisticRegression &model, MatrixXd &feature_matrix){
    MatrixXd result = model.predict(feature_matrix);
    auto func = [](double value)->double{
        return value > 0.5 ? 1.0 : 0;
    };
    return result.unaryExpr(func);
}
int main(int argc, char *argv[]) {
    std::cout << "---------- 1.load model ------------" << std::endl;
    LogisticRegression lr_model = load_model("logistic_regression_weights");

    std::cout << "---------- 2.load data ------------" << std::endl;
    MatrixXd  feature_matrix;
    load_data(argv[1], feature_matrix);

    std::cout << "---------- 3.get prediction ------------" << std::endl;
    MatrixXd result = predict(lr_model, feature_matrix);

    std::cout << "---------- 4.save prediction ------------" << std::endl;
    save_result("result", result);
}
