#include "computation/SMPTransient.h"
#include <stdexcept>
#include "imatrix.hpp"
#include "utility/IMatrixUtils.h"

#include "utility/Logging.hpp"

namespace ivk{

const char* SMPTransient::PARAM_ITERATIONS = "iterations";
const char* SMPTransient::PARAM_THRESHOLD = "threshold";

SMPTransient::SMPTransient(const SSMProcess* data, const ComputationParameters & parameters)
: AbstractComputation<SSMProcess , IWorkloadVector>( data , parameters){

	// Eingabedaten validieren
	real expectationValue = data->getExpectationValue();
	if(!(expectationValue < 0))
		// Stau!!
		throw new std::invalid_argument("Expectation value of process must be negative");

	setParameters(parameters);
}

int SMPTransient::getIterations(){
	return this->iterations;
}
void SMPTransient::setIterations(int value){
	this->iterations = value;
}

real SMPTransient::getThreshold(){
	return this->threshold;
}
void SMPTransient::setThreshold(real value){
	this->threshold = value;
}

void SMPTransient::setParameters(const ComputationParameters& params){
	setIterations( params.getInt( SMPTransient::PARAM_ITERATIONS ) );
	setThreshold( params.getReal( SMPTransient::PARAM_THRESHOLD ) );
}

IWorkloadVector* SMPTransient::compute(){
	int progress = 1;
	setProgressText("starting computation...");
	setProgressMax(110);
	setProgressValue(progress);

	imatrix dists(this->m_ptrData->getDistributions());
	imatrix trans(this->m_ptrData->getTransitionMatrix());

	// Indizes
	const int h = - Lb(dists,2);
	const int g = Ub(dists,2);

	// Ausgangsworkload festlegen
	const int numStates = this->m_ptrData->getNumStates();
	imatrix w(1,numStates,0,0);
	rvector statProb( m_ptrData->getStationaryProbabilities() );

	setProgressText("setting up calculations...");

	for( int stateIndex = Lb(w, ROW); stateIndex<=Ub(w, ROW); ++stateIndex){
		w[stateIndex][0] = statProb[stateIndex];
	}

	vector<imatrix> u;
	intvector translate( -h , g);

	for(int l = -h; l <= g;l++){
		u.push_back( imatrix( trans ) );
		translate[l] = u.size()-1;

		for(int i = Lb(trans, ROW) ; i <= Ub( trans, ROW) ; i++){
			for(int j = Lb( trans, ROW); j <= Ub( trans, ROW) ; j++){
				u[ translate[ l ] ][i][j] = trans[i][j] * dists[i][l];
			}
		}
	}

	progress = 5;
	setProgressValue(progress);
	setProgressText("calculating");
	bool checkEpsilon;

	for(int i = 1; i <= this->iterations; i++){
		imatrix w_( IMatrixUtils::zeros( Lb( w , ROW ) , Ub ( w , ROW ) , -h , Ub( w , COL )+g) );

		// Hier wird mit w{i-1} gerechnet
		for(int k = -h; k <= Ub( w_ , COL); k++){
			for(int j = -h ; j <= g; j++){
				for( int m = Lb(trans , ROW) ; m <= Ub( trans, ROW ); m++){
					for (int n = Lb(trans , ROW) ; n <= Ub( trans, ROW ); n++) {
						if( !( ( k-j) < 0 || (k-j) > Ub(w, COL) ) ){
							w_[n][k] += w[m][k-j] * u[translate[j]][m][n] ;
						}
					}
				}
			}
		}

		// Berechne w{i}
		w = imatrix(1,numStates,0,Ub(w_,COL));
		for(int state = Lb(w, ROW); state <= Ub(w, ROW); ++state)
		{
			for(int value = 0; value < Ub(w, COL); ++value)
			{
				w[state][value] = w_[state][value];
			}
			for(int value = Lb(w, COL); value < 0; ++value)
			{
				w[state][0] += w_[state][value];
			}

		}

		progress = (int) ( 5 + 100.0/(double) iterations * i );
		setProgressValue(progress);

		checkEpsilon = true;
		for(int wl = Lb(w, COL); wl <= Ub(w, COL);wl++){
			for(int states = Lb(w, ROW);states <= Ub(w,ROW); states++){
				if (this->threshold > fabs( _double( Sup(w[states][wl]) - Sup(w_[states][wl]) ) )){
					checkEpsilon = false;
				}
				if (this->threshold > fabs( _double( Inf(w[states][wl]) - Inf(w_[states][wl]) ) )){
					checkEpsilon = false;
				}
				if( !checkEpsilon ) break;
			}
			if( !checkEpsilon ) break;
		}

		if( checkEpsilon ){
			progress = 105;
			setProgressValue(progress);
			setProgressText("calculations ended by Epsilon");
			break;
		}
		// TODO: Vergleich von jedem Element von w{i-1} und w{i}, bestimme maximale Änderung der Intervallgrenzen
		// Bei neuen Elementen von w{i} (hohe Workloads) annehmen, dass w{i-1} an der Stelle exakt 0 ist.

	}

	if( !checkEpsilon ) setProgressText("calculation ended by Iterations");

	ivector workvec(  Lb( w, COL ), Ub( w , COL) );

	for(int i = Lb(workvec); i <= Ub(workvec); i++){
		workvec[i] = interval(0.0,0.0);
		for(int state = Lb(w, ROW); state <= Ub(w, ROW) ; state++){
			workvec[i] += w[state][i];
		}
	}

	progress = 110;
	setProgressValue(progress);

	IWorkloadVector* wlv = new IWorkloadVector( workvec );
	return wlv;

}

}
