//=============================================================================
/*! destroy all the matrix data */
inline void _dsymatrix::destroy() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dsymatrix::destroy() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dsymatrix::destroy() "
            << " An array at " << Array
            << " is going to be destroyed." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
  delete [] Darray;
}

//=============================================================================
/*! complete the upper-right components */
inline void _dsymatrix::complete() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dsymatrix::complete() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
    for(long i=0; i<N; i++){
    for(long j=0; j<i; j++){
      Darray[i][j] =Darray[j][i];
    }
  }
}

