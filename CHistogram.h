/*
 * @author hans@dkmt.io
 * @since 2020-07-15
 */

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
  typedef void *CHistogram;
  CHistogram CHistogramInit(void);
  void CHistogramFree(void *);
  void CHistogramAdd(void *, double);
  const char *CHistogramToString(void *);
#ifdef __cplusplus
}
#endif
