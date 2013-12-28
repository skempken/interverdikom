//=============================================================================
/*! +zcovector operator */
inline const zcovector& operator+(const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return vec;
}

//=============================================================================
/*! -zcovector operator */
inline _zcovector operator-(const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zcovector newvec(vec.L);
  for(long i=0; i<newvec.L; i++){ newvec.array[i]=-vec.Array[i]; }
  
  return _(newvec);
}
