/* Copyright (c) 2009-2013, UT-Battelle, LLC
All rights reserved

[PsimagLite, Version 1.0.0]

*********************************************************
THE SOFTWARE IS SUPPLIED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED.

Please see full open source license included in file LICENSE.
*********************************************************

*/
#include "NewConcurrency.h"
#include <iostream>
#include <cstdlib>
#include "Parallelizer.h"

template<typename MutexType>
class MyHelper {

public:

	typedef double RealType;

	void thread_function_(SizeType threadNum,
	                      SizeType blockSize,
	                      SizeType total,
	                      MutexType* myMutex)
	{
		for (SizeType p=0;p<blockSize;p++) {
			SizeType taskNumber = threadNum*blockSize + p;
			if (taskNumber>=total) break;
			std::cout<<"This is thread number "<<threadNum;
			std::cout<<" and taskNumber="<<taskNumber<<"\n";
		}
	}

}; // class MyHelper


int main(int argc,char *argv[])
{
	typedef PsimagLite::Concurrency<double> ConcurrencyType;

	
	if (argc!=3) {
		std::cout<<"USAGE: "<<argv[0]<<" nthreads ntasks\n";
		return 1;
	}

	SizeType nthreads  = atoi(argv[1]);
	SizeType ntasks = atoi(argv[2]);

	std::cout<<"Using "<<nthreads<<" threads.\n";

	ConcurrencyType concurrency(argc,argv);

	typedef MyHelper<ConcurrencyType::MutexType> HelperType;
	typedef PsimagLite::Parallelizer<ConcurrencyType,HelperType> ParallelizerType;
	ParallelizerType threadObject;

	ParallelizerType::setThreads(nthreads);

	HelperType helper;

	threadObject.loopCreate(ntasks,helper);

}
