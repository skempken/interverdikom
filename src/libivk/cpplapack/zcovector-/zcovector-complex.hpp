//=============================================================================
/*! zcovector*=std::complex<double> operator */
inline zcovector& zcovector::operator*=(const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::operator*=(const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(L, d, Array, 1);
  return *this;
}

//=============================================================================
/*! zcovector/=std::complex<double> operator */
inline zcovector& zcovector::operator/=(const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::operator/=(const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(L, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zcovector*std::complex<double> operator */
inline _zcovector operator*(const zcovector& vec, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zcovector&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zcovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.array[i] =vec.Array[i]*d; }
  
  return _(newvec);
}

//=============================================================================
/*! zcovector/std::complex<double> operator */
inline _zcovector operator/(const zcovector& vec, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const zcovector&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::complex<double> inv_d(1./d);
  
  zcovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.array[i] =vec.Array[i]*inv_d; }
  
  return _(newvec);
}
