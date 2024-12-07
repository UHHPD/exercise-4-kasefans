#include "Data.hh"

#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>

using namespace std;

Data::Data(const std::string& filename) {
  ifstream file(filename);

  // check if file opened correctly
  if (!file.is_open()) {
    throw std::runtime_error("Error could not open file with name: " +
                             filename);
  }

  int size = -1;
  file >> size;

  // read in data from file: m_siz+1 bin edges
  for (int i = 0; i < size + 1; ++i) {
    double edge;
    file >> edge;
    m_bins.push_back(edge);
  }
  // read in data from file: m_siz bin contents
  for (int i = 0; i < size; ++i) {
    double entries;
    file >> entries;
    m_data.push_back(entries);
  }
  // read in uncertainties from file: m_siz errors
  for(int i = 0; i < size; ++i){
    double uncertainties;
    file >> uncertainties;
    m_errors.push_back(uncertainties);
  }

  // done! close the file
  file.close();

  assertSizes();

};

void Data::assertSizes() { assert(m_data.size() + 1 == m_bins.size()); }

bool Data::check_compatibility_single(Data d1, int bin, int n) {
  double error = error_prop(d1.error(bin), this->error(bin));
  return std::abs (d1.measurement(bin) - this->measurement(bin)) < n * error;
}

int Data::checkCompatibility(const Data& in, int n) {
  int comp = 0;
  int notcomp = 0;
  for(int i = 0; i < in.size(); i++) {
    if (this->check_compatibility_single(in, i, n)) {
      comp++;
    }
    else {
      notcomp++;
    }
  }
  return notcomp;
}

Data Data::operator+(Data& in){
  Data out;
  for (int i = 0; i < in.size(); i++) {
    double w1 = 1 / (this->error(i) * this->error(i));
    double w2 = 1 / (in.error(i) * in.error(i));
    double y1 = this->measurement(i);
    double y2 = in.measurement(i);
    
    out.m_data.push_back((w1 * y1 + w2 * y2) / (w1 + w2));
    out.m_errors.push_back(std::sqrt(1 / (w1 + w2)));
  }
  return out;
}
