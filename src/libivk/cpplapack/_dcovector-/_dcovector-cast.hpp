//============================================================================
/*! cast operator to _zcovector */
inline _dcovector::operator _zcovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dcovector::operator _zcovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zcovector newvec(L);
  for(long i=0; i<L; i++){
    newvec.array[i] =std::complex<double>(Array[i],0.0);
  }
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dcovector::operator _zcovector() "
            << "A new casted matrix at " << newvec.array 
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
  
  destroy();
  return _(newvec);
}
