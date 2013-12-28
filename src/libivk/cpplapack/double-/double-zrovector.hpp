//=============================================================================
/*! double*zrovector operator */
inline _zrovector operator*(const double& d, const zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zrovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.Array[i] =d*vec.Array[i]; }  
  return _(newvec);
}
