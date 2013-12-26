//============================================================================
/*! cast operator to _zhematrix */
inline dsymatrix::operator _zhematrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::operator _zhematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  complete();
  zhematrix newmat(N);
  for(long i=0; i<N*N; i++){
    newmat.array[i] =std::complex<double>(array[i],0.0);
  }
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dsymatrix::operator _zhematrix() "
            << "A new casted matrix at " << newmat.array 
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
  
  return _(newmat);
}
