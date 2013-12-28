//============================================================================
/*! cast operator to _zgematrix */
inline _dgematrix::operator _zgematrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dgematrix::operator _zgematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(M,N);
  for(long i=0; i<M*N; i++){
    newmat.array[i] =std::complex<double>(Array[i],0.0);
  }
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dgematrix::operator _zgematrix() "
            << "A new casted matrix at " << newmat.array 
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
  
  destroy();
  return _(newmat);
}
