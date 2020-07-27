/*
 * @author hans@dkmt.io
 * @since 2020-07-15
 */

#include "CHistogram.h"
#include "histogram.h"

#include <mutex>
#include <thread>

namespace
{

  class Histogram
  {
  public:
    Histogram() : histogramImpl(new dkmt::leveldb::Histogram()) {}
    virtual ~Histogram() {}
    dkmt::leveldb::Histogram *histogramImpl;
    std::mutex mutex;

  private:
    Histogram(const Histogram &) {}
    Histogram &operator=(const Histogram &) { return *this; }
  };

} // anonymous namespace

CHistogram CHistogramInit()
{
  Histogram *histogram = new Histogram();
  histogram->histogramImpl->Clear();
  return (CHistogram)histogram;
}

void CHistogramFree(CHistogram chistogram)
{
  Histogram *histogram = (Histogram *)chistogram;
  delete histogram->histogramImpl;
  delete histogram;
}

void CHistogramAdd(CHistogram chistogram, double value)
{
  Histogram *histogram = (Histogram *)chistogram;
  const std::lock_guard<std::mutex> lock(histogram->mutex);
  histogram->histogramImpl->Add(value);
}

const char *CHistogramToString(CHistogram chistogram)
{
  Histogram *histogram = (Histogram *)chistogram;
  return histogram->histogramImpl->ToString().c_str();
}
