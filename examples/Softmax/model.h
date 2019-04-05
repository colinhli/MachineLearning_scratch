#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
using Eigen::MatrixXd;
using Eigen::RowVectorXd;
using Eigen::VectorXd;

class Softmax {
  public:
    Softmax() {
    }
    Softmax(int input_size, int output_size) {
        this->weights_ = MatrixXd::Ones(input_size, output_size);
    }
    MatrixXd predict(MatrixXd &x) {
        MatrixXd target = x * this->weights_;
        // target.transposeInPlace();
        // MatrixXd max_v = target.colwise().maxCoeff();
        // std::cout << "row max" <<std::endl;
        // std::cout << max_v.rows() << " " << max_v.cols() <<std::endl;
        // std::cout << target.rows() << " " << target.cols() <<std::endl;
        // RowVectorXd max_vector = max_v;
        // std::cout << "target" <<std::endl;
        // std::cout << target << std::endl;
        // std::cout << "max_vector" <<std::endl;
        // std::cout << max_vector <<std::endl;
        // target.rowwise() -= max_vector;
        target = target.array().exp();
        MatrixXd S = target.rowwise().sum();
        // S = S.array().inverse();
        VectorXd e_s = S;
        MatrixXd y = target.array().colwise() / e_s.array();
        return y;
    }
    void update_weights(MatrixXd &diff) {
        this->weights_ += diff;
    }
    void save(std::string fname) {
        ofstream out(fname.c_str(), ios::out);
        for (int i = 0; i < weights_.rows(); i++) {
            for (int j = 0; j < weights_.cols(); j++) {
                if (j != 0) {
                    out << "\t";
                }
                out << std::setprecision(16) << weights_(i, j);
            }
            out << std::endl;
        }
    }

    void load(std::string fname) {
        auto data = load_data_double(fname, "\t");
        weights_.resize(data.size(), data[0].size());

        for (int row = 0; row < data.size(); row++) {
            auto row_data = data[row];
            for (int col = 0; col < row_data.size(); col++) {
                weights_(row, col) = row_data[col];
            }
        }
    }

    const MatrixXd &weights() const {
        return this->weights_;
    }

  private:
    MatrixXd weights_;
};
