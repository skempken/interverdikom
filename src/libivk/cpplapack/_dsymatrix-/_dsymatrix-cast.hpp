//============================================================================
/*! cast operator to _zhematrix */
inline _dsymatrix::operator _zhematrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dsymatrix::operator _zhematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  complete();
  zhematrix newmat(N);
  for(long i=0; i<N*N; i++){
    newmat.array[i] =std::complex<double>(Array[i],0.0);
  }
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dsymatrix::operator _zhematrix() "
            << "A new casted matrix at " << newmat.array 
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
  
  destroy();
  return _(newmat);
}
