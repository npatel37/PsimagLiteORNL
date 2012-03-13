/*
Copyright (c) 2012, UT-Battelle, LLC
All rights reserved

[PsimagLite, Version 1.0.0]
[by G.A., Oak Ridge National Laboratory]

UT Battelle Open Source Software License 11242008

OPEN SOURCE LICENSE

Subject to the conditions of this License, each
contributor to this software hereby grants, free of
charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), a
perpetual, worldwide, non-exclusive, no-charge,
royalty-free, irrevocable copyright license to use, copy,
modify, merge, publish, distribute, and/or sublicense
copies of the Software.

1. Redistributions of Software must retain the above
copyright and license notices, this list of conditions,
and the following disclaimer.  Changes or modifications
to, or derivative works of, the Software should be noted
with comments and the contributor and organization's
name.

2. Neither the names of UT-Battelle, LLC or the
Department of Energy nor the names of the Software
contributors may be used to endorse or promote products
derived from this software without specific prior written
permission of UT-Battelle.

3. The software and the end-user documentation included
with the redistribution, with or without modification,
must include the following acknowledgment:

"This product includes software produced by UT-Battelle,
LLC under Contract No. DE-AC05-00OR22725  with the
Department of Energy."

*********************************************************
DISCLAIMER

THE SOFTWARE IS SUPPLIED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT OWNER, CONTRIBUTORS, UNITED STATES GOVERNMENT,
OR THE UNITED STATES DEPARTMENT OF ENERGY BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
DAMAGE.

NEITHER THE UNITED STATES GOVERNMENT, NOR THE UNITED
STATES DEPARTMENT OF ENERGY, NOR THE COPYRIGHT OWNER, NOR
ANY OF THEIR EMPLOYEES, REPRESENTS THAT THE USE OF ANY
INFORMATION, DATA, APPARATUS, PRODUCT, OR PROCESS
DISCLOSED WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*********************************************************


*/
// END LICENSE BLOCK
/** \ingroup PsimagLite */
/*@{*/

/*! \file RungeKutta.h
 *
 * contributed by K.A.A
 *
 * DOC HERE FIXME
 *
 */
#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H

#include <cassert>
#include "Complex.h"

namespace PsimagLite {

template<typename RealType,
         typename FunctionType,
	 typename ArrayType = Vector<RealType> >
class RungeKutta {
public:
	RungeKutta(const FunctionType& f, const RealType& h)
	: f_(f),h_(h)
	{ }

	void solve(RealType t0, RealType t, const ArrayType& y0)
	{
		size_t N = static_cast<size_t> (std::real((t - t0)/h_));
		ArrayType k1(y0), k2(y0), k3(y0), k4(y0);
		RealType w1 = 1, w2 = 2, w3 = 2, w4 = 1, wtotInverse = 1.0/6.0;

		RealType ti = t0;
		ArrayType yi = y0;
		std::cout << std::real(ti) << " " << std::real(yi(0,0)) << " ";
		std::cout << std::real(yi(1,1)) << " " << std::real(yi(2,2))<< '\n';
		for(size_t i = 0; i < N; i++) {
			k1 = h_ * f_(ti, yi);
			k2 = h_ * f_(ti + h_*0.5, yi + k1*0.5);
			k3 = h_ * f_(ti + h_*0.5, yi + k2*0.5);
			k4 = h_ * f_(ti + h_, yi + k3);

			std::cout << std::real(ti) << " ";
			for (size_t j=0;j<yi.n_row();j++) std::cout<< std::real(yi(j,j)) << " ";
			std::cout << '\n';
			ti += h_;
			yi += (w1*k1 + w2*k2 + w3*k3 + w4*k4) * wtotInverse;

		}
	}

private:
	FunctionType f_;
	RealType h_;
}; // class RungeKutta

} // namespace Dmrg

/*@}*/
#endif // RUNGE_KUTTA


