//=============================================================================
/*! +_dcovector operator */
inline const _dcovector& operator+(const _dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return vec;
}

//=============================================================================
/*! -_dcovector operator */
inline _dcovector operator-(const _dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<vec.L; i++){ vec.Array[i]=-vec.Array[i]; }
  
  return vec;
}
