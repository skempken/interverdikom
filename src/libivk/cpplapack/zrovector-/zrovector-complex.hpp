//=============================================================================
/*! zrovector*=std::complex<double> operator */
inline zrovector& zrovector::operator*=(const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::operator*=(const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(L, d, Array, 1);
  return *this;
}

//=============================================================================
/*! zrovector/=std::complex<double> operator */
inline zrovector& zrovector::operator/=(const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::operator/=(const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(L, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zrovector*std::complex<double> operator */
inline _zrovector operator*(const zrovector& vec, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zrovector&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zrovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.array[i] =vec.Array[i]*d; }
  
  return _(newvec);
}

//=============================================================================
/*! zrovector/std::complex<double> operator */
inline _zrovector operator/(const zrovector& vec, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const zrovector&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::complex<double> inv_d(1./d);
  zrovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.array[i] =vec.Array[i]*inv_d; }
  
  return _(newvec);
}
