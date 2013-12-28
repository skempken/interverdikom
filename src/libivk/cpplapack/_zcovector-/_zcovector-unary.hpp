//=============================================================================
/*! +_zcovector operator */
inline const _zcovector& operator+(const _zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return vec;
}

//=============================================================================
/*! -_zcovector operator */
inline _zcovector operator-(const _zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<vec.L; i++){ vec.Array[i]=-vec.Array[i]; }
  return vec;
}
