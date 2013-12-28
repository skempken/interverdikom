#ifndef CYCLEPERIODWIZARD_H_
#define CYCLEPERIODWIZARD_H_

#include "modbase/ModuleWidget.h"
#include "module/ExtractGopWidget.h"

using namespace ivk;

class CyclePeriodWizard: public ExtractGopWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(CyclePeriodWizard)

public:
	CyclePeriodWizard();

	virtual ~CyclePeriodWizard();

private:
protected:

};


#endif /*CYCLEPERIODWIZARD_H_*/
