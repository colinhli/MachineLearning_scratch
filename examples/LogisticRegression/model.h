#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
using Eigen::MatrixXd;

class LogisticRegression {
  public:
    LogisticRegression() {

    }
    LogisticRegression(int feature_num) {
        this->weights_ = MatrixXd::Ones(feature_num, 1);
    }
    MatrixXd predict(MatrixXd &x) {
        MatrixXd target = x * this->weights_;
        // target.exp();  //unsupported
        target = 1 / (1 + (-target).array().exp());
        return target;
    }
    void update_weights(MatrixXd &diff) {
        this->weights_ += diff;
    }
    void save(std::string fname) {
        ofstream out(fname.c_str(), ios::out);
        for (int i = 0; i < weights_.rows(); i++) {
            if (i != 0) {
                out << "\t";
            }
            out << std::setprecision(16)  << weights_(i, 0);
        }

    }
    void load(std::string fname) {
        auto data = load_data_double(fname, "\t");
        assert(data.size() == 1);
        weights_.resize(data[0].size(), 1);

        auto row_data = data[0];
        for (int col = 0; col < row_data.size(); col++) {
            weights_(col, 0) = row_data[col];
        }

    }
    const MatrixXd &weights() const {
        return this->weights_;
    }
  private:
    MatrixXd weights_;
};

