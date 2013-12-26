/*
 * WienerHopfLVWidget.cpp
 *
 *  Created on: 05.01.2009
 *      Author: ivkdev
 */

#include "WienerHopfLVWidget.h"

#include "SSMPQueueDisplayWidget.h"
#include "WHResultWidget.h"
#include "MainWindow.h"
#include "computation/SMPWienerHopfLV.h"

#include <math.h>

FACTORY_DEFINITIONS_FOR(WienerHopfLVWidget)

WienerHopfLVWidget::WienerHopfLVWidget() {
	// TODO Auto-generated constructor stub

}

WienerHopfLVWidget::~WienerHopfLVWidget() {
	// TODO Auto-generated destructor stub
}

void WienerHopfLVWidget::initModel()
{
	// Create new parameter object
	ComputationParameters params;

	// Set default values
	params.setReal(SMPWienerHopf::PARAM_EPSILON, 1e-15);
	params.setInt(SMPWienerHopf::PARAM_NUMITERATIONS, 200);
	params.setInt(SMPWienerHopf::PARAM_RELAXATIONSTEPS, 0);

	// Use saveXXX methods to set to XML data.
	saveReal(SMPWienerHopf::PARAM_EPSILON, params.getReal(SMPWienerHopf::PARAM_EPSILON));
	saveInt(SMPWienerHopf::PARAM_NUMITERATIONS, params.getInt(SMPWienerHopf::PARAM_NUMITERATIONS));

	// Get parent data
	const SSMPQueue *queue = ((SSMPQueueDisplayWidget*) parentModule)->getSSMPQueue();

	whComputation = new SMPWienerHopfLV(queue, params);
}
