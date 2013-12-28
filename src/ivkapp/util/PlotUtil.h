#ifndef PLOTUTIL_H_
#define PLOTUTIL_H_

#include <rvector.hpp>

#include <qwt-qt4/qwt_plot_curve.h>

using namespace cxsc;

class PlotUtil
{
public:
	static QwtPlotCurve *constructCurveFromRVector(rvector data);
};

#endif /*PLOTUTIL_H_*/
