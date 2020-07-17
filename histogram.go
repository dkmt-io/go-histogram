/*
 * @author hans@dkmt.io
 * @since 2020-07-15
 */

package histogram

// #include "CHistogram.h"
import "C"
import (
	"unsafe"
)

// GoHistogram a golang wrapper for leveldb::Histogram
type GoHistogram struct {
	histogram C.CHistogram
}

// New create the histogram
func New() GoHistogram {
	var ret GoHistogram
	ret.histogram = C.CHistogramInit()
	return ret
}

// Free release the histogram
func (h GoHistogram) Free() {
	C.CHistogramFree(unsafe.Pointer(h.histogram))
}

// Add add a value to the histogram
func (h GoHistogram) Add(value float64) {
	C.CHistogramAdd(unsafe.Pointer(h.histogram), C.double(value))
}

// ToString print out the content of the histogram
func (h GoHistogram) ToString() string {
	str := C.CHistogramToString(unsafe.Pointer(h.histogram))
	return C.GoString(str)
}
