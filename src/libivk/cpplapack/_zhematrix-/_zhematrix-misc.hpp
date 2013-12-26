//=============================================================================
/*! destroy all the matrix data */
inline void _zhematrix::destroy() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zhematrix::destroy() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zhematrix::destroy() "
            << " An array at " << Array
            << " is going to be destroyed." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
  delete [] Darray;
}

//=============================================================================
/*! complete the upper-right components */
inline void _zhematrix::complete() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zhematrix::complete() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<N; i++){
    for(long j=0; j<i; j++){
      Darray[i][j] =std::conj(Darray[j][i]);
    }
    
#ifdef  CPPL_DEBUG
    if(std::fabs(std::imag(operator()(i,i))) > CPPL_EPS){
      std::cerr << "[WARNING] _zhematrix::complete() const" << std::endl
                << "The " << i << "th diagonal component of the _zhematrix"
                << "is not a real number." << std::endl;
    }
#endif//CPPL_DEBUG
  }
}

