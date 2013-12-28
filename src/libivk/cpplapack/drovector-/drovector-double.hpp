//=============================================================================
/*! drovector*=double operator */
inline drovector& drovector::operator*=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::operator*=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(L, d, Array, 1);
  return *this;
}

//=============================================================================
/*! drovector/=double operator */
inline drovector& drovector::operator/=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::operator/=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(L, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! drovector*double operator */
inline _drovector operator*(const drovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const drovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  drovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.array[i] =vec.Array[i]*d; }
  
  return _(newvec);
}

//=============================================================================
/*! drovector/double operator */
inline _drovector operator/(const drovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const drovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double inv_d(1./d);
  
  drovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.array[i] =vec.Array[i]*inv_d; }
  
  return _(newvec);
}
