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

// double cost(MatrixXd &err, MatrixXd &label) {
//     int m = err.rows();
//     double sum_err = 0;
//     for (int i = 0; i < m; i++) {
//         int gt = (int)(label(i, 0));
//         double v = err(i, gt);
//         if (v > 0) {
//             sum_err += -std::log(v);
//         } else {
//             sum_err += 0;
//         }
//     }
//     return sum_err / m;
// }

void load_data(std::string fname, MatrixXd &data_matrix, MatrixXd &label_data) {
    auto data = load_data_double(fname, "\t");
    int feature_num = data[0].size() - 1;
    data_matrix.resize(data.size(), feature_num);
    label_data.resize(data.size(), 1);
    for (int row = 0; row < data.size(); row++) {
        auto row_data = data[row];
        for (int col = 0; col < row_data.size() - 1; col++) {
            data_matrix(row, col) = row_data[col];
        }

        label_data(row, 0) = row_data[row_data.size() - 1] * 2 - 1; //转换成{-1,1}
    }
}

// Softmax gradient_ascent(MatrixXd &feature_matrix, MatrixXd &label_data, double lr, int steps) {
//     int feature_num = feature_matrix.cols();
//     int num_class = (int)(label_data.maxCoeff()) + 1;
//     std::cout << "Class: " << num_class << std::endl;
//     Softmax lr_model(feature_num, num_class);
//     for (int i = 0; i < steps; i++) {
//         auto target = lr_model.predict(feature_matrix);

//         if (i % 500 == 0) {
//             double loss = cost(target, label_data);
//             std::cout << "\t---------iter = " << i << " loss: " << loss << std::endl;
//         }

//         int m = target.rows();
//         MatrixXd grad = target;
//         for (int j = 0; j < m; j++) {
//             int gt = (int)(label_data(j, 0));
//             grad(j, gt) -= 1;
//         }
//         grad *= -1;

//         MatrixXd diff = (lr / m) * feature_matrix.transpose() * grad; //应该 除以 batch_size
//         lr_model.update_weights(diff);
//     }
//     return lr_model;
// }

int main(int argc, char *argv[]) {
    //加载数据，数据格式 v1, v2 label
    std::cout << "---------- 1.load data ------------" << std::endl;
    MatrixXd data_matrix;
    MatrixXd label_data;
    load_data(argv[1], data_matrix, label_data);
    
    // //训练模型
    // std::cout << "---------- 2.training ------------" << std::endl;
    // Softmax lr_model = gradient_ascent(feature_matrix, label_data, 0.4, 10000);

    // std::cout << "---------- 3.save model ------------" << std::endl;
    // string model_path = "softmax_weights";
    // std::cout << "\tsave model to : " << model_path;
    // lr_model.save(model_path);
}
