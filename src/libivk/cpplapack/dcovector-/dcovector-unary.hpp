//=============================================================================
/*! +dcovector operator */
inline const dcovector& operator+(const dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return vec;
}

//=============================================================================
/*! -dcovector operator */
inline _dcovector operator-(const dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dcovector newvec(vec.L);
  for(long i=0; i<newvec.L; i++){ newvec.Array[i]=-vec.Array[i]; }
  
  return _(newvec);
}
