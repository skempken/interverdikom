#ifndef ROOTFINDER_H_
#define ROOTFINDER_H_

// Interne Includes
#include "bibl0.hpp"            // Grundfunktionen
#include "vmblock.hpp"          // fuer den Root-Finder; Mueller, Bauhuber
#include "basis.hpp"            // fuer den Root-Finder; Mueller, Bauhuber
#include "u_proto.hpp"          // fuer den Root-Finder; Mueller, Bauhuber

// C-XSC Includes
#include <cvector.hpp>
#include "utility/Polynomial.hpp"

namespace ivk
{

class RootFinder
{
public:
	static cvector rootsMueller(const RPolynomial &poly);
	static cvector rootsBauhuber(const RPolynomial &poly);
	static cvector rootsLapack(const RPolynomial &poly);
	static cvector rootsSphere(const RPolynomial &poly, const int number);
	static RPolynomial deflatePolynomial(const RPolynomial &poly);
	static RPolynomial splitOffRootAt1(const RPolynomial &poly);
};

}

#endif /*ROOTFINDER_H_*/
