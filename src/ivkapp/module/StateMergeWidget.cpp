#include "StateMergeWidget.h"
#include "ArrivalProcessDisplay.h"

#include "utility/Logging.hpp"

#include <QHeaderView>

FACTORY_DEFINITIONS_FOR(StateMergeWidget)

StateMergeWidget::StateMergeWidget()
{
	setupUi(this);
	thread = new ComputationThread<StateMerge>(&modeler, this, computeButton, progressBar, progressLabel);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
	connect(contractTable, SIGNAL(cellClicked(int, int)), this, SLOT(handleCellEvent(int, int)));

	contractTable->verticalHeader()->hide();
	contractTable->resizeRowsToContents();
}

StateMergeWidget::~StateMergeWidget()
{
}

void StateMergeWidget::loadModel()
{
	ComputationParameters params;

	params.setIntVector(StateMerge::PARAM_CONTRACTIONVECTOR, loadIntVector(StateMerge::PARAM_CONTRACTIONVECTOR));
	params.setInt(StateMerge::PARAM_CONTRACTIONTYPE, 1 );
	setTableCellsChecked( params.getIntVector( StateMerge::PARAM_CONTRACTIONVECTOR ) );

	modeler->setParameters(params);
}

void StateMergeWidget::initModel()
{
	ComputationParameters params;
	intvector initVec(0,1);
	initVec[0] = 5;
	initVec[1] = 2;
	params.setIntVector(StateMerge::PARAM_CONTRACTIONVECTOR, initVec);
	params.setInt(StateMerge::PARAM_CONTRACTIONTYPE , 1);

	const SSMProcess *process = dynamic_cast<DataProvider<SSMProcess>*>(parentModule)->getData();
	StateMerge* pre_modeler = new StateMerge(process, params);

	assert( process->getNumStates() >= 2);

	numContractions->setMaximum( process->getNumStates() );
	sliderContractions->setMaximum( process->getNumStates() );

	intvector contractionVector( pre_modeler->generateContractionVector( 2 ) );

	params.setIntVector(StateMerge::PARAM_CONTRACTIONVECTOR, contractionVector);
	params.setInt(StateMerge::PARAM_CONTRACTIONTYPE, 1 );
	modeler = new StateMerge(process, params);

	generateContractTable( process->getNumStates() , process->getStationaryProbabilities() , process->getStateMeans() , contractionVector);

	tableToVector();
}

void StateMergeWidget::updateGUI()
{

	// Copy values from model to GUI fields
	ComputationParameters params = modeler->getParameters();
	intvector conStates = params.getIntVector( StateMerge::PARAM_CONTRACTIONVECTOR );
	setTableUnchecked();
	setTableCellsChecked( conStates );
}

void StateMergeWidget::generateContractTable(int states , rvector statProb, rvector means, intvector contractionVector){
	contractTable->setRowCount(states);

	for(int i = 0; i < states ; i++){
		QTableWidgetItem * stateItem = new QTableWidgetItem( tr( "%1" ).arg( i+1 ) );
		stateItem->setFlags( Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
		stateItem->setCheckState( Qt::Unchecked );
		contractTable->setItem( i , 0 , stateItem );

		QTableWidgetItem * probItem = new QTableWidgetItem( tr("%1").arg( _double( statProb[i+1] ) ) );
		probItem->setFlags( Qt::ItemIsEnabled );
		contractTable->setItem( i , 1 , probItem );

		QTableWidgetItem * meanItem = new QTableWidgetItem( tr("%1").arg( _double( means[i+1] ) ) );
		meanItem->setFlags( Qt::ItemIsEnabled );
		contractTable->setItem( i , 2 , meanItem );
	}
	setTableCellsChecked( contractionVector );

	contractTable->resizeRowsToContents();
}

void StateMergeWidget::createActions()
{

}

void StateMergeWidget::spawnResultWidget()
{
	SSMProcess* result = thread->getResult();
	addSubWidget(new ArrivalProcessDisplay(result), tr("Arrival Process"));
}

void StateMergeWidget::setTableUnchecked(){
	for(int i = 0; i <= modeler->getNumStates()-1 ; i++){
		QTableWidgetItem *item = contractTable->item( i , 0);
		item->setCheckState( Qt::Unchecked );
	}
}

void StateMergeWidget::setTableCellsChecked(intvector cells){
	//if(Lb( cells ) != Ub( cells )){
		for(int n = Lb( cells ); n <= Ub(cells); n++){
			QTableWidgetItem *item = contractTable->item( cells[n]-1 , 0);
			item->setCheckState( Qt::Checked );
		}
	//}
}

void StateMergeWidget::handleCellEvent(int row, int col){
	QTableWidgetItem* item = contractTable->item( row , 0 );
	bool status = item->checkState();

	if( status ){
		item->setCheckState( Qt::Unchecked );
	}
	else{
		item->setCheckState( Qt::Checked );
	}
	tableToVector();
}

void StateMergeWidget::on_numContractions_valueChanged(const QString & newText)
{
	intvector contractionVector( modeler->generateContractionVector( newText.toInt() ) );

	setTableUnchecked();
	setTableCellsChecked(contractionVector);
	tableToVector();
}

void StateMergeWidget::tableToVector(){
	vector<int> tmp;
	for(int i = 0; i < contractTable->rowCount() ; i++){
		QTableWidgetItem *item = contractTable->item( i , 0);
		if( item->checkState() ){
			tmp.push_back(i+1);
		}
	}

	intvector contractStates(1,tmp.size() );
	for(unsigned int i = 0; i < tmp.size() ; i++){
		contractStates[i+1] = tmp[i];
	}

	ComputationParameters params = modeler->getParameters();
	params.setIntVector( StateMerge::PARAM_CONTRACTIONVECTOR , contractStates );
	modeler->setParameters(params);
	saveIntVector(StateMerge::PARAM_CONTRACTIONVECTOR, contractStates);
}

void StateMergeWidget::on_statProb_clicked(){
	statProb->setChecked(true);
	means->setChecked(false);

	ComputationParameters params = modeler->getParameters();
	params.setInt( StateMerge::PARAM_CONTRACTIONTYPE , 1 );
	modeler->setParameters(params);
	saveInt(StateMerge::PARAM_CONTRACTIONTYPE, 1);
}

void StateMergeWidget::on_means_clicked(){
	statProb->setChecked(false);
	means->setChecked(true);

	ComputationParameters params = modeler->getParameters();
	params.setInt( StateMerge::PARAM_CONTRACTIONTYPE , 2 );
	modeler->setParameters(params);
	saveInt(StateMerge::PARAM_CONTRACTIONTYPE, 2);
}
