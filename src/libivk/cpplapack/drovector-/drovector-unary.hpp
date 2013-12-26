//=============================================================================
/*! +drovector operator */
inline const drovector& operator+(const drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return vec;
}

//=============================================================================
/*! -drovector operator */
inline _drovector operator-(const drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  drovector newvec(vec.L);
  for(long i=0; i<newvec.L; i++){ newvec.array[i]=-vec.Array[i]; }
  
  return _(newvec);
}
