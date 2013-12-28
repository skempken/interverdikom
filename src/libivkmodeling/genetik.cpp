#include "genetik.hpp"

namespace IvkModeling{
	Genetik::Genetik(char* dateiname,int gopGr,int zustaende,int autok,int iterationen,int poolGr){
		this->datenPerVector = false;
		this->setDateiname(dateiname);
		this->setGopGr(gopGr);
		this->setZustaende(zustaende);
		this->setAutok(autok);
		this->setIter(iterationen);
		this->setPoolGr(poolGr);
		this->klemmbrett = new rvector(0,poolGr-1);
		this->emp = new SSMP(dateiname);
		this->empirische_Daten_erzeugen(gopGr,zustaende,autok);
		this->pool_initialisieren(this->emp->datenreihe->gop_anz,this->emp->get_umatrix(),poolGr);
	}

	Genetik::Genetik(vector<double>* daten,int gopGr,int zustaende,int autok,int iterationen,int poolGr){
		this->datenPerVector = true;
		this->setGopGr(gopGr);
		this->setZustaende(zustaende);
		this->setAutok(autok);
		this->setIter(iterationen);
		this->setPoolGr(poolGr);
		this->klemmbrett = new rvector(0,poolGr-1);
		this->emp = new SSMP(daten);
		this->empirische_Daten_erzeugen(gopGr,zustaende,autok);
		this->pool_initialisieren(this->emp->datenreihe->gop_anz,this->emp->get_umatrix(),poolGr);
	}
	
	Genetik::~Genetik(){
		delete this->emp;
	}

	char* Genetik::getDateiname(){ 		return this->dateiname; }
	int Genetik::getGopGr(){ 				return this->gopGr; }	
	int Genetik::getZustaende(){ 			return this->zustaende; }
	int Genetik::getAutok(){				return this->autok; }
	int Genetik::getIter(){					return this->iterationen; }
	int Genetik::getPoolGr(){				return this->poolGr; }
	int Genetik::getBester(){				return this->bester;}
	double Genetik::getMin(){				return this->emp->datenreihe->min; }
	double Genetik::getMax(){				return this->emp->datenreihe->max; }
	double* Genetik::getGop(){				return this->emp->datenreihe->gop; }
	rmatrix Genetik::getPool(){			return *this->pool; }
	rmatrix Genetik::getBesteUmatrix(){
		rmatrix* um_ = new rmatrix(this->emp->umatrix_erstellen(*this->pool,this->bester,this->emp->get_Zustaende()));
		cout << *um_ << endl;
		Hilfsklasse::testeMatrix(*um_);
		cout << *um_ << endl;
		this->setZustaende((Ub(*um_,ROW)-Lb(*um_,ROW))+1);		
		return *um_;
	}

	void Genetik::setDateiname(char* dateiname){ this->dateiname = dateiname; }
	void Genetik::setGopGr(int gopGr){ 				this->gopGr = gopGr; }
	void Genetik::setZustaende(int zustaende){ 	this->zustaende = zustaende; }
	void Genetik::setAutok(int autok){				this->autok = autok; }
	void Genetik::setIter(int iterationen){		this->iterationen = iterationen; }
	void Genetik::setPoolGr(int poolGr){			this->poolGr = poolGr; }

	void Genetik::empirische_Daten_erzeugen(int gopGr,int zustaende,int autok){
		if(this->datenPerVector != true){ this->emp->datenreihe->frames_zu_gop(gopGr); }
		this->emp->gop_groesse = gopGr;
		this->emp->zustaende_berechnen(zustaende);
		this->emp->zmittelwerte();
		this->emp->umatrix_erstellen();
		this->emp->stat_wahrsch_rechnen();
		this->eak = new rvector(0,autok-1);
		*this->eak = emp->autokorrelation_em(autok);
	}

	void Genetik::pool_initialisieren(int n,rmatrix umatrix,int poolgroesse){
		this->pool = new rmatrix(0,n-1,0,poolgroesse-1);
		for(int i = 0;i < poolgroesse;i++){
			rvector* tv = Hilfsklasse::zustandsfolge(n,umatrix);
			(*this->pool)[cxsc::Col(i)] = *tv;
			delete tv;
		}
		this->zmittelwerte = new rmatrix(0,this->emp->get_Zustaende()-1,0,poolgroesse-1);
		Hilfsklasse::zero(*zmittelwerte);
		this->mittelwerte_vorbereiten();
	}

	void Genetik::mittelwerte_vorbereiten(){
		rmatrix vert(0,this->emp->get_Zustaende()-1,0,Ub(*this->pool,COL));
		Hilfsklasse::zero(vert);
		Hilfsklasse::zero(*this->zmittelwerte);
		
		for(int n = Lb(*this->pool,COL);n <= Ub(*this->pool,COL);n++){ //n => x Werte der Matrix => spezifische Folge
			for(int i = Lb(*this->pool,ROW);i <= Ub(*this->pool,ROW);i++){ //i => y Werte der Matrix => Elemente der Folge
				vert[(int) cxsc::_double((*this->pool)[i][n])][n] += 1; 
			}
		}
		for(int n = 0;n <= Ub(*this->pool,COL);n++){
			for(int i=0;i < emp->datenreihe->gop_anz;i++){
				(*this->zmittelwerte)[(int) cxsc::_double((*this->pool)[i][n])][n] += emp->datenreihe->gop[i];
			}
		}
		for(int n = 0;n <= Ub(*this->zmittelwerte,COL);n++){
			for(int i=0;i <= Ub(*this->zmittelwerte,ROW);i++){
				if(vert[i][n] != 0){ (*this->zmittelwerte)[i][n] = (*this->zmittelwerte)[i][n] / vert[i][n]; }
			}
		}
	}

	int Genetik::fitness(){
		this->mittelwerte_vorbereiten();
		Hilfsklasse::zero(*this->klemmbrett);
		int fittest = 0;
		for(int n = 0;n <= Ub(*this->pool,COL);n++){
			rmatrix* um_ = new rmatrix(this->emp->umatrix_erstellen(*this->pool,n,this->emp->get_Zustaende()));
			rvector* sw_ = new rvector(this->emp->stat_wahrsch_rechnen(*um_));
			rvector* a = new rvector(this->emp->autokorrelation_um(this->autok,*this->zmittelwerte,*um_,*sw_,n));
			(*this->klemmbrett)[n] = Hilfsklasse::fitness(*this->eak,*a);
			if((*this->klemmbrett)[fittest] < (*this->klemmbrett)[n]){
				fittest = n;
			}
			delete um_;
			delete sw_;
		}
		return fittest;
	}

	int Genetik::mutier(int fittest){
		this->mutator = new Mutator(this->emp->get_Zustaende(),*this->pool);
		for(int i = 0;i <= Ub(*this->pool,COL);i++){
			if(i != fittest){ this->mutator->mutier(*this->pool,i); }
		}
		return fittest;
	}

	int Genetik::evolutionStarten(){
		this->bester = this->fitness();
		int toGo = this->iterationen;
		double went = 0;
		double avg = 0;
		timeval start,ende;
		setProgressText("Evolution...");
		setProgressMax(this->iterationen);
		for(int i = 0;i < this->iterationen;i++){
			gettimeofday(&start,0);
			this->mittelwerte_vorbereiten();
			int x = this->mutier(this->fitness());
			if(this->bester != x) {
				cout <<endl<< "neuen besten gefunden"<<endl;
				i = 0;
				toGo = this->iterationen;
				setProgressMax((int)(went+toGo));
				this->bester = x;
			}
			gettimeofday(&ende,0);
			setProgressValue((int)went);
			avg += (double)ende.tv_sec-(double)start.tv_sec;
			went++;
			toGo--;
		}
		int vert[5] = {0,0,0,0,0};
		for(int i = 0;i <= Ub(*this->mutator->mut_stat,ROW);i++){
			vert[0] += (int) cxsc::_double((*this->mutator->mut_stat)[i][0]);
			vert[1] += (int) cxsc::_double((*this->mutator->mut_stat)[i][1]);
			vert[2] += (int) cxsc::_double((*this->mutator->mut_stat)[i][2]);
			vert[3] += (int) cxsc::_double((*this->mutator->mut_stat)[i][3]);
			vert[4] += (int) cxsc::_double((*this->mutator->mut_stat)[i][4]);
		}
		return this->bester;
	}
}
