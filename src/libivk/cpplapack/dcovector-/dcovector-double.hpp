//=============================================================================
/*! dcovector*=double operator */
inline dcovector& dcovector::operator*=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::operator*=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(L, d, Array, 1);
  return *this;
}

//=============================================================================
/*! dcovector/=double operator */
inline dcovector& dcovector::operator/=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::operator/=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(L, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dcovector*double operator */
inline _dcovector operator*(const dcovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dcovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dcovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.Array[i] =vec.Array[i]*d; }
  
  return _(newvec);
}

//=============================================================================
/*! dcovector/double operator */
inline _dcovector operator/(const dcovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const dcovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double inv_d(1./d);
  
  dcovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.Array[i] =vec.Array[i]*inv_d; }
  
  return _(newvec);
}
