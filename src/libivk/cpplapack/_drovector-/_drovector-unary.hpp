//=============================================================================
/*! +_drovector operator */
inline const _drovector& operator+(const _drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return vec;
}

//=============================================================================
/*! -_drovector operator */
inline _drovector operator-(const _drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<vec.L; i++){ vec.Array[i]=-vec.Array[i]; }
  return vec;
}
