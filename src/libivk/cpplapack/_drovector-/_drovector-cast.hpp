//============================================================================
/*! cast operator to _zrovector */
inline _drovector::operator _zrovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _drovector::operator _zrovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zrovector newvec(L);
  for(long i=0; i<L; i++){
    newvec.array[i] =std::complex<double>(Array[i],0.0);
  }
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _drovector::operator _zrovector() "
            << "A new casted matrix at " << newvec.array 
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
  
  destroy();
  return _(newvec);
}
