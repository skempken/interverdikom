//=============================================================================
/*! +zrovector operator */
inline const zrovector& operator+(const zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return vec;
}

//=============================================================================
/*! -zrovector operator */
inline _zrovector operator-(const zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zrovector newvec(vec.L);
  for(long i=0; i<newvec.l; i++){ newvec.array[i]=-vec.Array[i]; }
  
  return _(newvec);
}
