#include <GIProcess.h>
#include <ComputationParameters.h>
#include <SMPWienerHopf.h>
#include <SMPWienerHopfLV.h>
#include <SMPGrassmannJain1.h>
#include <SMPGrassmannJain2.h>
#include <SMPGrassmannJain3.h>
#include <ISMPWHFactors.h>
#include <ISMPWHWorkload.h>
#include <WorkloadVector.hpp>
#include <IVKExport.h>
#include <FFT.h>
#include <IntFastConvolution.h>
#include <AutoSMPModeler.h>
#include <Trace.h>
#include <PronyMethod.h>

#include <data/SSMPQueue.h>
#include <computation/SMPOutputModeler.h>

#include <math.h>
#include <vector>

#include <time.h>

#include <imatrix.hpp>
#include <types/MatrixAccu.hpp>

#include "FileImport.h"

#include <Logging.hpp>

#include <imath.hpp>
#include <l_cinterval.hpp>
#include <types/cicircle.h>
#include "GaussApproximation.h"

#include "utility/solvers/EigenvalueSolver.h"
#include "utility/CPolynomialUtils.h"

using namespace ivk;
using namespace std;
using namespace cxsc;

void normalize(ivector &dist)
{
	interval sum(0.0);
	for(int i = Lb(dist); i<=Ub(dist); ++i)
	{
		sum += dist[i];
	}
	for(int i = Lb(dist); i<=Ub(dist); ++i)
	{
		dist[i] /= sum;
	}
}

void test_subConv()
{
	ivector arrival(1,10);
	for(int i = Lb(arrival); i<=Ub(arrival); ++i)
		arrival[i] = i;
	normalize(arrival);
	ivector service(1,8);
	for(int i = Lb(service); i<=Ub(service); ++i)
		service[i] = 0.0;
	service[6] = 0.5;
	service[7] = 1.0;
	service[8] = 0.7;
	normalize(service);
	SetLb(service, 10);
	cout << "Arrival:" << Lb(arrival) << ".." << Ub(arrival) << endl << arrival;
	cout << "Service:" << Lb(service) << ".. " << Ub(service) << endl << service;
	ivector diff = SSMProcess::subDists(arrival, service);
	cout << "A-S:" << endl << Lb(diff) << ".." << Ub(diff) << endl << diff;
}

void test_cicircle()
{
	cicircle d(complex(0.0,0.0), real(0.1));
	d = d + d;
	cout << d << endl;
}

void test_roots()
{
	cvector poly(1,5);
	for(int i = Lb(poly); i<=Ub(poly); ++i)
	{
		poly[i] = complex(Ub(poly)-i+1,0.0);
	}

	cout << CPolynomialUtils::roots(poly) << endl;
}

void test_gauss() {
	GaussApproximation approx;
	for (int steps = 2; steps <= 16777216; steps*=2) {
		GIProcess process = approx.approximateGaussian(0.5, 0.5, steps);
		rvector dist = mid(process.getDistribution());
		real sum = 0.0;
		for (int i = Lb(dist); i<=Ub(dist); ++i)
			sum += dist[i] * (i+1);
		sum = sum / steps;
		cout << steps << " steps: " << sum << endl;
	}
}

void test_polyeig() {
	imatrix A0(1,4,1,4);
	A0[1][1] = 1;
	A0[1][2] = 2;
	A0[1][3] = 3;
	A0[1][4] = -3;
	A0[2][1] = 4;
	A0[2][2] = 6;
	A0[2][3] = 5;
	A0[2][4] = 5;
	A0[3][1] = 7;
	A0[3][2] = 1;
	A0[3][3] = 3;
	A0[3][4] = -3;
	A0[4][1] = 7;
	A0[4][2] = -1;
	A0[4][3] = 3;
	A0[4][4] = -3;

	imatrix A1(1,4,1,4);
	A1[1][1] = 7;
	A1[1][2] = 6;
	A1[1][3] = 3;
	A1[1][4] = -4;
	A1[2][1] = 4;
	A1[2][2] = -8;
	A1[2][3] = 1;
	A1[2][4] = -11;
	A1[3][1] = 3;
	A1[3][2] = -12;
	A1[3][3] = 9;
	A1[3][4] = 1;
	A1[4][1] = 3;
	A1[4][2] = 2;
	A1[4][3] = -9;
	A1[4][4] = 1;

	imatrix A2(1,4,1,4);
	A2[1][1] = -3;
	A2[1][2] = 4;
	A2[1][3] = -1;
	A2[1][4] = -1;
	A2[2][1] = 4;
	A2[2][2] = 1;
	A2[2][3] = -2;
	A2[2][4] = 2;
	A2[3][1] = 7;
	A2[3][2] = 5;
	A2[3][3] = -3;
	A2[3][4] = -3;
	A2[4][1] = 7;
	A2[4][2] = 2;
	A2[4][3] = -4;
	A2[4][4] = -3;

	IMatrixPolynomial p(0, 2,1,4,1,4);
	p[0] = A0;
	p[1] = A1;
	p[2] = A2;

	// MATLAB:
	// A0 = [1 2 3;4 6 5;7 1 3], A1 = [7 6 3;4 8 1;3 -12 9], A2 = [-3 4 -1;4 4 2;7 5 -3]
	// [X,E] = polyeig(A0,A1,A2)
	civector eval;
	cimatrix evec;
	EigenvalueSolver es;
	es.getVerifiedEigenvalues(p, eval, evec);

	for(int i = Lb(eval); i<=Ub(eval); ++i)
	{
		cinterval lambda = eval[i];
		cimatrix tmp = p.evaluateCI(lambda);
		civector alpha = evec[Col(i)];
		cout << "Test " << i << endl << tmp*alpha << endl;
	}


	// MATLAB RESULT:
	// X =
	//	-0.3044 - 0.0741i  -0.3044 + 0.0741i   0.4205            -0.6321 + 0.2323i  -0.6321 - 0.2323i   0.3121
	//	 0.5822 - 0.1836i   0.5822 + 0.1836i  -0.7968             0.0596 + 0.0866i   0.0596 - 0.0866i   0.1530
	//	 0.7111 - 0.1532i   0.7111 + 0.1532i   0.4338             0.7125 - 0.1668i   0.7125 + 0.1668i  -0.9376
	// E =
	//	-0.8841 + 1.1936i
	//	-0.8841 - 1.1936i
	//	-0.2260
	//	 0.3390 + 0.5061i
	//	 0.3390 - 0.5061i
	//	 1.6700

	// MATLAB
	// A = zeros(6); A(1:3,4:6) = eye(3); A(4:6, 1:3) = -A0; A(4:6, 4:6) = -A1, B = eye(6); B(4:6, 4:6) = A2
	// [V,D] = eig(A,B)
	// [L, X] = verifyeig(A, D(1,1), V(:,1), B)
}

void test_eig_wrapper() {
	srand(time(0));
	rmatrix eigtest(1, 5, 1, 5);
		for (int i = Lb(eigtest, 1); i <= Ub(eigtest, 1); i++) {
			for (int j = Lb(eigtest, 2); j <= Ub(eigtest, 2); j++) {
				eigtest[i][j] = ((i + 5) * (j + 7)) % 23 + (rand() % 10) - 10;
			}
		}

		rmatrix eigtestB(1, 5, 1, 5);
			for (int i = Lb(eigtest, 1); i <= Ub(eigtest, 1); i++) {
				for (int j = Lb(eigtest, 2); j <= Ub(eigtest, 2); j++) {
					eigtestB[i][j] = ((i + 3) * (j + 5)) % 19 + (rand() % 10) - 10;
				}
			}

	cvector eigenValues;
	cmatrix eigenVectors;

	EigenvalueSolver es;
	es.getEigenvalues(eigtest, eigtestB, eigenValues, eigenVectors);

	cout << "eigwrapper test for A = " << endl << eigtest << "and B = " << endl << eigtestB << endl
			<< ", result: eigenvalues:" << endl << eigenValues << endl
			<< "eigen vectors:" << endl << eigenVectors << endl;
}

void test_verifyeig_port() {
	//static void getVerifiedEigenvalues(const imatrix A, civector & eigenValues, cimatrix & eigenVectors);
	srand(time(0));
	rmatrix eigtest(1, 5, 1, 5);
		for (int i = Lb(eigtest, 1); i <= Ub(eigtest, 1); i++) {
			for (int j = Lb(eigtest, 2); j <= Ub(eigtest, 2); j++) {
				eigtest[i][j] = ((i + 5) * (j + 7)) % 23 + (rand() % 10) - 10;
			}
		}

		rmatrix eigtestB(1, 5, 1, 5);
			for (int i = Lb(eigtest, 1); i <= Ub(eigtest, 1); i++) {
				for (int j = Lb(eigtest, 2); j <= Ub(eigtest, 2); j++) {
					eigtestB[i][j] = ((i + 3) * (j + 5)) % 19 + (rand() % 10) - 10;
				}
			}

	civector eigenValues;
	cimatrix eigenVectors;

	EigenvalueSolver es;
	es.getVerifiedEigenvalues(imatrix(eigtest), imatrix(eigtestB), eigenValues, eigenVectors);

	cout << "Testing verifyeig() port..." << endl << "Matrix:" << endl
			<< eigtest << endl << "RESULT:" << endl << "eigen values: "
			<< eigenValues << endl << "eigen vectors:" << endl << eigenVectors
			<< endl;
}

void test_matrix_solving() {
	cimatrix ldivl = cimatrix(1, 3, 1, 3);
	for (int i = Lb(ldivl, 1); i <= Ub(ldivl, 1); i++) {
		for (int j = Lb(ldivl, 2); j <= Ub(ldivl, 2); j++) {
			ldivl[i][j] = ((i + 5) * (j + 7)) % 23;
		}
	}

	cout << ldivl << endl << "DIVIDED BY" << endl;

	cimatrix ldivr(1, 3, 1, 3);
	for (int i = Lb(ldivl, 1); i <= Ub(ldivl, 1); i++) {
		for (int j = Lb(ldivl, 2); j <= Ub(ldivl, 2); j++) {
			ldivr[i][j] = (i == j);
		}
	}

	cout << ldivr << endl << "RESULT" << endl;

	cimatrix y;
	ILinSys solver;
	for (int i = 1; i <= (Ub(ldivl, 2) - Lb(ldivl, 2) + 1); i++) {
		civector resultVector;
		int returnCode;

		solver.CILinSolveIndirekt(ldivl, ldivr[Col(i)], resultVector, returnCode);
		y[Col(i)] = resultVector;
	}

	cout << y << endl;
}

void test_rootsofunity() {
	// set Precision (global C-XSC variable)
	stagprec = 2;

	cout << SetDotPrecision(31, 32);
	cout << SetPrecision(15, 16);
	const l_interval Pi(Pi_l_interval());
	cout << "Pi:" << Pi << endl;

	const int N = 1000;
	for (int k = 0; k<=N; ++k) {
		l_interval tmp = (2.0 * Pi * k / N);
		l_interval re(cos(tmp));
		l_interval im(sin(tmp));

		cout << "[" << re << ", " << im << "]" << endl;
	}

}

void test_matrixaccu() {
	imatrix a(1, 3, 1, 3);
	imatrix b(1, 3, 1, 3);
	for (int i = Lb(a, 1); i<= Ub(a, 1); ++i)
		for (int j = Lb(a, 2); j<= Ub(a, 2); ++j) {
			a[i][j] = interval(i+j, i+j);
			b[i][j] = interval(i+j, i+j);
		}

	imatrixaccu accu(1, 3, 1, 3);

	for (int i = 1; i<3; ++i)
		accu.accumulate(a, b);

	cout << accu.rnd() << endl;
}

void test_circular() {
	rvector c(1, 5);
	rvector b(1, 5);
	for (int i=Lb(c); i<=Ub(c); ++i) {
		c[i] = i;
		b[i] = i*2;
	}
	rvector result = RMatrixUtils::solveCircular(c, b);
	cout << Lb(result) << ".." << Ub(result) << endl << result << endl;
}

void test_fautocorrelation() {
	rvector
			data =
					FileImport::loadData("/home/kempken/workspace/InterVerdiKom/testdata/horizon.data");
	Trace trace(data);
	cout << trace.getAutocorrelation(120) << endl;
	/*
	 for(int coeff = 10; coeff <= 1000; coeff*=10)
	 {
	 cout << "Coefficients up to " << coeff << endl;
	 clock_t start = std::clock();
	 for(int i = 0; i<100; ++i)
	 {
	 rvector _dummy = Trace::getAutocorrelation(data, coeff);
	 }
	 cout << BaseProgressListener::formatTime((std::clock() - start) / CLOCKS_PER_SEC)  << endl;
	 start = std::clock();
	 for(int i = 0; i<100; ++i)
	 {
	 rvector _dummy = Trace::getAutocorrelationFFT(data, coeff);
	 }
	 cout << BaseProgressListener::formatTime((std::clock() - start) / CLOCKS_PER_SEC)  << endl;
	 }
	 */
}

void analyzeQueue(const SSMProcess &queue) {
	cout << "Queue SSMP model states:" << queue.getNumStates() << endl;

	cout << "Difference distributions:" << endl << queue.getDistributions()
			<< endl;
	cout << "Expectation value:" << queue.getExpectationValue() << endl;

	// Progress notification
	//BaseProgressListener listener;

	real limit(1e-15);
	real delta(1e-15);
	ComputationParameters param_WH;
	param_WH.setReal(SMPWienerHopf::PARAM_EPSILON, limit);
	param_WH.setInt(SMPWienerHopf::PARAM_NUMITERATIONS, 100);
	param_WH.setInt(SMPWienerHopf::PARAM_RELAXATIONSTEPS, 0);

	// Reference
	// SMPWienerHopf _wh(&queue, param_WH);

	//Algorithm 1
	//SMPGrassmannJain1 _wh(&queue, param_WH);

	//Algorithm 2
	//SMPGrassmannJain2 _wh(&queue, param_WH);

	//Algorithm 3
	//SMPGrassmannJain3 _wh(&queue, param_WH);

	// Multiple Precision
	SMPWienerHopfLV _wh(&queue, param_WH);

	// Polynomial Factorization
	//_wh.addProgressListener(&listener);
	ISMPWHFactors* factors = _wh.compute();

	cout << "Approximation iterations: " << _wh.getNumApproximationIterations()
			<< endl;
	cout << "Verification iterations: " << _wh.getNumVerificationIterations()
			<< endl;

	Polynomial<imatrix> idle = factors->getIdleDistributions();

	ComputationParameters param_wl;
	param_wl.setInt(ISMPWHWorkload::PARAM_UPTO, 100);
	ISMPWHWorkload _workload(factors, param_wl);

	WorkloadVector<ivector>* wl = _workload.compute();
	cout << "end." << endl;
	//cout << wl->getWorkloadVector() << endl;
}

void test_largeGIG1() {
	rvector arrival(0, 4000);
	arrival[0] = 0.0;
	for (int i = 1; i<=Ub(arrival); ++i)
		arrival[i] = 0.00025;
	rvector service(0, 3200);
	service[0] = 0.0;
	for (int i = 1; i<=Ub(service); ++i)
		service[i] = 0.0003125;

	GIProcess arrProcess((ivector)arrival);
	GIProcess serProcess((ivector)service);

	SSMProcess queue = serProcess - arrProcess;

	analyzeQueue(queue);
}

void test_GIG1()
{
	rvector arrival(0,100);
	for(int i = Lb(arrival); i<=Ub(arrival); ++i)
	{
		arrival[i] = 0.01;
	}
	arrival[0] = 0.005;
	arrival[100] = 0.005;

	rvector service(0,25);
	for(int i = Lb(service); i<=Ub(service); ++i)
	{
		service[i] = 0.0;
	}
	service[25] = 1.0;

	GIProcess arrProcess((ivector)arrival);
	GIProcess serProcess((ivector)service);

	SSMProcess queue = serProcess - arrProcess;

	analyzeQueue(queue);
}

void test_chaudhry4() {
	rvector arrival(0, 30);
	for (int i = Lb(arrival); i<=Ub(arrival); ++i)
		arrival[i] = 0.0;
	rvector service(0, 50);
	for (int i = Lb(service); i<=Ub(service); ++i)
		service[i] = 0.0;
	arrival[15] = 0.4;
	arrival[30] = 0.6;
	service[10] = 0.8;
	service[50] = 0.2;

	GIProcess arrProcess((ivector)arrival);
	GIProcess serProcess((ivector)service);

	SSMProcess queue = serProcess - arrProcess;

	analyzeQueue(queue);

}

void test_SMP3() {
	rmatrix trans(1, 3, 1, 3);
	trans[1][1] = 0.2;
	trans[1][2] = 0.6;
	trans[1][3] = 0.2;
	trans[2][1] = 0.6;
	trans[2][2] = 0.3;
	trans[2][3] = 0.1;
	trans[3][1] = 0.4;
	trans[3][2] = 0.3;
	trans[3][3] = 0.3;

	rmatrix arrival(1, 3, 0, 50);

	// state 1
	arrival[1][0] = 0.01;
	for (int k=1; k<=49; ++k)
		arrival[1][k] = 0.02;
	arrival[1][50] = 0.01;

	// state 2
	arrival[2][0] = 0.02;
	for (int k=1; k<=24; ++k)
		arrival[2][k] = 0.04;
	arrival[2][25]=0.02;
	for (int k=26; k<=50; ++k)
		arrival[2][k] = 0.0;

	// state 3
	arrival[3][0] = 0.02;
	for (int k=1; k<=25; ++k)
		arrival[3][k] = 0.0;
	for (int k=26; k<=49; ++k)
		arrival[3][k] = 0.04;
	arrival[3][50] = 0.02;

	rvector service(0, 8);
	for (int i = Lb(service); i<=Ub(service); ++i)
		service[i] = 0.0;
	service[1] = 0.05;
	service[2] = 0.3;
	service[3] = 0.6;
	service[8] = 0.05;

	imatrix itrans = (imatrix)(trans);
	imatrix iarrival = (imatrix)(arrival);
	ivector iservice = (ivector)(service);

	// optional: blow intervals.
	/*
	const real blowfactor(1e-4);
	interval blow(1.0 - blowfactor, 1.0 + blowfactor);

	for (int i = Lb(iarrival, 1); i<=Ub(iarrival, 1); ++i)
		for (int j = Lb(iarrival, 2); j<=Ub(iarrival, 2); ++j)
			iarrival[i][j] *= blow;
	for (int i = Lb(iservice); i<=Ub(iservice); ++i)
		iservice[i] *= blow;
	*/
	SSMProcess arrProcess(itrans, iarrival);
	cout << "Autocorrelation:" << endl;
	cout << arrProcess.getAutocorrelation(10) << endl;

	GIProcess serProcess(iservice);
	SSMPQueue* queue = SSMPQueue::constructInterarrivalQueue(&arrProcess, &serProcess);

	//Logging::log(Logging::Debug, "U", queue.getTransitionMatrix());

	//IVKExport::writeToIVKFile("smp3.ivk", arrProcess, serProcess);
	/*
	ComputationParameters params;
	SMPOutputModeler outputModeler(queue, params);
	outputModeler.compute();
	*/
	analyzeQueue((*queue));
}

void test_conv() {
	ivector a(0, 2);
	for (int i = Lb(a); i<=Ub(a); ++i)
		a[i] = interval(i, i);
	ivector b(0, 5);
	for (int i = Lb(b); i<=Ub(b); ++i)
		b[i] = interval(i+20, i+20);
	ivector c = SSMProcess::subDists(a, b);
	cout << a << endl;
	cout << b << endl;

	cout << Lb(c) << "..." << Ub(c) << endl;
	cout << c << endl;

}

void test_fft_conv() {
	rvector a(0, 200);
	for (int i = Lb(a); i<=Ub(a); ++i)
		a[i] = i+1;
	rvector b(0, 200);
	for (int i = Lb(b); i<=Ub(b); ++i)
		b[i] = 20+i;
	cvector result = FFT::fconv((cvector)a, (cvector)b);
	cout << result << endl;
}

void test_Iconv() {
	ivector a(0, 200);
	for (int i = Lb(a); i<=Ub(a); ++i)
		a[i] = interval(i+0.9, i+1.1);
	ivector b(0, 200);
	for (int i = Lb(b); i<=Ub(b); ++i)
		b[i] = interval(i+19.9, i+20.1);
	IntFastConvolution fast(a, b);
	civector result = fast.compute();
	for (int i=Lb(result); i<=Ub(result); i++)
		cout << Re(result[i]) << endl;
}

void test_ASMP() {
	std::vector<double>* inhalt = new std::vector<double>;
	char tmp[20];
	char tmpstr[20]="";

	ifstream* dateiobjekt = new ifstream("testdata/horizon.data");

	while (dateiobjekt->getline(tmp, 20)) {
		for (int i = 0; i<=20; i++) {
			if ( !isdigit(tmp[i]) ) {
				strncat(tmpstr, tmp, i);
				break;
			}
		}
		inhalt->push_back(atoi(tmpstr));

		strcpy(tmpstr, "");
	}

	dateiobjekt->close();
	delete dateiobjekt;

	int gop_groesse = 12;
	int gop_anz = (int) ceil((double) inhalt->size()/ (double) gop_groesse);

	rvector gop(0, gop_anz-1);
	double sigma = 0;

	for (int gops = 0; gops < gop_anz; gops++) {
		unsigned int vergl;
		for (int i = 0; i < gop_groesse; i++) {
			sigma += (*inhalt)[(gops*gop_groesse+i)];
			vergl = gops*gop_groesse+i;
			if (vergl >= inhalt->size()-1) {
				break;
			}
		}
		gop[gops] = sigma;

		sigma=0;
	}

	Trace* _trace = new Trace(gop);

	ComputationParameters paramModel;
	paramModel.setInt(AutoSMPModeler::PARAM_NUMDSTEPS, 10);
	paramModel.setInt(AutoSMPModeler::PARAM_NUMSTATES, 10);
	paramModel.setInt(AutoSMPModeler::PARAM_CONFNIVEAU, 1);

	AutoSMPModeler model(_trace, paramModel);
	SSMProcess* smp = model.compute();
	cout << mid(smp->getTransitionMatrix()) <<endl;
}

void test_Toeplitz() {
	rvector t(-1, 1);
	//t[-2] = 5.0;
	t[-1] = 4.0;
	t[0] = 3.0;
	t[1] = 2.0;
	//t[2] = 1.0;

	rvector y(1, 2);
	y[1] = 1.0;
	y[2] = 2.0;
	//y[3] = 3.0;

	cout << RMatrixUtils::solveToeplitz(t, y) << endl;
}

void test_Prony() {
	rmatrix trans(1, 3, 1, 3);
	trans[1][1] = 0.2;
	trans[1][2] = 0.6;
	trans[1][3] = 0.2;
	trans[2][1] = 0.6;
	trans[2][2] = 0.3;
	trans[2][3] = 0.1;
	trans[3][1] = 0.4;
	trans[3][2] = 0.3;
	trans[3][3] = 0.3;

	rmatrix arrival(1, 3, 0, 50);

	// state 1
	arrival[1][0] = 0.01;
	for (int k=1; k<=49; ++k)
		arrival[1][k] = 0.02;
	arrival[1][50] = 0.01;

	// state 2
	arrival[2][0] = 0.02;
	for (int k=1; k<=24; ++k)
		arrival[2][k] = 0.04;
	arrival[2][25]=0.02;
	for (int k=26; k<=50; ++k)
		arrival[2][k] = 0.0;

	// state 3
	arrival[3][0] = 0.02;
	for (int k=1; k<=25; ++k)
		arrival[3][k] = 0.0;
	for (int k=26; k<=49; ++k)
		arrival[3][k] = 0.04;
	arrival[3][50] = 0.02;

	SetLb(trans, 1, 0);
	SetLb(trans, 2, 0);
	SetLb(arrival, 1, 0);

	SSMProcess smp((imatrix)(trans), (imatrix)(arrival));

	rvector a(smp.getAutocorrelation(6));

	//for(int i = Lb(a); i<=Ub(a); ++i)
	//	a[i] = i+1;
	cout << Lb(a) << ".." << Ub(a) << endl << a << endl;

	PronyMethod p(&smp);
	p.setN(6);
	cout << p.compute() << endl;
	/*
	 for(int i = 1; i<= 6; ++i)
	 cout << p.computeAutocorrelation(i) << endl;
	 */
	cout << "done." << endl;
}

void test_PM() {
	std::vector<double>* inhalt = new std::vector<double>;
	char tmp[20];
	char tmpstr[20]="";

	ifstream* dateiobjekt = new ifstream("/home/kempken/workspace/InterVerdiKom/testdata/horizon.data");

	while (dateiobjekt->getline(tmp, 20)) {
		for (int i = 0; i<=20; i++) {
			if ( !isdigit(tmp[i]) ) {
				strncat(tmpstr, tmp, i);
				break;
			}
		}
		inhalt->push_back(atoi(tmpstr));

		strcpy(tmpstr, "");
	}

	dateiobjekt->close();
	delete dateiobjekt;

	int gop_groesse = 12;
	int gop_anz = (int) ceil((double) inhalt->size()/ (double) gop_groesse);

	rvector gop(0, gop_anz-1);
	double sigma = 0;

	for (int gops = 0; gops < gop_anz; gops++) {
		unsigned int vergl;
		for (int i = 0; i < gop_groesse; i++) {
			sigma += (*inhalt)[(gops*gop_groesse+i)];
			vergl = gops*gop_groesse+i;
			if (vergl >= inhalt->size()-1) {
				break;
			}
		}
		gop[gops] = sigma;

		sigma=0;
	}

	Trace* _trace = new Trace(gop);

	ComputationParameters paramModel;
	paramModel.setInt(AutoSMPModeler::PARAM_NUMDSTEPS, 10);
	paramModel.setInt(AutoSMPModeler::PARAM_NUMSTATES, 5);

	SimpleMCModeler model(_trace, paramModel);
	SSMProcess* smp = model.compute();
	cout << smp->getTransitionMatrix();
	cout << smp->getAutocorrelation(10);

	//~ PronyMethod* p = new PronyMethod(&smp);
	//~ p->setN(5);
	//~ cout << p->compute();


	//~ rmatrix a(0,2,0,2);
	//~ a[0][0] = 1;
	//~ a[0][1] = 2;
	//~ a[0][2] = 3;
	//~ a[1][0] = 1;
	//~ a[1][1] = 1;
	//~ a[1][2] = 1;
	//~ a[2][0] = 3;
	//~ a[2][1] = 3;
	//~ a[2][2] = 1;

	//~ 1.1500000000000000E+002
	//~ 4.0570621306209548e-01

	//~ string x = "./blah";

	//~ SMPQueue q(SMPQueue::constructTimeSlottedQueue(&smp,&smp));
	//~ cout << q.getTransitionMatrix() << endl;
	//~ MatlabExport::writeToFile(q,x);

	//~ cout << RMatrixUtils::exportMatlab(a) << endl;


	//~ cout << RMatrixUtils::eigLR(a,0.00000001);

}

void test_Vandermonde() {
	rvector alpha(0, 2);
	alpha[0] = 1.0;
	alpha[1] = 2.0;
	alpha[2] = 3.0;
	cout << RMatrixUtils::invertVandermonde(alpha) << endl;
}

