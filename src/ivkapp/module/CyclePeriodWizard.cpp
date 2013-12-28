#include "CyclePeriodWizard.h"

FACTORY_DEFINITIONS_FOR(CyclePeriodWizard)

CyclePeriodWizard::CyclePeriodWizard()
: ExtractGopWidget()
{
	// Knopf verstecken
	this->performButton->setVisible(false);
}

CyclePeriodWizard::~CyclePeriodWizard()
{

}
