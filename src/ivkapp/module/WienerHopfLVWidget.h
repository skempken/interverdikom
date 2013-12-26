/*
 * WienerHopfLVWidget.h
 *
 *  Created on: 05.01.2009
 *      Author: ivkdev
 */

#ifndef WIENERHOPFLVWIDGET_H_
#define WIENERHOPFLVWIDGET_H_

#include "WienerHopfWidget.h"

class WienerHopfLVWidget: public WienerHopfWidget {
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(WienerHopfLVWidget)

public:
	WienerHopfLVWidget();

	virtual ~WienerHopfLVWidget();

	virtual void initModel();
};

#endif /* WIENERHOPFLVWIDGET_H_ */
