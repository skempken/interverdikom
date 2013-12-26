//=============================================================================
/*! +_zrovector operator */
inline const _zrovector& operator+(const _zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return vec;
}

//=============================================================================
/*! -_zrovector operator */
inline _zrovector operator-(const _zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<vec.L; i++){ vec.Array[i]=-vec.Array[i]; }
  return vec;
}
