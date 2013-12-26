//=============================================================================
/*! double*zcovector operator */
inline _zcovector operator*(const double& d, const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zcovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.Array[i] =d*vec.Array[i]; }
  return _(newvec);
}
