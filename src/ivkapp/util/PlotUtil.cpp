#include "PlotUtil.h"

QwtPlotCurve *PlotUtil::constructCurveFromRVector(rvector data) {
	int size = Ub(data) - Lb(data) + 1;
	double *xValues = new double[size];
	double *yValues = new double[size];

	int i = 0;
	for (int j = Lb(data); j <= Ub(data); j++) {
		xValues[i] = j;
		yValues[i] = _double(data[j]);
		i++;
	}

	QwtPlotCurve *result = new QwtPlotCurve();
	result->setData(xValues, yValues, size);

	delete[] xValues;
	delete[] yValues;
	
	return result;
}
