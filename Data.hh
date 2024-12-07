#ifndef DATA_HH
#define DATA_HH

#include <vector>
#include <string>
# include <cmath>

class Data {
 public:
  Data(const std::string& filename);

  unsigned int size() const { return m_data.size(); }
  double measurement(int i) const { return m_data[i]; }
  double binCenter(int i) const { return m_bins[i] + (m_bins[i + 1] - m_bins[i]) / 2; }
  double binLow(int i) const { return m_bins[i]; }
  double binHigh(int i) const { return m_bins[i + 1]; }
  double error(int i) const { return m_errors[i]; }

  double error_prop(double e1, double e2) {
    return std::sqrt(e1 * e1 + e2 * e2);
  }

  bool check_compatibility_single(Data d1, int bin, int n);

  int checkCompatibility(const Data& in, int n);

  Data operator+(Data& in);

  double chi2();

  std::string name() { return m_name; }

 private:
  Data() {}  // disallow empty data set
  void assertSizes();
  std::vector<double> m_data;
  std::vector<double> m_bins;
  std::vector<double> m_errors;
  std::string m_name;
};

#endif
