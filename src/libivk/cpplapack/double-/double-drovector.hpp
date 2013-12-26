//=============================================================================
/*! double*drovector operator */
inline _drovector operator*(const double& d, const drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  drovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.Array[i] =d*vec.Array[i]; }  
  return _(newvec);
}
