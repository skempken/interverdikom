//============================================================================
/*! cast operator to _zgbmatrix */
inline _dgbmatrix::operator _zgbmatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dgbmatrix::operator _zgbmatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgbmatrix newmat(M,N,KL,KU);
  for(long i=0; i<(KL+KU+1)*N; i++){
    newmat.array[i] =std::complex<double>(Array[i],0.0);
  }
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dgbmatrix::operator _zgbmatrix() "
            << "A new casted matrix at " << newmat.array 
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
  
  destroy();
  return _(newmat);
}
