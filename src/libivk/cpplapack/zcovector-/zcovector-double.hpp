//=============================================================================
/*! zcovector*=double operator */
inline zcovector& zcovector::operator*=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::operator*=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(L, d, Array, 1);
  return *this;
}

//=============================================================================
/*! zcovector/=double operator */
inline zcovector& zcovector::operator/=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::operator/=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(L, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zcovector*double operator */
inline _zcovector operator*(const zcovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zcovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zcovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.array[i] =vec.Array[i]*d; }
  
  return _(newvec);
}

//=============================================================================
/*! zcovector/double operator */
inline _zcovector operator/(const zcovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const zcovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double inv_d(1./d);
  zcovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.array[i] =vec.Array[i]*inv_d; }
  
  return _(newvec);
}
