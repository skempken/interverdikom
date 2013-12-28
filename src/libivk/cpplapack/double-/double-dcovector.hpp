//=============================================================================
/*! double*dcovector operator */
inline _dcovector operator*(const double& d, const dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dcovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.Array[i] =d*vec.Array[i]; }
  return _(newvec);
}
