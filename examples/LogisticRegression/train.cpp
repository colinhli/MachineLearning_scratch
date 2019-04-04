#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include "utils.h"
#include "model.h"
using namespace std;

#include <Eigen/Dense>
using Eigen::MatrixXd;

/***
 * 计算当前的损失函数值
***/

double error_rate(MatrixXd &h, MatrixXd &label){
    int m = h.rows();
    double sum_err = 0;
    for(int i = 0; i < m; i++){
        if (h(i, 0) > 0 and (1 - h(i, 0)) > 0){
            sum_err -= label(i, 0) * std::log(h(i, 0)) + (1 - label(i, 0)) * std::log(1 - h(i, 0));
        }else{
            sum_err -= 0;
        }
        
    }
    return sum_err / m;
}

void load_data(std::string fname, MatrixXd &feature_matrix, MatrixXd &label_data){
    auto data = load_data_double(fname, "\t");
    int feature_num = data[0].size() - 1 + 1;
    feature_matrix.resize(data.size(), feature_num);
    label_data.resize(data.size(), 1);
    for (int row = 0; row < data.size(); row++) {
        auto row_data = data[row];
        feature_matrix(row, 0) = 1; // [1, v1, v2]， 1 为bias
        for (int col = 0; col < row_data.size() - 1; col++) {
            feature_matrix(row, col + 1) = row_data[col];
        }

        label_data(row, 0) = row_data[row_data.size() - 1];
    }
}

LogisticRegression lr_train_bgd(MatrixXd &feature_matrix, MatrixXd &label_data, double lr, int steps){
    int feature_num = feature_matrix.cols();
    LogisticRegression lr_model(feature_num);
    for (int i = 0; i < steps; i++) {
        auto target = lr_model.predict(feature_matrix);

        auto error = label_data - target;
        double loss = error_rate(target, label_data);
        if (i % 100 == 0){
            std::cout << "\t---------iter = " << i <<  " loss: " << error_rate(target, label_data) << std::endl;
        }
        
        MatrixXd diff = lr * feature_matrix.transpose() * error;
        lr_model.update_weights(diff);
    }
    return lr_model;
}

int main(int argc, char *argv[]) {
    //加载数据，数据格式 v1, v2 label
    std::cout << "---------- 1.load data ------------" << std::endl;
    MatrixXd  feature_matrix;
    MatrixXd  label_data;
    load_data(argv[1], feature_matrix, label_data);

    //训练模型
    std::cout << "---------- 2.training ------------" << std::endl;
    LogisticRegression lr_model = lr_train_bgd(feature_matrix, label_data, 0.01, 1000); 

    std::cout << "---------- 3.save model ------------" << std::endl;
    string model_path = "logistic_regression_weights";
    std::cout << "\tsave model to : " << model_path;
    lr_model.save(model_path);
}
