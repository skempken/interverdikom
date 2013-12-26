#ifndef AUTOSMPMODELER_H_
#define AUTOSMPMODELER_H_

#include "data/Trace.h"
#include "data/SSMProcess.h"
#include "utility/StatUtils.h"
#include "computation/SimpleMCModeler.h"

namespace ivk{
	/**\class AutoSMPModeler
	\brief AutoSMPModeler is used to contract multiple states to one*/
	class AutoSMPModeler : public SimpleMCModeler{
		public:	
			/*Parameter to set the confidence niveau*/
			static const char * PARAM_CONFNIVEAU;
			
			/**Contructor to create an instance of the AutoSMPModeler-class
			\param data is the SSMProcess in which multiple states should be contracted
			\param parameters contains the confidence niveau */
			AutoSMPModeler(const Trace* data, const ComputationParameters &parameters);
			virtual ~AutoSMPModeler();
			
			/**Method to set the set of parameters*/
			virtual void setParameters(const ComputationParameters &parameters);
			
			void setConfNiveau(const int value);
			int getConfNiveau() const;		
			
			/**Method to contract multiple states to one 
			\return The SSMProcess with m-n states where m is the base number of states and n the number of states that were contracted*/
			SSMProcess* compute();
			
		private:
			intvector indexSequence;
			int confNiveau;
			SSMProcess* computeModel(int n_states);
	};
}

#endif /*AUTOSMPMODELER_H_*/
