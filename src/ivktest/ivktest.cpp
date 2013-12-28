#include "test.h"
#include "PartitionModeler.h"
#include "SAPartitionModeler.h"
#include "computation/SimpleMCModeler.h"
#include "GeneticModeler.h"
#include "SPEA2Modeler.h"
#include "SSMProcess.h"
#include "ISMPWHWorkload.h"
#include "data/Trace.h"
#include "Polynomial.hpp"
#include "SMPWienerHopf.h"
#include "utility/IMatrixUtils.h"
#include "utility/RMatrixUtils.h"
#include "SAPartitionModeler.h"
#include "MeanDivisionModeler.h"
#include "SceneModeler.h"
#include "MMCModeler.h"
#include "IVKExport.h"
#include "Simulation.h"
#include "GISteadyOutput.h"
#include "FFT.h"

#include "utility/Logging.hpp"
#include "ConsoleLogger.h"

#include "DiagonalizationTest.h"
#include "DFTTest.h"

using namespace std;
using namespace ivk;
using cxsc::real;
using cxsc::rvector;



int main() {
	// Initialize logging
	AbstractLogger* logger = new ConsoleLogger();
	Logging::setLogger(logger);
	Logging::setLogLevel(Logging::Trace);
	Logging::log(Logging::Info, "Start of debug build");
	cout << SetPrecision(16,15) << Scientific;
	//test_chaudhry4();
	test_SMP3();
	//test_subConv();
	//test_roots();
	//test_eig_wrapper();
	//test_verifyeig_port();
	//test_cicircle();
	//test_polyeig();
	cout << "end." << endl;
	return 0;
/*
	civector a(0, 99);
	for(int i = Lb(a); i<=Ub(a); ++i)
	{
		a[i] = cinterval(interval((double)i+1, (double)i+1), interval(0.0,0.0));
	}
	DFTTest::l_dft3(a);
	/*
	civector b = DFTTest::dft3(a);
	civector c = DFTTest::idft3(b);
	cout << "MaxDiam(iDFT(DFT(a))) = " << DFTTest::getMaxDiam(c) << endl;
	double maxdiam = 0.0;
	for(int i = Lb(b); i<=Ub(b); ++i)
	{
		cout << b[i] << " d: " << diam(b[i]) << endl;
		maxdiam = std::max<double>(maxdiam,
				std::max<double>(_double(Re(diam(b[i]))), _double(Im(diam(b[i]))))
						);
	}
	cout << "Max. diam: " << maxdiam << endl;
	Logging::log(Logging::Info, "End of line.");
	return 0;

	//DiagonalizationTest test;
	//test.runTest();

	//test_gauss();
	//test_rootsofunity();
	//test_Toeplitz();
	//test_PM();
	//test_Vandermonde();
	//test_Prony();
	//test_matrixaccu();
	test_fautocorrelation();
	//test_circular();

	//test_SMP3();
	//test_largeGIG1();
	//test_ASMP();

	// Fast convolutions
	//test_fft_conv();
	//test_conv();
	//test_Iconv();


	/* Workload analysis
	const int k = 3;
	const int dSteps = 150;
	const int states = 15;

	rvector data = frame2gop(loadData("testdata/horizon.data"),12);
	Trace trace(data);

	// Compute buffer occupancy
	real capacity = trace.getMean() + k * trace.getStandardDeviation();
	Trace buffer(trace.computeBuffer(capacity));
	rvector bufferOccupancy = buffer.discretize(trace.getDiscretizationPoints(dSteps));

	// Create Model
	ComputationParameters param_pm;
	param_pm.setInt(PartitionModeler::PARAM_NUMDSTEPS, dSteps);
	param_pm.setInt(PartitionModeler::PARAM_NUMSTATES, states);

	SimpleMCModeler _smcm(&trace, param_pm);
	SMProcess _model = _smcm.compute();

	cout << "Transition matrix:" << endl << _model.getTransitionMatrix() << endl;
	cout << "Distributions:" << endl << _model.getDistributions() << endl;

	// Check distributions
	cout << "Autocorrelation: " << endl << _model.getAutocorrelation(10) << endl;

	// Simulate
	ComputationParameters param_sim;
	param_sim.setInt(Simulation::PARAM_LENGTH, Ub(data)-Lb(data)+1);
	Simulation sim(&_model, param_sim);
	DiscretizedTrace simulated = sim.compute();

	// Scale trace.
	Trace scaledSimTrace = simulated.scale(trace.getDiscretizationPoints(dSteps));

	cout << "Model variance:" << scaledSimTrace.getVariance() << endl;
	cout << "Trace variance:" << trace.getVariance() << endl;


	Trace simBuffer(scaledSimTrace.computeBuffer(capacity));
	rvector simBufferOccupancy = simBuffer.discretize(trace.getDiscretizationPoints(dSteps));


	// Service process
	rvector bandwidth(0,0);
	bandwidth[0] = trace.getMean() + k * trace.getStandardDeviation();

	Trace _serviceTrace(bandwidth);
	GIProcess service(_serviceTrace.discretize(trace.getDiscretizationPoints(dSteps)));

	DBG("Service distribution:" << endl << service.getDistribution());

	SMProcess queue = _model - service;
	IVKExport::writeToIVKFile("test.ivk", _model, service);

	queue.trimDistributions();

	DBG("Computing Wiener-Hopf factorization...");
	DBG("Expectation value: " << queue.getExpectationValue());

	real epsilon(1e-14);
	ComputationParameters param_WH;
	param_WH.setReal(SMPWienerHopf::PARAM_EPSILON, epsilon);
	param_WH.setInt(SMPWienerHopf::PARAM_NUMITERATIONS, 500);
	SMPWienerHopf _wh(&queue, param_WH);

	BaseProgressListener listener;
	_wh.addProgressListener(&listener);
	ISMPWHFactors factors = _wh.compute();

	cout << "Approximation iterations: " << _wh.getNumApproximationIterations() << endl;
	cout << "Verification iterations: " << _wh.getNumVerificationIterations() << endl;


	ComputationParameters param_wl;
	param_wl.setInt(ISMPWHWorkload::PARAM_UPTO, 10);
	ISMPWHWorkload _workload(&factors, param_wl);

	WorkloadVector<ivector> wl = _workload.compute();

	cout << "Workload probabilites from model:" << endl << wl.getWorkloadVector() << endl;

	cout << "Estimated Buffer occupancy (trace):" << endl << bufferOccupancy << endl;
	cout << "Estimated Buffer occupancy (model):" << endl << simBufferOccupancy << endl;


	// Output processes
	/* Example 1
	ivector arrival(0,50);
	for(int i=Lb(arrival); i<=Ub(arrival);++i)
		arrival[i] = interval(0.0,0.0);
	arrival[10] = interval(0.8,0.8);
	arrival[50] = interval(0.2,0.2);
	GIProcess A(arrival);

	ivector service1(0,30);
	for(int i=Lb(service1); i<=Ub(service1);++i)
		service1[i] = interval(0.0,0.0);
	service1[15] = interval(0.4,0.4);
	service1[30] = interval(0.6,0.6);
	GIProcess S1(service1);

	pair<GIProcess, GIProcess> Q1 = make_pair(A,S1);

	GISteadyOutput _output(&Q1, ComputationParameters());
	GIProcess output = _output.compute();

	ivector outDist = output.getDistribution();
	interval sum = interval(0.0,0.0);

	cout << outDist << endl;
	cout << Lb(outDist) << ".." << Ub(outDist) << endl;
	for(int i = Lb(outDist); i<=Ub(outDist); ++i)
		sum += outDist[i];
	cout << sum << endl;

	ivector service2(0,25);
	for(int i=Lb(service2); i<=Ub(service2);++i)
		service2[i] = interval(0.0,0.0);
	service2[15] = interval(0.4,0.4);
	service2[25] = interval(0.6,0.6);
	GIProcess S2(service2);

	pair<GIProcess, GIProcess> Q2 = make_pair(GIProcess(Sup(outDist)),S2);
	GISteadyOutput _output2(&Q2, ComputationParameters());
	GIProcess output2 = _output2.compute();
	outDist = output2.getDistribution();
	cout << outDist << endl;
	*/

	/* Example 2: Strict
	ivector arrival(0,5);
	for(int i=Lb(arrival); i<=Ub(arrival);++i)
		arrival[i] = interval(0.0,0.0);
	arrival[1] = interval(0.5,0.5);
	arrival[5] = interval(0.5,0.5);
	GIProcess A(arrival);

	ivector service1(0,10);
	for(int i=Lb(service1); i<=Ub(service1);++i)
		service1[i] = interval(0.0,0.0);
	service1[10] = interval(1.0,1.0);
	GIProcess S1(service1);

	pair<GIProcess, GIProcess> Q1 = make_pair(A,S1);

	GISteadyOutput _output(&Q1, ComputationParameters());
	GIProcess output = _output.compute();

	ivector outDist = output.getDistribution();
	service1 = GIProcess::subDists(service1, outDist);
	service1 = GIProcess::subDists(service1, outDist);
	for(int i = Lb(service1); i<0; ++i)
		service1[0] += service1[i];
	Resize(service1, 0, Ub(service1));
	GIProcess S2(service1);

	pair<GIProcess, GIProcess> Q2 = make_pair(A,S2);
	GISteadyOutput _output2(&Q2, ComputationParameters());
	GIProcess output2 = _output2.compute();
	outDist = output2.getDistribution();
	cout << outDist << endl;
	*/

	return 0;
}
